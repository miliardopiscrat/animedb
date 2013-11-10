# TARGET = linux/mipsel

ifndef TARGET
$(info target variable not defined!! TARGET=linux/mipsel)
else
ARCH := $(TARGET)


TARGET = testlib


include Makefile.$(strip $(ARCH))


endif

.PHONY: all clean tarball TARGET