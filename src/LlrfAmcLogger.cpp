/**
 *-----------------------------------------------------------------------------
 * Title      : Simple Logger
 * ----------------------------------------------------------------------------
 * File       : LlrfAmcLogger.cpp
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * Simple logger class.
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

#include "LlrfAmcLogger.h"

LoggerLevel ILogger::globalLevel = LoggerLevel::Error;

Logger ILogger::create(const std::string& n)
{
    if(n.empty())
        throw std::runtime_error("Logger created without a name!");

    return boost::make_shared<ILogger>(n);
}

ILogger::ILogger(const std::string& n)
:
    name(n)
{
}

void ILogger::log(const LoggerLevel& lvl, const std::string& msg)
{
    // Filter the message depending on the message and global log levels
    if (lvl >= globalLevel)
        std::cout << lvl << name << " : " << msg << std::endl;
}


bool operator<(LoggerLevel lhs, LoggerLevel rhs)
{
    return (static_cast<int>(lhs) < static_cast<int>(rhs));
}

bool operator>(LoggerLevel lhs, LoggerLevel rhs)
{
    return rhs < lhs;
}

bool operator<=(LoggerLevel lhs, LoggerLevel rhs)
{
    return !(lhs > rhs);
}

bool operator>=(LoggerLevel lhs, LoggerLevel rhs)
{
    return !(lhs < rhs);
}

bool operator==(LoggerLevel lhs, LoggerLevel rhs)
{
    return (static_cast<int>(lhs) == static_cast<int>(rhs));
}

bool operator!=(LoggerLevel lhs, LoggerLevel rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, LoggerLevel ll)
{
    switch(ll)
    {
        case LoggerLevel::Debug:
            os << "DEBUG : ";
            break;
        case LoggerLevel::Warning:
            os << "WARNING : ";
            break;
        case LoggerLevel::Error:
            os << "ERROR : ";
            break;
    }

    return os;
}


