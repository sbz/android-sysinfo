# android-sysinfo

## Overview

`android-sysinfo` is a Android Native program which reports the system
properties of any android device using the [system properties][1] [C API][2]
existing in Android libc [bionic][3].

It is simlar to the `Settings or System > About phone` system information
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

## Output on devices

On few of my personal Android devices, this is what output information look likes.

### HTC Magic

[HTC Magic](https://en.wikipedia.org/wiki/HTC_Magic)

```
Model name               : HTC Magic
Android codename         : sapphire
Android version          : 2.2.1
Android SDK version      : 8
Kernel version           : Linux 2.6.32.9-27237-gbe746fb android-build@apa26.mtv.corp.google.com #1 PREEMPT Thu Jul 22 15:50:12 PDT 2010 armv6l
Baseband version         : 62.50SJ.20.17U_2.22.28.25
Build number             : FRG83D

```
### Nexus S

[Nexus S](https://en.wikipedia.org/wiki/Nexus_S)

```
Model name               : Nexus S
Android codename         : crespo
Android version          : 4.1.2
Android SDK version      : 16
Kernel version           : Linux 3.0.31-g5894150 android-build@vpba17.mtv.corp.google.com #1 PREEMPT Mon Sep 10 14:10:13 PDT 2012 armv7l
Baseband version         : I9023XXKI1
Build number             : JZO54K
```

### Nexus 6

[Nexus 6](https://en.wikipedia.org/wiki/Nexus_6)

```
Model name               : Nexus 6
Android codename         : shamu
Android version          : 7.1.1
Android SDK version      : 25
Kernel version           : Linux 3.10.40-gc7ebca13933 android-build@wprh2.hot.corp.google.com #1 SMP PREEMPT Wed Aug 16 15:25:44 UTC 2017 armv7l
Baseband version         : MDM9625_104670.31.05.45R
Build number             : N6F27M
```

### Huawei Y5 II

[Huawei Y series](https://en.wikipedia.org/wiki/List_of_Huawei_phones#Ascend_Y_series)

```
Model name               : HUAWEI CUN-L21
Android codename         : CUN-L21
Android version          : 5.1 (Lollipop)
Android SDK version      : 22
Kernel version           : Linux 3.10.65+ jslave@WUH1000021377 #1 SMP PREEMPT Thu Jul 5 11:30:57 CST 2018 armv7l
Baseband version         : MOLY.LR9.W1444.MD.LWTG.MP.V42.P40,MOLY.LR9.W1444.MD.LWTG.MP.V42.P40, 2017/07/07 17:29
Build number             : CUN-L21C429B109
```

### Huawei P20

[Huawei P20 Pro](https://en.wikipedia.org/wiki/Huawei_P20)

```
Model name               : CLT-L09
Android codename         : CLT
Android version          : 9
Android SDK version      : 28
Kernel version           : Linux 4.9.148 test@cn-central-1b-e859467521576132696835-1535427282-tvxt6 #1 SMP PREEMPT Thu Dec 12 15:34:28 CST 2019 aarch64
Baseband version         : 21C20B369S009C000
Build number             : CLT-L09 9.1.0.372(C782E12R1P11)
```

## License

The project is released under [MIT license](https://en.wikipedia.org/wiki/MIT_License).

[1]: https://android.googlesource.com/platform/bionic/+/master/libc/include/sys/system_properties.h
[2]: https://developer.android.com/ndk/guides/stable_apis#c_library
[3]: https://android.googlesource.com/platform/bionic/
[4]: https://developer.android.com/studio/command-line/adb
