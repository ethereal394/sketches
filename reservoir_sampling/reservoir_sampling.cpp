#include "reservoir_sampling.h"

namespace sketch {

ReservoirSampling::ReservoirSampling(Parameters params) : k_(params.k), rnd_(params.seed) {}

void ReservoirSampling::Add(int64_t value) {
  ++cnt_;
  if (sample_.size() < k_) {
    sample_.push_back(value);
  } else if (auto x = rnd_() % cnt_; x < k_) {
    sample_[x] = value;
  }
}

std::vector<int64_t> ReservoirSampling::Sample() const {
  return sample_;
}

}  // namespace sketch