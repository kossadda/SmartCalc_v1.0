#include "s21_credit.h"

static int calculate_this_month(initial *data, payments *pay, time_data next_month, long double paid_percent);
static int check_and_calc_redemption(initial *data, payments *pay, another_payments *redemption, time_data *next_month, long double *paid_percent);

/// @brief Calculates monthly payments for an annuity payment type
/// @param data Structure containing input parameters for calculation
/// @param pay Structure containing buffer variables for monthly results and general payment data arrays
/// @param redemption Structure containing data on early repayments
/// @param next_month Structure containing the payment end date for the current month
/// @return Returns the error code. If memory is allocated - ALLOCATED, if not - NOT_ALLOCATED
int annuity(initial *data, payments *pay, another_payments *redemption, time_data next_month)
{
    int error_code = ALLOCATED;
    int const_day = data->date.day;
    double monthly_percent = data->rate / (100.0 * 12.0);
    pay->monthly = round_value(data->debt * monthly_percent / (1 - pow((1.0 + monthly_percent), data->months * (-1))));

    for(data->current = -1; data->debt != 0;) {
        long double paid_percent = 0;
        determine_date(&data->date, &next_month);
        error_code = check_and_calc_redemption(data, pay, redemption, &next_month, &paid_percent);
        error_code = calculate_this_month(data, pay, next_month, paid_percent);
        add_month(&(data->date), const_day);
        add_month(&next_month, const_day);
        data->debt = (error_code == ALLOCATED) ? data->debt : 0;
    }
    return error_code;
}

/// @brief Function for calculating monthly payments of annuity type
/// @param data Structure containing input parameters for calculation
/// @param pay Structure containing buffer variables for monthly results and general payment data arrays
/// @param next_month Structure containing the payment end date for the current month
/// @return Returns the error code. If memory is allocated - ALLOCATED, if not - NOT_ALLOCATED
static int calculate_this_month(initial *data, payments *pay, time_data next_month, long double paid_percent)
{
    int error_code = ALLOCATED;
    static long double rest = 0;
    if(data->debt) {
        data->current++;
        error_code = allocate_memory(data, pay);
        if(error_code == ALLOCATED) {
            calc_percent(data, pay, next_month);
            pay->percent -= paid_percent; // temp

            if(rest) {
                pay->percent += rest;
                rest = 0;
            }
            if(pay->percent > pay->monthly) {
                rest = pay->percent - pay->monthly;
                pay->percent = pay->monthly;
                pay->main = 0;
            } else {
                if(data->debt >= pay->monthly) {
                    pay->main = pay->monthly - pay->percent;
                } else if(data->debt < pay->monthly && data->debt + pay->percent > pay->monthly) {
                    pay->main = pay->monthly - pay->percent;
                } else {
                    pay->main = data->debt;
                    pay->monthly = pay->main + pay->percent;
                }
            }
            data->debt -= pay->main;
            
            remember_result(data, pay);
        }
    }
    return error_code;
}

/// @brief Determines whether the current early repayment is within the current month and calculates it
/// @param data Structure containing input parameters for calculation
/// @param pay Structure containing buffer variables for monthly results and general payment data arrays
/// @param redemption Structure containing data on early repayments
/// @param next_month Structure containing the payment end date for the current month
/// @param paid_percent The amount deducted from the monthly interest in case of early repayment
/// @return Returns the error code. If memory is allocated - ALLOCATED, if not - NOT_ALLOCATED
static int check_and_calc_redemption(initial *data, payments *pay, another_payments *redemption, time_data *next_month, long double *paid_percent)
{
    int error_code = ALLOCATED;
    int change = DEBT_NOT_CHANGED;
    if(redemption && redemption->sum && redemption->current < redemption->count) {
        while(compare_date_with_month(data->date, &(redemption->date[redemption->current]), *next_month)) {
            error_code = redemp_payment(data, pay, next_month, redemption, paid_percent, &change);
            if(redemption->current == redemption->count) {
                break;
            }
        }
    }
    return error_code;
}