/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/external_latency.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

ExternalLatency::ExternalLatency() : stream_id_{"stream_id"sv}, account_{"account"sv}, latency_{"latency"sv} {
}

std::string ExternalLatency::get_fields() const {
  return fmt::format(
      "{}, "    // stream_id
      "{}, "    // account
      "{}"_cf,  // latency
      stream_id_,
      account_,
      latency_);
}

size_t ExternalLatency::operator()(roq::ExternalLatency const &external_latency) {
  stream_id_.append(external_latency.stream_id);
  account_.append(external_latency.account);
  latency_.append(external_latency.latency);
  return 1;
}

void ExternalLatency::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  account_.append(block);
  latency_.append(block);
}

void ExternalLatency::clear() {
  stream_id_.clear();
  account_.clear();
  latency_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
