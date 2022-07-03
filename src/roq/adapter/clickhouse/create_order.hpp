/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct CreateOrder final {
  using value_type = roq::CreateOrder;

  static const constexpr auto table_name = []() {
    using namespace std::literals;
    return "create_order"sv;
  }();

  CreateOrder();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
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
  Column<std::string_view, true> order_template_;
  Column<double> quantity_;
  Column<double> price_;
  Column<double> stop_price_;
  Column<std::string_view> routing_id_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
