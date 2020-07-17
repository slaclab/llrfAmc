#ifndef _LTC2000_H_
#define _LTC2000_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : Ltc2000 Driver
 * ----------------------------------------------------------------------------
 * File       : Ltc2000.h
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

#include <string>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cpsw_api_user.h>

#include "helpers.h"
#include "Logger.h"

class ILtc2000;

typedef boost::shared_ptr<ILtc2000> Ltc2000;

class ILtc2000
{
public:
    ILtc2000(Path p);

    // Factory method, which returns a smart pointer
    static Ltc2000 create(Path p);

    void init();

    bool isLocked();

private:
    static const std::string ModuleName;

    Path        root;
    Logger      log;
};

#endif
