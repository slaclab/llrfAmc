#ifndef _JESDTX_H_
#define _JESDTX_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : JesdTx Driver
 * ----------------------------------------------------------------------------
 * File       : JesdTx.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the JesdTx module.
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
#include <cpsw_api_user.h>

#include "helpers.h"
#include "LlrfAmcLogger.h"

class IJesdTx;

typedef boost::shared_ptr<IJesdTx> JesdTx;

class IJesdTx
{
public:
    IJesdTx(Path p);

    // Factory method, which returns a smart pointer
    static JesdTx create(Path p);

    void setEnable(uint32_t enable) const;
    uint32_t getEnable() const;
    void clearErrors() const;
    void resetGTs() const;
    bool isLocked();

private:
    static const std::string ModuleName;
    static const std::size_t MaxNumLanes;

    Path        root;
    ScalVal     enableReg;
    ScalVal_RO  dataValidReg;
    ScalVal_RO  statusValidCntReg;
    ScalVal_RO  sysRefPeriodMinReg;
    ScalVal_RO  sysRefPeriodMaxReg;
    Command     clearErrorsCmd;
    Command     resetGTsCmd;
    std::size_t numLanes;
    Logger      log;
};

#endif
