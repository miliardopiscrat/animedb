# TARGET = linux/mipsel

ifndef TARGET
$(info target variable not defined!! TARGET=linux/mipsel)
else
ARCH := $(TARGET)

ifeq ($(MAKECMDGOALS),testlib)
TARGET := testlib
endif

include Makefile.$(strip $(ARCH))


endif

.PHONY: all clean tarball TARGET