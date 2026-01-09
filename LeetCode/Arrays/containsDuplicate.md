# LeetCode 217. Contains Duplicate

## Problem:
  Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
  This is a search problem: for each element determine if a there is a second occurrence.
## Constraints:
  * 1 <= nums.length <= 105
  * -10^9 <= nums[i] <= 10^9

## Structure:
  An unsorted array of integers of length n.
## Solution:
  In a unsorted array the search space for a duplicate of any element is n - 1.
  ### Method 1: Naive Brute Force
    Use nested loop to compare each element with all next elments
    * The outside loop iterates from i = 0 to i == n - 1
    * The inner loop iterates from j = i to i - 1:
      ** at each iteration compare nums[j] to nums[i] if they are equal return true
    if the loop finishs without returning,  return false
    
    Time Complexity: 
      (n^2 - n) / 2, O(n^2).
    Space Complexity: 
      O(1)
    
    This method is preferred when memory is limited and the array can't be sorted in place.
    
  ### Method 2:
    In a sorted array, duplicate elements are next to each other.
    The search space is reduced to 1.
    Steps:
      1. Sort the array.
      2. Iterate from i = 1 to i = n - 1.
      3. At each iteration compare the element at i to the element at i -1:
        1. if they equal return true
        2. iterate to the next element
      4. if the iteration reaches end return false
      
    Time Complexity: 
      n * logn + n, O(n*logn).
    Space Complexity: 
      1. O(n) if a new sorted array is created.
      2. O(1) if the array is sorted in place.
      
    This method is preferred when the meory is not limited and the array can be sorted in place or a new sorted array can be created.  

