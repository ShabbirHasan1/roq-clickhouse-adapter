/* Copyright (c) 2017-2022, Hans Erik Thrane */

#pragma once

#include "roq/service.hpp"

namespace roq {
namespace adapter {
namespace clickhouse {

class Application final : public roq::Service {
 public:
  using roq::Service::Service;

 protected:
  int main(int argc, char **argv) override;
};

}  // namespace clickhouse
}  // namespace adapter
}  // namespace roq
