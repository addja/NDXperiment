#ifndef NDXPERIMENT_NATIVE_RENDERER_H
#define NDXPERIMENT_NATIVE_RENDERER_H

#include <jni.h>

extern "C" {

JNIEXPORT void JNICALL Java_somebody_ndkxperiment_RendererWrapper_onSurfaceCreatedNative(
        JNIEnv *env,
        jobject /* this */
);

JNIEXPORT void JNICALL Java_somebody_ndkxperiment_RendererWrapper_onSurfaceChangedNative(
        JNIEnv *env,
        jobject /* this */,
        jint width,
        jint height
);

JNIEXPORT void JNICALL Java_somebody_ndkxperiment_RendererWrapper_onDrawFrameNative(
        JNIEnv *env,
        jobject /* this */
);

};
#endif //NDXPERIMENT_NATIVE_RENDERER_H
