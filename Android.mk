LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_LDFLAGS   += -llog
LOCAL_CFLAGS    += -DDEBUG
LOCAL_MODULE    := android-sysinfo
LOCAL_SRC_FILES := sysinfo.c

include $(BUILD_EXECUTABLE)


