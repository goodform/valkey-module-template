
ifeq ($(NOPAR),1)
.NOTPARALLEL: ;
endif

ROOT=..

MK_ALL_TARGETS=bindirs deps build

include $(ROOT)/deps/readies/mk/main

#----------------------------------------------------------------------------------------------  

export RMUTIL_BINDIR=$(ROOT)/bin/$(FULL_VARIANT)/rmutil
include $(ROOT)/build/rmutil/Makefile.defs
#----------------------------------------------------------------------------------------------  

define HELPTEXT
make setup         # install packages required for build
make fetch         # download and prepare dependant modules

make build
  DEBUG=1          # build debug variant
  VARIANT=name     # use a build variant 'name'
  PROFILE=1        # enable profiling compile flags (and debug symbols) for release type
                   # You can consider this as build type release with debug symbols and -fno-omit-frame-pointer
  DEPS=1           # also build dependant modules
  COV=1            # perform coverage analysis (implies debug build)
make clean         # remove binary files
  ALL=1            # remove binary directories
  DEPS=1           # also clean dependant modules

make deps          # build dependant modules
make all           # build all libraries and packages

make test          # run unit and flow tests

make unit_tests    # run unit tests

make flow_tests    # run tests
  TEST=name        # run test matching 'name'
  TEST_ARGS="..."  # RLTest arguments
  SIMPLE=1         # shortcut for GEN=1 AOF=0 SLAVES=0 AOF_SLAVES=0 OSS_CLUSTER=0
  GEN=1            # run general tests on a standalone Redis topology
  AOF=1            # run AOF persistency tests on a standalone Redis topology
  SLAVES=1         # run replication tests on standalone Redis topology
  AOF_SLAVES=1     # run AND and replication tests on standalone Redis topology
  OSS_CLUSTER=1    # run general tests on an OSS Cluster topology
  SHARDS=num       # run OSS cluster with `num` shards (default: 3)
  RLEC=1           # flow tests on RLEC
  COV=1            # perform coverage analysis
  VALGRIND|VG=1    # run specified tests with Valgrind
  EXT=1            # run tests with existing redis-server running

make pack          # build packages (ramp & dependencies)

make benchmarks    # run all benchmarks
  BENCHMARK=file   # run benchmark specified by 'filename'
  BENCH_ARGS="..." # redisbench_admin  extra arguments

make platform      # build artifacts for given platform
  OSNICK=nick        # build for OSNICK `nick`
  TEST=1             # also run tests

endef

#----------------------------------------------------------------------------------------------  

MK_CUSTOM_CLEAN=1

BINDIR=$(BINROOT)/src
SRCDIR=.

#----------------------------------------------------------------------------------------------

TARGET=$(BINROOT)/redis_module_example.so

define CC_INCLUDES +=
	$(ROOT)/deps/RedisModulesSDK
	$(ROOT)/deps
	$(LIBEVENT_BINDIR)/include
endef

define CC_DEFS +=
	REDIS_MODULE_TARGET
	REDISMODULE_EXPERIMENTAL_API
endef

CC_PEDANTIC=1

define _CC_FLAGS +=
	-std=gnu11
endef
CC_FLAGS += $(call flaten,_CC_FLAGS)

LD_LIBS = $(RMUTIL) -lm -lpthread -lstdc++

# LD_LIBS += $(call flatten,$(_LD_LIBS))

ifeq ($(OS),linux)
LD_LIBS += -lssl -lcrypto
endif

ifeq ($(VALGRIND),1)
CC_DEFS += _VALGRIND
endif

define _SOURCES
	module.c
endef

SOURCES=$(addprefix $(SRCDIR)/,$(call flatten,$(_SOURCES)))
HEADERS=$(patsubst $(SRCDIR)/%.c,$(SRCDIR)/%.h,$(SOURCES))
OBJECTS=$(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.o,$(SOURCES))

CC_DEPS = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%.d,$(SOURCES))

include $(MK)/defs

#----------------------------------------------------------------------------------------------

MISSING_DEPS:=

ifeq ($(wildcard $(RMUTIL)),)
MISSING_DEPS += $(RMUTIL)
endif

ifneq ($(MISSING_DEPS),)
DEPS=1
endif

DEPENDENCIES=rmutil

ifneq ($(filter all deps $(DEPENDENCIES) pack,$(MAKECMDGOALS)),)
DEPS=1
endif

.PHONY: deps $(DEPENDENCIES)
#----------------------------------------------------------------------------------------------

.PHONY: clean all install uninstall docker bindirs

all: bindirs $(TARGET)

include $(MK)/rules

#----------------------------------------------------------------------------------------------

ifeq ($(DEPS),1)

.PHONY: rmutil

