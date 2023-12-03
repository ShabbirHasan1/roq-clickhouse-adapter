/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct StreamStatus final {
  using value_type = roq::StreamStatus;

  static constexpr auto const table_name = []() {
    using namespace std::literals;
    return "stream_status"sv;
  }();

  StreamStatus();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t> stream_id_;
  Column<std::string_view, true> account_;
  Column<Mask<SupportType>> supports_;
  Column<Transport, true> transport_;
  Column<Protocol, true> protocol_;
  Column<Mask<Encoding>> encoding_;
  Column<Priority, true> priority_;
  Column<ConnectionStatus, true> connection_status_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
