//
// Created by 卢润发 on 2016/9/27.
//
#include "com_lurunfa_ndkopencv_Hello.h"
#include "jni.h"


JNIEXPORT jstring JNICALL Java_com_lurunfa_ndkopencv_Hello_stringFromJNI
        (JNIEnv env, jobject jc){
    return env.NewStringUTF("Hello world");
}
