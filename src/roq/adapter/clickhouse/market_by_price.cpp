/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/market_by_price.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

MarketByPrice::MarketByPrice()
    : stream_id_{"stream_id"sv}, exchange_{"exchange"}, symbol_{"symbol"sv}, update_type_{"update_type"sv},
      exchange_time_utc_{"exchange_time_utc"sv} {
}

std::string MarketByPrice::get_fields() const {
  return fmt::format(
      "{}, "    // stream_id
      "{}, "    // exchange
      "{}, "    // symbol
      "{}, "    // update_type
      "{}"_cf,  // exchange_time_utc
      stream_id_,
      exchange_,
      symbol_,
      update_type_,
      exchange_time_utc_);
}

size_t MarketByPrice::operator()(roq::MarketByPriceUpdate const &market_by_price_update) {
  stream_id_.append(market_by_price_update.stream_id);
  exchange_.append(market_by_price_update.exchange);
  symbol_.append(market_by_price_update.symbol);
  update_type_.append(market_by_price_update.update_type);
  exchange_time_utc_.append(market_by_price_update.exchange_time_utc);
  return 1;
}

void MarketByPrice::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  update_type_.append(block);
  exchange_time_utc_.append(block);
}

void MarketByPrice::clear() {
  stream_id_.clear();
  exchange_.clear();
  symbol_.clear();
  update_type_.clear();
  exchange_time_utc_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
