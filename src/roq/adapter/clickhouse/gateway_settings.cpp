/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/gateway_settings.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

GatewaySettings::GatewaySettings()
    : supports_{"supports"sv}, mbp_max_depth_{"mbp_max_depth"sv},
      mbp_tick_size_multiplier_{"mbp_tick_size_multiplier"sv},
      mbp_min_trade_vol_multiplier_{"mbp_min_trade_vol_multiplier"sv},
      mbp_allow_remove_non_existing_{"mbp_allow_remove_non_existing"sv},
      mbp_allow_price_inversion_{"mbp_allow_price_inversion"sv}, mbp_checksum_{"mbp_checksum"sv},
      oms_download_has_state_{"oms_download_has_state"sv},
      oms_download_has_routing_id_{"oms_download_has_routing_id"sv}, oms_request_id_type_{"oms_request_id_type"sv} {
}

std::string GatewaySettings::get_fields() const {
  return fmt::format(
      "{}, "    // supports
      "{}, "    // mbp_max_depth
      "{}, "    // mbp_tick_size_multiplier
      "{}, "    // mbp_min_trade_vol_multiplier
      "{}, "    // mbp_allow_remove_non_existing
      "{}, "    // mbp_allow_price_inversion
      "{}, "    // mbp_checksum
      "{}, "    // oms_download_has_state
      "{}, "    // oms_download_has_routing_id
      "{}"_cf,  // oms_request_id_type
      supports_,
      mbp_max_depth_,
      mbp_tick_size_multiplier_,
      mbp_min_trade_vol_multiplier_,
      mbp_allow_remove_non_existing_,
      mbp_allow_price_inversion_,
      mbp_checksum_,
      oms_download_has_state_,
      oms_download_has_routing_id_,
      oms_request_id_type_);
}

size_t GatewaySettings::operator()(roq::GatewaySettings const &gateway_settings) {
  supports_.append(gateway_settings.supports);
  mbp_max_depth_.append(gateway_settings.mbp_max_depth);
  mbp_tick_size_multiplier_.append(gateway_settings.mbp_tick_size_multiplier);
  mbp_min_trade_vol_multiplier_.append(gateway_settings.mbp_min_trade_vol_multiplier);
  mbp_allow_remove_non_existing_.append(gateway_settings.mbp_allow_remove_non_existing);
  mbp_allow_price_inversion_.append(gateway_settings.mbp_allow_price_inversion);
  mbp_checksum_.append(gateway_settings.mbp_checksum);
  oms_download_has_state_.append(gateway_settings.oms_download_has_state);
  oms_download_has_routing_id_.append(gateway_settings.oms_download_has_routing_id);
  oms_request_id_type_.append(gateway_settings.oms_request_id_type);
  return 1;
}

void GatewaySettings::append(third_party::clickhouse::Block &block) {
  supports_.append(block);
  mbp_max_depth_.append(block);
  mbp_tick_size_multiplier_.append(block);
  mbp_min_trade_vol_multiplier_.append(block);
  mbp_allow_remove_non_existing_.append(block);
  mbp_allow_price_inversion_.append(block);
  mbp_checksum_.append(block);
  oms_download_has_state_.append(block);
  oms_download_has_routing_id_.append(block);
  oms_request_id_type_.append(block);
}

void GatewaySettings::clear() {
  supports_.clear();
  mbp_max_depth_.clear();
  mbp_tick_size_multiplier_.clear();
  mbp_min_trade_vol_multiplier_.clear();
  mbp_allow_remove_non_existing_.clear();
  mbp_allow_price_inversion_.clear();
  mbp_checksum_.clear();
  oms_download_has_state_.clear();
  oms_download_has_routing_id_.clear();
  oms_request_id_type_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
