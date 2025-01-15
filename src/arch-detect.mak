#=================================================#
# Simple utility script to detect host arch
#=================================================#

HOST_ARCH:=$(shell uname -r | grep -Eo "el[0-9][0-9]?")
ifneq ($(HOST_ARCH),)
	HOST_ARCH:=rhel$(subst el,,$(HOST_ARCH))
else
	HOST_ARCH:=linux
endif

