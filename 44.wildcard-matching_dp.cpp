/*
 * @lc app=leetcode id=44 lang=cpp
 *
 * [44] Wildcard Matching
 */
#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    string compressPattern(const string& p) {
        string ret;
        for (const char c: p) {
            if (c == '*' && !ret.empty() && ret.back() == '*') continue;
            ret += c;
        }
        return ret;
    }

    bool isMatch(string s, string p) {
        int s_len = s.size();
        p = compressPattern(p);
        int p_len = p.size();

        vector<vector<bool>> dp(s_len + 1, vector<bool>(p_len + 1, false));
        dp[0][0] = true;
        dp[0][1] = p[0] == '*';

        for (int si = 1; si <= s_len; ++si) {
            for (int pi = 1; pi <= p_len; ++pi) {
                switch (p[pi - 1]) {
                    case '?':
                        dp[si][pi] = dp[si - 1][pi - 1];
                        break;
                    case '*':
                        dp[si][pi] = dp[si - 1][pi] || dp[si][pi - 1];
                        break;
                    default:
                        dp[si][pi] = dp[si - 1][pi - 1] && s[si - 1] == p[pi - 1];
                        break;
                }
            }
        }

        return dp[s_len][p_len];
    }
};
// @lc code=end

