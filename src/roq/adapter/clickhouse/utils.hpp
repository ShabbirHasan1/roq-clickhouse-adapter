/* Copyright (c) 2017-2024, Hans Erik Thrane */

#pragma once

#include "roq/third_party/clickhouse/client.hpp"

#include "roq/api.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

inline auto to_uint128(const UUID &value) {
  auto tmp = static_cast<absl::uint128>(value);
  return third_party::clickhouse::UInt128{absl::Uint128High64(tmp), absl::Uint128Low64(tmp)};
}

inline UUID from_uint128(third_party::clickhouse::UInt128 const &value) {
  return UUID{value.first, value.second};
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
