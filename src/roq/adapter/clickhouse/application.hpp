/* Copyright (c) 2017-2023, Hans Erik Thrane */

#pragma once

#include "roq/service.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

struct Application final : public roq::Service {
  using roq::Service::Service;

 protected:
  int main(int argc, char **argv) override;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
