/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/table.hpp"

#include "roq/logging.hpp"

using namespace std::literals;
using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === HELPERS ===

namespace detail {
std::string create_table_name(Settings const &settings, std::string_view const &table_name) {
  return fmt::format("{}.{}"_cf, settings.database, table_name);  // prefix database name
}

bool is_full(Settings const &settings, size_t rows) {
  return settings.max_rows <= rows;
}

// note!
// this strategy is based on keeping tables relatively in sync
// we don't want to flush all the time so we allow for some slack and only
// force table flush when its last update is far away from current update
bool sync(Settings const &settings, size_t last_update, size_t current) {
  if (!last_update)
    return false;
  if (current < last_update)  // overflow
    return true;
  constexpr size_t factor = 1;
  return (settings.max_rows * factor) <= (current - last_update);
}
}  // namespace detail

// === IMPLEMENTATION ===

detail::Common::Common()
    : gateway_{"gateway"sv}, session_id_{"session_id"sv}, seqno_{"seqno"sv}, source_{"source"sv},
      receive_time_utc_{"receive_time_utc"sv}, origin_create_time_utc_{"origin_create_time_utc"sv} {
}

void detail::Common::create_table(
    third_party::clickhouse::Client &client,
    std::string_view const &table_name,
    std::string_view const &extra_fields,
    std::string_view const &extra_index_fields) {
  log::debug("table_name={}"sv, table_name);
  log::debug("extra_fields={}"sv, extra_fields);
  log::debug("extra_index_fields={}"sv, extra_index_fields);
  auto query = fmt::format(
      "CREATE TABLE IF NOT EXISTS {} ("  // table_name
      "{}, "                             // gateway
      "{}, "                             // session_id
      "{}, "                             // seqno
      "{}, "                             // source
      "{}, "                             // receive_time_utc
      "{}, "                             // origin_create_time_utc
      "{}"                               // extra_fields
      ") "
      "ENGINE=ReplacingMergeTree() "
      "PARTITION BY toYearWeek({}) "  // receive_time_utc
      "ORDER BY ("
      "{}, "           // session_id
      "intHash64({})"  // seqno
      "{}"             // extra_index_fields
      ")"_cf,
      table_name,
      gateway_,
      session_id_,
      seqno_,
      source_,
      receive_time_utc_,
      origin_create_time_utc_,
      extra_fields,
      receive_time_utc_.name(),
      session_id_.name(),
      seqno_.name(),
      extra_index_fields);
  log::info<1>(R"(query="{}")"sv, query);
  client.Execute(query);
}

void detail::Common::clear() {
  gateway_.clear();
  session_id_.clear();
  seqno_.clear();
  source_.clear();
  receive_time_utc_.clear();
  origin_create_time_utc_.clear();
}

void detail::Common::operator()(roq::MessageInfo const &message_info, std::string_view const &gateway, size_t rows) {
  for (size_t i = 0; i < rows; ++i) {
    gateway_.append(gateway);
    session_id_.append(message_info.source_session_id);
    seqno_.append(message_info.source_seqno);
    source_.append(message_info.source_name);
    receive_time_utc_.append(message_info.receive_time_utc);
    origin_create_time_utc_.append(message_info.origin_create_time_utc);
  }
}

void detail::Common::append(third_party::clickhouse::Block &block) {
  gateway_.append(block);
  session_id_.append(block);
  seqno_.append(block);
  source_.append(block);
  receive_time_utc_.append(block);
  origin_create_time_utc_.append(block);
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
