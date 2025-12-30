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

        int si = 0, pi = 0;
        int s_star = -1, p_star = -1;
        while (si < s_len) {
            if (pi < p_len && (p[pi] == '?' || p[pi] == s[si])) {
                si++;
                pi++;
            } else if (pi < p_len && p[pi] == '*') {
                s_star = si;
                p_star = pi;
                pi++;
            } else {
                if (p_star == -1) return false;
                si = s_star + 1;
                pi = p_star + 1;
                s_star++;
            }
        }

        for (; pi < p_len; ++pi) {
            if (p[pi] != '*') {
                return false;
            }
        }
        return true;
    }
};
// @lc code=end

