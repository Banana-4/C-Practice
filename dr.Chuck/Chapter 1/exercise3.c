#include <stdio.h>

int main() {
    int lower, upper, step;
    float fahr, cels;
    lower = 0;
    upper = 300;
    step = 20;
    cels = lower - step;
    printf("%s %s\n", "Celsius", "Fahrenheit");
    while( (cels += step) <= upper) {
        fahr = cels * (5.0/9.0) + 32.0;
        printf("%-7.0f %-6.1f\n", cels, fahr);
    }
}
