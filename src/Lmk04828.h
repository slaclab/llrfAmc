#ifndef _LMK04828_H_
#define _LMK04828_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : Lmk04828 Driver
 * ----------------------------------------------------------------------------
 * File       : Lmk04828.h
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

#include <string>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cpsw_api_user.h>

#include "helpers.h"
#include "LlrfAmcLogger.h"

class ILmk04828;

typedef boost::shared_ptr<ILmk04828> Lmk04828;

class ILmk04828
{
public:
    ILmk04828(Path p);

    // Factory method, which returns a smart pointer
    static Lmk04828 create(Path p);

    void pwrDwnSysRef();

private:
    static const std::string ModuleName;

    Path        root;
    Command     pwrDwnSysRefCmd;
    Logger      log;
};

#endif
