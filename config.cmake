#----------------------------------------------------------------------------#
# Company    : SLAC National Accelerator Laboratory
#----------------------------------------------------------------------------#
# Description: Definitions of all CPSW package dependencies for llrfAmc
#----------------------------------------------------------------------------#
# This file is part of 'llrfAmc'. It is subject to the license terms 
# in the LICENSE.txt file found in the top-level directory of this
# distribution, and at:
#    https://confluence.slac.stanford.edu/display/ppareg/LICENSE.html.
# No part of 'llrfAmc', including this file, may be copied, modified,
# propagated, or distributed except according to the terms contained in
# the LICENSE.txt file.
#----------------------------------------------------------------------------#

set(CPSW_VERSION "R4.7.0")

if (NOT DEFINED CPSW_TOP)
    set(CPSW_TOP "$ENV{PACKAGE_SITE_TOP}/cpsw/framework/${CPSW_VERSION}")
endif()
