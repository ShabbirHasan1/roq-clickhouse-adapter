/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct GatewayStatus final {
  using value_type = roq::GatewayStatus;

  static constexpr auto const table_name = []() {
    using namespace std::literals;
    return "gateway_status"sv;
  }();

  GatewayStatus();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<std::string_view, true> account_;
  Column<Mask<SupportType>> supported_;
  Column<Mask<SupportType>> available_;
  Column<Mask<SupportType>> unavailable_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
