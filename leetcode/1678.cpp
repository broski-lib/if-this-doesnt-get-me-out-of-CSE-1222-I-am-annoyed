#include <string>

using std::string;

class Solution {
public:
  string interpret(string command) {
    string result{};

    for (size_t idx{0}; idx < command.size(); idx++) {
      if (command[idx] == 'G') {
        result += 'G';
      } else if (command[idx] == '(' && command[idx + 1] == ')') {
        result += 'o';
        idx += 1;
      } else {
        result += "al";
        idx += 3;
      }
    }

    return result;
  }
};
