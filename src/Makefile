-include ../config.mak

ifdef BR_VERSION
	CXX	     = $(XCROSS_HOME)g++
	TARCH    = $(BR_VERSION)-x86_64
	TVERS    = $(BR_VERSION)
else
	CXX    = g++
	TARCH  = $(H_VERSION)-x86_64
	TVERS  = $(H_VERSION)
endif

OBJDIR   = O.$(TARCH)
SRCDIR   = .
LIBDIR   = O.$(TARCH)
INSTALL_DIR = ..

DEPS     =
SRCS     = $(wildcard $(SRCDIR)/*.cpp)
OBJS     = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
SLIB     = $(LIBDIR)/lib$(LIB_NAME).a
DLIB     = $(LIBDIR)/lib$(LIB_NAME).so
HEADERS  = $(wildcard $(SRCDIR)/*.h)

TESTDIR     = test
TESTBINDIR  = O.$(TARCH)
TESTSRCS    = $(wildcard $(TESTDIR)/*.cpp)
TEST_TARGET = $(patsubst $(TESTDIR)/%.cpp, $(TESTBINDIR)/%, $(TESTSRCS))

CXXFLAGS  = -g -std=c++0x -fPIC
CXXFLAGS += $(addprefix -I,. $(CPSW_DIR)/include $(BOOST_DIR)/include $(YAML_CPP_DIR)/include)

LIBS_EXT = $(addprefix -l,$(LIB_NAME) cpsw yaml-cpp boost_system)
LIBS_SYS = -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -lrt -ldl

# For host builds, statically link everything except libstdc++, rt, dl, and tirpc (if used)
ifeq ($(TVERS),$(H_VERSION))
LIBS_EXT := -Wl,-Bstatic $(LIBS_EXT) -Wl,-Bdynamic
else
LIBS_EXT := -static $(LIBS_EXT)
endif

LDIR  = -L.
LDIR += -L$(CPSW_DIR)/lib
LDIR += -L$(BOOST_DIR)/lib
LDIR += -L$(YAML_CPP_DIR)/lib
LDIR += -L$(LIBDIR)

TIRPC_INC_default=/usr/include/tirpc

ifeq ($(USE_TIRPC),YES)
USE_TIRPC_$(TVERS)=YES
endif

ifeq ($(TIRPC_INC_$(TVERS)),)
TIRPC_INC_$(TVERS):=$(TIRPC_INC_default)
endif

ifeq ($(USE_TIRPC_$(TVERS)),YES)
LIBS_SYS += -ltirpc
CXXFLAGS += -I$(TIRPC_INC_$(TVERS))
endif

.PHONY: all clean insatll uninstall

all: $(SLIB) $(DLIB) $(TEST_TARGET)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(DEPS) | $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(OBJDIR):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(SLIB): $(OBJS) | $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^

$(DLIB): LDFLAGS += -shared
$(DLIB): $(OBJS) | $(LIBDIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TESTBINDIR):
	@mkdir -p $@

$(TESTBINDIR)/%: $(TESTDIR)/%.cpp
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDIR) $(LIBS_EXT) $(LIBS_SYS)

clean:
	$(RM) -rf $(OBJDIR)
	$(RM) -rf $(LIBDIR)
	$(RM) -rf $(TESTBINDIR)

install: $(SLIB) $(DLIB) $(TEST_TARGET)
	@mkdir -p $(INSTALL_DIR)/$(TARCH)/lib
	install -C $(SLIB) $(INSTALL_DIR)/$(TARCH)/lib/
	install -C $(DLIB) $(INSTALL_DIR)/$(TARCH)/lib/

	@mkdir -p $(INSTALL_DIR)/$(TARCH)/include
	install -C $(HEADERS) $(INSTALL_DIR)/$(TARCH)/include/

	@mkdir -p $(INSTALL_DIR)/$(TARCH)/bin
	install -C $(TEST_TARGET) $(INSTALL_DIR)/$(TARCH)/bin/

uninstall:
	$(RM) -rf $(INSTALL_DIR)/$(TARCH)
