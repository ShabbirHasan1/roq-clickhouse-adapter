/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/modify_order.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

ModifyOrder::ModifyOrder()
    : account_{"account"}, order_id_{"order_id"}, request_template_{"request_template"}, quantity_{"quantity"},
      price_{"price"}, routing_id_{"routing_id"}, version_{"version"}, conditional_on_version_{
                                                                           "conditional_on_version"} {
}

std::string ModifyOrder::get_fields() const {
  return fmt::format(
      "{}, "    // account
      "{}, "    // order_id
      "{}, "    // request_template
      "{}, "    // quantity
      "{}, "    // price
      "{}, "    // routing_id
      "{}, "    // version
      "{}"_cf,  // conditional_on_version
      account_,
      order_id_,
      request_template_,
      quantity_,
      price_,
      routing_id_,
      version_,
      conditional_on_version_);
}

size_t ModifyOrder::operator()(roq::ModifyOrder const &modify_order) {
  account_.append(modify_order.account);
  order_id_.append(modify_order.order_id);
  request_template_.append(modify_order.request_template);
  quantity_.append(modify_order.quantity);
  price_.append(modify_order.price);
  routing_id_.append(modify_order.routing_id);
  version_.append(modify_order.version);
  conditional_on_version_.append(modify_order.conditional_on_version);
  return 1;
}

void ModifyOrder::append(third_party::clickhouse::Block &block) {
  account_.append(block);
  order_id_.append(block);
  request_template_.append(block);
  quantity_.append(block);
  price_.append(block);
  routing_id_.append(block);
  version_.append(block);
  conditional_on_version_.append(block);
}

void ModifyOrder::clear() {
  account_.clear();
  order_id_.clear();
  request_template_.clear();
  quantity_.clear();
  price_.clear();
  routing_id_.clear();
  version_.clear();
  conditional_on_version_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
