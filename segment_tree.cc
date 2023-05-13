#include <bits/stdc++.h>
using namespace std;

template <typename T = int64_t>
class SegmentTree {
 public:
  // Initializes a tree with the given initial values.
  explicit SegmentTree(const vector<T>& v)
      : value_(v.size() * 4), lazy_(v.size() * 4), size_(v.size()) {
    BuildTree(1, 0, v.size() - 1, v);
  }

  // Initializes an empty tree of the given size.
  explicit SegmentTree(int n) : SegmentTree(vector<T>(n)) {}

  // Returns the sum over range [left, right].
  T Sum(int left, int right) { return Sum(1, 0, size_ - 1, left, right); }

  // Adds `value` on the range [left, right].
  void Add(int left, int right, T value) {
    Add(1, 0, size_ - 1, left, right, value);
  }

 private:
  void BuildTree(int root, int left, int right, const vector<T>& v) {
    if (left == right) {
      value_[root] = v[left];
      return;
    }
    const int mid = Mid(left, right);
    BuildTree(LeftChild(root), left, mid, v);
    BuildTree(RightChild(root), mid + 1, right, v);
    Maintain(root);
  }

  T Sum(int root, int curr_left, int curr_right, int target_left,
        int target_right) {
    if (target_right < curr_left || curr_right < target_left) {
      return 0;
    }
    if (target_left <= curr_left && target_right >= curr_right) {
      return value_[root];
    }

    const int mid = Mid(curr_left, curr_right);
    PushDown(root, curr_left, curr_right, mid);

    T sum = 0;
    if (target_left <= mid) {
      sum += Sum(LeftChild(root), curr_left, mid, target_left, target_right);
    }
    if (target_right > mid) {
      sum +=
          Sum(RightChild(root), mid + 1, curr_right, target_left, target_right);
    }
    return sum;
  }

  void Add(int root, int curr_left, int curr_right, int target_left,
           int target_right, T value) {
    if (target_right < curr_left || curr_right < target_left) {
      return;
    }
    if (target_left <= curr_left && target_right >= curr_right) {
      value_[root] += value * (curr_right - curr_left + 1);
      lazy_[root] += value;
      return;
    }

    const int mid = Mid(curr_left, curr_right);
    PushDown(root, curr_left, curr_right, mid);
    if (target_left <= mid) {
      Add(LeftChild(root), curr_left, mid, target_left, target_right, value);
    }
    if (target_right > mid) {
      Add(RightChild(root), mid + 1, curr_right, target_left, target_right,
          value);
    }
    Maintain(root);
  }

  void Maintain(int root) {
    value_[root] = value_[LeftChild(root)] + value_[RightChild(root)];
  }

  void PushDown(int root, int left, int right, int mid) {
    if (lazy_[root] == 0) return;
    lazy_[LeftChild(root)] += lazy_[root];
    value_[LeftChild(root)] += lazy_[root] * (mid - left + 1);
    lazy_[RightChild(root)] += lazy_[root];
    value_[RightChild(root)] += lazy_[root] * (right - mid);
    lazy_[root] = 0;
  }

 private:
  static int Mid(int left, int right) { return left + (right - left) / 2; }
  static int LeftChild(int root) { return 2 * root; }
  static int RightChild(int root) { return 2 * root + 1; }

 private:
  vector<int64_t> value_, lazy_;
  int size_;
};