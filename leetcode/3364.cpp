#include <vector>

using std::vector;

class Solution {
public:
  int sum_vector(const vector<int> &nums, size_t start, size_t len) {
    int sum{0};
    size_t counted{0};
    for (size_t idx = start; counted < len; idx++) {
      sum += nums.at(idx);
      counted++;
    };

    return sum;
  };

  int minimumSumSubarray(vector<int> &nums, int l, int r) {
    int lowest{-1};
    size_t nums_size{nums.size()};

    for (int len{l}; len <= r; len++) {
      for (size_t cursor{0}; cursor + len <= nums_size; cursor++) {
        int sum = sum_vector(nums, cursor, len);
        if (sum > 0) {
          if (lowest == -1 || sum < lowest) {
            lowest = sum;
          }
        }
      }
    }

    return lowest;
  }
};
