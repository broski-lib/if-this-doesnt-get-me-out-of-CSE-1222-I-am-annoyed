#include <string>
#include <string_view>

using std::string;

constexpr size_t window_len = 2;

class Solution {
public:
  int minLength(string s) {
    if (s.length() < 2) {
      return s.length();
    };

    size_t idx{0};
    while (idx < s.length() - 1 && s.length() > 0) {
      std::string_view window = std::string_view(s).substr(idx, window_len);

      if (window == "AB" || window == "CD") {
        s.erase(idx, window_len);
        idx = 0;
      } else {
        idx++;
      };
    };

    return s.length();
  }
};
