/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct Order final {
  using value_type = roq::OrderUpdate;

  static const constexpr auto table_name = []() {
    using namespace std::literals;
    return "order"sv;
  }();

  Order();

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
  Column<double> max_show_quantity_;
  Column<OrderType, true> order_type_;
  Column<TimeInForce, true> time_in_force_;
  Column<Mask<ExecutionInstruction>> execution_instructions_;
  Column<std::string_view> order_template_;
  Column<std::chrono::nanoseconds> create_time_utc_;
  Column<std::chrono::nanoseconds> update_time_utc_;
  Column<std::string_view, true> external_account_;
  Column<std::string_view> external_order_id_;
  Column<OrderStatus, true> status_;
  Column<double> quantity_;
  Column<double> price_;
  Column<double> stop_price_;
  Column<double> remaining_quantity_;
  Column<double> traded_quantity_;
  Column<double> average_traded_price_;
  Column<double> last_traded_quantity_;
  Column<double> last_traded_price_;
  Column<Liquidity, true> last_liquidity_;
  Column<std::string_view> routing_id_;
  Column<uint32_t> max_request_version_;
  Column<uint32_t> max_response_version_;
  Column<uint32_t> max_accepted_version_;
  Column<UpdateType, true> update_type_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
