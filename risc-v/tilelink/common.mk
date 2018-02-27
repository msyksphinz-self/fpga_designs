src_path := src/main/scala
default_submodules := . chisel3 hardfloat

chisel_srcs := $(foreach submodule,$(default_submodules) $(ROCKETCHIP_ADDONS),$(shell find $(base_dir)/$(submodule)/$(src_path) -name "*.scala"))

