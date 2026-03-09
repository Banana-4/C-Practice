#include <stdio.h>

int main() {
    int lower, upper, step;
    float fahr, cels;
    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower - step;
    printf("%s %s\n", "Fahrenheit", "Celsius");
    while( (fahr += step) <= upper) {
        cels = (5.0/9.0) * (fahr-32.0);
        printf("%-10.0f %-6.1f\n", fahr, cels);
    }
}
