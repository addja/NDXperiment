#include "native-renderer.h"
#include <GLES3/gl31.h>
#include <string>


std::string fragmentShader = "#version 330\n"
        "\n"
        "uniform sampler2D tex;\n"
        "uniform vec4 color;\n"
        "out vec4 out_color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    out_color = color;\n"
        "}";

std::string vertexShader = "#version 330\n"
        "\n"
        "uniform mat4 projection, view, model;\n"
        "in vec2 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position = projection * view * model * vec4(position, 0.0, 1.0);\n"
        "}";

extern "C" {

JNIEXPORT void JNICALL Java_somebody_ndkxperiment_RendererWrapper_onSurfaceCreatedNative(
        JNIEnv *env,
        jobject /* this */
) {
    glClearColor(0.0, 1.0, 0.0, 1.0);
}

JNIEXPORT void JNICALL Java_somebody_ndkxperiment_RendererWrapper_onSurfaceChangedNative(
        JNIEnv *env,
        jobject /* this */,
        jint width,
        jint height
) {

}

JNIEXPORT void JNICALL Java_somebody_ndkxperiment_RendererWrapper_onDrawFrameNative(
        JNIEnv *env,
        jobject /* this */
) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

};
