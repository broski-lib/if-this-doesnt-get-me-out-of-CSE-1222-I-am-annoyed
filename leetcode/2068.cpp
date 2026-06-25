#include <cstdlib>
#include <string>
#include <unordered_map>

using std::string;

class Solution {
public:
  bool checkAlmostEquivalent(string word1, string word2) {
    size_t len = word1.length();
    std::unordered_map<char, int> offsets{};

    for (size_t i = 0; i < len; i++) {
      offsets[word1[i]] += 1;
      offsets[word2[i]] -= 1;
    };

    for (const auto &[key, val] : offsets) {
      if (abs(val) > 3) {
        return false;
      }
    }

    return true;
  };
};
