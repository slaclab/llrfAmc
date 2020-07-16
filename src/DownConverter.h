#ifndef _DOWNCONVERTER_H_
#define _DOWNCONVERTER_H_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>

#include "CpswTopPaths.h"
#include "JesdRx.h"
#include "Lmk04828.h"
#include "Logger.h"

class IDownConverter;

typedef boost::shared_ptr<IDownConverter> DownConverter;

class IDownConverter
{
public:
    IDownConverter(Path p);

    // Factory method, which returns a smart pointer
    static DownConverter create(Path p);

    bool init();

    bool isInited();

private:
    static const std::string ModuleName;

    Path       root;
    Path       jesdRoot;

    // Devices
    JesdRx     jesdRx;
    Lmk04828   lmk;

    // Local commands
    Command    initAmcCardCmd;

    // Logger
    Logger     log;
};

#endif
