#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
  int numOfStrings(const vector<string> &patterns, const string &word) {
    int hits{0};
    size_t word_len = word.length();

    for (const string &substr : patterns) {
      if (word.find(substr) != std::string::npos) {
        hits++;
      }
    }

    return hits;
  }
};
