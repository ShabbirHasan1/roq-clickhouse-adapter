/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/position.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

Position::Position()
    : stream_id_{"stream_id"}, account_{"account"}, exchange_{"exchange"}, symbol_{"symbol"},
      external_account_{"external_account"}, long_quantity_{"long_quantity"}, short_quantity_{"short_quantity"},
      long_quantity_begin_{"long_quantity_begin"}, short_quantity_begin_{"short_quantity_begin"} {
}

std::string Position::get_fields() const {
  return fmt::format(
      "{}, "    // stream_id
      "{}, "    // account
      "{}, "    // exchange
      "{}, "    // symbol
      "{}, "    // external_account
      "{}, "    // long_quantity
      "{}, "    // short_quantity
      "{}, "    // long_quantity_begin
      "{}"_cf,  // short_quantity_begin
      stream_id_,
      account_,
      exchange_,
      symbol_,
      external_account_,
      long_quantity_,
      short_quantity_,
      long_quantity_begin_,
      short_quantity_begin_);
}

size_t Position::operator()(roq::PositionUpdate const &position_update) {
  stream_id_.append(position_update.stream_id);
  account_.append(position_update.account);
  exchange_.append(position_update.exchange);
  symbol_.append(position_update.symbol);
  external_account_.append(position_update.external_account);
  long_quantity_.append(position_update.long_quantity);
  short_quantity_.append(position_update.short_quantity);
  long_quantity_begin_.append(position_update.long_quantity_begin);
  short_quantity_begin_.append(position_update.short_quantity_begin);
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
  long_quantity_begin_.append(block);
  short_quantity_begin_.append(block);
}

void Position::clear() {
  stream_id_.clear();
  account_.clear();
  exchange_.clear();
  symbol_.clear();
  external_account_.clear();
  long_quantity_.clear();
  short_quantity_.clear();
  long_quantity_begin_.clear();
  short_quantity_begin_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
