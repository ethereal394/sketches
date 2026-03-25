#include "misra_gries.h"

namespace sketch {

MisraGriesSketch::MisraGriesSketch(Parameters params) {
  k_ = params.memory_limit_bytes / (sizeof(ElementType) + sizeof(CounterType));
}

void MisraGriesSketch::Append(const ElementType& value) {
  if (count_.contains(value)) {
    ++count_[value];
    return;
  }
  if (count_.size() < k_) {
    count_[value] = 1;
  } else {
    std::vector<ElementType> del;
    for (auto& [e, c] : count_) {
      --c;
      if (c == 0) {
        del.push_back(e);
      }
    }
    for (auto i : del) {
      count_.erase(i);
    }
  }
}

std::unordered_map<MisraGriesSketch::ElementType, MisraGriesSketch::CounterType> MisraGriesSketch::Candidates() const {
  return count_;
}

MisraGriesSketch::CounterType MisraGriesSketch::Estimate(const ElementType& value) {
  if (count_.contains(value)) {
    return count_[value];
  }
  return 0;
}

}  // namespace sketch
