################
### Lib name ###
################
LIB_NAME = llrfAmc

#####################
### Arch Versions ###
#####################
# Host versions
HARCH=$(HOST_ARCH)
# Buildroot versions
BR_ARCHES += buildroot-2019.08

########################
### Package versions ###
########################
CPSW_VERSION     = R4.5.2
BOOST_VERSION    = 1.64.0
YAML_CPP_VERSION = yaml-cpp-0.5.3_boost-1.64.0

# RPC symbols were removed from glibc 2.26+
USE_TIRPC_rhel9  = YES
USE_TIRPC_rhel8  = YES

################################
### Default path definitions ###
################################

# Set a default location for the buildroot toolchain. Allow override on the command line/environment
ifeq ($(BUILDROOT_HOME),)
ifneq ($(EPICS_PACKAGE_TOP),)
BUILDROOT_HOME=$(EPICS_PACKAGE_TOP)/linuxRT/$(BR_VERSION)
else
BUILDROOT_HOME=/afs/slac/package/linuxRT/$(BR_VERSION)
endif
endif

# Set PACKAGE_TOP to EPICS_PACKAGE_TOP, if not provided
ifeq ($(PACKAGE_TOP),)
ifneq ($(EPICS_PACKAGE_TOP),)
PACKAGE_TOP=$(EPICS_PACKAGE_TOP)
else
$(error PACKAGE_TOP or EPICS_PACKAGE_TOP must be provided in the environment or on the command line)
endif
endif

########################
### Path definitions ###
########################
# Location CrossCompiler HOME:
XCROSS_HOME=$(BUILDROOT_HOME)/host/linux-x86_64/x86_64/usr/bin/x86_64-buildroot-linux-gnu-

# Packages location
CPSW_DIR         = $(PACKAGE_TOP)/cpsw/framework/$(CPSW_VERSION)/$(TARCH)
BOOST_DIR        = $(PACKAGE_TOP)/boost/$(BOOST_VERSION)/$(TARCH)
YAML_CPP_DIR     = $(PACKAGE_TOP)/yaml-cpp/$(YAML_CPP_VERSION)/$(TARCH)


