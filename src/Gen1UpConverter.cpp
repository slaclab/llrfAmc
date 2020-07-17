/**
 *-----------------------------------------------------------------------------
 * Title      : Gen1UpConverter Card Driver
 * ----------------------------------------------------------------------------
 * File       : Gen1UpConverter.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the Gen1 up converter card.
 * ----------------------------------------------------------------------------
 * This file is part of llrfAmc. It is subject to
 * the license terms in the LICENSE.txt file found in the top-level directory
 * of this distribution and at:
    * https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
 * No part of llrfAmc, including this file, may be
 * copied, modified, propagated, or distributed except according to the terms
 * contained in the LICENSE.txt file.
 * ----------------------------------------------------------------------------
**/

#include <unistd.h>
#include "Gen1UpConverter.h"

const std::string IGen1UpConverter::ModuleName = "AmcMrLlrfGen1UpConvert";

Gen1UpConverter IGen1UpConverter::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<IGen1UpConverter>(p);
}

IGen1UpConverter::IGen1UpConverter(Path p)
:
    IUpConverter   ( p, ModuleName )
    //dac            ( DacLtc2000::create(root) )
{
     log->log(LoggerLevel::Debug, "Object created");
}

std::string IGen1UpConverter::getModuleName()
{
    return ModuleName;
}

bool IGen1UpConverter::init()
{
    log->log(LoggerLevel::Debug, "Initializing...");

    // Initialization sequence
    bool success = true;

    return success;
}

bool IGen1UpConverter::isInited()
{
    log->log(LoggerLevel::Debug, "Checking lock status:");
    log->log(LoggerLevel::Debug, "----------------------------------");

    bool success { true };

    // Check if DAC is locked
    //success &= dac->isLocked();

    // Check is JesdRx is locked
    success &= jesdRx->isLocked();

    // Check if JesdTx is locked
    success &= jesdTx->isLocked();

    if ( success )
        log->log(LoggerLevel::Debug, "It is locked!");
    else
        log->log(LoggerLevel::Error, "It is not locked!");

    log->log(LoggerLevel::Debug, "----------------------------------");

    return success;
}

