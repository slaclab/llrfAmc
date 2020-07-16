/**
 *-----------------------------------------------------------------------------
 * Title      : JesdTx Driver
 * ----------------------------------------------------------------------------
 * File       : JesdTx.cpp
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

#include "JesdTx.h"

const std::string IJesdTx::ModuleName  = "JesdTx";
const std::size_t IJesdTx::MaxNumLanes = 8;

JesdTx IJesdTx::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<IJesdTx>(p);
}

IJesdTx::IJesdTx(Path p)
:
    root               ( p->findByName( ModuleName.c_str() ) ),
    enableReg          ( IScalVal::create( root->findByName("Enable") ) ),
    dataValidReg       ( IScalVal_RO::create( root->findByName("DataValid") ) ),
    statusValidCntReg  ( IScalVal_RO::create( root->findByName("StatusValidCnt") ) ),
    sysRefPeriodMinReg ( IScalVal_RO::create( root->findByName("SysRefPeriodmin") ) ),
    sysRefPeriodMaxReg ( IScalVal_RO::create( root->findByName("SysRefPeriodmax") ) ),
    clearErrorsCmd     ( ICommand::create( root->findByName("ClearTxStatus") ) ),
    resetGTsCmd        ( ICommand::create( root->findByName("ResetTxGTs") ) ),
    numLanes           ( enableReg->getSizeBits() ),
    log                ( ILogger::create(ModuleName.c_str()) )
{
    log->log(LoggerLevel::Debug, "Object created. Number of lanes = " + to_string(numLanes));
}

bool IJesdTx::isLocked()
{
    log->log(LoggerLevel::Debug, "Checking lock status:");
    log->log(LoggerLevel::Debug, "----------------------------------");

    bool success { true };

    // Verify that SysRefPeriodMin == SysRefPeriodMax
    uint32_t sysRefPeriodMin, sysRefPeriodMax;
    sysRefPeriodMinReg->getVal(&sysRefPeriodMin);
    sysRefPeriodMaxReg->getVal(&sysRefPeriodMax);
    log->log(LoggerLevel::Debug, "SysRefPeriodMin = " + to_string(sysRefPeriodMin));
    log->log(LoggerLevel::Debug, "SysRefPeriodMax = " + to_string(sysRefPeriodMax));
    success = (sysRefPeriodMin == sysRefPeriodMax);

    // Check that all the enabled lanes have DataValid
    // - Get the enable mask
    uint32_t enable;
    enableReg->getVal(&enable);
    log->log(LoggerLevel::Debug, "Enable = " + to_string(enable));
    // - Get the DataValid values
    std::vector<uint32_t> vec(numLanes);
    dataValidReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(dataValidReg->getName(), vec));
    // - Finally, compare the DataValid (converted to word) and enable mask
    success &= ( vec2word(vec) == enable );

    // Check that the status valid counters are zero
    statusValidCntReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(statusValidCntReg->getName(), vec));
    success &= allZeros(vec);

    if ( success )
        log->log(LoggerLevel::Debug, "It is locked!");
    else
        log->log(LoggerLevel::Error, "It is not locked!");

    log->log(LoggerLevel::Debug, "----------------------------------");

    return success;
}

void IJesdTx::setEnable(uint32_t enable) const
{
    enableReg->setVal(&enable);
}

uint32_t IJesdTx::getEnable() const
{
    uint32_t u32;
    enableReg->getVal(&u32);
    return u32;
}

void IJesdTx::clearErrors() const
{
    // We will use the Command defined in YAML
    clearErrorsCmd->execute();
}

void IJesdTx::resetGTs() const
{
    // We will use the Command defined in YAML
    resetGTsCmd->execute();
}
