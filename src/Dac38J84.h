#ifndef _DAC38J84_H_
#define _DAC38J84_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : Dac38J84 Driver
 * ----------------------------------------------------------------------------
 * File       : Dac38J84.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Low level driver for the Dac38J84 DAC.
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

class IDac38J84;

typedef boost::shared_ptr<IDac38J84> Dac38J84;

class IDac38J84
{
public:
    IDac38J84(Path p);

    // Factory method, which returns a smart pointer
    static Dac38J84 create(Path p);

    void init();
    void initDac();
    void ncoSync();
    void clearAlarms();

    bool isLocked();

private:
    static const std::string ModuleName;
    static const std::size_t MaxNumLanes;

    Path        root;
    ScalVal     enableTxReg;
    Command     clearAlarmsCmd;
    Command     ncoSyncCmd;
    Command     initDacCmd;
    ScalVal     dacReg;
    ScalVal_RO  linkErrCntReg;
    ScalVal_RO  readFifoEmptyReg;
    ScalVal_RO  readFifoUnderflowReg;
    ScalVal_RO  readFifoFullReg;
    ScalVal_RO  readFifoOverflowReg;
    ScalVal_RO  dispErrReg;
    ScalVal_RO  notitableErrReg;
    ScalVal_RO  codeSyncErrReg;
    ScalVal_RO  firstDataMatchErrReg;
    ScalVal_RO  elasticBuffOverflowReg;
    ScalVal_RO  linkConfigErrReg;
    ScalVal_RO  frameAlignErrReg;
    ScalVal_RO  multiFrameAlignErrReg;
    std::size_t numLanes;
    Logger      log;
};

#endif
