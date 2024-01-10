/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/position.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

Position::Position()
    : stream_id_{"stream_id"}, account_{"account"}, exchange_{"exchange"}, symbol_{"symbol"},
      external_account_{"external_account"}, long_quantity_{"long_quantity"}, short_quantity_{"short_quantity"},
      update_type_{"update_type"}, exchange_time_utc_{"exchange_time_utc"}, sending_time_utc_{"sending_time_utc"} {
}

std::string Position::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id
      "{}, "   // account
      "{}, "   // exchange
      "{}, "   // symbol
      "{}, "   // external_account
      "{}, "   // long_quantity
      "{}, "   // short_quantity
      "{}, "   // update_type
      "{}, "   // exchange_time_utc
      "{}"sv,  // sending_time_utc
      stream_id_,
      account_,
      exchange_,
      symbol_,
      external_account_,
      long_quantity_,
      short_quantity_,
      update_type_,
      exchange_time_utc_,
      sending_time_utc_);
}

size_t Position::operator()(roq::PositionUpdate const &position_update) {
  stream_id_.append(position_update.stream_id);
  account_.append(position_update.account);
  exchange_.append(position_update.exchange);
  symbol_.append(position_update.symbol);
  external_account_.append(position_update.external_account);
  long_quantity_.append(position_update.long_quantity);
  short_quantity_.append(position_update.short_quantity);
  update_type_.append(position_update.update_type);
  exchange_time_utc_.append(position_update.exchange_time_utc);
  sending_time_utc_.append(position_update.sending_time_utc);
  return 1;
}

void Position::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  account_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  external_account_.append(block);
  long_quantity_.append(block);
  short_quantity_.append(block);
  update_type_.append(block);
  exchange_time_utc_.append(block);
  sending_time_utc_.append(block);
}

void Position::clear() {
  stream_id_.clear();
  account_.clear();
  exchange_.clear();
  symbol_.clear();
  external_account_.clear();
  long_quantity_.clear();
  short_quantity_.clear();
  update_type_.clear();
  exchange_time_utc_.clear();
  sending_time_utc_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
