int removeElement(int* nums, int numsSize, int val) {
    if(!nums || !numsSize) return 0;
    int* left = nums;
    int* right = nums + numsSize - 1;
    while(left <= right) {
        if (*right == val) {
            right--; 
        } else {
            if (*left == val) {
            int tmp = *left;
            *this = *right;
            *right = tmp;
            }
            left++;
        }
    }
    return (int)(left - nums);
}
