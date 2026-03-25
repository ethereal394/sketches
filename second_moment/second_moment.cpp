#include "second_moment.h"

namespace sketch {

SecondMomentSketch::SecondMomentSketch(Parameters params)
    : seed_(params.seed), rnd_(seed_), a_(rnd_()), b_(rnd_()), c_(rnd_()), d_(rnd_()), t_(0) {
  a_ %= mod_;
  b_ %= mod_;
  c_ %= mod_;
  d_ %= mod_;
}

void SecondMomentSketch::Add(int64_t value) {
  uint64_t x = static_cast<uint64_t>(value - std::numeric_limits<int64_t>::min());
  t_ += ((a_ * x * x * x + b_ * x * x + c_ * x + d_) % mod_) % 2 == 0 ? 1 : -1;
}

int64_t SecondMomentSketch::Estimate() const {
  return t_ * t_;
}

std::vector<uint8_t> SecondMomentSketch::Serialize() const {
  std::vector<uint8_t> bytes(sizeof(uint64_t) + sizeof(int64_t));
  std::memcpy(bytes.data(), &seed_, sizeof(uint64_t));
  std::memcpy(bytes.data() + sizeof(uint64_t), &t_, sizeof(int64_t));
  return bytes;
}

SecondMomentSketch SecondMomentSketch::Deserialize(const std::vector<uint8_t>& bytes) {
  uint64_t seed;
  std::memcpy(&seed, bytes.data(), sizeof(uint64_t));
  SecondMomentSketch s({seed});
  std::memcpy(&s.t_, bytes.data() + sizeof(uint64_t), sizeof(int64_t));
  return s;
}

};  // namespace sketch