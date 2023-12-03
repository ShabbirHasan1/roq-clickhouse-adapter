/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/statistics.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

Statistics::Statistics()
    : stream_id_{"stream_id"sv}, exchange_{"exchange"}, symbol_{"symbol"sv}, type_{"type"sv}, value_{"value"sv},
      update_type_{"update_type"sv}, exchange_time_utc_{"exchange_time_utc"sv} {
}

std::string Statistics::get_fields() const {
  return fmt::format(
      "{}, "    // stream_id
      "{}, "    // exchange
      "{}, "    // symbol
      "{}, "    // type
      "{}, "    // value
      "{}, "    // update_type
      "{}"_cf,  // exchange_time_utc
      stream_id_,
      exchange_,
      symbol_,
      type_,
      value_,
      update_type_,
      exchange_time_utc_);
}

std::string Statistics::get_index_fields() const {
  return fmt::format(", {}"_cf, type_.name());
}

size_t Statistics::operator()(roq::StatisticsUpdate const &statistics_update) {
  for (auto &item : statistics_update.statistics) {
    stream_id_.append(statistics_update.stream_id);
    exchange_.append(statistics_update.exchange);
    symbol_.append(statistics_update.symbol);
    type_.append(item.type);
    value_.append(item.value);
    update_type_.append(statistics_update.update_type);
    exchange_time_utc_.append(statistics_update.exchange_time_utc);
  }
  return std::size(statistics_update.statistics);
}

void Statistics::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  type_.append(block);
  value_.append(block);
  update_type_.append(block);
  exchange_time_utc_.append(block);
}

void Statistics::clear() {
  stream_id_.clear();
  exchange_.clear();
  symbol_.clear();
  type_.clear();
  value_.clear();
  update_type_.clear();
  exchange_time_utc_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
