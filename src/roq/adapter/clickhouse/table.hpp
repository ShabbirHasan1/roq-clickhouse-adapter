/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <string>
#include <string_view>

#include "roq/third_party/clickhouse/client.hpp"

#include "roq/adapter/clickhouse/columns.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

namespace detail {
extern std::string create_table_name(std::string_view const &table_name);
extern bool is_full(size_t rows);
extern bool sync(size_t last_update, size_t current);

struct Common {
  Common();

  void clear();

  void create_table(
      third_party::clickhouse::Client &,
      std::string_view const &table_name,
      std::string_view const &extra_fields,
      std::string_view const &extra_index_fields);

  void operator()(roq::MessageInfo const &, std::string_view const &gateway, size_t rows);

  void append(third_party::clickhouse::Block &);

 private:
  Column<std::string_view, true> gateway_;
  Column<UUID> session_id_;
  Column<uint64_t> seqno_;
  Column<std::string_view, true> source_;
  Column<std::chrono::nanoseconds> receive_time_utc_;
  Column<std::chrono::nanoseconds> origin_create_time_utc_;
};
}  // namespace detail

template <typename T>
struct Table {
  Table() : table_name_(detail::create_table_name(T::table_name)) {}

  void create_table(third_party::clickhouse::Client &client) {
    common_.create_table(client, table_name_, table_.get_fields(), table_.get_index_fields());
  }

  bool operator()(Event<typename T::value_type> const &event, std::string_view const &gateway, size_t counter) {
    auto &[message_info, value] = event;
    auto rows = table_(value);
    common_(message_info, gateway, rows);
    counter_ = counter;
    rows_ += rows;
    return detail::is_full(rows_);
  }

  void flush(third_party::clickhouse::Client &client, uint64_t counter, bool force = false) {
    if (force || detail::is_full(rows_) || detail::sync(counter_, counter)) {
      third_party::clickhouse::Block block;
      common_.append(block);
      table_.append(block);
      client.Insert(table_name_, block);
      common_.clear();
      table_.clear();
      rows_ = {};
      counter_ = {};
    }
  }

 private:
  const std::string table_name_;
  detail::Common common_;
  T table_;
  size_t rows_ = {};
  size_t counter_ = {};
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
