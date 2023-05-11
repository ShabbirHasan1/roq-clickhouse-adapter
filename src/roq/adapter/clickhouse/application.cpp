/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/application.hpp"

#include "roq/logging.hpp"

#include "roq/adapter/clickhouse/controller.hpp"
#include "roq/adapter/clickhouse/settings.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

int Application::main(int argc, [[maybe_unused]] char **argv) {
  if (argc > 1)
    log::fatal("Connecting to gateway(s) not yet supported"sv);
  Settings settings;
  Controller{settings}.dispatch();
  return EXIT_SUCCESS;
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
