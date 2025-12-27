/*
/*
 * @lc app=leetcode id=28 lang=cpp
 *
 * [28] Find the Index of the First Occurrence in a String
 */
#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() > haystack.size()) return -1;

        size_t m = haystack.size(), n = needle.size();

        vector<int> lps(n, 0);
        
        for (size_t i = 1, len = 0; i < n; ) {
            if (needle[i] == needle[len]) {
                lps[i++] = ++len;
            } else {
                if (len) {
                    len = lps[len - 1];
                } else {
                    lps[i++] = 0;
                }
            }
        }

        for (size_t i = 0, j = 0; i < m; ) {
            if (haystack[i] == needle[j]) {
                ++i; ++j;
                if (j == n) return i - n;
            } else {
                if (j) {
                    j = lps[j - 1];
                } else {
                    ++i;
                }
            }
        }

        return -1;
    }
};
// @lc code=end
