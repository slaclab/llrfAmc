#ifndef _LMK04828_H_
#define _LMK04828_H_

#include <string>
#include <unistd.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <cpsw_api_user.h>

#include "helpers.h"
#include "Logger.h"

class ILmk04828;

typedef boost::shared_ptr<ILmk04828> Lmk04828;

class ILmk04828
{
public:
    ILmk04828(Path p);

    // Factory method, which returns a smart pointer
    static Lmk04828 create(Path p);

    void pwrDwnSysRef();

private:
    static const std::string ModuleName;

    Path        root;
    Command     pwrDwnSysRefCmd;
    Logger      log;
};

#endif
