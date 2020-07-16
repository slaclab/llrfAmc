#ifndef _GEN2LLRF_H_
#define _GEN2LLRF_H_

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <yaml-cpp/yaml.h>
#include <cpsw_api_user.h>

#include "Gen2UpConverter.h"
#include "DownConverter.h"
#include "Logger.h"

class IGen2Llrf;

typedef boost::shared_ptr<IGen2Llrf> Gen2Llrf;

class IGen2Llrf
{
public:
    IGen2Llrf(Path p);

    // Factory method, which returns a smart pointer
    static Gen2Llrf create(Path p);

    // Call initialization sequence of both cards
    bool init() const;

    // Check if the down converter card is initialized
    bool isDownConvInited() const;

    // Check if the up converter card is initialized
    bool isUpConvInited() const;

    // Check is both cards are initialized
    bool isInited() const;

    // Get copies of the Down and Up converter objects
    DownConverter   getDownConv() const;
    Gen2UpConverter getUpConv() const;

private:
    static const std::string ModuleName;

    Path            root;

    // Devices
    Gen2UpConverter upConv;
    DownConverter   downConv;

    // Logger
    Logger          log;
};

#endif
