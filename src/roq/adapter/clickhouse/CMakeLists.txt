set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(flags)

set(SOURCES
    application.cpp
    cancel_order.cpp
    controller.cpp
    create_order.cpp
    custom_metrics.cpp
    external_latency.cpp
    funds.cpp
    gateway_settings.cpp
    gateway_status.cpp
    market_by_price.cpp
    market_status.cpp
    modify_order.cpp
    order_ack.cpp
    order.cpp
    position.cpp
    reference_data.cpp
    settings.cpp
    statistics.cpp
    stream_status.cpp
    table.cpp
    top_of_book.cpp
    trade.cpp
    trade_summary.cpp
    main.cpp)

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(
  ${TARGET_NAME}
  PRIVATE ${TARGET_NAME}-flags
          roq-adapter::roq-adapter
          roq-adapter::roq-adapter-flags
          roq-logging::roq-logging
          roq-logging::roq-logging-flags
          roq-flags::roq-flags
          roq-api::roq-api
          fmt::fmt
          absl::flags
          ${CLICKHOUSE_CPP_LIBRARIES}
          ${CITYHASH_LIBRARIES}
          ${LZ4_LIBRARIES}
          ${UUID_LIBRARIES})

set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)

target_compile_definitions(
  ${TARGET_NAME}
  PRIVATE ROQ_PACKAGE_NAME="${TARGET_NAME}" ROQ_BUILD_VERSION="${GIT_REPO_VERSION}"
          ROQ_GIT_DESCRIBE_HASH="${GIT_DESCRIBE_HASH}" ROQ_BUILD_NUMBER="${ROQ_BUILD_NUMBER}"
          ROQ_BUILD_TYPE="${ROQ_BUILD_TYPE}")

install(TARGETS ${TARGET_NAME})
