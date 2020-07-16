#ifndef _LOGGER_H_
#define _LOGGER_H_

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

    // Log a new mesage
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