deps: $(RMUTIL)

rmutil: $(RMUTIL)

$(RMUTIL):
	@echo Building $@ ...
	$(SHOW)$(MAKE) --no-print-directory -C $(ROOT)/build/rmutil

#----------------------------------------------------------------------------------------------

else

deps: ;

endif # DEPS

clean:
	@echo Cleaning $(ALL) ...
ifeq ($(ALL),1)
	-$(SHOW)rm -rf $(BINROOT)
	$(SHOW)$(MAKE) -C $(ROOT)/build/libevent clean AUTOGEN=1
else
	-$(SHOW)rm -rf $(BINDIR)
ifeq ($(DEPS),1)
	-$(SHOW)$(MAKE) --no-print-directory -C $(ROOT)/build/rmutil clean
endif
endif

-include $(CC_DEPS)

REGULAR_OBJECTS=$(OBJECTS)

$(REGULAR_OBJECTS) : $(BINDIR)/%.o : $(SRCDIR)/%.c
	@echo Compiling $<...
	$(SHOW)$(CC) $(CC_FLAGS) -c $< -o $@

$(TARGET): $(BIN_DIRS) $(MISSING_DEPS) $(OBJECTS)
	@echo Linking $@...
	$(SHOW)$(CC) $(SO_LD_FLAGS) $(LD_FLAGS) -o $@ $(RMUTIL) $(OBJECTS) $(LD_LIBS)

#----------------------------------------------------------------------------------------------

# test: unit_tests flow_tests
test: flow_tests

clean-tests:
	$(SHOW)$(MAKE) -C $(ROOT)/tests/unit clean

.PHONY: test unit_tests flow_tests clean-tests

#----------------------------------------------------------------------------------------------

UNITTESTS_RUNNER=$(BINROOT)/unit_tests/unit_tests

$(UNITTESTS_RUNNER)	: $(TARGET)
	$(SHOW)$(MAKE) -C $(ROOT)/tests/unit

unit_tests: $(UNITTESTS_RUNNER)
	@echo Running unit tests...
	$(SHOW)$<

#----------------------------------------------------------------------------------------------

ifeq ($(SIMPLE),1)
export GEN=1
export SLAVES=0
export AOF=0
export AOF_SLAVES=0
export OSS_CLUSTER=0
else
export GEN ?= 1
export SLAVES ?= 1
export AOF ?= 1
export AOF_SLAVES ?= 1
export OSS_CLUSTER ?= 1
endif

ifneq ($(RLEC),1)

flow_tests: #$(TARGET)
	$(SHOW)\
	MODULE=$(realpath $(TARGET)) \
	GEN=$(GEN) AOF=$(AOF) SLAVES=$(SLAVES) AOF_SLAVES=$(AOF_SLAVES) OSS_CLUSTER=$(OSS_CLUSTER) \
	VALGRIND=$(VALGRIND) \
	TEST=$(TEST) \
	$(ROOT)/tests/flow/tests.sh

else # RLEC

flow_tests: #$(TARGET)
	$(SHOW)RLEC=1 $(ROOT)/tests/flow/tests.sh

endif # RLEC

#----------------------------------------------------------------------------------------------

COV_EXCLUDE_DIRS += \
	deps \
	tests/unit

COV_EXCLUDE+=$(foreach D,$(COV_EXCLUDE_DIRS),'$(realpath $(ROOT))/$(D)/*')

coverage:
	$(SHOW)$(MAKE) build COV=1
	$(SHOW)$(COVERAGE_RESET)
	-$(SHOW)$(MAKE) test COV=1
	$(SHOW)$(COVERAGE_COLLECT_REPORT)

.PHONY: coverage

#----------------------------------------------------------------------------------------------

REDIS_ARGS=\
	COMPACTION_POLICY "" \
	RETNTION_POLICY 3600 \
	MAX_SAMPLE_PER_CHUNK 1024

run: $(TARGET)
	$(SHOW)redis-server --loadmodule $(realpath $(TARGET)) --dir /tmp

run_dev: $(TARGET)
	$(SHOW)redis-server --loadmodule $(realpath $(TARGET)) $(REDIS_ARGS) --dir /tmp

gdb: $(TARGET)
	$(SHOW)gdb --args `command -v redis-server` --loadmodule $(realpath $(TARGET)) --dir /tmp

#----------------------------------------------------------------------------------------------

install: all
	$(SHOW)mkdir -p $(INSTALL_LIB)
	$(SHOW)$(INSTALL) $(TARGET) $(INSTALL_LIB)

uninstall:
	$(SHOW)rm -f $(INSTALL_LIB)/$(notdir $(TARGET))

docker:
	$(SHOW)cd .. && docker build -t redis-tsdb .
