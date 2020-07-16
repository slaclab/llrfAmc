#ifndef _JESDTX_H_
#define _JESDTX_H_

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cpsw_api_user.h>

#include "helpers.h"
#include "Logger.h"

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
