/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct OrderAck final {
  using value_type = roq::OrderAck;

  static constexpr auto const table_name = []() {
    using namespace std::literals;
    return "order_ack"sv;
  }();

  OrderAck();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t> stream_id_;
  Column<std::string_view, true> account_;
  Column<uint64_t> order_id_;
  Column<std::string_view, true> exchange_;
  Column<std::string_view, true> symbol_;
  Column<Side, true> side_;
  Column<RequestType, true> type_;
  Column<Origin, true> origin_;
  Column<RequestStatus, true> status_;
  Column<Error, true> error_;
  Column<std::string_view> text_;
  Column<std::string_view> request_id_;
  Column<std::string_view, true> external_account_;
  Column<std::string_view> external_order_id_;
  Column<std::string_view> routing_id_;
  Column<uint32_t> version_;
  Column<std::chrono::nanoseconds> round_trip_latency_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
