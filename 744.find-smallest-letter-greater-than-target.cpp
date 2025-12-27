/*
 * @lc app=leetcode id=744 lang=cpp
 *
 * [744] Find Smallest Letter Greater Than Target
 */
#include <vector>
#include <algorithm>

using namespace std;

// @lc code=start
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        size_t lo = 0;
        size_t hi = letters.size();
        while (lo < hi) {
            size_t mid = (hi + lo) / 2;
            if (letters[mid] > target) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        if (lo == letters.size()) {
            return letters.front();
        } else {
            return letters[lo];
        }
    }
};
// @lc code=end

