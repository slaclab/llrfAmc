#ifndef _CPSWTOPPATHS_H_
#define _CPSWTOPPATHS_H_

#include <string>

namespace CpswTopPaths
{
    // Top Level CPSW Paths
    const std::string mmio           = "/mmio/";
    const std::string AppTop         = mmio + "AppTop/";
    const std::string AppCore        = AppTop + "AppCore/";
    const std::string AppTopJesdBay0 = AppTop + "AppTopJesd0";
    const std::string AppTopJesdBay1 = AppTop + "AppTopJesd1";

}

#endif
