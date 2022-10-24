/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/funds.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

Funds::Funds()
    : stream_id_{"stream_id"}, account_{"account"}, currency_{"currency"}, balance_{"balance"}, hold_{"hold"},
      external_account_{"external_account"} {
}

std::string Funds::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id
      "{}, "   // account
      "{}, "   // currency
      "{}, "   // balance
      "{}, "   // hold
      "{}"sv,  // external_account
      stream_id_,
      account_,
      currency_,
      balance_,
      hold_,
      external_account_);
}

size_t Funds::operator()(roq::FundsUpdate const &funds_update) {
  stream_id_.append(funds_update.stream_id);
  account_.append(funds_update.account);
  currency_.append(funds_update.currency);
  balance_.append(funds_update.balance);
  hold_.append(funds_update.hold);
  external_account_.append(funds_update.external_account);
  return 1;
}

void Funds::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  account_.append(block);
  currency_.append(block);
  balance_.append(block);
  hold_.append(block);
  external_account_.append(block);
}

void Funds::clear() {
  stream_id_.clear();
  account_.clear();
  currency_.clear();
  balance_.clear();
  hold_.clear();
  external_account_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
