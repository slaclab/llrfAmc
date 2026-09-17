#----------------------------------------------------------------------------#
# Company    : SLAC National Accelerator Laboratory
#----------------------------------------------------------------------------#
# Description:
#----------------------------------------------------------------------------#
# This file is part of 'llrfAmc'. It is subject to the license terms 
# in the LICENSE.txt file found in the top-level directory of this
# distribution, and at:
#    https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
# No part of 'llrfAmc', including this file, may be copied, modified,
# propagated, or distributed except according to the terms contained in
# the LICENSE.txt file.
#----------------------------------------------------------------------------#

cpsw_add_library(
    llrfAmc

    CpswTopPaths.h
    Dac38J84.cpp
    Dac38J84.h
    DownConverter.cpp
    DownConverter.h
    Gen1UpConverter.cpp
    Gen1UpConverter.h
    Gen2UpConverter.cpp
    Gen2UpConverter.h
    helpers.cpp
    helpers.h
    JesdRx.cpp
    JesdRx.h
    JesdTx.cpp
    JesdTx.h
    LlrfAmc.cpp
    LlrfAmc.h
    LlrfAmcLogger.cpp
    LlrfAmcLogger.h
    Lmk04828.cpp
    Lmk04828.h
    Ltc2000.cpp
    Ltc2000.h
    UpConverter.cpp
    UpConverter.h
)

install(
    FILES

        CpswTopPaths.h
        Dac38J84.h
        DownConverter.h
        Gen1UpConverter.h
        Gen2UpConverter.h
        helpers.h
        JesdRx.h
        JesdTx.h
        LlrfAmc.h
        LlrfAmcLogger.h
        Lmk04828.h
        Ltc2000.h
        UpConverter.h
    TYPE INCLUDE
)

add_executable(
    llrfAmc_check_dac
    
    test/check_dac.cpp
)

add_executable(
    llrf

    test/llrf.cpp
)

add_executable(
    llrfAmc_saveConfig
    
    test/saveConfig.cpp
)

target_link_libraries(llrfAmc_check_dac PRIVATE llrfAmc-static cpsw.a yaml-cpp.a ${TIRPC_LIBRARIES})
target_link_libraries(llrf PRIVATE llrfAmc-static cpsw.a yaml-cpp.a ${TIRPC_LIBRARIES})
target_link_libraries(llrfAmc_saveConfig PRIVATE llrfAmc-static cpsw.a yaml-cpp.a ${TIRPC_LIBRARIES})

install(TARGETS llrfAmc_check_dac llrfAmc_saveConfig llrf)

add_definitions(
    -DFRAMEWORK_R3_4
)

# Must be -isystem to allow for <> resolve properly
include_directories(
    SYSTEM "${CMAKE_CURRENT_LIST_DIR}"
)

