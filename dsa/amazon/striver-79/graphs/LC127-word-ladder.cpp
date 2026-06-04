/*
 * A transformation sequence from word beginWord to word endWord using a
 * dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk
 * such that:
 *
 * Every adjacent pair of words differs by a single letter.
 * Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to
 * be in wordList. sk == endWord
 * Given two words, beginWord and endWord, and a dictionary wordList, return the
 * number of words in the shortest transformation sequence from beginWord to
 * endWord, or 0 if no such sequence exists.
 *
 * Example 1:
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log","cog"] Output: 5 Explanation: One shortest
 * transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is
 * 5 words long.
 * Example 2:
 *
 * Input: beginWord = "hit", endWord = "cog", wordList =
 * ["hot","dot","dog","lot","log"] Output: 0 Explanation: The endWord "cog" is
 * not in wordList, therefore there is no valid transformation sequence.
 *
 * Constraints:
 * 1 <= beginWord.length <= 10
 * endWord.length == beginWord.length
 * 1 <= wordList.length <= 5000
 * wordList[i].length == beginWord.length
 * beginWord, endWord, and wordList[i] consist of lowercase English letters.
 * beginWord != endWord
 * All the words in wordList are unique.
 */

class Solution {
 public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> unvisitedStrings(wordList.begin(), wordList.end());
    queue<pair<string, int>> q;
    q.push({beginWord, 1});
    unvisitedStrings.erase(beginWord);
    int steps = INT_MAX;

    while (!q.empty()) {
      auto [currWord, currSteps] = q.front();
      q.pop();

      if (currWord == endWord) {
        return currSteps;
      }

      for (int i = 0; i < currWord.length(); i++) {
        char original = currWord[i];
        for (char ch = 'a'; ch <= 'z'; ch++) {
          currWord[i] = ch;
          if (unvisitedStrings.find(currWord) != unvisitedStrings.end()) {
            q.push({currWord, currSteps + 1});
            unvisitedStrings.erase(currWord);
          }
        }
        currWord[i] = original;
      }
    }

    return 0;
  }
};
