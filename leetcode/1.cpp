#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
  vector<int> twoSum(const vector<int> &nums, int target) {
    for (size_t first_idx{0}; first_idx < nums.size(); first_idx++) {
      for (size_t second_idx{1}; second_idx < nums.size(); second_idx++) {
        if (first_idx == second_idx) {
          continue;
        }

        if (nums[first_idx] + nums[second_idx] == target) {
          return std::vector{(int)first_idx, (int)second_idx};
        }
      }
    }

    return std::vector{-1, -1};
  }
};
