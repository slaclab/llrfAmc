#ifndef _JESDRX_H_
#define _JESDRX_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : JesdRx Driver
 * ----------------------------------------------------------------------------
 * File       : JesdRx.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the JesdRx module.
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

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <algorithm>
#include <cpsw_api_user.h>

#include "helpers.h"
#include "Logger.h"

class IJesdRx;

typedef boost::shared_ptr<IJesdRx> JesdRx;

class IJesdRx
{
public:
    IJesdRx(Path p);

    // Factory method, which returns a smart pointer
    static JesdRx create(Path p);

    void     setEnable(uint32_t enable) const;
    uint32_t getEnable() const;
    void     clearErrors() const;
    void     resetGTs() const;
    bool     isLocked();

private:
    static const std::string ModuleName;
    static const std::size_t MaxNumLanes;

    Path        root;
    ScalVal     enableReg;
    ScalVal_RO  dataValidReg;
    ScalVal_RO  statusValidCntReg;
    ScalVal_RO  sysRefPeriodMinReg;
    ScalVal_RO  sysRefPeriodMaxReg;
    ScalVal_RO  positionErrReg;
    ScalVal_RO  alignErrReg;
    Command     clearErrorsCmd;
    Command     resetGTsCmd;
    std::size_t numLanes;
    Logger      log;
};

#endif
