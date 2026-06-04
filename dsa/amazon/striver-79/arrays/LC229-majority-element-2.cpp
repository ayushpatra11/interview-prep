/*
 * Note: this is a modification of the boyer moore voting algo
 *
 * Given an integer array of size n, find all elements that appear more
 * than n/3 times.
 *
 * Example 1:
 * Input: nums = [3,2,3]
 * Output: [3]
 * Example 2:
 *
 * Input: nums = [1]
 * Output: [1]
 * Example 3:
 *
 * Input: nums = [1,2]
 * Output: [1,2]
 *
 * Constraints:
 * 1 <= nums.length <= 5 * 104
 * -109 <= nums[i] <= 109
 *
 * Follow up: Could you solve the problem in linear time and in O(1) space?
 */

class Solution {
 public:
  vector<int> majorityElement(vector<int> &nums) {
    int n1 = INT_MIN, n2 = INT_MIN, c1 = 0, c2 = 0;
    vector<int> ans;
    for (int num : nums) {
      if (c1 == 0 && num != n2) {
        n1 = num;
        c1++;
      } else if (c2 == 0 && num != n1) {
        n2 = num;
        c2++;
      } else if (num == n1)
        c1++;
      else if (num == n2)
        c2++;
      else {
        c1--;
        c2--;
      }
    }
    c1 = 0;
    c2 = 0;
    for (int num : nums) {
      if (num == n1)
        c1++;
      else if (num == n2)
        c2++;
    }
    if (c1 > nums.size() / 3) ans.push_back(n1);
    if (n2 != n1 && c2 > nums.size() / 3) ans.push_back(n2);
    return ans;
  }
};
