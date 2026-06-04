/*
 * Given two sorted arrays nums1 and nums2 of size m and n respectively, return
 * the median of the two sorted arrays.
 *
 * The overall run time complexity should be O(log (m+n)).
 *
 * Example 1:
 * Input: nums1 = [1,3], nums2 = [2]
 * Output: 2.00000
 * Explanation: merged array = [1,2,3] and median is 2.
 * Example 2:
 *
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 2.50000
 * Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 *
 * Constraints:
 * nums1.length == m
 * nums2.length == n
 * 0 <= m <= 1000
 * 0 <= n <= 1000
 * 1 <= m + n <= 2000
 * -106 <= nums1[i], nums2[i] <= 106
 */

class Solution {
 public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int m = nums1.size(), n = nums2.size();
    if (m > n) return findMedianSortedArrays(nums2, nums1);
    int low = 0, high = m;

    while (low <= high) {
      int count1 = low - (low - high) / 2;

      int count2 = (m + n + 1) / 2 - count1;

      int leftMax1 = (count1 == 0) ? INT_MIN : nums1[count1 - 1];
      int rightMin1 = (count1 == m) ? INT_MAX : nums1[count1];

      int leftMax2 = (count2 == 0) ? INT_MIN : nums2[count2 - 1];
      int rightMin2 = (count2 == n) ? INT_MAX : nums2[count2];

      if (leftMax1 <= rightMin2 && leftMax2 <= rightMin1) {
        if ((n + m) % 2 == 0)
          return (max(leftMax1, leftMax2) + min(rightMin1, rightMin2)) / 2.0;
        return max(leftMax1, leftMax2);
      } else if (leftMax1 > rightMin2) {
        high = count1 - 1;
      } else
        low = count1 + 1;
    }

    return 0.0;
  }
};
