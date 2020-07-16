/**
 *-----------------------------------------------------------------------------
 * Title      : Lmk04828 Driver
 * ----------------------------------------------------------------------------
 * File       : Lmk04828.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the Lmk04828 device.
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

#include "Lmk04828.h"

const std::string ILmk04828::ModuleName = "Lmk04828";

Lmk04828 ILmk04828::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<ILmk04828>(p);
}

ILmk04828::ILmk04828(Path p)
:
    root            ( p->findByName( ModuleName.c_str() ) ),
    pwrDwnSysRefCmd ( ICommand::create( root->findByName("PwrDwnSysRef") ) ),
    log             ( ILogger::create(ModuleName.c_str()) )
{
    log->log(LoggerLevel::Debug, "Object created");
}

void ILmk04828::pwrDwnSysRef()
{
    // We will use the Command defined in YAML
    pwrDwnSysRefCmd->execute();
}
