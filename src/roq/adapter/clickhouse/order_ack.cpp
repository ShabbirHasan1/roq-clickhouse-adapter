/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/order_ack.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

OrderAck::OrderAck()
    : stream_id_{"stream_id"}, account_{"account"}, order_id_{"order_id"}, exchange_{"exchange"}, symbol_{"symbol"},
      side_{"side"}, request_type_{"request_type"}, origin_{"origin"}, request_status_{"request_status"},
      error_{"error"}, text_{"text"}, request_id_{"request_id"}, external_account_{"external_account"},
      external_order_id_{"external_order_id"}, routing_id_{"routing_id"}, version_{"version"},
      round_trip_latency_{"round_trip_latency"} {
}

std::string OrderAck::get_fields() const {
  return fmt::format(
      "{}, "   // stream_id,
      "{}, "   // account,
      "{}, "   // order_id,
      "{}, "   // exchange,
      "{}, "   // symbol,
      "{}, "   // side,
      "{}, "   // type,
      "{}, "   // origin,
      "{}, "   // status,
      "{}, "   // error,
      "{}, "   // text,
      "{}, "   // request_id,
      "{}, "   // external_account,
      "{}, "   // external_order_id,
      "{}, "   // routing_id,
      "{}, "   // version,
      "{}"sv,  // round_trip_latency
      stream_id_,
      account_,
      order_id_,
      exchange_,
      symbol_,
      side_,
      request_type_,
      origin_,
      request_status_,
      error_,
      text_,
      request_id_,
      external_account_,
      external_order_id_,
      routing_id_,
      version_,
      round_trip_latency_);
}

size_t OrderAck::operator()(roq::OrderAck const &order_update) {
  stream_id_.append(order_update.stream_id);
  account_.append(order_update.account);
  order_id_.append(order_update.order_id);
  exchange_.append(order_update.exchange);
  symbol_.append(order_update.symbol);
  side_.append(order_update.side);
  request_type_.append(order_update.request_type);
  origin_.append(order_update.origin);
  request_status_.append(order_update.request_status);
  error_.append(order_update.error);
  text_.append(order_update.text);
  request_id_.append(order_update.request_id);
  external_account_.append(order_update.external_account);
  external_order_id_.append(order_update.external_order_id);
  routing_id_.append(order_update.routing_id);
  version_.append(order_update.version);
  round_trip_latency_.append(order_update.round_trip_latency);
  return 1;
}

void OrderAck::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  account_.append(block);
  order_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  side_.append(block);
  request_type_.append(block);
  origin_.append(block);
  request_status_.append(block);
  error_.append(block);
  text_.append(block);
  request_id_.append(block);
  external_account_.append(block);
  external_order_id_.append(block);
  routing_id_.append(block);
  version_.append(block);
  round_trip_latency_.append(block);
}

void OrderAck::clear() {
  stream_id_.clear();
  account_.clear();
  order_id_.clear();
  exchange_.clear();
  symbol_.clear();
  side_.clear();
  request_type_.clear();
  origin_.clear();
  request_status_.clear();
  error_.clear();
  text_.clear();
  request_id_.clear();
  external_account_.clear();
  external_order_id_.clear();
  routing_id_.clear();
  version_.clear();
  round_trip_latency_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
