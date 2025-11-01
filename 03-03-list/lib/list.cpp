#include <ostream>

#include "list.hpp"

namespace dts {

void List::show(std::ostream &os) const {
    if (empty()) {
        os << "[]";
        return;
    }

    os << '[';
    for (auto *node = head_; node != tail_; node = node->next) {
        os << node->value << ", ";
    }
    os << tail_->value << ']';
}

} // namespace dts
