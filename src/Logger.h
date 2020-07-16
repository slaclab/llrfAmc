#ifndef _LOGGER_H_
#define _LOGGER_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : Simple Logger
 * ----------------------------------------------------------------------------
 * File       : Logger.h
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

#include <iostream>
#include <string>
#include <stdexcept>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

class ILogger;

typedef boost::shared_ptr<ILogger> Logger;

// Logger level values
enum class LoggerLevel { Debug, Warning, Error, None };

// Simple logger class
class ILogger
{
public:
    ILogger(const std::string& n);

    static Logger create(const std::string& n);

    // Set/Get global log level
    static void        setLevel(const LoggerLevel& l) { globalLevel = l; };
    static LoggerLevel getLevel()                     { return globalLevel; };

    // Log a new message
    void log(const LoggerLevel& lvl, const std::string& msg);

private:
    static LoggerLevel globalLevel; // Global log level
    std::string        name;        // Logger instance name
};

// Logger level operators
bool operator<(LoggerLevel lhs, LoggerLevel rhs);
bool operator>(LoggerLevel lhs, LoggerLevel rhs);
bool operator<=(LoggerLevel lhs, LoggerLevel rhs);
bool operator>=(LoggerLevel lhs, LoggerLevel rhs);
bool operator==(LoggerLevel lhs, LoggerLevel rhs);
bool operator!=(LoggerLevel lhs, LoggerLevel rhs);

// Operator used to print the level name
std::ostream& operator<<(std::ostream& os, LoggerLevel ll);

#endif
