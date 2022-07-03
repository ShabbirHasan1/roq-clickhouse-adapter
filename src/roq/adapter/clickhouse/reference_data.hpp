/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct ReferenceData final {
  using value_type = roq::ReferenceData;

  static const constexpr auto table_name = []() {
    using namespace std::literals;
    return "reference_data"sv;
  }();

  ReferenceData();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<uint16_t, true> stream_id_;
  Column<std::string_view, true> exchange_;
  Column<std::string_view, true> symbol_;
  Column<std::string_view, false> description_;
  Column<SecurityType, true> security_type_;
  Column<std::string_view, true> base_currency_;
  Column<std::string_view, true> quote_currency_;
  Column<std::string_view, true> margin_currency_;
  Column<std::string_view, true> commission_currency_;
  Column<double> tick_size_;
  Column<double> multiplier_;
  Column<double> min_trade_vol_;
  Column<double> max_trade_vol_;
  Column<double> trade_vol_step_size_;
  Column<OptionType, true> option_type_;
  Column<std::string_view, true> strike_currency_;
  Column<double> strike_price_;
  Column<std::string_view, true> underlying_;
  Column<std::string_view, true> time_zone_;
  Column<std::chrono::days> issue_date_;
  Column<std::chrono::days> settlement_date_;
  Column<std::chrono::seconds> expiry_datetime_;
  Column<std::chrono::seconds> expiry_datetime_utc_;
  Column<bool> discard_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
