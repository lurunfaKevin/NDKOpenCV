/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_lurunfa_ndkopencv_Hello */
#include <opencv2/opencv.hpp>
#ifndef _Included_com_lurunfa_ndkopencv_Hello
#define _Included_com_lurunfa_ndkopencv_Hello

JNIEXPORT jint JNICALL
Java_com_lurunfa_test_OpenCVHelper_FindFeatures(JNIEnv *env, jobject instance, jint width,
                                                jint height, jbyteArray yuv_, jintArray rgba_) {
    jbyte *yuv = env->GetByteArrayElements(yuv_, NULL);
    jint *rgba = env->GetIntArrayElements(rgba_, NULL);

    // TODO

    env->ReleaseByteArrayElements(yuv_, yuv, 0);
    env->ReleaseIntArrayElements(rgba_, rgba, 0);
}

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_lurunfa_ndkopencv_Hello
 * Method:    stringFromJNI
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_lurunfa_ndkopencv_Hello_stringFromJNI
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
