/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/trade_summary.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

TradeSummary::TradeSummary()
    : stream_id_{"stream_id"sv}, exchange_{"exchange"}, symbol_{"symbol"sv}, exchange_time_utc_{"exchange_time_utc"sv} {
}

std::string TradeSummary::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id
      "{}, "   // exchange
      "{}, "   // symbol
      "{}"sv,  // exchange_time_utc
      stream_id_,
      exchange_,
      symbol_,
      exchange_time_utc_);
}

std::string TradeSummary::get_index_fields() const {
  // return fmt::format(", {}"sv, type_.name());
  return {};
}

size_t TradeSummary::operator()(roq::TradeSummary const &top_of_book) {
  stream_id_.append(top_of_book.stream_id);
  exchange_.append(top_of_book.exchange);
  symbol_.append(top_of_book.symbol);
  exchange_time_utc_.append(top_of_book.exchange_time_utc);
  return 1;
}

void TradeSummary::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  exchange_time_utc_.append(block);
}

void TradeSummary::clear() {
  stream_id_.clear();
  exchange_.clear();
  symbol_.clear();
  exchange_time_utc_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
