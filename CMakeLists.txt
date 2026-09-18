#----------------------------------------------------------------------------#
# Company    : SLAC National Accelerator Laboratory
#----------------------------------------------------------------------------#
# Description: Root CMake script for llrfAmc
#----------------------------------------------------------------------------#
# This file is part of 'llrfAmc'. It is subject to the license terms 
# in the LICENSE.txt file found in the top-level directory of this
# distribution, and at:
#    https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
# No part of 'llrfAmc', including this file, may be copied, modified,
# propagated, or distributed except according to the terms contained in
# the LICENSE.txt file.
#----------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.18)

project(llrfAmc C CXX)

find_package(PkgConfig REQUIRED)

# Setup our dependencies
include (config.cmake)

include ("${CPSW_TOP}/cmake/CpswUtils.cmake")

cpsw_package_init()

if (WITH_TIRPC)
    find_package(TIRPC REQUIRED)
endif()

# Required for cpsw::shared_ptr
if (WITH_BOOST)
    find_package(Boost REQUIRED)
    message(STATUS "Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
endif()

add_subdirectory(src)
