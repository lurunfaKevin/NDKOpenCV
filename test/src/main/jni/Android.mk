LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


OpenCV_INSTALL_MODULES := on
OpenCV_CAMERA_MODULES := off

OPENCV_LIB_TYPE :=SHARED

ifeq ("$(wildcard $(OPENCV_MK_PATH))","")
include /Users/lurunfa/Downloads/OpenCV-2.3.1-android-bin/OpenCV-2.3.1/share/OpenCV/OpenCV.mk
else
include $(OPENCV_MK_PATH)
endif

LOCAL_MODULE := OpenCV

LOCAL_SRC_FILES := com_lurunfa_test_OpenCVHelper.cpp

LOCAL_LDLIBS +=  -lm -llog

include $(BUILD_SHARED_LIBRARY)