#include "s21_tests/s21_test.h"
#include <stdio.h>

void input_initial(initial *data, long double debt, long double months, int type, long double rate, int day, int month, int year) {
    data->debt = debt;
    data->months = months;
    data->payment_type = type;
    data->rate = rate;
    data->date.day = day;
    data->date.month = month;
    data->date.year = year;
}

void input_redemption(another_payments *redemption, int day, int month, int year, long double sum, int type) {
    redemption->date = (time_data *)realloc(redemption->date, (redemption->count + 1) * sizeof(time_data));
    redemption->sum = (long double *)realloc(redemption->sum, (redemption->count + 1) * sizeof(long double));
    redemption->type = (int *)realloc(redemption->type, (redemption->count + 1) * sizeof(int));
    redemption->date[redemption->count].day = day;
    redemption->date[redemption->count].month = month;
    redemption->date[redemption->count].year = year;
    redemption->sum[redemption->count] = sum;
    redemption->type[redemption->count] = type;
    redemption->count++; 
}

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

void free_memory(int row, payments *pay, another_payments *redemption) {
    if(pay) {
        int redemp_rows = 0;
        if(redemption) {
            redemp_rows = 1;
        }
        for(int i = 0; i < row + redemp_rows; i++) {
            free(pay->result[i]);
            pay->result[i] = NULL;
        }
        free(pay->result);
        free(pay->total);
        pay->result = NULL;
        pay->total = NULL;
    }
    if(redemption) {
        free(redemption->date);
        free(redemption->sum);
        free(redemption->type);
        redemption->date = NULL;
        redemption->sum = NULL;
        redemption->type = NULL;
    }
}

int main() {
    initial data;
    payments pay;
    another_payments redemption;
    init_redemption(&redemption);

    input_initial(&data, 333333.33, 25, DIFFERENTIATED, 5, 23, 02, 2022);
    input_redemption(&redemption, 01, 04, 2022, 5232, REDUCE_TERM);
    input_redemption(&redemption, 23, 12, 2022, 25000, REDUCE_PAY);

    calculate_credit(&data, &pay, &redemption);
    long double result_total[3] = {349800.87, 333333.33, 16467.54};

    for(int i = 0; i < 3; i++) {
        printf("  my:%Lf\ntrue:%Lf\n\n", pay.total[i], result_total[i]);
    }
    free_memory(data.current, &pay, &redemption);
}