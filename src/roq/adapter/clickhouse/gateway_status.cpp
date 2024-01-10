/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/gateway_status.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

GatewayStatus::GatewayStatus()
    : account_{"account"sv}, supported_{"supported"sv}, available_{"available"sv}, unavailable_{"unavailable"sv} {
}

std::string GatewayStatus::get_fields() const {
  return fmt::format(
      "{}, "   // account
      "{}, "   // supported
      "{}, "   // available
      "{}"sv,  // unavailable
      account_,
      supported_,
      available_,
      unavailable_);
}

size_t GatewayStatus::operator()(roq::GatewayStatus const &gateway_status) {
  account_.append(gateway_status.account);
  supported_.append(gateway_status.supported);
  available_.append(gateway_status.available);
  unavailable_.append(gateway_status.unavailable);
  return 1;
}

void GatewayStatus::append(third_party::clickhouse::Block &block) {
  account_.append(block);
  supported_.append(block);
  available_.append(block);
  unavailable_.append(block);
}

void GatewayStatus::clear() {
  account_.clear();
  supported_.clear();
  available_.clear();
  unavailable_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
