/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/custom_metrics.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

CustomMetrics::CustomMetrics()
    : user_{"user"}, label_{"label"}, account_{"account"}, exchange_{"exchange"}, symbol_{"symbol"}, name_{"name"},
      value_{"value"} {
}

std::string CustomMetrics::get_fields() const {
  return fmt::format(
      "{}, "    // user
      "{}, "    // label
      "{}, "    // account
      "{}, "    // exchange
      "{}, "    // symbol
      "{}, "    // name
      "{}"_cf,  // value
      user_,
      label_,
      account_,
      exchange_,
      symbol_,
      name_,
      value_);
}

std::string CustomMetrics::get_index_fields() const {
  return fmt::format(", {}"_cf, name_.name());
}

size_t CustomMetrics::operator()(roq::CustomMetricsUpdate const &custom_metrics_update) {
  for (auto &item : custom_metrics_update.measurements) {
    user_.append(custom_metrics_update.user);
    label_.append(custom_metrics_update.label);
    account_.append(custom_metrics_update.account);
    exchange_.append(custom_metrics_update.exchange);
    symbol_.append(custom_metrics_update.symbol);
    name_.append(item.name);
    value_.append(item.value);
  }
  return std::size(custom_metrics_update.measurements);
}

void CustomMetrics::append(third_party::clickhouse::Block &block) {
  user_.append(block);
  label_.append(block);
  account_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  name_.append(block);
  value_.append(block);
}

void CustomMetrics::clear() {
  user_.clear();
  label_.clear();
  account_.clear();
  exchange_.clear();
  symbol_.clear();
  name_.clear();
  value_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
