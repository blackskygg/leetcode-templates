#include <bits/stdc++.h>
using namespace std;

// A trie implementation backed by a statically allocated node pool.
// The class assumes the alphabet is a contiguous range of integers. E.g. 'a'-'z'.
//
// Template arguments:
//  @AlphabetBase: The first valid character in the alphabet. E.g. 'a'.
//  @AlphabetSize: Size of the alphabet. E.g. 26.
//  @PoolSize: Size of the pre-allocated node pool.
//
// Example usage:
//   Trie<'a', 26, 10010> trie;
//   trie.GetHead()->Insert("abcdefg");
//   auto head = trie.GetHead();
//   for (const char c : "abcde") {
//     head = head->at(c);
//   }
//   if (head->is_end) cout << "abcde is in Trie" << endl;
template<char AlphabetBase, int AlphabetSize, int PoolSize>
class Trie {
 public:
  // A trie node.
  class Node {
   public:
    // Resets this node to empty status.
    Node& Reset() {
      ch_.assign(AlphabetSize, nullptr);
      is_end = false;
      return *this;
    }

    // Walks by one character.
    Node* at(const char c) const {
      return ch_.at(c-AlphabetBase);
    }

    // Inserts one characer.
    Node* operator[](char c) {
      c -= AlphabetBase;
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

   public:
    // Is this a end node or not.
    bool is_end = false;

   private:
    vector<Node*> ch_ = vector<Node*>(AlphabetSize);
  };

  friend class Node;

 public:
  Trie() { head_ = NewNode(); }

  // Returns the head node of this trie.
  Node* GetHead() { return head_; }

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
    static auto* kPool = new Pool();
    return *kPool;
  }

  static Node* NewNode() {
    Pool& pool = GetPoolSingleton();
    return &pool.nodes[pool.curr_index++].Reset();
  }
};
