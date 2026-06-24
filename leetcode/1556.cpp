#include <algorithm>
#include <string>

using std::string;

class Solution {
public:
  string thousandSeparator(int n) {
    if (n == 0) {
      return "0";
    }

    string result{""};
    result.reserve(13);

    int count{0};
    while (n > 0) {
      int digit = n % 10;
      n /= 10;

      if (count >= 3) {
        result += ".";
        count = 0;
      }

      result.push_back('0' + digit);
      count++;
    }

    std::reverse(result.begin(), result.end());
    return result;
  }
};
