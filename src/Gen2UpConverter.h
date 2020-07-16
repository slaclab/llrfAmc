#ifndef _GEN2UPCONVERTER_H_
#define _GEN2UPCONVERTER_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : Gen2UpConverter Card Driver
 * ----------------------------------------------------------------------------
 * File       : Gen2UpConverter.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the Gen2 up converter card.
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

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>

#include "CpswTopPaths.h"
#include "JesdRx.h"
#include "JesdTx.h"
#include "Lmk04828.h"
#include "Dac38J84.h"
#include "Logger.h"

class IGen2UpConverter;

typedef boost::shared_ptr<IGen2UpConverter>  Gen2UpConverter;

class IGen2UpConverter
{
public:
    IGen2UpConverter(Path p);

    // Factory method, which returns a smart pointer
    static Gen2UpConverter create(Path p);

    bool init();

    bool isInited();

private:
    static const std::string ModuleName;

    Path       root;
    Path       jesdRoot;

    // Devices
    JesdRx     jesdRx;
    JesdTx     jesdTx;
    Lmk04828   lmk;
    Dac38J84   dac;

    // Local commands
    Command    initAmcCardCmd;

    // Logger
    Logger     log;
};

#endif
