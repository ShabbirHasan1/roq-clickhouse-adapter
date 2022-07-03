/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct Trade final {
  using value_type = roq::TradeUpdate;

  static const constexpr auto table_name = []() {
    using namespace std::literals;
    return "trade"sv;
  }();

  Trade();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t> stream_id_;
  Column<std::string_view, true> account_;
  Column<uint32_t> order_id_;
  Column<std::string_view, true> exchange_;
  Column<std::string_view, true> symbol_;
  Column<Side, true> side_;
  Column<PositionEffect, true> position_effect_;
  Column<std::chrono::nanoseconds> create_time_utc_;
  Column<std::chrono::nanoseconds> update_time_utc_;
  Column<std::string_view, true> external_account_;
  Column<std::string_view> external_order_id_;
  Column<std::string_view> routing_id_;
  Column<UpdateType, true> update_type_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
