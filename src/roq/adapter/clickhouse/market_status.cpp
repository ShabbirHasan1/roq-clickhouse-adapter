/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/market_status.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

MarketStatus::MarketStatus()
    : stream_id_("stream_id"sv), exchange_("exchange"), symbol_("symbol"sv), trading_status_("trading_status"sv) {
}

std::string MarketStatus::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id
      "{}, "   // exchange
      "{}, "   // symbol
      "{}"sv,  // trading_status
      stream_id_,
      exchange_,
      symbol_,
      trading_status_);
}

void MarketStatus::operator()(roq::MarketStatus const &market_status) {
  stream_id_.append(market_status.stream_id);
  exchange_.append(market_status.exchange);
  symbol_.append(market_status.symbol);
  trading_status_.append(market_status.trading_status);
}

void MarketStatus::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  trading_status_.append(block);
}

void MarketStatus::clear() {
  stream_id_.clear();
  exchange_.clear();
  symbol_.clear();
  trading_status_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
