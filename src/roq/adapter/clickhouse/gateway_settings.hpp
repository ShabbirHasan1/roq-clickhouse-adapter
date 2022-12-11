/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <string>

#include "roq/adapter/clickhouse/table.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct GatewaySettings final {
  using value_type = roq::GatewaySettings;

  static const constexpr auto table_name = []() {
    using namespace std::literals;
    return "gateway_settings"sv;
  }();

  GatewaySettings();

  std::string get_fields() const;
  std::string get_index_fields() const { return {}; }

  size_t operator()(value_type const &);

  void append(third_party::clickhouse::Block &);

  void clear();

 private:
  Column<Mask<SupportType>> supports_;
  Column<uint32_t> mbp_max_depth_;
  Column<double> mbp_tick_size_multiplier_;
  Column<double> mbp_min_trade_vol_multiplier_;
  Column<bool> mbp_allow_remove_non_existing_;
  Column<bool> mbp_allow_price_inversion_;
  Column<bool> mbp_checksum_;
  Column<bool> oms_download_has_state_;
  Column<bool> oms_download_has_routing_id_;
  Column<RequestIdType, true> oms_request_id_type_;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
