/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct Statistics final {
  using value_type = roq::StatisticsUpdate;

  static const constexpr auto table_name = []() {
    using namespace std::literals;
    return "statistics"sv;
  }();

  Statistics();

  std::string get_fields() const;
  std::string get_index_fields() const;

  void operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t> stream_id_;
  Column<std::string_view, true> exchange_;
  Column<std::string_view, true> symbol_;
  Column<StatisticsType, true> type_;
  Column<double> value_;
  Column<UpdateType, true> update_type_;
  Column<std::chrono::nanoseconds> exchange_time_utc_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
