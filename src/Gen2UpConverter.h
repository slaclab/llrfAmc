#ifndef _GEN2UPCONVERTER_H_
#define _GEN2UPCONVERTER_H_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>

#include "CpswTopPaths.h"
#include "JesdRx.h"
#include "JesdTx.h"
#include "Lmk04828.h"
#include "Dac38J84.h"
#include "Logger.h"

class IGen2UpConverter;

typedef boost::shared_ptr<IGen2UpConverter>  Gen2UpConverter;

class IGen2UpConverter
{
public:
    IGen2UpConverter(Path p);

    // Factory method, which returns a smart pointer
    static Gen2UpConverter create(Path p);

    bool init();

    bool isInited();

private:
    static const std::string ModuleName;

    Path       root;
    Path       jesdRoot;

    // Devices
    JesdRx     jesdRx;
    JesdTx     jesdTx;
    Lmk04828   lmk;
    Dac38J84   dac;

    // Local commands
    Command    initAmcCardCmd;

    // Logger
    Logger     log;
};

#endif
