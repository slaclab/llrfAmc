#include "Lmk04828.h"

const std::string ILmk04828::ModuleName = "Lmk04828";

Lmk04828 ILmk04828::create(Path p)
{
    if(!p)
        throw std::runtime_error(ModuleName + " : The root Path is empty");

    return boost::make_shared<ILmk04828>(p);
}

ILmk04828::ILmk04828(Path p)
:
    root            ( p->findByName( ModuleName.c_str() ) ),
    pwrDwnSysRefCmd ( ICommand::create( root->findByName("PwrDwnSysRef") ) ),
    log             ( ILogger::create(ModuleName.c_str()) )
{
    log->log(LoggerLevel::Debug, "Object created");
}

void ILmk04828::pwrDwnSysRef()
{
    // We will use the Command defined in YAML
    pwrDwnSysRefCmd->execute();
}
