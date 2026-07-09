#include <string>

using std::string;

class Solution {
public:
  int minOperations(string s) {
    bool previous_is_zero{false};
    int previous_ops{-1};

    while (true) {
      int ops{0};
      for (size_t idx{0}; idx < s.length(); idx++) {
        bool is_zero{s[idx] == '0'};
        if (previous_is_zero && is_zero) {
          previous_is_zero = false;
          ops++;
          continue;
        } else if (previous_is_zero && !is_zero) {
          previous_is_zero = false;
          continue;
        } else if (!previous_is_zero && is_zero) {
          previous_is_zero = true;
          continue;
        } else {
          previous_is_zero = true;
          ops++;
          continue;
        }
      }

      if (previous_ops == -1) {
        previous_ops = ops;
        previous_is_zero = true;
      } else if (previous_ops > ops) {
        return ops;
      } else {
        return previous_ops;
      }
    }
  }
};
