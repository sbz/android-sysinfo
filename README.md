# android-sysinfo

## Overview

`android-sysinfo` is a Android Native program which reports the system
properties of any android device using the [system properties][1] [C API][2]
existing in Android libc [bionic][3].

It is simlar to the `Settings or System > About the Phone` system information
displayed on your mobile device.

It reports the model, build version and kernel info, etc.

## Requirements

You need to install the Android SDK and Android NDK to use `adb` and `ndk-build`
used in the build process.

## Build

The build Makefile is using [adb][4] to determine the Android version and ABI of
the NDK to use in order to produce the binary.

Connect your Android device via USB and enable USB Debugging, then run:

```
make push
```

## Run

```
make run
```


[1]: https://android.googlesource.com/platform/bionic/+/master/libc/include/sys/system_properties.h
[2]: https://developer.android.com/ndk/guides/stable_apis#c_library
[3]: https://android.googlesource.com/platform/bionic/
[4]: https://developer.android.com/studio/command-line/adb
