#include <vector>

using std::vector;

class Solution {
public:
  int minimumSumSubarray(const vector<int> &nums, int l, int r) {
    int lowest{-1};
    size_t nums_size{nums.size()};

    for (size_t len{(size_t)l}; len <= r; len++) {
      int sum{0};

      for (size_t idx{0}; idx < len; idx++) {
        sum += nums[idx];
      };

      if (sum > 0 && (lowest == -1 || sum < lowest)) {
        lowest = sum;
      };

      for (size_t idx{len}; idx < nums_size; idx++) {
        int val = nums[idx];
        sum += val;
        sum -= nums[idx - len];
        if (sum > 0 && (lowest == -1 || sum < lowest)) {
          lowest = sum;
        };
      };
    }

    return lowest;
  }
};
