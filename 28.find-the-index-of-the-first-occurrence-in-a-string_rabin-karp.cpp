/*
 * @lc app=leetcode id=28 lang=cpp
 *
 * [28] Find the Index of the First Occurrence in a String
 */
#include <string>

using namespace std;

// @lc code=start
const int MOD = 1e9 + 7;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.size() > haystack.size()) return -1;
        
        long long needleHash = 0, haystackHash = 0, power = 1;
        size_t n = needle.size();
        size_t m = haystack.size();

        for (int i = 0; i < n; ++i) {
            needleHash = (needleHash * 26 + needle[i]) % MOD;
            haystackHash = (haystackHash * 26 + haystack[i]) % MOD;
            if (i > 0) power = (power * 26) % MOD;
        }

        for (int i = 0; i <= m - n; ++i) {
            if (haystackHash == needleHash) {
                if (haystack.substr(i, n) == needle) {
                    return i;
                }
            }
            if (i < m - n) {
                haystackHash = (haystackHash - haystack[i] * power % MOD + MOD) % MOD;
                haystackHash = (haystackHash * 26 + haystack[i + n]) % MOD;
            }
        }

        return -1;
    }
};
// @lc code=end
