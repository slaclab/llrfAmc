# LLRF AMC card low level driver

[DOE Code](https://www.osti.gov/doecode/biblio/79168)

## Description

This is a low level driver for the LLRF AMC cards. The driver is based on CPSW and implement low level routines to configure the different LLRF AMC cards:
- Gen1 UpConverter
- Gen2 UpConverter
- DownConverter

The driver also implements health checks to verify that the different JESD links are locked and stable.

## How the driver works

The top level if the [LlrfAmc](src/LlrfAmc.h) class. When and `LlrfAmc` object is created, it will automatically detect the type of AMC cards used in your application. The cards are detected based on the devices defined in the YAML files. the driver will look for the DownConverter and UpConverter devices under `/mmio/AppTop/AppCore`:
- First, it will look for the DownConverter device. Currently, only the device called `AmcMrLlrfDownConvert` is supported.
- Then, it will look for a UpConveter device. Currently there are two type of devices supported:
  - The Gen1 UpConverter device called `AmcMrLlrfUpConvert`,
  - The Gen2 UpConverter device called `AmcMrLlrfGen2UpConvert`

If the DownConverter or either of the UpConverter devices is not found, an `std::runtime_error` exception is thrown.

Once the `LlrfAmc` object is created, it provides several methods. Among then we have:
- `void init()`: Call initialization sequence of both cards,
- `bool isDownConvLocked()`: Check if the down converter card is locked,
- `bool isUpConvLocked()`: Check if the up converter card is locked,
- `bool bool isLocked()`: Check is both cards are locked

For a complete list refer to the [LlrfAmc.h](src/LlrfAmc.h) header file.

### Note about the initialization method

The initialization sequence executed by the `init()` method requires that the defaults YAML configuration is already loaded when the method is called. You can take a look at the [llrf.cpp](src/test/llrf.cpp) test application as an example.

## Installation Instructions

### CMake

To build with the CMake build system, use the standard `cmake-configure.sh` script provided with CPSW:
```
$PACKAGE_SITE_TOP/cpsw/framework/R4.7.0/cmake/cmake-configure-pkg.sh -p $PACKAGE_SITE_TOP/cpsw/framework/R4.7.0 -b
```

Where `-p` defines the location of CPSW itself, `-b` tells the script to run the build instead of just configuring.
Use `cmake-configure-pkg.sh --help` to see the rest of the options and usage examples.

Advanced users can configure with `cmake` directly, but you'll need to supply a CMake toolchain file for the cross targets.

### Make

Run `make` and `make install` to build for all available targets. The CPSW path and version are hardcoded in src/makefile.

## Copyright Notice:

COPYRIGHT © SLAC National Accelerator Laboratory. All rights reserved. 
This work is supported [in part] by the U.S. Department of Energy, Office of Basic Energy Sciences under contract DE-AC02-76SF00515.

## Usage Restrictions:

Neither the name of the Leland Stanford Junior University, SLAC National Accelerator Laboratory, U.S. Department of Energy 
nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
