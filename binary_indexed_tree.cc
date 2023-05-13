#include <bits/stdc++.h>
using namespace std;

class BinaryIndexedTree {
 public:
  // Initializes the tree with `n` elements.
  BinaryIndexedTree(int64_t n) : sums_(n + 1, 0) {}

  // Adds `n` to the element on `pos` (1-based).
  void Update(int64_t pos, int64_t n) {
    while (pos < sums_.size()) {
      sums_[pos] += n;
      pos += LowBit(pos);
    }
  }

  // Returns the sum of elements from position 1 to `pos` (1-based).
  int64_t Query(int64_t pos) {
    int64_t ans = 0;
    while (pos > 0) {
      ans += sums_[pos];
      pos -= LowBit(pos);
    }
    return ans;
  }

 private:
  inline int64_t LowBit(int64_t x) { return x & -x; }

 private:
  vector<int64_t> sums_;
};
