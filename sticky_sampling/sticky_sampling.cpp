#include "sticky_sampling.h"

namespace sketch {

StickySamplingSketch::StickySamplingSketch(Parameters params)
    : rnd_(1337), now_(0), r_(1), t_(2 * std::log(1.0 / (params.s * params.delta)) / params.eps) {}

void StickySamplingSketch::Add(const ElementType& elem) {
  ++now_;
  if (now_ == t_) {
    r_ <<= 1;
    t_ <<= 1;
    std::vector<ElementType> to_del;
    for (auto &[e, c] : cnt_) {
      while ((rnd_() & 1) && c) {
        --c;
      }
      if (!c) {
        to_del.push_back(e);
      }
    }
    for (auto i : to_del) {
      cnt_.erase(i);
    }
  }
  auto it = cnt_.find(elem);
  if (it != cnt_.end() || rnd_() % r_ == 0) {
    ++cnt_[elem];
  }
}

StickySamplingSketch::CounterType StickySamplingSketch::Estimate(const StickySamplingSketch::ElementType& elem) const {
  auto it = cnt_.find(elem);
  return (it == cnt_.end() ? 0 : cnt_.find(elem)->second);
}

}  // namespace sketch
