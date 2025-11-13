# OpenDMI

OpenDMI is a cross-platform, commercial-grade DMI/SMBIOS framework, focused on functionality and ease of use. It provides direct access to all of the DMI/SMBIOS data, command line tools, bindings for major programming languages and even more.

## Highlights

* Platform-agnostic access to DMI/SMBIOS structures
* Full SMBIOS support up to version 3.9
* Bindings for C, C++, Python and Go languages
* Modular extensions for handling OEM-specific structures
* Shell interface compatible with `dmidecode`
* JSON and XML output support for automation purposes
* Works on Linux, MacOS, BSD and Windows platforms
* Small footprint, no external dependencies

## Building

### Prerequisites

* GCC, CLang or MSVC compiler
* CMake 4.1 or newer

### Configuration

Use the following command to configure build:

```sh
$ cmake .
```

This produces a debug build by default. Optimisation isn't enabled, and debug
assertions are included. Pass `-DCMAKE_BUILD_TYPE=Release` to `cmake` to
configure a release build:

```sh
$ cmake -DCMAKE_BUILD_TYPE=Release .
```

### Testing

OpenDMI uses the CTest framework for testing. You can simply run it to ensure
that build was successful:

```sh
$ ctest
```

## Contributing

The project is under active development. Please feel free to test it and create
create bug reports or feature requests on GitHub. You can also help the project
by sending SMBIOS dumps to the authors. To get the dump you can use the following
command:

```sh
$ dmidecode --dump-bin <filename>
```

## Authors

* [Dmitry Sednev](https://github.com/sdnvx) (<dmitry@sednev.ru>)

## Licensing

OpenDMI is licensed under BSD 3-clause license. See `LICENSE` for details.
