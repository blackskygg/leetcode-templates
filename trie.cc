#include <bits/stdc++.h>
using namespace std;

// A trie implementation backed by a statically allocated node pool.
// The class assumes the alphabet is a contiguous range of integers. E.g. 'a'-'z'.
//
// Template arguments:
//  @AlphabetStart: The first valid character in the alphabet. E.g. 'a'.
//  @AlphabetEnd: The last valid character in the alphabet. E.g. 'z'.
//  @PoolSize: Size of the pre-allocated node pool.
template<char AlphabetStart, int AlphabetEnd, int PoolSize>
class Trie {
 public:
  // A trie node.
  class Node {
   public:
    // Resets this node to empty status.
    Node& Reset() {
      ch_.assign(AlphabetEnd-AlphabetStart+1, nullptr);
      is_end = false;
      return *this;
    }

    // Walks by one character.
    Node* at(const char c) const {
      return ch_.at(c-AlphabetStart);
    }

    // Inserts one characer.
    Node* operator[](char c) {
      c -= AlphabetStart;
      if (this->ch_[c] == nullptr) this->ch_[c] = Trie::NewNode();
      return this->ch_[c];
    }

    // Inserts a string.
    void Insert(const string& s) {
      Node* curr = this;
      for (const auto c : s) {
        curr = (*curr)[c];
      }
      curr->is_end = true;
    }

    // Walks along a string. Returns nullptr if `s` doesn't exist.
    Node* Walk(const string& s) {
      Node* curr = this;
      for (const auto c : s) {
        curr = curr->at(c);
        if (curr == nullptr) return nullptr;
      }
      return curr;
    }

   public:
    // Is this a end node or not.
    bool is_end = false;

   private:
    vector<Node*> ch_ = vector<Node*>(AlphabetEnd-AlphabetStart+1);
  };

  friend class Node;

 public:
  Trie() { head_ = NewNode(); }

  // Returns the head node of this trie.
  Node* GetHead() { return head_; }

  // Inserts a string.
  void Insert(const string& s) { head_->Insert(s); }

  // Walks along a string. Returns nullptr if `s` doesn't exist.
  Node* Walk(const string& s) { return head_->Walk(s); }

  // Resets the global node pool, invalidating all instances.
  static void ResetPool() { GetPoolSingleton().curr_index = 0; }

 private:
  Node* head_;

 private:
  // Node pool shared by all Trie instances.
  struct Pool{
    Node nodes[PoolSize];
    int curr_index = 0;
  };

  static Pool& GetPoolSingleton() {
    static auto& kPool = *new Pool();
    return kPool;
  }

  static Node* NewNode() {
    Pool& pool = GetPoolSingleton();
    return &pool.nodes[pool.curr_index++].Reset();
  }
};
