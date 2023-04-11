/* Copyright (c) 2017-2023, Hans Erik Thrane */

#include "roq/adapter/clickhouse/funds.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

Funds::Funds()
    : stream_id_{"stream_id"}, account_{"account"}, currency_{"currency"}, balance_{"balance"}, hold_{"hold"},
      external_account_{"external_account"}, update_type_{"update_type"}, exchange_time_utc_{"exchange_time_utc"},
      sending_time_utc_{"sending_time_utc"} {
}

std::string Funds::get_fields() const {
  return fmt::format(
      "{}, "    // stream_id
      "{}, "    // account
      "{}, "    // currency
      "{}, "    // balance
      "{}, "    // hold
      "{}, "    // external_account
      "{}, "    // update_type
      "{}, "    // exchange_time_utc
      "{}"_cf,  // sending_time_utc
      stream_id_,
      account_,
      currency_,
      balance_,
      hold_,
      external_account_,
      update_type_,
      exchange_time_utc_,
      sending_time_utc_);
}

size_t Funds::operator()(roq::FundsUpdate const &funds_update) {
  stream_id_.append(funds_update.stream_id);
  account_.append(funds_update.account);
  currency_.append(funds_update.currency);
  balance_.append(funds_update.balance);
  hold_.append(funds_update.hold);
  external_account_.append(funds_update.external_account);
  update_type_.append(funds_update.update_type);
  exchange_time_utc_.append(funds_update.exchange_time_utc);
  sending_time_utc_.append(funds_update.sending_time_utc);
  return 1;
}

void Funds::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  account_.append(block);
  currency_.append(block);
  balance_.append(block);
  hold_.append(block);
  external_account_.append(block);
  update_type_.append(block);
  exchange_time_utc_.append(block);
  sending_time_utc_.append(block);
}

void Funds::clear() {
  stream_id_.clear();
  account_.clear();
  currency_.clear();
  balance_.clear();
  hold_.clear();
  external_account_.clear();
  update_type_.clear();
  exchange_time_utc_.clear();
  sending_time_utc_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
