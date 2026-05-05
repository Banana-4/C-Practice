int searchInsert(int* nums, int numsSize, int target) {
    int *left = nums;
    int *right = nums + numsSize - 1;
    while (left <= right) {
        int *mid = left + (right - left) / 2;
        if (*mid == target) {
            return (int)(mid - nums);
        } else if (*mid > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return (int)(right - nums + 1);
}
