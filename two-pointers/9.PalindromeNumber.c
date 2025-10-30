#include <math.h>
bool isPalindrome(int x) {
    if (x < 0)  return false;
    if (x < 10) return true;
    
    int base = 10;
    long left = (long)pow(base, (int)log10(x));
    long right = base;

    int left_dig, right_dig; 
    while (x) {
        left_dig = x / left;
        right_dig = x % base;
        x = (x % left) / right;
        if (left_dig != right_dig) return false;
        left /= 100;
    }
    return true;
}
