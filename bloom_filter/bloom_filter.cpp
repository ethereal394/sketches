#include "bloom_filter.h"
#include <random>

namespace sketch {

BloomFilter::BloomFilter(Parameters params) {
  b_.resize(params.array_size, 0);
  h_.resize(params.hash_func_count);
  std::mt19937_64 rnd(1337);
  for (size_t i = 0; i < h_.size(); ++i) {
    h_[i].first = rnd();
    if (h_[i].first & 1) {
      ++h_[i].first;
    }
    h_[i].second = rnd();
  }
}

void BloomFilter::Add(const ElementType& elem) {
  for (size_t i = 0; i < h_.size(); ++i) {
    b_[(h_[i].first * static_cast<uint64_t>(elem - std::numeric_limits<ElementType>::min()) + h_[i].second) % b_.size()] = 1;
  }
}

bool BloomFilter::Estimate(const ElementType& elem) const {
  bool res = true;
  for (size_t i = 0; i < h_.size(); ++i) {
    res &= b_[(h_[i].first * static_cast<uint64_t>(elem - std::numeric_limits<ElementType>::min()) + h_[i].second) % b_.size()];
  }
  return res;
}

}  // namespace sketch