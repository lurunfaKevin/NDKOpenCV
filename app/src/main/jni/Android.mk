LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

#open
OPENCVROOT:= /Users/lurunfa/Library/Android/OpenCV-android-sdk
OPENCV_CAMERA_MODULES:=on
OPENCV_INSTALL_MODULES:=on
OPENCV_LIB_TYPE:=STATIC
include ${OPENCVROOT}/sdk/native/jni/OpenCV.mk

LOCAL_MODULE := hello-jni
LOCAL_SRC_FILES := Test.cpp
include $(BUILD_SHARED_LIBRARY)