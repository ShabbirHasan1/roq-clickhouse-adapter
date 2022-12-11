/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string_view>

namespace roq {
namespace adapter {
namespace clickhouse {
namespace flags {

struct Flags final {
  static std::string_view db_host();
  static uint16_t db_port();
  static std::string_view database();
  static uint32_t max_rows();
};

}  // namespace flags
}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
