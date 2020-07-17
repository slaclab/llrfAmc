#ifndef _DOWNCONVERTER_H_
#define _DOWNCONVERTER_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : LLRF Down Converter Card Driver
 * ----------------------------------------------------------------------------
 * File       : DownConverter.h
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

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>

#include "CpswTopPaths.h"
#include "JesdRx.h"
#include "Lmk04828.h"
#include "Logger.h"

class IDownConverter;

typedef boost::shared_ptr<IDownConverter> DownConverter;

class IDownConverter
{
public:
    IDownConverter(Path p);

    // Factory method, which returns a smart pointer
    static DownConverter create(Path p);

    static std::string getModuleName();

    bool init();

    bool isInited();

private:
    static const std::string ModuleName;

    Path       root;
    Path       jesdRoot;

    // Devices
    JesdRx     jesdRx;
    Lmk04828   lmk;

    // Local commands
    Command    initAmcCardCmd;

    // Logger
    Logger     log;
};

#endif
