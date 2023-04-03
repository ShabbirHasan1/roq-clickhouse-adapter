/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/cancel_order.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

CancelOrder::CancelOrder()
    : account_{"account"}, order_id_{"order_id"}, request_template_{"request_template"}, routing_id_{"routing_id"},
      version_{"version"}, conditional_on_version_{"conditional_on_version"} {
}

std::string CancelOrder::get_fields() const {
  return fmt::format(
      "{}, "    // account
      "{}, "    // order_id
      "{}, "    // request_template
      "{}, "    // routing_id
      "{}, "    // version
      "{}"_cf,  // conditional_on_version
      account_,
      order_id_,
      request_template_,
      routing_id_,
      version_,
      conditional_on_version_);
}

size_t CancelOrder::operator()(roq::CancelOrder const &cancel_order) {
  account_.append(cancel_order.account);
  order_id_.append(cancel_order.order_id);
  request_template_.append(cancel_order.request_template);
  routing_id_.append(cancel_order.routing_id);
  version_.append(cancel_order.version);
  conditional_on_version_.append(cancel_order.conditional_on_version);
  return 1;
}

void CancelOrder::append(third_party::clickhouse::Block &block) {
  account_.append(block);
  order_id_.append(block);
  request_template_.append(block);
  routing_id_.append(block);
  version_.append(block);
  conditional_on_version_.append(block);
}

void CancelOrder::clear() {
  account_.clear();
  order_id_.clear();
  request_template_.clear();
  routing_id_.clear();
  version_.clear();
  conditional_on_version_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
