#ifndef _GENUPCONVERTER_H_
#define _GEN1UPCONVERTER_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : Gen1UpConverter Card Driver
 * ----------------------------------------------------------------------------
 * File       : Gen1UpConverter.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-17
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

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>

#include "CpswTopPaths.h"
#include "UpConverter.h"
#include "Ltc2000.h"
#include "Logger.h"

class IGen1UpConverter;

typedef boost::shared_ptr<IGen1UpConverter>  Gen1UpConverter;

class IGen1UpConverter : public IUpConverter
{
public:
    IGen1UpConverter(Path p);

    // Factory method, which returns a smart pointer
    static Gen1UpConverter create(Path p);

    // Module name
    static const std::string ModuleName;

    bool init();

    bool isInited();

private:
    // Devices specific to Gen1 card
    Ltc2000 dac;
};

#endif
