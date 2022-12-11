/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <clickhouse/client.h>

namespace roq {
namespace third_party {
namespace clickhouse {

using ::clickhouse::UInt128;

using ::clickhouse::Client;
using ::clickhouse::ClientOptions;

using ::clickhouse::Block;

using ::clickhouse::ColumnDateTime64;
using ::clickhouse::ColumnFloat64;
using ::clickhouse::ColumnString;
using ::clickhouse::ColumnUInt16;
using ::clickhouse::ColumnUInt32;
using ::clickhouse::ColumnUInt64;
using ::clickhouse::ColumnUInt8;
using ::clickhouse::ColumnUUID;

}  // namespace clickhouse
}  // namespace third_party
}  // namespace roq
