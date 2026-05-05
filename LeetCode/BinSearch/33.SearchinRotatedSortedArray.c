#define NOT_FOUND -1
int search(int* nums, int numsSize, int target) {
    if(numsSize == 1) {
        return (nums[0] == target ? 0 : NOT_FOUND);
    }
    int last = nums[numsSize -1];
    int *left = nums;
    int *right = nums + numsSize - 1;
    int *pivot = NULL;
    while (left <= right) {
        int *mid = left + (right - left) / 2;
        if (last >= *mid) {
            pivot = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if (target > last) {
        left = nums;
        right = pivot -1;
    } else {
        left = pivot;
        right = nums + numsSize - 1;
    }
    while (left <= right) {
        int *mid = left + (right - left) / 2;
        if (target == *mid) {
            return (int)(mid - nums);
        } else if (target > *mid) {
            left = mid + 1;
        } else {
             right = mid - 1; 
        }
    }
    return NOT_FOUND;
}
