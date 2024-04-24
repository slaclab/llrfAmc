/**
 *-----------------------------------------------------------------------------
 * Title      : Dac38J84 Driver
 * ----------------------------------------------------------------------------
 * File       : Dac38J84.cpp
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

#include "Dac38J84.h"

const std::string IDac38J84::ModuleName = "Dac38J84";
const std::size_t IDac38J84::MaxNumLanes = 8;

Dac38J84 IDac38J84::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<IDac38J84>(p);
}

IDac38J84::IDac38J84(Path p)
:
    root                   ( p->findByName( ModuleName.c_str() ) ),
    enableTxReg            ( IScalVal::create( root->findByName("EnableTx") )  ),
    laneEnableReg          ( IScalVal_RO::create( root->findByName("LaneEnable") ) ),
    clearAlarmsCmd         ( ICommand::create( root->findByName("ClearAlarms") ) ),
    ncoSyncCmd             ( ICommand::create( root->findByName("NcoSync") ) ),
    initDacCmd             ( ICommand::create( root->findByName("InitDac") ) ),
    dacReg                 ( IScalVal::create( root->findByName("DacReg") )    ),
    linkErrCntReg          ( IScalVal_RO::create( root->findByName("LinkErrCnt") ) ),
    readFifoEmptyReg       ( IScalVal_RO::create( root->findByName("ReadFifoEmpty") ) ),
    readFifoUnderflowReg   ( IScalVal_RO::create( root->findByName("ReadFifoUnderflow") ) ),
    readFifoFullReg        ( IScalVal_RO::create( root->findByName("ReadFifoFull") ) ),
    readFifoOverflowReg    ( IScalVal_RO::create( root->findByName("ReadFifoOverflow") ) ),
    dispErrReg             ( IScalVal_RO::create( root->findByName("DispErr") ) ),
    notitableErrReg        ( IScalVal_RO::create( root->findByName("NotitableErr") ) ),
    codeSyncErrReg         ( IScalVal_RO::create( root->findByName("CodeSyncErr") ) ),
    firstDataMatchErrReg   ( IScalVal_RO::create( root->findByName("FirstDataMatchErr") ) ),
    elasticBuffOverflowReg ( IScalVal_RO::create( root->findByName("ElasticBuffOverflow") ) ),
    linkConfigErrReg       ( IScalVal_RO::create( root->findByName("LinkConfigErr") ) ),
    frameAlignErrReg       ( IScalVal_RO::create( root->findByName("FrameAlignErr") ) ),
    multiFrameAlignErrReg  ( IScalVal_RO::create( root->findByName("MultiFrameAlignErr") ) ),
    Serdes0pllAlarmReg     ( IScalVal_RO::create( root->findByName("Serdes0pllAlarm") ) ),
    SysRefAlarmsReg        ( IScalVal_RO::create( root->findByName("SysRefAlarms") ) ),
    numLanes               ( linkErrCntReg->getNelms() ),
    log                    ( ILogger::create(ModuleName.c_str()) )
{

    log->log(LoggerLevel::Debug, "Object created. Number of lanes = " + to_string(numLanes));

    laneEnableReg->getVal(&laneEnable);
    log->log(LoggerLevel::Debug, "laneEnable = " + to_string(laneEnable));

}

void IDac38J84::init()
{
    log->log(LoggerLevel::Debug, "Initializing...");

    enableTxReg->setVal(0ul);
    usleep(10000);

    clearAlarmsCmd->execute();
    usleep(10000);

    uint32_t u32;
    IndexRange rng(59);
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 37;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    // Set and Reset Bit 9 – VRANGE, select between high and low VCO.
    rng = 60;
    dacReg->getVal(&u32, 1, &rng);
    u32 |= 0x200;
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);
    u32 &= 0xFDFF;
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 62;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 76;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 77;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);


    rng = 75;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 77;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 78;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 0;
    dacReg->getVal(&u32, 1, &rng);
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    rng = 74;
    dacReg->getVal(&u32, 1, &rng);
    u32 &= 0xFFE0;
    u32 |= 0x1E;
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    dacReg->getVal(&u32, 1, &rng);
    u32 &= 0xFFE0;
    u32 |= 0x1F;
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    dacReg->getVal(&u32, 1, &rng);
    u32 &= 0xFFE0;
    u32 |= 0x01;
    dacReg->setVal(&u32, 1, &rng);
    usleep(10000);

    enableTxReg->setVal(1ul);
    usleep(10000);

    log->log(LoggerLevel::Debug, "Done!");
}

void IDac38J84::initDac()
{
    // We will use the Command defined in YAML
    initDacCmd->execute();
}

void IDac38J84::ncoSync()
{
    // We will use the Command defined in YAML
    ncoSyncCmd->execute();
}

void IDac38J84::clearAlarms()
{
    // We will use the Command defined in YAML
    clearAlarmsCmd->execute();
}

bool IDac38J84::isLocked()
{
    log->log(LoggerLevel::Debug, "Checking lock status:");
    log->log(LoggerLevel::Debug, "----------------------------------");

    bool success { true };

    std::vector<uint32_t> vec(numLanes);

    linkErrCntReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(linkErrCntReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    readFifoEmptyReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(readFifoEmptyReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    readFifoUnderflowReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(readFifoUnderflowReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    readFifoFullReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(readFifoFullReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    readFifoOverflowReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(readFifoOverflowReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    dispErrReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(dispErrReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    notitableErrReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(notitableErrReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    codeSyncErrReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(codeSyncErrReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    firstDataMatchErrReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(firstDataMatchErrReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    elasticBuffOverflowReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(elasticBuffOverflowReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    linkConfigErrReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(linkConfigErrReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    frameAlignErrReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(frameAlignErrReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    multiFrameAlignErrReg->getVal(vec.data(), vec.size());
    log->log(LoggerLevel::Debug, vec2str(multiFrameAlignErrReg->getName(), vec));
    success &= (0 == ( vec2word(vec) & laneEnable ));

    uint32_t val;
    Serdes0pllAlarmReg->getVal(&val);
    log->log(LoggerLevel::Debug, "Serdes0pllAlarm =" + to_string(val));
    success &= (val == 0);

    SysRefAlarmsReg->getVal(&val);
    log->log(LoggerLevel::Debug, "SysRefAlarm =" + to_string(val));
    success &= (val == 0);


    if ( success )
         log->log(LoggerLevel::Debug, "It is locked!");
    else
         log->log(LoggerLevel::Error, "It is not locked!");

    log->log(LoggerLevel::Debug, "----------------------------------");

    return success;
}

