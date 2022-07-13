#pragma once
#include "agpch.h"

#include "Core.h"

namespace Agate
{

    class API Logger {
    public:
        static void printMSG(std::string msg);
        static void printWarn(std::string msg);
        static void printError(std::string msg);
        static void printCrit(std::string msg);
    };
}// namespace Agate

#define PRINTMSG(x) Logger::printMSG(x);
#define PRINTWARN(x) Logger::printWarn(x);
#define PRINTERROR(x) Logger::printError(x);
#define PRINTCRIT(x) Logger::printCrit(x);
