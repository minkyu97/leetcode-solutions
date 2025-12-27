/*
/*
 * @lc app=leetcode id=28 lang=cpp
 *
 * [28] Find the Index of the First Occurrence in a String
 */
#include <string>

using namespace std;

// @lc code=start
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() > haystack.size()) return -1;

        for (int left = 0; left <= haystack.size() - needle.size(); ++left) {
            if (haystack.substr(left, needle.size()) == needle) {
                return left;
            }
        }

        return -1;
    }
};
// @lc code=end
