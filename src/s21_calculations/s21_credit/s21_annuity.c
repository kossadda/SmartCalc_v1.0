#include "s21_credit.h"

/// @brief Function for calculating monthly payments of annuity type
/// @param data Structure containing input parameters for calculation
/// @param pay Structure containing buffer variables for monthly results and general payment data arrays
/// @param next_month Structure containing the payment end date for the current month
void annuity(initial *data, payments *pay, time_data next_month) {
    static long double rest = 0;
    int error_code = ALLOCATED;
    data->current++;
    error_code = allocate_memory(data, pay);
    if(error_code == ALLOCATED) {
        calc_percent(data, pay, next_month);

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
