/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <magic_enum.hpp>

#include "roq/adapter/clickhouse/utils.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

namespace detail {
template <typename T, bool low_cardinality, typename = void>
struct Meta;

// enum

template <typename T>
struct Meta<T, true, typename std::enable_if<std::is_enum<T>::value>::type> final {
  using value_type = T;
  using column_type = third_party::clickhouse::ColumnString;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "LowCardinality(String)"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return magic_enum::enum_name(value); }
};

// Mask<enum>

template <typename T>
struct Meta<Mask<T>, false> final {
  using value_type = Mask<T>;
  using column_type = third_party::clickhouse::ColumnUInt64;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "UInt64"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return static_cast<std::underlying_type<value_type>::type>(value.get()); }
};

// bool

template <>
struct Meta<bool, false> final {
  using value_type = bool;
  // note!
  // the clickhouse-cpp library does not support boolean columns
  using column_type = third_party::clickhouse::ColumnUInt8;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "Boolean"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return value ? 1 : 0; }
};

// uint16_t

template <>
struct Meta<uint16_t, false> final {
  using value_type = uint16_t;
  using column_type = third_party::clickhouse::ColumnUInt16;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "UInt16"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return value; }
};

template <>
struct Meta<uint16_t, true> final {
  using value_type = uint16_t;
  using column_type = third_party::clickhouse::ColumnUInt16;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    // note!
    // the database will reject "LowCardinality(UInt16)" for performance reasons
    return "UInt16"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return value; }
};

// uint32_t

template <>
struct Meta<uint32_t, false> final {
  using value_type = uint32_t;
  using column_type = third_party::clickhouse::ColumnUInt32;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "UInt32"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return value; }
};

// uint64_t

template <>
struct Meta<uint64_t, false> final {
  using value_type = uint64_t;
  using column_type = third_party::clickhouse::ColumnUInt64;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "UInt64"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return value; }
};

// double

template <>
struct Meta<double, false> final {
  using value_type = double;
  using column_type = third_party::clickhouse::ColumnFloat64;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "Float64 DEFAULT toFloat64(nan)"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type value) { return value; }
};

// std::chrono::nanoseconds

template <>
struct Meta<std::chrono::nanoseconds, false> final {
  using value_type = std::chrono::nanoseconds;
  using column_type = third_party::clickhouse::ColumnDateTime64;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "DateTime(9)"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(9); }
  static auto to_value(value_type value) {
    using namespace std::chrono_literals;
    constexpr value_type upper_limit = 4291707599s;  // 2105-12-31 23:59:59
    constexpr value_type lower_limit = 0s;           // 1970-01-01 00:00:00
    auto tmp = std::max(std::min(value, upper_limit), lower_limit);
    return std::time_t{std::chrono::duration_cast<value_type>(tmp).count()};
  }
};

// std::chrono::seconds

template <>
struct Meta<std::chrono::seconds, false> final {
  using value_type = std::chrono::seconds;
  using column_type = third_party::clickhouse::ColumnDateTime64;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "DateTime64(0)"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(0); }
  static auto to_value(value_type value) {
    using namespace std::chrono_literals;
    constexpr value_type upper_limit = 4291707599s;  // 2105-12-31 23:59:59
    constexpr value_type lower_limit = 0s;           // 1970-01-01 00:00:00
    auto tmp = std::max(std::min(value, upper_limit), lower_limit);
    return std::time_t{std::chrono::duration_cast<value_type>(tmp).count()};
  }
};

// std::chrono::days

template <>
struct Meta<std::chrono::days, false> final {
  using value_type = std::chrono::seconds;
  using column_type = third_party::clickhouse::ColumnDateTime64;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "DateTime64(0)"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(0); }
  static auto to_value(value_type value) {
    using namespace std::chrono_literals;
    constexpr value_type upper_limit = 4291707599s;  // 2105-12-31 23:59:59
    constexpr value_type lower_limit = 0s;           // 1970-01-01 00:00:00
    auto tmp = std::max(std::min(value, upper_limit), lower_limit);
    return std::time_t{std::chrono::duration_cast<value_type>(tmp).count()};
  }
};

// std::string_view

template <>
struct Meta<std::string_view, false> final {
  using value_type = std::string_view;
  using column_type = third_party::clickhouse::ColumnString;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "String"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type const &value) { return value; }
};

template <>
struct Meta<std::string_view, true> final {
  using value_type = std::string_view;
  using column_type = third_party::clickhouse::ColumnString;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "LowCardinality(String)"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type const &value) { return value; }
};

// UUID

template <>
struct Meta<UUID, false> final {
  using value_type = UUID;
  using column_type = third_party::clickhouse::ColumnUUID;
  static const constexpr auto database_type = []() {
    using namespace std::literals;
    return "UUID"sv;
  }();
  static auto create_column() { return std::make_shared<column_type>(); }
  static auto to_value(value_type const &value) { return to_uint128(value); }
};
}  // namespace detail

template <typename T, bool low_cardinality = false>
struct Column final {
  using meta_type = detail::Meta<T, low_cardinality>;

  explicit Column(auto const &name) : name_(name), column_(meta_type::create_column()) {}

  std::string_view name() const { return name_; }

  size_t size() const { return (*column_).Size(); }

  void clear() { (*column_).Clear(); }

  void append(T value) { (*column_).Append(meta_type::to_value(value)); }

  void append(third_party::clickhouse::Block &block) const { block.AppendColumn(name_, column_); }

  template <typename Context>
  auto format_to(Context &context) const {
    using namespace std::literals;
    return fmt::format_to(context.out(), "{} {}"sv, name_, meta_type::database_type);
  }

 private:
  const std::string name_;
  std::shared_ptr<typename meta_type::column_type> column_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq

template <typename T, bool low_cardinality>
struct fmt::formatter<roq::adapter::clickhouse::Column<T, low_cardinality>> {
  template <typename Context>
  constexpr auto parse(Context &context) {
    return std::begin(context);
  }
  template <typename Context>
  auto format(roq::adapter::clickhouse::Column<T, low_cardinality> const &value, Context &context) const {
    return value.format_to(context);
  }
};
