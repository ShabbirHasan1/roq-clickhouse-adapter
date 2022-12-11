/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct MarketStatus final {
  using value_type = roq::MarketStatus;

  static const constexpr auto table_name = []() {
    using namespace std::literals;
    return "market_status"sv;
  }();

  MarketStatus();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t> stream_id_;
  Column<std::string_view, true> exchange_;
  Column<std::string_view, true> symbol_;
  Column<TradingStatus, true> trading_status_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
