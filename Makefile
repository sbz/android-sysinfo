ARCH := $(shell adb shell getprop ro.product.cpu.abi)
SDK_VERSION := $(shell adb shell getprop ro.build.version.sdk)
DESTDIR := /data/local/tmp

all: install

build:
	ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk APP_PLATFORM=android-$(SDK_VERSION) APP_ABI=$(ARCH)

push: build
	adb push libs/$(ARCH)/android-sysinfo $(DESTDIR)/android-sysinfo

run:
	adb shell $(DESTDIR)/android-sysinfo

clean:
	rm -rf libs
	rm -rf obj

