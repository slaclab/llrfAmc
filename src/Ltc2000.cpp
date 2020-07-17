/**
 *-----------------------------------------------------------------------------
 * Title      : Ltc2000 Driver
 * ----------------------------------------------------------------------------
 * File       : Ltc2000.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the Ltc2000 DAC.
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

#include "Ltc2000.h"

const std::string ILtc2000::ModuleName = "Ltc2000";

Ltc2000 ILtc2000::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<ILtc2000>(p);
}

ILtc2000::ILtc2000(Path p)
:
    root ( p->findByName( ModuleName.c_str() ) ),
    log  ( ILogger::create(ModuleName.c_str()) )
{
    log->log(LoggerLevel::Debug, "Object created.");
}

void ILtc2000::init()
{
    log->log(LoggerLevel::Debug, "Initializing...");

    // It seems like there is not defined way to initialize
    // this DAC. So, this method is empty for now.

    log->log(LoggerLevel::Debug, "Done!");
}

bool ILtc2000::isLocked()
{
    log->log(LoggerLevel::Debug, "Checking lock status:");
    log->log(LoggerLevel::Debug, "----------------------------------");

    bool success { true };

    // It seems like there is not defined way to verify
    // if this DAC is locked. So this method is empty for
    // now, and it will always return 'true'.

    if ( success )
         log->log(LoggerLevel::Debug, "It is locked!");
    else
         log->log(LoggerLevel::Error, "It is not locked!");

    log->log(LoggerLevel::Debug, "----------------------------------");

    return success;
}

