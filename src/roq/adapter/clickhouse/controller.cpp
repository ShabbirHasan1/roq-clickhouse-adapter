/* Copyright (c) 2017-2022, Hans Erik Thrane */

#include "roq/adapter/clickhouse/controller.hpp"

#include <memory>
#include <thread>

#include "roq/logging.hpp"

#include "roq/adapter/clickhouse/utils.hpp"

#include "roq/adapter/clickhouse/flags/flags.hpp"

using namespace std::literals;

namespace roq {
namespace adapter {
namespace clickhouse {

// === HELPERS ===

namespace {
auto create_client() {
  third_party::clickhouse::ClientOptions options;
  options.SetHost(std::string{flags::Flags::db_host()});
  options.SetPort(flags::Flags::db_port());
  // XXX should be flags
  options.SetSendRetries(3);
  options.SetRetryTimeout(5s);
  options.TcpKeepAlive(true);
  return third_party::clickhouse::Client{options};
}
}  // namespace

// === IMPLEMENTATION ===

Controller::Controller() : dispatcher_{adapter::Factory::create(*this)}, client_{create_client()} {
  create_database();
  // completely processed event-logs (to avoid redundant inserts)
  create_processed_table();
  load_processed_table();
  // tables
  gateway_settings_.create_table(client_);
  stream_status_.create_table(client_);
  external_latency_.create_table(client_);
  gateway_status_.create_table(client_);
  reference_data_.create_table(client_);
  market_status_.create_table(client_);
  top_of_book_.create_table(client_);
  market_by_price_.create_table(client_);
  trade_summary_.create_table(client_);
  statistics_.create_table(client_);
  create_order_.create_table(client_);
  modify_order_.create_table(client_);
  cancel_order_.create_table(client_);
  order_ack_.create_table(client_);
  order_.create_table(client_);
  trade_.create_table(client_);
  position_.create_table(client_);
  funds_.create_table(client_);
  custom_metrics_.create_table(client_);
}

void Controller::dispatch() {
  while (true) {
    switch ((*dispatcher_).dispatch()) {
      using enum adapter::Status;
      case STOP:
        flush(true);
        return;
      case EXHALE:
        std::this_thread::sleep_for(10ms);
        break;
      case INTERRUPTED:
        flush();
        break;
    }
  }
}

bool Controller::operator()(adapter::Category category, adapter::Add const &add) {
  log::info(R"(Adding session_id="{}")"sv, add.session_id);
  auto &processed = processed_[category];
  auto &key = add.session_id;
  if (processed.find(key) != std::end(processed)) {
    return true;
  } else {
    auto &feeds = feeds_[category];
    auto res = feeds.try_emplace(key, add.name);
    assert(res.second);
    return false;
  }
}

void Controller::operator()(adapter::Category category, adapter::Remove const &remove) {
  auto &feeds = feeds_[category];
  auto &key = remove.session_id;
  auto iter = feeds.find(key);
  if (iter != std::end(feeds)) {
    log::info(R"(Removing session_id="{}")"sv, remove.session_id);
    feeds.erase(iter);
    flush(true);
    insert_processed(category, remove.session_id);
  } else {
    assert(false);
    log::warn(R"(Unexpected session_id="{}")"sv, remove.session_id);
  }
}

bool Controller::operator()(adapter::Category category, Event<roq::GatewaySettings> const &event) {
  return dispatch(category, event, gateway_settings_);
}

bool Controller::operator()(adapter::Category category, Event<roq::StreamStatus> const &event) {
  return dispatch(category, event, stream_status_);
}

bool Controller::operator()(adapter::Category category, Event<roq::ExternalLatency> const &event) {
  return dispatch(category, event, external_latency_);
}

bool Controller::operator()(adapter::Category category, Event<roq::GatewayStatus> const &event) {
  return dispatch(category, event, gateway_status_);
}

bool Controller::operator()(adapter::Category category, Event<roq::ReferenceData> const &event) {
  return dispatch(category, event, reference_data_);
}

bool Controller::operator()(adapter::Category category, Event<roq::MarketStatus> const &event) {
  return dispatch(category, event, market_status_);
}

bool Controller::operator()(adapter::Category category, Event<roq::TopOfBook> const &event) {
  return dispatch(category, event, top_of_book_);
}

bool Controller::operator()(adapter::Category category, Event<roq::MarketByPriceUpdate> const &event) {
  return dispatch(category, event, market_by_price_);
}

bool Controller::operator()(adapter::Category category, Event<roq::TradeSummary> const &event) {
  return dispatch(category, event, trade_summary_);
}

bool Controller::operator()(adapter::Category category, Event<roq::StatisticsUpdate> const &event) {
  return dispatch(category, event, statistics_);
}

bool Controller::operator()(adapter::Category category, Event<roq::CreateOrder> const &event) {
  return dispatch(category, event, create_order_);
}

bool Controller::operator()(adapter::Category category, Event<roq::ModifyOrder> const &event) {
  return dispatch(category, event, modify_order_);
}

bool Controller::operator()(adapter::Category category, Event<roq::CancelOrder> const &event) {
  return dispatch(category, event, cancel_order_);
}

bool Controller::operator()(adapter::Category category, Event<roq::OrderAck> const &event) {
  return dispatch(category, event, order_ack_);
}

bool Controller::operator()(adapter::Category category, Event<roq::OrderUpdate> const &event) {
  return dispatch(category, event, order_);
}

bool Controller::operator()(adapter::Category category, Event<roq::TradeUpdate> const &event) {
  return dispatch(category, event, trade_);
}

bool Controller::operator()(adapter::Category category, Event<roq::PositionUpdate> const &event) {
  return dispatch(category, event, position_);
}

bool Controller::operator()(adapter::Category category, Event<roq::FundsUpdate> const &event) {
  return dispatch(category, event, funds_);
}

bool Controller::operator()(adapter::Category category, Event<roq::CustomMetricsUpdate> const &event) {
  return dispatch(category, event, custom_metrics_);
}

template <typename T, typename U>
bool Controller::dispatch(adapter::Category category, Event<T> const &event, Table<U> &table) {
  auto &feeds = feeds_[category];
  auto &key = event.message_info.source_session_id;
  auto iter = feeds.find(key);
  if (iter != std::end(feeds))
    return table(event, (*iter).second, ++counter_);
  log::critical("Unexpected"sv);
  return false;
}

void Controller::flush(bool force) {
  gateway_settings_.flush(client_, counter_, force);
  stream_status_.flush(client_, counter_, force);
  external_latency_.flush(client_, counter_, force);
  gateway_status_.flush(client_, counter_, force);
  reference_data_.flush(client_, counter_, force);
  market_status_.flush(client_, counter_, force);
  top_of_book_.flush(client_, counter_, force);
  market_by_price_.flush(client_, counter_, force);
  trade_summary_.flush(client_, counter_, force);
  statistics_.flush(client_, counter_, force);
  create_order_.flush(client_, counter_, force);
  modify_order_.flush(client_, counter_, force);
  cancel_order_.flush(client_, counter_, force);
  order_ack_.flush(client_, counter_, force);
  order_.flush(client_, counter_, force);
  trade_.flush(client_, counter_, force);
  position_.flush(client_, counter_, force);
  funds_.flush(client_, counter_, force);
  custom_metrics_.flush(client_, counter_, force);
}

void Controller::create_database() {
  auto query = fmt::format("CREATE DATABASE IF NOT EXISTS {}"sv, flags::Flags::database());
  client_.Execute(query);
}

void Controller::create_processed_table() {
  auto query = fmt::format(
      "CREATE TABLE IF NOT EXISTS {}.processed ("
      "category LowCardinality(String), "
      "session_id UUID"
      ") "
      "ENGINE = ReplacingMergeTree() "
      "ORDER BY (session_id)"sv,
      flags::Flags::database());
  client_.Execute(query);
}

void Controller::load_processed_table() {
  auto query = fmt::format("SELECT category, session_id FROM {}.processed"sv, flags::Flags::database());
  client_.Select(query, [this](auto &block) {
    if (block.GetRowCount() == 0)
      return;
    auto category = (*block[0]).template As<third_party::clickhouse::ColumnString>();
    auto session_id = (*block[1]).template As<third_party::clickhouse::ColumnUUID>();
    for (size_t i = 0; i < (*category).Size(); ++i) {
      auto category_ = (*category).At(i);
      auto session_id_ = (*session_id).At(i);
      // parse
      auto key = magic_enum::enum_cast<adapter::Category>(category_).value();
      auto value = from_uint128(session_id_);
      processed_[key].emplace(value);
    }
  });
}

void Controller::insert_processed(adapter::Category category, const UUID &session_id) {
  auto category_ = std::make_shared<third_party::clickhouse::ColumnString>();
  auto session_id_ = std::make_shared<third_party::clickhouse::ColumnUUID>();
  (*category_).Append(magic_enum::enum_name(category));
  (*session_id_).Append(to_uint128(session_id));
  third_party::clickhouse::Block block;
  block.AppendColumn("category"s, category_);
  block.AppendColumn("session_id"s, session_id_);
  auto table_name = fmt::format("{}.processed"sv, flags::Flags::database());
  client_.Insert(table_name, block);
}

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
