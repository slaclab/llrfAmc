/**
 *-----------------------------------------------------------------------------
 * Title      : LLRF Down Converter Card Driver
 * ----------------------------------------------------------------------------
 * File       : DownConverter.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the LLRF down converter card.
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
#include "DownConverter.h"

const std::string IDownConverter::ModuleName = "AmcMrLlrfDownConvert";

DownConverter IDownConverter::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<IDownConverter>(p);
}

IDownConverter::IDownConverter(Path p)
:
    root           ( p->findByName( (CpswTopPaths::AppCore + ModuleName).c_str() ) ),
    jesdRoot       ( p->findByName( CpswTopPaths::AppTopJesdBay0.c_str() ) ),
    jesdRx         ( IJesdRx::create(jesdRoot) ),
    lmk            ( ILmk04828::create(root) ),
    initAmcCardCmd ( ICommand::create(root->findByName("InitAmcCard") ) ),
    log            ( ILogger::create(ModuleName.c_str()) )
{
    log->log(LoggerLevel::Debug, "Object created");
}

bool IDownConverter::init()
{
    log->log(LoggerLevel::Debug, "Initializing...");

    // Initialization sequence
    bool success;
    std::size_t maxRetries { 5 };
    for (std::size_t i {1}; i <= maxRetries; ++i)
    {
        log->log(LoggerLevel::Debug, "Initialization try # " + to_string(i) + ":");
        log->log(LoggerLevel::Debug, "===========================");

        // - Power down Lmk sys ref
        lmk->pwrDwnSysRef();
        // - Reset JesdRx GTs
        jesdRx->resetGTs();
        // - Initialize AMC card
        initAmcCardCmd->execute();
        // - Clear JesdRx errors
        jesdRx->clearErrors();

        sleep(1);

        // JESD Link Health Checking
        // - Check JesdRx errors
        success = jesdRx->isLocked();

       if ( success )
       {
           log->log(LoggerLevel::Debug, "Initialization succeed!");
           break;
       }
       else
       {
           if ( i == maxRetries )
           {
                log->log(LoggerLevel::Error, "Initialization failed after " + to_string(maxRetries) + " retries. Aborting!");
               break;
           }
           else
           {
               log->log(LoggerLevel::Warning, "Initialization # " + to_string(i) + " failed. Retying...");
           }
       }
    }

    log->log(LoggerLevel::Debug, "===========================");

    return success;
}

bool IDownConverter::isInited()
{
    log->log(LoggerLevel::Debug, "Checking lock status:");
    log->log(LoggerLevel::Debug, "----------------------------------");

    // Check is JesdRx is locked
    bool success { jesdRx->isLocked() };

    if ( success )
        log->log(LoggerLevel::Debug, "It is locked!");
    else
        log->log(LoggerLevel::Error, "It is not locked!");

    log->log(LoggerLevel::Debug, "----------------------------------");

    return success;
}

