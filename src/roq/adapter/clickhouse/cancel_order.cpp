/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/cancel_order.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

CancelOrder::CancelOrder()
    : account_{"account"}, order_id_{"order_id"}, routing_id_{"routing_id"}, version_{"version"},
      conditional_on_version_{"conditional_on_version"} {
}

std::string CancelOrder::get_fields() const {
  return fmt::format(
      "{}, "   // account
      "{}, "   // order_id
      "{}, "   // routing_id
      "{}, "   // version
      "{}"sv,  // conditional_on_version
      account_,
      order_id_,
      routing_id_,
      version_,
      conditional_on_version_);
}

size_t CancelOrder::operator()(roq::CancelOrder const &create_order) {
  account_.append(create_order.account);
  order_id_.append(create_order.order_id);
  routing_id_.append(create_order.routing_id);
  version_.append(create_order.version);
  conditional_on_version_.append(create_order.conditional_on_version);
  return 1;
}

void CancelOrder::append(third_party::clickhouse::Block &block) {
  account_.append(block);
  order_id_.append(block);
  routing_id_.append(block);
  version_.append(block);
  conditional_on_version_.append(block);
}

void CancelOrder::clear() {
  account_.clear();
  order_id_.clear();
  routing_id_.clear();
  version_.clear();
  conditional_on_version_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
