#include "../main.h"
#include <stdio.h>

int main() {
    // printf("%lf\n", calculation(str));
    // validation(str);
    // printf("%s\n", str);
    char str[500] = "((5*x-2.123)*3.98*(x^2-1))/19.55";
    // str_without_spaces(str);
    // input_varibles(str, -13.123);

    // add_symbol(str, &count, 7, '1', '*', '(', );
    // add_symbol(str, &count, NUMBER, k);
    // printf("%s\n", str);
    // validation_x(str, -13.123);
    // validation(str, -5);
    // printf("%s\n", str);
    printf("\n\n%lf\n\n\n", calculation(str, 1));
}
