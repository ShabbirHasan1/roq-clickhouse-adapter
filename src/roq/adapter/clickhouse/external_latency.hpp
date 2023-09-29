/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct ExternalLatency final {
  using value_type = roq::ExternalLatency;

  static constexpr auto const table_name = []() {
    using namespace std::literals;
    return "external_latency"sv;
  }();

  ExternalLatency();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t> stream_id_;
  Column<std::string_view, true> account_;
  Column<std::chrono::nanoseconds> latency_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
