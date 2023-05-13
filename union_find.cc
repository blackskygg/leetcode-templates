#include <bits/stdc++.h>
using namespace std;

class UnionFind {
 public:
  // Constructs an instance with `n` elements.
  UnionFind(int n) {
    parent_ = vector<int>(n);
    for (int i = 0; i < n; ++i) {
      parent_[i] = i;
    }

    rank_ = vector<int>(n, 1);
    size_ = vector<int64_t>(n, 1);
  }

  // Returns the parent of `x`'s cluster.
  int Find(int x) {
    if (x == parent_[x]) {
      return x;
    } else {
      return parent_[x] = Find(parent_[x]);
    }
  }

  // Unions `x`'s and `y`'s cluster and returns the new parent.
  int Union(int x, int y) {
    int px = Find(x), py = Find(y);
    if (px == py) return px;

    if (rank_[px] > rank_[py]) swap(px, py);
    if (rank_[px] == rank_[py]) rank_[py]++;
    size_[py] += size_[px];
    parent_[px] = py;
    return py;
  }

  // Returns the size of `x`'s cluster.
  int64_t Size(int x) { return size_[x]; }

 private:
  vector<int> parent_, rank_;
  vector<int64_t> size_;
};
