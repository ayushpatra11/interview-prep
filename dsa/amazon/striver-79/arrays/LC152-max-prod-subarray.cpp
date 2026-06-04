/*
 * Given an integer array nums, find a subarray that has the largest product,
 * and return the product.
 *
 * The test cases are generated so that the answer will fit in a 32-bit integer.
 *
 * Note that the product of an array with a single element is the value of that
 * element.
 *
 * Example 1:
 * Input: nums = [2,3,-2,4]
 * Output: 6
 * Explanation: [2,3] has the largest product 6.
 * Example 2:
 *
 * Input: nums = [-2,0,-1]
 * Output: 0
 * Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 *
 * Constraints:
 * 1 <= nums.length <= 2 * 104
 * -10 <= nums[i] <= 10
 * The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
 */

class Solution {
 public:
  int maxProduct(vector<int> &nums) {
    int left = 1;
    int right = 1;
    int ans = INT_MIN;

    for (int num : nums) {
      if (left == 0) left = 1;
      left = left * num;

      ans = max(left, ans);
    }
    for (int i = nums.size() - 1; i >= 0; i--) {
      if (right == 0) right = 1;
      right = right * nums[i];
      ans = max(ans, right);
    }
    return ans;
  }
};
