/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/stream_status.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

StreamStatus::StreamStatus()
    : stream_id_{"stream_id"sv}, account_{"account"sv}, supports_{"supports"sv}, transport_{"transport"sv},
      protocol_{"protocol"sv}, encoding_{"encoding"sv}, priority_{"priority"sv},
      connection_status_{"connection_status"sv} {
}

std::string StreamStatus::get_fields() const {
  return fmt::format(
      "{}, "    // stream_id
      "{}, "    // account
      "{}, "    // supports
      "{}, "    // transport
      "{}, "    // protocol
      "{}, "    // encoding
      "{}, "    // priority
      "{}"_cf,  // connection_status
      stream_id_,
      account_,
      supports_,
      transport_,
      protocol_,
      encoding_,
      priority_,
      connection_status_);
}

size_t StreamStatus::operator()(roq::StreamStatus const &stream_status) {
  stream_id_.append(stream_status.stream_id);
  account_.append(stream_status.account);
  supports_.append(stream_status.supports);
  transport_.append(stream_status.transport);
  protocol_.append(stream_status.protocol);
  encoding_.append(stream_status.encoding);
  priority_.append(stream_status.priority);
  connection_status_.append(stream_status.connection_status);
  return 1;
}

void StreamStatus::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  account_.append(block);
  supports_.append(block);
  transport_.append(block);
  protocol_.append(block);
  encoding_.append(block);
  priority_.append(block);
  connection_status_.append(block);
}

void StreamStatus::clear() {
  stream_id_.clear();
  account_.clear();
  supports_.clear();
  transport_.clear();
  protocol_.clear();
  encoding_.clear();
  priority_.clear();
  connection_status_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
