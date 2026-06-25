
class Solution {
public:
  int xorOperation(const int n, const int start) {
    int output = start;

    for (int i = 1; i < n; i++) {
      output ^= (start + (2 * i));
    };

    return output;
  }
};
