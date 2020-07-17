/**
 *-----------------------------------------------------------------------------
 * Title      : UpConverter Card Driver
 * ----------------------------------------------------------------------------
 * File       : UpConverter.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-17
 * ----------------------------------------------------------------------------
 * Description:
 * Base class for the low level driver for the up converter card. 
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
#include "UpConverter.h"

IUpConverter::IUpConverter(Path p, const std::string& moduleName)
:
    root           ( p->findByName( (CpswTopPaths::AppCore + moduleName).c_str() ) ),
    jesdRoot       ( p->findByName( CpswTopPaths::AppTopJesdBay1.c_str() ) ),
    jesdRx         ( IJesdRx::create(jesdRoot) ),
    jesdTx         ( IJesdTx::create(jesdRoot) ),
    lmk            ( ILmk04828::create(root) ),
    initAmcCardCmd ( ICommand::create(root->findByName("InitAmcCard") ) ),
    log            ( ILogger::create(moduleName.c_str()) )
{
}
