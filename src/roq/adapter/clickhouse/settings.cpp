/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/settings.hpp"

#include "roq/logging.hpp"

#include "roq/adapter.hpp"

#include "roq/adapter/clickhouse/flags/flags.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

Settings::Settings(args::Parser const &args)
    : adapter::flags::Settings{args, ROQ_PACKAGE_NAME, ROQ_BUILD_NUMBER}, db_host{flags::Flags::db_host()},
      db_port{flags::Flags::db_port()}, database{flags::Flags::database()}, max_rows{flags::Flags::max_rows()} {
  log::info("settings={}"sv, *this);
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
