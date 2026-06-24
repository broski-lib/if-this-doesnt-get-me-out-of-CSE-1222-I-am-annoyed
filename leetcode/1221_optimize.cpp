#include <string_view>

class Solution {
public:
  int balancedStringSplit(std::string_view s) {
    int num_splits{0};

    int offset{0};
    for (size_t i = 0; i < s.length(); i++) {
      if (s[i] == 'L') {
        offset++;
      } else {
        offset--;
      }

      if (offset == 0) {
        num_splits++;
      }
    }

    return num_splits;
  }
};
