#ifndef _CPSWTOPPATHS_H_
#define _CPSWTOPPATHS_H_

/**
 *-----------------------------------------------------------------------------
 * Title      : CPSW Top Level Paths
 * ----------------------------------------------------------------------------
 * File       : CpswTopPaths.h
 * Author     : Jesus Vasquez, jvasquez@slac.stanford.edu
 * Created    : 2020-07-16
 * ----------------------------------------------------------------------------
 * Description:
 * CPSW top level paths definitions. Used by all modules.
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
