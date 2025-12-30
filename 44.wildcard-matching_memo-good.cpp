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
    bool isMatchRec(const string& s, const string& p, size_t si, size_t pi, vector<vector<bool>>& memo) {
        if (memo[si][pi]) {
            return false;
        }

        bool result = false;
        if (si == s.size() && pi == p.size()) {
            result = true;
        } else if (si == s.size()) {
            if (p[pi] == '*') {
                result = isMatchRec(s, p, si, pi + 1, memo);
            }
        } else if (pi == p.size()) {
            result = false;
        } else if (p[pi] == '?') {
            result = isMatchRec(s, p, si + 1, pi + 1, memo);
        } else if (p[pi] == '*') {
            result = isMatchRec(s, p, si + 1, pi, memo) || isMatchRec(s, p, si, pi + 1, memo);
        } else {
            result = p[pi] == s[si] && isMatchRec(s, p, si + 1, pi + 1, memo);
        }

        if (!result) {
            memo[si][pi] = true;
        }
        return result;
    }

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

        vector<vector<bool>> memo(s_len + 1, vector<bool>(p_len + 1, false));
        return isMatchRec(s, p, 0, 0, memo);
    }
};
// @lc code=end

