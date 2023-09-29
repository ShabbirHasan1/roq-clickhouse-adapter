/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct CustomMetrics final {
  using value_type = roq::CustomMetricsUpdate;

  static constexpr auto const table_name = []() {
    using namespace std::literals;
    return "custom_metrics"sv;
  }();

  CustomMetrics();

  std::string get_fields() const;
  std::string get_index_fields() const;

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<std::string_view, true> user_;
  Column<std::string_view, true> label_;
  Column<std::string_view, true> account_;
  Column<std::string_view, true> exchange_;
  Column<std::string_view, true> symbol_;
  Column<std::string_view, true> name_;
  Column<double> value_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
