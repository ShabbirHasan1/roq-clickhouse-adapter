/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/create_order.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

CreateOrder::CreateOrder()
    : account_{"account"}, order_id_{"order_id"}, exchange_{"exchange"}, symbol_{"symbol"}, side_{"side"},
      position_effect_{"position_effect"}, max_show_quantity_{"max_show_quantity"}, order_type_{"order_type"},
      time_in_force_{"time_in_force"}, execution_instructions_{"execution_instructions"},
      order_template_{"order_template"}, quantity_{"quantity"}, price_{"price"}, stop_price_{"stop_price"},
      routing_id_{"routing_id"} {
}

std::string CreateOrder::get_fields() const {
  return fmt::format(
      "{}, "    // account
      "{}, "    // order_id
      "{}, "    // exchange
      "{}, "    // symbol
      "{}, "    // side
      "{}, "    // position_effect
      "{}, "    // max_show_quantity
      "{}, "    // order_type
      "{}, "    // time_in_force
      "{}, "    // execution_instructions
      "{}, "    // order_template
      "{}, "    // quantity
      "{}, "    // price
      "{}, "    // stop_price
      "{}"_cf,  // routing_id
      account_,
      order_id_,
      exchange_,
      symbol_,
      side_,
      position_effect_,
      max_show_quantity_,
      order_type_,
      time_in_force_,
      execution_instructions_,
      order_template_,
      quantity_,
      price_,
      stop_price_,
      routing_id_);
}

size_t CreateOrder::operator()(roq::CreateOrder const &create_order) {
  account_.append(create_order.account);
  order_id_.append(create_order.order_id);
  exchange_.append(create_order.exchange);
  symbol_.append(create_order.symbol);
  side_.append(create_order.side);
  position_effect_.append(create_order.position_effect);
  max_show_quantity_.append(create_order.max_show_quantity);
  order_type_.append(create_order.order_type);
  time_in_force_.append(create_order.time_in_force);
  execution_instructions_.append(create_order.execution_instructions);
  order_template_.append(create_order.order_template);
  quantity_.append(create_order.quantity);
  price_.append(create_order.price);
  stop_price_.append(create_order.stop_price);
  routing_id_.append(create_order.routing_id);
  return 1;
}

void CreateOrder::append(third_party::clickhouse::Block &block) {
  account_.append(block);
  order_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  side_.append(block);
  position_effect_.append(block);
  max_show_quantity_.append(block);
  order_type_.append(block);
  time_in_force_.append(block);
  execution_instructions_.append(block);
  order_template_.append(block);
  quantity_.append(block);
  price_.append(block);
  stop_price_.append(block);
  routing_id_.append(block);
}

void CreateOrder::clear() {
  account_.clear();
  order_id_.clear();
  exchange_.clear();
  symbol_.clear();
  side_.clear();
  position_effect_.clear();
  max_show_quantity_.clear();
  order_type_.clear();
  time_in_force_.clear();
  execution_instructions_.clear();
  order_template_.clear();
  quantity_.clear();
  price_.clear();
  stop_price_.clear();
  routing_id_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
