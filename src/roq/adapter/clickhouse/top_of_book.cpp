/* Copyright (c) 2017-2024, Hans Erik Thrane */

#include "roq/adapter/clickhouse/top_of_book.hpp"

#include "roq/logging.hpp"

using namespace std::literals;

using namespace fmt::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === IMPLEMENTATION ===

TopOfBook::TopOfBook()
    : stream_id_{"stream_id"sv}, exchange_{"exchange"}, symbol_{"symbol"sv}, bid_price_{"bid_price"sv},
      bid_quantity_{"bid_quantity"sv}, ask_price_{"ask_price"sv}, ask_quantity_{"ask_quantity"sv},
      update_type_{"update_type"sv}, exchange_time_utc_{"exchange_time_utc"sv} {
}

std::string TopOfBook::get_fields() const {
  return fmt::format(
      "{}, "    // stream_id
      "{}, "    // exchange
      "{}, "    // symbol
      "{}, "    // bid_price
      "{}, "    // bid_quantity
      "{}, "    // ask_price
      "{}, "    // ask_quantity
      "{}, "    // update_type
      "{}"_cf,  // exchange_time_utc
      stream_id_,
      exchange_,
      symbol_,
      bid_price_,
      bid_quantity_,
      ask_price_,
      ask_quantity_,
      update_type_,
      exchange_time_utc_);
}

size_t TopOfBook::operator()(roq::TopOfBook const &top_of_book) {
  stream_id_.append(top_of_book.stream_id);
  exchange_.append(top_of_book.exchange);
  symbol_.append(top_of_book.symbol);
  bid_price_.append(top_of_book.layer.bid_price);
  bid_quantity_.append(top_of_book.layer.bid_quantity);
  ask_price_.append(top_of_book.layer.ask_price);
  ask_quantity_.append(top_of_book.layer.ask_quantity);
  update_type_.append(top_of_book.update_type);
  exchange_time_utc_.append(top_of_book.exchange_time_utc);
  return 1;
}

void TopOfBook::append(third_party::clickhouse::Block &block) {
  stream_id_.append(block);
  exchange_.append(block);
  symbol_.append(block);
  bid_price_.append(block);
  bid_quantity_.append(block);
  ask_price_.append(block);
  ask_quantity_.append(block);
  update_type_.append(block);
  exchange_time_utc_.append(block);
}

void TopOfBook::clear() {
  stream_id_.clear();
  exchange_.clear();
  symbol_.clear();
  bid_price_.clear();
  bid_quantity_.clear();
  ask_price_.clear();
  ask_quantity_.clear();
  update_type_.clear();
  exchange_time_utc_.clear();
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
