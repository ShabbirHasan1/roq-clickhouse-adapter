/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/reference_data.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

ReferenceData::ReferenceData()
    : stream_id_("stream_id"sv), exchange_("exchange"sv), symbol_("symbol"sv), description_("description"sv),
      security_type_("security_type"sv), base_currency_("base_currency"sv), quote_currency_("quote_currency"sv),
      margin_currency_("margin_currency"sv), commission_currency_("commission_currency"sv), tick_size_("tick_size"sv),
      multiplier_("multiplier"sv), min_trade_vol_("min_trade_vol"sv), max_trade_vol_("max_trade_vol"sv),
      trade_vol_step_size_("trade_vol_step_size"sv), option_type_("option_type"sv),
      strike_currency_("strike_currency"sv), strike_price_("strike_price"sv), underlying_("underlying"sv),
      time_zone_("time_zone"sv), issue_date_("issue_date"sv), settlement_date_("settlement_date"sv),
      expiry_datetime_("expiry_datetime"sv), expiry_datetime_utc_("expiry_datetime_utc"sv), discard_("discard"sv) {
}

std::string ReferenceData::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id
      "{}, "   // exchange
      "{}, "   // symbol
      "{}, "   // description
      "{}, "   // security_type
      "{}, "   // base_currency
      "{}, "   // quote_currency
      "{}, "   // margin_currency
      "{}, "   // commission_currency
      "{}, "   // tick_size
      "{}, "   // multiplier
      "{}, "   // min_trade_vol
      "{}, "   // max_trade_vol
      "{}, "   // trade_vol_step_size
      "{}, "   // option_type
      "{}, "   // strike_currency
      "{}, "   // strike_price
      "{}, "   // underlying
      "{}, "   // time_zone
      "{}, "   // issue_date
      "{}, "   // settlement_date
      "{}, "   // expiry_datetime
      "{}, "   // expiry_datetime_utc
      "{}"sv,  // discard
      stream_id_,
      exchange_,
      symbol_,
      description_,
      security_type_,
      base_currency_,
      quote_currency_,
      margin_currency_,
      commission_currency_,
      tick_size_,
      multiplier_,
      min_trade_vol_,
      max_trade_vol_,
      trade_vol_step_size_,
      option_type_,
      strike_currency_,
      strike_price_,
      underlying_,
      time_zone_,
      issue_date_,
      settlement_date_,
      expiry_datetime_,
      expiry_datetime_utc_,
      discard_);
}

void ReferenceData::operator()(roq::ReferenceData const &reference_data) {
  stream_id_.append(reference_data.stream_id);
  exchange_.append(reference_data.exchange);
  symbol_.append(reference_data.symbol);
  description_.append(reference_data.description);
  security_type_.append(reference_data.security_type);
  base_currency_.append(reference_data.base_currency);
  quote_currency_.append(reference_data.quote_currency);
  margin_currency_.append(reference_data.margin_currency);
  commission_currency_.append(reference_data.commission_currency);
  tick_size_.append(reference_data.tick_size);
  multiplier_.append(reference_data.multiplier);
  min_trade_vol_.append(reference_data.min_trade_vol);
  max_trade_vol_.append(reference_data.max_trade_vol);
  trade_vol_step_size_.append(reference_data.trade_vol_step_size);
  option_type_.append(reference_data.option_type);
  strike_currency_.append(reference_data.strike_currency);
  strike_price_.append(reference_data.strike_price);
  underlying_.append(reference_data.underlying);
  time_zone_.append(reference_data.time_zone);
  issue_date_.append(reference_data.issue_date);
  settlement_date_.append(reference_data.settlement_date);
  expiry_datetime_.append(reference_data.expiry_datetime);
  expiry_datetime_utc_.append(reference_data.expiry_datetime_utc);
  discard_.append(reference_data.discard);
}

void ReferenceData::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  description_.append(block);
  security_type_.append(block);
  base_currency_.append(block);
  quote_currency_.append(block);
  margin_currency_.append(block);
  commission_currency_.append(block);
  tick_size_.append(block);
  multiplier_.append(block);
  min_trade_vol_.append(block);
  max_trade_vol_.append(block);
  trade_vol_step_size_.append(block);
  option_type_.append(block);
  strike_currency_.append(block);
  strike_price_.append(block);
  underlying_.append(block);
  time_zone_.append(block);
  issue_date_.append(block);
  settlement_date_.append(block);
  expiry_datetime_.append(block);
  expiry_datetime_utc_.append(block);
  discard_.append(block);
}

void ReferenceData::clear() {
  stream_id_.clear();
  exchange_.clear();
  symbol_.clear();
  description_.clear();
  security_type_.clear();
  base_currency_.clear();
  quote_currency_.clear();
  margin_currency_.clear();
  commission_currency_.clear();
  tick_size_.clear();
  multiplier_.clear();
  min_trade_vol_.clear();
  max_trade_vol_.clear();
  trade_vol_step_size_.clear();
  option_type_.clear();
  strike_currency_.clear();
  strike_price_.clear();
  underlying_.clear();
  time_zone_.clear();
  issue_date_.clear();
  settlement_date_.clear();
  expiry_datetime_.clear();
  expiry_datetime_utc_.clear();
  discard_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
