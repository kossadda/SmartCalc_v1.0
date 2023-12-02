#include "C_funcs.h"



#define SIN 115
#define COS 99
#define TAN 116
#define ASIN 83
#define ACOS 67
#define ATAN 84
#define SQRT 81
#define LOG 76
#define LN 101
#define OPEN_BRCK 40
#define CLOSE_BRCK 41
#define ADD 43
#define SUB 45
#define MUL 42
#define DIV 47

int main() {
    // char *example = "T(43245.67)/(C(0.432455)-0.0032)";
    // printf("%lf\n", polish(example));
    test();
}

double polish(char *str) {
    char attachment[256] = "1*";
    if (check_first_symobol(*str)) {
        strcat(attachment, str);
    } else {
        strcpy(attachment, str);
    }
    double result = notation(attachment);
    return result;
}

int check_first_symobol(char first_symbol) {
    int check = 0;
    char moves[] = "(sctSCT";
    for (size_t i = 0; i < strlen(moves); i++) {
        if(first_symbol == moves[i]) {
            check = 1;
        }
    }
    return check;
}

double notation(char *str) {
    char token[256];
    strcpy(token, str);
    char *temp = NULL;
    char moves[] = "()^+-*/sctSCT";
    int n_count = 0;
    int o_count = -1;
    double nums[20] = {0};
    char oper[20];
    temp = strtok(token, moves);
    nums[n_count++] = atof(temp);
    for(size_t i = 0; i < strlen(str); i++) {
        if(oper_find(str, i)) {
            if(str[i] != CLOSE_BRCK) {
                o_count++;
            } else {
                while(oper[o_count] != OPEN_BRCK) {
                    bracket_close(nums, oper, &n_count, &o_count);
                }
            }
            if(str[i] == CLOSE_BRCK && oper[o_count] == OPEN_BRCK) {
                oper[o_count--] = '\000';
                if(oper[o_count] == SIN || oper[o_count] == COS || oper[o_count] == TAN || oper[o_count] == ASIN || oper[o_count] == ACOS || oper[o_count] == ATAN) {
                    trigonometry(&(nums[n_count - 1]), oper[o_count--]);
                }
            }
            if(n_count > 1) {
                if(prior_comparison(str[i], oper[o_count-1]) == 1) {
                    math_in_condition(nums, oper, &n_count, &o_count);
                }
                if(prior_comparison(str[i], oper[o_count-1]) == 2) {
                    math_in_condition(nums, oper, &n_count, &o_count);
                }
            }
            if(str[i] != CLOSE_BRCK) {
                oper[o_count] = str[i];
            }
            if(!oper_find(str, i + 1)) {
                temp = strtok(NULL, moves);
                if(temp != NULL) nums[n_count++] = atof(temp);
            }
        }
        if(i == strlen(str) - 1) {
            while(o_count != -1) {
                bracket_close(nums, oper, &n_count, &o_count);
                if(oper[o_count] == OPEN_BRCK) {
                    oper[o_count--] = '\000';
                }
            }
        }
    }
    return nums[0];
}

int prior_comparison(char first, char second) {
    int decision = 0;
    int priority_1 = determine_priority(first);
    int priority_2 = determine_priority(second);
    if(priority_1 < priority_2) {
        decision = 1;
    } else if(priority_1 == priority_2) {
        decision = 2;
    }
    if(first == 40 || first == 41 || second == 40 || second == 41) {
        decision = 0;
    }
    return decision;
}

int determine_priority(char operation) {
    int priority = 0;
    if(operation == ADD || operation == SUB) {
        priority = 1;
    } else if (operation == MUL || operation == DIV) {
        priority = 2;
    } else if (operation == SIN || operation == COS || operation == TAN || operation == ASIN || operation == ACOS || operation == ATAN) {
        priority = 3;
    } else if (operation == OPEN_BRCK || operation == CLOSE_BRCK) {
        priority = 4;
    }
    return priority;
}

bool oper_find(char *str, int i) {
    bool oper_trig = false;
    char operations[] = "()^+-*/sctSCT";
    for(size_t j = 0; j < strlen(operations); j++) {
        if(str[i] == operations[j]) {
            oper_trig = true;
        }
    }
    return oper_trig;
}

double math_nums(double first, double second, char operation) {
    if(operation == ADD) {
        first += second;
    } else if(operation == SUB) {
        first -= second;
    } else if(operation == DIV) {
        first /= second;
    } else if(operation == MUL) {
        first *= second;
    }
    return first;
}

void trigonometry(double *number, char operation) {
    if(operation == SIN) {
        *number = sin(*number);
    } else if(operation == COS) {
        *number = cos(*number);
    } else if(operation == TAN) {
        *number = tan(*number);
    } else if(operation == ASIN) {
        *number = asin(*number);
    } else if(operation == ACOS) {
        *number = acos(*number);
    } else if(operation == ATAN) {
        *number = atan(*number);
    }
}

void bracket_close(double *nums, char *oper, int *n_count, int *o_count) {
    if(check_first_symobol(oper[*o_count])) {
        trigonometry(&(nums[*n_count-1]), oper[*o_count]);
        oper[(*o_count)--] = '\000';
    } else {
        nums[*n_count-2] = math_nums(nums[*n_count-2], nums[*n_count-1], oper[*o_count]);
        nums[*n_count-1] = 0;
        oper[(*o_count)--] = '\000';
        (*n_count)--;
    }
}

void math_in_condition(double *nums, char *oper, int *n_count, int *o_count) {
    nums[(*n_count)--] = 0;
    oper[(*o_count)--] = '\000';
    nums[*n_count-1] = math_nums(nums[*n_count-1], nums[*n_count], oper[*o_count]);
}

void test() {
    int testing = 0;
    for (size_t i = 43; i < sizeof(examples)/sizeof(examples[0]); i++) {
        double one_ex = polish(examples[i]);
        double diff = one_ex - results[i];
        if((long long)(diff * 1e5) != 0) {
            testing = 1;
        }
    }
    (testing == 0) ? printf("SUCCESS\n") : printf("FAIL\n"); 
//     for (size_t i = 0; i < sizeof(examples)/sizeof(examples[0]); i++) {
//         if(i == 39) printf("=======================+SINUS+=======================\n");
//         if(i == 44) printf("=======================+COSINUS+=======================\n");
//         if(i == 49) printf("=======================+TANGENS+=======================\n");
//         if(i == 54) printf("=======================+ARCFUNCS+=======================\n");
//         double one_ex = polish(examples[i]);
//         printf ("%ld) %s\n", i, examples[i]);
//         printf ("(my) %lf = %lf\n", one_ex, results[i]);
//     }
}