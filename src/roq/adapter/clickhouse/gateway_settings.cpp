/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/gateway_settings.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

GatewaySettings::GatewaySettings()
    : supports_("supports"sv), mbp_max_depth_("mbp_max_depth"sv),
      mbp_tick_size_multiplier_("mbp_tick_size_multiplier"sv),
      mbp_min_trade_vol_multiplier_("mbp_min_trade_vol_multiplier"sv),
      mbp_allow_remove_non_existing_("mbp_allow_remove_non_existing"sv),
      mbp_allow_price_inversion_("mbp_allow_price_inversion"sv), oms_download_has_state_("oms_download_has_state"sv),
      oms_download_has_routing_id_("oms_download_has_routing_id"sv), oms_request_id_type_("oms_request_id_type"sv) {
}

std::string GatewaySettings::get_fields() const {
  return fmt::format(
      "{}, "   // supports
      "{}, "   // mbp_max_depth
      "{}, "   // mbp_tick_size_multiplier
      "{}, "   // mbp_min_trade_vol_multiplier
      "{}, "   // mbp_allow_remove_non_existing
      "{}, "   // mbp_allow_price_inversion
      "{}, "   // oms_download_has_state
      "{}, "   // oms_download_has_routing_id
      "{}"sv,  // oms_request_id_type
      supports_,
      mbp_max_depth_,
      mbp_tick_size_multiplier_,
      mbp_min_trade_vol_multiplier_,
      mbp_allow_remove_non_existing_,
      mbp_allow_price_inversion_,
      oms_download_has_state_,
      oms_download_has_routing_id_,
      oms_request_id_type_);
}

void GatewaySettings::operator()(roq::GatewaySettings const &gateway_settings) {
  supports_.append(gateway_settings.supports);
  mbp_max_depth_.append(gateway_settings.mbp_max_depth);
  mbp_tick_size_multiplier_.append(gateway_settings.mbp_tick_size_multiplier);
  mbp_min_trade_vol_multiplier_.append(gateway_settings.mbp_min_trade_vol_multiplier);
  mbp_allow_remove_non_existing_.append(gateway_settings.mbp_allow_remove_non_existing);
  mbp_allow_price_inversion_.append(gateway_settings.mbp_allow_price_inversion);
  oms_download_has_state_.append(gateway_settings.oms_download_has_state);
  oms_download_has_routing_id_.append(gateway_settings.oms_download_has_routing_id);
  oms_request_id_type_.append(gateway_settings.oms_request_id_type);
}

void GatewaySettings::append(third_party::clickhouse::Block &block) {
  supports_.append(block);
  mbp_max_depth_.append(block);
  mbp_tick_size_multiplier_.append(block);
  mbp_min_trade_vol_multiplier_.append(block);
  mbp_allow_remove_non_existing_.append(block);
  mbp_allow_price_inversion_.append(block);
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
  oms_download_has_state_.clear();
  oms_download_has_routing_id_.clear();
  oms_request_id_type_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
