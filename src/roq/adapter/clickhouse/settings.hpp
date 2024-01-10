/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include <fmt/format.h>

#include "roq/adapter/flags/settings.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct Settings final : public adapter::flags::Settings {
  explicit Settings(args::Parser const &);

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
  constexpr auto parse(format_parse_context &context) { return std::begin(context); }
  auto format(roq::adapter::clickhouse::Settings const &value, format_context &context) const {
    using namespace std::literals;
    return fmt::format_to(
        context.out(),
        R"({{)"
        R"(db_host="{}", )"
        R"(db_port={}, )"
        R"(database="{}", )"
        R"(max_rows={}, )"
        R"(adapter={})"
        R"(}})"sv,
        value.db_host,
        value.db_port,
        value.database,
        value.max_rows,
        static_cast<roq::adapter::Settings const &>(value));
  }
};
