#ifndef _DAC38J84_H_
#define _DAC38J84_H_

#include <string>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cpsw_api_user.h>

#include "helpers.h"
#include "Logger.h"

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

    bool isLocked(bool verbose = false);

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
