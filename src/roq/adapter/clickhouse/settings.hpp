/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <fmt/compile.h>
#include <fmt/format.h>

#include "roq/adapter/settings.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct Settings final : public adapter::Settings {
  Settings();

  std::string_view const db_host;
  uint16_t const db_port = {};
  std::string_view const database;
  uint32_t const max_rows = {};
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq

template <>
struct fmt::formatter<roq::adapter::clickhouse::Settings> {
  template <typename Context>
  constexpr auto parse(Context &context) {
    return std::begin(context);
  }
  template <typename Context>
  auto format(roq::adapter::clickhouse::Settings const &value, Context &context) const {
    using namespace fmt::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(db_host="{}", )"
        R"(db_port={}, )"
        R"(database="{}", )"
        R"(max_rows={}, )"
        R"(adapter={})"
        R"(}})"_cf,
        value.db_host,
        value.db_port,
        value.database,
        value.max_rows,
        static_cast<roq::adapter::Settings const &>(value));
  }
};
