base_dir = $(abspath ..)
src_path := src/main/scala
default_submodules := . chisel3 firrtl

generated_dir = $(abspath ./generated-src)
generated_dir_debug = $(abspath ./generated-src-debug)
sim_dir = .
output_dir = $(sim_dir)/output
chisel_srcs := $(foreach submodule,$(default_submodules) $(ROCKETCHIP_ADDONS),$(shell find $(base_dir)/$(submodule)/$(src_path) -name "*.scala"))

emu = emulator-$(PROJECT)-$(CONFIG)
emu_debug = emulator-$(PROJECT)-$(CONFIG)-debug

MODEL ?= TestHarness
PROJECT ?= freechips.rocketchip.system
CFG_PROJECT ?= $(PROJECT)
CONFIG ?= DefaultConfig
# TODO: For now must match rocketchip.Generator
long_name = $(PROJECT).$(CONFIG)

verilog = \
  $(generated_dir)/$(long_name).v \
  $(generated_dir)/$(long_name).behav_srams.v \

CXX ?= g++
CXXFLAGS := -O1
JVM_MEMORY ?= 2G

SBT ?= java -Xmx$(JVM_MEMORY) -Xss8M -XX:MaxPermSize=256M -jar $(base_dir)/sbt-launch.jar
SHELL := /bin/bash

FIRRTL_JAR ?= $(base_dir)/firrtl/utils/bin/firrtl.jar
FIRRTL ?= java -Xmx$(JVM_MEMORY) -Xss8M -XX:MaxPermSize=256M -cp $(FIRRTL_JAR) firrtl.Driver

all: $(emu)

include ../Verilator.mk

$(emu): $(verilog) $(cppfiles) $(headers) $(INSTALLED_VERILATOR)
	mkdir -p $(generated_dir)/$(long_name)
	$(VERILATOR) $(VERILATOR_FLAGS) -Mdir $(generated_dir)/$(long_name) \
	-o $(abspath $(sim_dir))/$@ $(verilog) $(cppfiles) -LDFLAGS "$(LDFLAGS)" \
	-CFLAGS "-I$(generated_dir) -include $(model_header)"
	$(MAKE) VM_PARALLEL_BUILDS=1 -C $(generated_dir)/$(long_name) -f V$(MODEL).mk

$(generated_dir)/%.fir $(generated_dir)/%.d: $(FIRRTL_JAR) $(chisel_srcs) $(bootrom_img)
	mkdir -p $(dir $@)
	cd $(base_dir) && $(SBT) "runMain $(PROJECT).Generator $(generated_dir) $(PROJECT) $(MODEL) $(CFG_PROJECT) $(CONFIG)"

%.v %.conf: %.fir $(FIRRTL_JAR)
	mkdir -p $(dir $@)
	$(FIRRTL) $(patsubst %,-i %,$(filter %.fir,$^)) -o $*.v -X verilog --infer-rw $(MODEL) --repl-seq-mem -c:$(MODEL):-o:$*.conf -faf $*.anno -ffaaf

# Build firrtl.jar and put it where chisel3 can find it.
$(FIRRTL_JAR): $(shell find $(base_dir)/firrtl/src/main/scala -iname "*.scala")
	$(MAKE) -C $(base_dir)/firrtl SBT="$(SBT)" root_dir=$(base_dir)/firrtl build-scala
	touch $(FIRRTL_JAR)
	mkdir -p $(base_dir)/lib
	cp -p $(FIRRTL_JAR) $(base_dir)/lib
# When chisel3 pr 448 is merged, the following extraneous copy may be removed.
	mkdir -p $(base_dir)/chisel3/lib
	cp -p $(FIRRTL_JAR) $(base_dir)/chisel3/lib

