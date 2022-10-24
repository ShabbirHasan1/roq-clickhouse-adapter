/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/trade.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

Trade::Trade()
    : stream_id_{"stream_id"}, account_{"account"}, order_id_{"order_id"}, exchange_{"exchange"}, symbol_{"symbol"},
      side_{"side"}, position_effect_{"position_effect"}, create_time_utc_{"create_time_utc"},
      update_time_utc_{"update_time_utc"}, external_account_{"external_account"},
      external_order_id_{"external_order_id"}, routing_id_{"routing_id"}, update_type_{"update_type"} {
}

std::string Trade::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id
      "{}, "   // account
      "{}, "   // order_id
      "{}, "   // exchange
      "{}, "   // symbol
      "{}, "   // side
      "{}, "   // position_effect
      "{}, "   // create_time_utc
      "{}, "   // update_time_utc
      "{}, "   // external_account
      "{}, "   // external_order_id
      "{}, "   // routing_id
      "{}"sv,  // update_type
      stream_id_,
      account_,
      order_id_,
      exchange_,
      symbol_,
      side_,
      position_effect_,
      create_time_utc_,
      update_time_utc_,
      external_account_,
      external_order_id_,
      routing_id_,
      update_type_);
}

size_t Trade::operator()(roq::TradeUpdate const &trade_update) {
  stream_id_.append(trade_update.stream_id);
  account_.append(trade_update.account);
  order_id_.append(trade_update.order_id);
  exchange_.append(trade_update.exchange);
  symbol_.append(trade_update.symbol);
  side_.append(trade_update.side);
  position_effect_.append(trade_update.position_effect);
  create_time_utc_.append(trade_update.create_time_utc);
  update_time_utc_.append(trade_update.update_time_utc);
  external_account_.append(trade_update.external_account);
  external_order_id_.append(trade_update.external_order_id);
  routing_id_.append(trade_update.routing_id);
  update_type_.append(trade_update.update_type);
  return 1;
}

void Trade::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  account_.append(block);
  order_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  side_.append(block);
  position_effect_.append(block);
  create_time_utc_.append(block);
  update_time_utc_.append(block);
  external_account_.append(block);
  external_order_id_.append(block);
  routing_id_.append(block);
  update_type_.append(block);
}

void Trade::clear() {
  stream_id_.clear();
  account_.clear();
  order_id_.clear();
  exchange_.clear();
  symbol_.clear();
  side_.clear();
  position_effect_.clear();
  create_time_utc_.clear();
  update_time_utc_.clear();
  external_account_.clear();
  external_order_id_.clear();
  routing_id_.clear();
  update_type_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
