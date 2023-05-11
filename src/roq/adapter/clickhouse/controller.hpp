/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include <absl/container/flat_hash_map.h>
#include <absl/container/flat_hash_set.h>

#include <string>

#include "roq/adapter.hpp"

#include "roq/third_party/clickhouse/client.hpp"

#include "roq/adapter/clickhouse/settings.hpp"

// tables

#include "roq/adapter/clickhouse/cancel_order.hpp"
#include "roq/adapter/clickhouse/create_order.hpp"
#include "roq/adapter/clickhouse/custom_metrics.hpp"
#include "roq/adapter/clickhouse/external_latency.hpp"
#include "roq/adapter/clickhouse/funds.hpp"
#include "roq/adapter/clickhouse/gateway_settings.hpp"
#include "roq/adapter/clickhouse/gateway_status.hpp"
#include "roq/adapter/clickhouse/market_by_price.hpp"
#include "roq/adapter/clickhouse/market_status.hpp"
#include "roq/adapter/clickhouse/modify_order.hpp"
#include "roq/adapter/clickhouse/order.hpp"
#include "roq/adapter/clickhouse/order_ack.hpp"
#include "roq/adapter/clickhouse/position.hpp"
#include "roq/adapter/clickhouse/reference_data.hpp"
#include "roq/adapter/clickhouse/statistics.hpp"
#include "roq/adapter/clickhouse/stream_status.hpp"
#include "roq/adapter/clickhouse/top_of_book.hpp"
#include "roq/adapter/clickhouse/trade.hpp"
#include "roq/adapter/clickhouse/trade_summary.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct Controller final : public adapter::Handler {
  explicit Controller(Settings const &);

  Controller(Controller const &) = delete;
  Controller(Controller &&) = delete;

  void dispatch();

 protected:
  bool operator()(Category, adapter::Add const &) override;
  void operator()(Category, adapter::Remove const &) override;

  // events

  bool operator()(Category, Event<roq::GatewaySettings> const &) override;
  bool operator()(Category, Event<roq::StreamStatus> const &) override;
  bool operator()(Category, Event<roq::ExternalLatency> const &) override;
  bool operator()(Category, Event<roq::GatewayStatus> const &) override;

  bool operator()(Category, Event<roq::ReferenceData> const &) override;
  bool operator()(Category, Event<roq::MarketStatus> const &) override;
  bool operator()(Category, Event<roq::TopOfBook> const &) override;
  bool operator()(Category, Event<roq::MarketByPriceUpdate> const &) override;
  bool operator()(Category, Event<roq::TradeSummary> const &) override;
  bool operator()(Category, Event<roq::StatisticsUpdate> const &) override;

  bool operator()(Category, Event<roq::CreateOrder> const &) override;
  bool operator()(Category, Event<roq::ModifyOrder> const &) override;
  bool operator()(Category, Event<roq::CancelOrder> const &) override;

  bool operator()(Category, Event<roq::OrderAck> const &) override;
  bool operator()(Category, Event<roq::OrderUpdate> const &) override;

  bool operator()(Category, Event<roq::TradeUpdate> const &) override;
  bool operator()(Category, Event<roq::PositionUpdate> const &) override;

  bool operator()(Category, Event<roq::FundsUpdate> const &) override;

  bool operator()(Category, Event<roq::CustomMetricsUpdate> const &) override;

 protected:
  template <typename T, typename U>
  bool dispatch(Category, Event<T> const &, Table<U> &);

  void flush(bool force = false);

  void create_database();
  void create_processed_table();

  void load_processed_table();

  void insert_processed(Category, const UUID &);

 private:
  std::unique_ptr<adapter::Dispatcher> const dispatcher_;
  Settings const &settings_;
  // event-logs
  absl::flat_hash_map<Category, absl::flat_hash_set<UUID>> processed_;
  absl::flat_hash_map<Category, absl::flat_hash_map<UUID, std::string>> feeds_;
  // state
  third_party::clickhouse::Client client_;
  size_t counter_ = {};
  // tables
  Table<GatewaySettings> gateway_settings_;
  Table<StreamStatus> stream_status_;
  Table<ExternalLatency> external_latency_;
  Table<GatewayStatus> gateway_status_;
  Table<ReferenceData> reference_data_;
  Table<MarketStatus> market_status_;
  Table<TopOfBook> top_of_book_;
  Table<MarketByPrice> market_by_price_;
  Table<TradeSummary> trade_summary_;
  Table<Statistics> statistics_;
  Table<CreateOrder> create_order_;
  Table<ModifyOrder> modify_order_;
  Table<CancelOrder> cancel_order_;
  Table<OrderAck> order_ack_;
  Table<Order> order_;
  Table<Trade> trade_;
  Table<Position> position_;
  Table<Funds> funds_;
  Table<CustomMetrics> custom_metrics_;
  // cache
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
