# OpenDMI

OpenDMI is a cross-platform, commercial-grade DMI/SMBIOS framework, focused on functionality and ease of use. It provides direct access to all of the DMI/SMBIOS data, command line tools, bindings for major programming languages and even more.

## Highlights

* Platform-agnostic access to DMI/SMBIOS structures
* Bindings for C, C++, Python and Go languages
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

## Licensing

OpenDMI is licensed under BSD 3-clause license. See `LICENSE` for details.
