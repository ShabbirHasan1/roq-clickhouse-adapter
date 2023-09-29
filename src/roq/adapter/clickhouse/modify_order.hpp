/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct ModifyOrder final {
  using value_type = roq::ModifyOrder;

  static constexpr auto const table_name = []() {
    using namespace std::literals;
    return "modify_order"sv;
  }();

  ModifyOrder();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<std::string_view, true> account_;
  Column<uint64_t> order_id_;
  Column<std::string_view, true> request_template_;
  Column<double> quantity_;
  Column<double> price_;
  Column<std::string_view> routing_id_;
  Column<uint32_t> version_;
  Column<uint32_t> conditional_on_version_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
