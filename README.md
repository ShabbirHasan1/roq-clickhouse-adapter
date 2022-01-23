# roq-clickhouse-adapter

* Creates ClickHouse tables on start-up.
* Using the `roq-adapter` library to implement a monitor of event-log files.
* Receives updates on new event-log files and messages being appended to already discovered files.
* Converts messages to ClickHouse table inserts.
* Maintains a ClickHouse table with processed event-logs (to avoid re-inserting).


## Operating Systems

* Linux (x86-64, AArch64)


## Building

These are the steps required to build from source

```bash
wget -N https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-Linux-x86_64.sh

bash Miniforge3-Linux-x86_64.sh -b -p opt/conda

source opt/conda/bin/activate

conda install -y \
    'gxx_linux-64>=12' \
    git \
    make \
    cmake \
    abseil-cpp \
    catch2

conda install -y --channel https://roq-trading.com/conda/stable \
    roq-adapter \
    roq-oss-clickhouse-cpp

git clone https://github.com/roq-trading/roq-clickhouse-adapter

cd roq-clickhouse-adapter

git submodule update --init --recursive

cmake .

make -j4
```

> This is a reference implementation.
> You are free to fork and modify the project if you need a custom format.


## Downloading

### Conda

```bash
wget -N https://github.com/conda-forge/miniforge/releases/latest/download/Miniforge3-Linux-x86_64.sh

bash Miniforge3-Linux-x86_64.sh -b -p opt/conda

source opt/conda/bin/activate

conda install -y --channel https://roq-trading.com/conda/stable \
    roq-clickhouse-adapter
```

### Docker

```bash
podman pull docker.io/roqtrading/roq-clickhouse-adapter
```


## Using

### Conda

```bash
roq-clickhouse-adapter \
    --name=clickhouse \
    --event_log_dir=$HOME/var/lib/roq/data
```

### Docker

```bash
podman exec -it docker.io/roqtrading/roq-clickhouse-adapter \
    --name=clickhouse \
    --event_log_dir=$HOME/var/lib/roq/data
```


## Dependencies

* [Abseil-C++](https://github.com/abseil/abseil-cpp) (Apache 2.0 License)
* [Catch2](https://github.com/catchorg/Catch2) (BSL 1.0 License)
* [ClickHouse-CPP](https://github.com/ClickHouse/clickhouse-cpp) (Apache 2.0 License)
* [FlatBuffers](https://github.com/google/flatbuffers) (Apache 2.0 License)
* [fmt](https://github.com/fmtlib/fmt) (MIT License)
* [magic\_enum](https://github.com/Neargye/magic_enum) (MIT License)
* [range-v3](https://github.com/ericniebler/range-v3) (BSL 1.0 License)
* [span-lite](https://github.com/martinmoene/span-lite) (BSL 1.0 License)
* [roq-api](https://github.com/roq-trading/roq-api) (MIT License)
* [roq-logging](https://github.com/roq-trading/roq-api) (MIT License)
* roq-adapter (Commerical License, free to use)


## License

The project is released under the terms of the BSD 3-Clause license.


## Links

* [Roq GmbH](https://roq-trading.com/)
* [Documentation](https://roq-trading.com/docs/)
* [Contact us](mailto:info@roq-trading.com)
