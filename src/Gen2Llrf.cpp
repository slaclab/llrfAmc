/**
 *-----------------------------------------------------------------------------
 * Title      : Gen2 LLRF System Driver
 * ----------------------------------------------------------------------------
 * File       : Gen2Llrf.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the LLRF system conformed by the Gen2UpConverter and
 * DownConverter cards.
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
#include "Gen2Llrf.h"

const std::string IGen2Llrf::ModuleName = "Gen2Llrf";

Gen2Llrf IGen2Llrf::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<IGen2Llrf>(p);
}

IGen2Llrf::IGen2Llrf(Path p)
:
    root     ( p ),
    upConv   ( IGen2UpConverter::create(root) ),
    downConv ( IDownConverter::create(root) ),
    log      ( ILogger::create(ModuleName.c_str()) )
{
    log->log(LoggerLevel::Debug, "Object created");
}

bool IGen2Llrf::init() const
{
    log->log(LoggerLevel::Debug, "Initializing...");

    // Initialization sequence
    bool success = downConv->init();
    success &= upConv->init();

    if ( success )
        log->log(LoggerLevel::Debug, "Initialization succeed!");
    else
         log->log(LoggerLevel::Error, "Initialization failed!");

    return success;
}

bool IGen2Llrf::isInited() const
{
    return ( downConv->isInited() & upConv->isInited() );
}

bool IGen2Llrf::isDownConvInited() const
{
    return downConv->isInited();
}

bool IGen2Llrf::isUpConvInited() const
{
    return upConv->isInited();
}

DownConverter IGen2Llrf::getDownConv() const
{
   return downConv;
}

Gen2UpConverter IGen2Llrf::getUpConv() const
{
    return upConv;
}
