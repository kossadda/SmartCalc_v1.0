#include "../main.h"
#include <stdio.h>

int main() {
    char str[] = "(6(((((((((((((5-6)*5)*3)*2)*5)*4)/2.421)/432)*324.12)*31.23)/4.123)+213.4325)-834.324))^2m4";
    // printf("1*(((u65324*(2654.5645-6541))/(u3654234-(u2234/4345)))+(u5747-(c(u3534/561.5345))))*(u5432-((u6541/4230.4325)-(u4232*1654.655)))\n");
    // validation(str);
    // printf("%s\n", str);
    printf("%lf\n", calculation(str));
}