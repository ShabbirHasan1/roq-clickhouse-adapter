/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/order.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

Order::Order()
    : stream_id_("stream_id"), account_("account"), order_id_("order_id"), exchange_("exchange"), symbol_("symbol"),
      side_("side"), position_effect_("position_effect"), max_show_quantity_("max_show_quantity"),
      order_type_("order_type"), time_in_force_("time_in_force"), execution_instructions_("execution_instructions"),
      order_template_("order_template"), create_time_utc_("create_time_utc"), update_time_utc_("update_time_utc"),
      external_account_("external_account"), external_order_id_("external_order_id"), status_("status"),
      quantity_("quantity"), price_("price"), stop_price_("stop_price"), remaining_quantity_("remaining_quantity"),
      traded_quantity_("traded_quantity"), average_traded_price_("average_traded_price"),
      last_traded_quantity_("last_traded_quantity"), last_traded_price_("last_traded_price"),
      last_liquidity_("last_liquidity"), routing_id_("routing_id"), max_request_version_("max_request_version"),
      max_response_version_("max_response_version"), max_accepted_version_("max_accepted_version"),
      update_type_("update_type") {
}

std::string Order::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id
      "{}, "   // account
      "{}, "   // order_id
      "{}, "   // exchange
      "{}, "   // symbol
      "{}, "   // side
      "{}, "   // position_effect
      "{}, "   // max_show_quantity
      "{}, "   // order_type
      "{}, "   // time_in_force
      "{}, "   // execution_instructions
      "{}, "   // order_template
      "{}, "   // create_time_utc
      "{}, "   // update_time_utc
      "{}, "   // external_account
      "{}, "   // external_order_id
      "{}, "   // status
      "{}, "   // quantity
      "{}, "   // price
      "{}, "   // stop_price
      "{}, "   // remaining_quantity
      "{}, "   // traded_quantity
      "{}, "   // average_traded_price
      "{}, "   // last_traded_quantity
      "{}, "   // last_traded_price
      "{}, "   // last_liquidity
      "{}, "   // routing_id
      "{}, "   // max_request_version
      "{}, "   // max_response_version
      "{}, "   // max_accepted_version
      "{}"sv,  // update_type
      stream_id_,
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
      create_time_utc_,
      update_time_utc_,
      external_account_,
      external_order_id_,
      status_,
      quantity_,
      price_,
      stop_price_,
      remaining_quantity_,
      traded_quantity_,
      average_traded_price_,
      last_traded_quantity_,
      last_traded_price_,
      last_liquidity_,
      routing_id_,
      max_request_version_,
      max_response_version_,
      max_accepted_version_,
      update_type_);
}

void Order::operator()(roq::OrderUpdate const &order_update) {
  stream_id_.append(order_update.stream_id);
  account_.append(order_update.account);
  order_id_.append(order_update.order_id);
  exchange_.append(order_update.exchange);
  symbol_.append(order_update.symbol);
  side_.append(order_update.side);
  position_effect_.append(order_update.position_effect);
  max_show_quantity_.append(order_update.max_show_quantity);
  order_type_.append(order_update.order_type);
  time_in_force_.append(order_update.time_in_force);
  execution_instructions_.append(order_update.execution_instructions);
  order_template_.append(order_update.order_template);
  create_time_utc_.append(order_update.create_time_utc);
  update_time_utc_.append(order_update.update_time_utc);
  external_account_.append(order_update.external_account);
  external_order_id_.append(order_update.external_order_id);
  status_.append(order_update.status);
  quantity_.append(order_update.quantity);
  price_.append(order_update.price);
  stop_price_.append(order_update.stop_price);
  remaining_quantity_.append(order_update.remaining_quantity);
  traded_quantity_.append(order_update.traded_quantity);
  average_traded_price_.append(order_update.average_traded_price);
  last_traded_quantity_.append(order_update.last_traded_quantity);
  last_traded_price_.append(order_update.last_traded_price);
  last_liquidity_.append(order_update.last_liquidity);
  routing_id_.append(order_update.routing_id);
  max_request_version_.append(order_update.max_request_version);
  max_response_version_.append(order_update.max_response_version);
  max_accepted_version_.append(order_update.max_accepted_version);
  update_type_.append(order_update.update_type);
}

void Order::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
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
  create_time_utc_.append(block);
  update_time_utc_.append(block);
  external_account_.append(block);
  external_order_id_.append(block);
  status_.append(block);
  quantity_.append(block);
  price_.append(block);
  stop_price_.append(block);
  remaining_quantity_.append(block);
  traded_quantity_.append(block);
  average_traded_price_.append(block);
  last_traded_quantity_.append(block);
  last_traded_price_.append(block);
  last_liquidity_.append(block);
  routing_id_.append(block);
  max_request_version_.append(block);
  max_response_version_.append(block);
  max_accepted_version_.append(block);
  update_type_.append(block);
}

void Order::clear() {
  stream_id_.clear();
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
  create_time_utc_.clear();
  update_time_utc_.clear();
  external_account_.clear();
  external_order_id_.clear();
  status_.clear();
  quantity_.clear();
  price_.clear();
  stop_price_.clear();
  remaining_quantity_.clear();
  traded_quantity_.clear();
  average_traded_price_.clear();
  last_traded_quantity_.clear();
  last_traded_price_.clear();
  last_liquidity_.clear();
  routing_id_.clear();
  max_request_version_.clear();
  max_response_version_.clear();
  max_accepted_version_.clear();
  update_type_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
