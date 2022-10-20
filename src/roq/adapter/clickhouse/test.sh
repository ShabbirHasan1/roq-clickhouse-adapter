#!/usr/bin/env bash

# debug?

if [ "$1" == "debug" ]; then
  KERNEL="$(uname -a)"
  case "$KERNEL" in
    Linux*)
      PREFIX="gdb --args"
      ;;
    Darwin*)
      PREFIX="lldb --"
      ;;
  esac
  shift 1
else
  PREFIX=
fi

# launch

$PREFIX "./roq-clickhouse-adapter" \
  --name=clickhouse \
  --metrics_listen_address=1234 \
  --event_log_dir=$HOME/var/lib/roq/data \
  $@
