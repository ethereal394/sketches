#include "munro_paterson.h"
#include <algorithm>

namespace sketch {

MunroPatersonSketch::MunroPatersonSketch(Parameters params) : k_(params.k) {
}

void MunroPatersonSketch::Add(ElementType value) {
  if (s_.empty() || s_.back().first.size() == k_) {
    s_.push_back({{}, 0});
  }
  s_.back().first.push_back(value);
  if (s_.back().first.size() == k_) {
    std::sort(s_.back().first.begin(), s_.back().first.end());
    while (s_.size() >= 2 && s_[static_cast<int64_t>(s_.size()) - 2].second == s_.back().second) {
      int64_t x = s_.back().second + 1;
      auto &a = s_[static_cast<int64_t>(s_.size()) - 2].first;
      auto &b = s_.back().first;
      std::vector<ElementType> c;
      std::merge(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(c));
      std::vector<ElementType> d;
      for (size_t i = 1; i < c.size(); i += 2) {
        d.push_back(c[i]);
      }
      s_.pop_back();
      s_.pop_back();
      s_.push_back({d, x});
    }
  }
}

void MunroPatersonSketch::Finalize() {
  while (s_.size() > 1 || s_[0].first.size() < k_) {
    Add(std::numeric_limits<ElementType>::max());
  }
}

// expected 1-indexing (for example, min value has k = 1)
std::pair<MunroPatersonSketch::ElementType, MunroPatersonSketch::ElementType> MunroPatersonSketch::KthRange(uint64_t kth) const {
  --kth;
  ElementType mn = std::numeric_limits<ElementType>::min();
  ElementType mx = std::numeric_limits<ElementType>::max();
  if (s_.empty()) {
    return {mn, mx};
  }
  for (size_t i = 0; i < s_[0].first.size(); ++i) {
    if ((s_[0].second + i) * (1ull << s_[0].second) <= kth) {
      mn = s_[0].first[i];
    }
    if ((i + 1) * (1ull << s_[0].second) - 1 >= kth) {
      mx = s_[0].first[i];
      break;
    }
  }
  return {mn, mx};
}

}  // namespace sketch