#include <bits/stdc++.h>
using namespace std;

// Splits `s` by `delim`. Will not return empty string if `skip_empty` is true.
template <typename T>
vector<string_view> StrSplit(const string_view s, T&& delim,
                             const bool skip_empty = false) {
  vector<string_view> parts;
  int start = 0;
  while (start < s.size()) {
    auto pos = s.find(forward<T>(delim), start);
    if (pos == string_view::npos) pos = s.size();
    if (!skip_empty || pos != start) {
      parts.push_back(s.substr(start, pos - start));
    }
    start = pos + 1;
  }
  return parts;
}
