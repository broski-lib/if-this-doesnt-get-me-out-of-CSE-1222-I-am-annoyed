#include <string>

using std::string;

class Solution {
public:
  int balancedStringSplit(string s) {
    int num_splits{0};

    int count_l{0};
    int count_r{0};
    for (size_t i = 0; i < s.length(); i++) {
      if (s[i] == 'L') {
        count_l++;
      } else {
        count_r++;
      }

      if (count_l == count_r) {
        num_splits++;
        count_l = 0;
        count_r = 0;
      }
    }

    return num_splits;
  }
};
