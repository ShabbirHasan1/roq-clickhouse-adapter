/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct MarketByPrice final {
  using value_type = roq::MarketByPriceUpdate;

  static constexpr auto const table_name = []() {
    using namespace std::literals;
    return "market_by_price"sv;
  }();

  MarketByPrice();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t> stream_id_;
  Column<std::string_view, true> exchange_;
  Column<std::string_view, true> symbol_;
  // bids
  // asks
  Column<UpdateType, true> update_type_;
  Column<std::chrono::nanoseconds> exchange_time_utc_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
