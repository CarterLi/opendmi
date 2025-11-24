# OpenDMI

OpenDMI is a cross-platform, commercial-grade DMI/SMBIOS framework, focused on functionality and ease of use. It provides direct access to all of the DMI/SMBIOS data, command line tools, bindings for major programming languages and even more.

The project is under active development, see [ROADMAP](ROADMAP.md) and [CHANGELOG](CHANGELOG.md) for details.

## Highlights

* Platform-agnostic access to DMI/SMBIOS structures.
* Full SMBIOS support up to version 3.9.
* Bindings for C, C++, Python, Go and Rust languages.
* Modular extensions for handling OEM-specific structures.
* JSON and XML output support for automation purposes.
* Works on Linux, MacOS, BSD and Windows platforms.
* Small footprint, no external dependencies.

## Components

* `opendmi` - Command line tool to query DMI/SMBIOS data
* `opendmi-dbus` - D-bus service providing access to DMI/SMBIOS data
* `libopendmi` - C library providing direct interface to DMI/SMBIOS
* `libopendmi-go` - Go bindings for `libopendmi`
* `libopendmi-python` - Python bindings for `libopendmi`
* `libopendmi-rust` - Rust bindings for `libopendmi`
* `libopendmi++` - Pure C++ version of `libopendmi`

## Building from sources

### Prerequisites

* GCC, CLang or MSVC compiler
* CMake 3.30 or newer
* AsciiDoctor (used to generate documentation and man pages)

### Configuring

Use the following command to configure OpenDMI build:

```sh
$ cmake -B build
```

This produces a debug build by default. Optimization isn't enabled, and debug
assertions are included. Pass `-DCMAKE_BUILD_TYPE=Release` to `cmake` to
configure a release build:

```sh
$ cmake -B build -DCMAKE_BUILD_TYPE=Release
```

### Building

Use the following command to build OpenDMI:

```sh
$ cmake --build build
```

### Testing

OpenDMI uses the CTest framework for testing. You can simply run it to ensure
that build was successful:

```sh
$ ctest
```

## Contributing

Please feel free to test it and create create bug reports or feature requests
on GitHub. You can also help the project by sending SMBIOS dumps to the
authors. To get the dump you can use the following command:

```sh
$ dmidecode --dump-bin <filename>
```

## Authors

* [Dmitry Sednev](https://github.com/sdnvx) (<dmitry@sednev.ru>)

## Licensing

OpenDMI is licensed under BSD 3-clause license. See `LICENSE` for details.
