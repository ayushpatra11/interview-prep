/*
 * Koko loves to eat bananas. There are n piles of bananas, the ith pile has
 * piles[i] bananas. The guards have gone and will come back in h hours.
 *
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she
 * chooses some pile of bananas and eats k bananas from that pile. If the pile
 * has less than k bananas, she eats all of them instead and will not eat any
 * more bananas during this hour.
 *
 * Koko likes to eat slowly but still wants to finish eating all the bananas
 * before the guards return.
 *
 * Return the minimum integer k such that she can eat all the bananas within h
 * hours.
 *
 * Example 1:
 * Input: piles = [3,6,7,11], h = 8
 * Output: 4
 * Example 2:
 *
 * Input: piles = [30,11,23,4,20], h = 5
 * Output: 30
 * Example 3:
 *
 * Input: piles = [30,11,23,4,20], h = 6
 * Output: 23
 *
 * Constraints:
 * 1 <= piles.length <= 104
 * piles.length <= h <= 109
 * 1 <= piles[i] <= 109
 */

class Solution {
 public:
  long long findTimeToEat(vector<int> &piles, int speed) {
    long long time = 0;
    for (int pile : piles) {
      time += (pile + speed - 1) / speed;
    }
    return time;
  }
  int minEatingSpeed(vector<int> &piles, int h) {
    // the range of the speeds will be from 1 banana per hour to N bananas
    // per hour where n is the max number of bananas in a pile so that it
    // takes only an hour to finish the pile.

    int low = 1, high = *max_element(piles.begin(), piles.end()), mid;
    int minimumSpeed = high;
    while (low <= high) {
      mid = low - (low - high) / 2;
      long long numOfHours = findTimeToEat(piles, mid);
      if (numOfHours > h) {
        low = mid + 1;
      } else {
        minimumSpeed = min(mid, minimumSpeed);
        high = mid - 1;
      }
    }

    return minimumSpeed;
  }
};
