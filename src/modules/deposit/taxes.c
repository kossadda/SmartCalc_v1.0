/**
 * @file taxes.c
 * @author kossadda (https://github.com/kossadda)
 * @brief The module contains all functionality for calculating taxes
 * @version 1.0
 * @date 2024-01-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./../include/deposit.h"

static int write_taxes(deposit_init *data, investment *pay,
                       long double *year_profit,
                       long double non_taxable_amount);

/*!
 * @brief Checks the current period for transition between years.
 *
 * @param[out] data structure containing input parameters for calculation.
 * @param[out] pay structure containing buffer variables for monthly results and
 * general payment data arrays.
 * @param[in] end structure containing information about the end of the current
 * period.
 * @param[in] last structure containing information about the last deposit day.
 * @param[out] year_profit amount accumulated during the year.
 * @param[in] non_taxable_amount tax free amount.
 * @param[in] begin_year the year from which the current period began.
 *
 * @return int - error code.
 * @retval ALLOCATED = 0 - if memory is allocated.
 * @retval NOT_ALLOCATED = 1 - if memory isn't allocated.
 */
int check_taxes(deposit_init *data, investment *pay, time_data end,
                time_data last, long double *year_profit,
                long double non_taxable_amount, int begin_year) {
  int code = ALLOCATED;

  if (begin_year != end.year && data->capital_time != BY_END_TERM) {
    data->date.year = begin_year;
    code = write_taxes(data, pay, year_profit, non_taxable_amount);
  }
  if (compare_dates(end, last) == DATE_EQUAL) {
    data->date.year = end.year;
    *year_profit += pay->profit;
    code = write_taxes(data, pay, year_profit, non_taxable_amount);
  }

  *year_profit += pay->profit;

  return code;
}

/*!
 * @brief A function that records taxation in an array.
 *
 * @param[out] data structure containing input parameters for calculation.
 * @param[out] pay structure containing buffer variables for monthly results and
 * general payment data arrays.
 * @param[out] year_profit amount accumulated during the year.
 * @param[in] non_taxable_amount tax free amount.
 *
 * @return int - error code.
 * @retval ALLOCATED = 0 - if memory is allocated.
 * @retval NOT_ALLOCATED = 1 - if memory isn't allocated.
 */
static int write_taxes(deposit_init *data, investment *pay,
                       long double *year_profit,
                       long double non_taxable_amount) {
  int code = ALLOCATED;

  code = allocate_row(&pay->taxes, pay->taxes_count, TAXES_COLUMNS);
  if (code == ALLOCATED) {
    if (*year_profit > non_taxable_amount) {
      long double year_tax =
          round_value((*year_profit - non_taxable_amount) * NDFL_RATE / 100);

      pay->taxes[pay->taxes_count][3] = *year_profit - non_taxable_amount;
      pay->taxes[pay->taxes_count][4] = year_tax;
    }

    pay->taxes[pay->taxes_count][0] = data->date.year;
    pay->taxes[pay->taxes_count][1] = *year_profit;
    pay->taxes[pay->taxes_count][2] = non_taxable_amount;

    *year_profit = 0;
  }

  pay->taxes_count++;

  return code;
}
