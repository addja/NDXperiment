#include "native-renderer.h"
#include <GLES3/gl31.h>
#include <vector>
#include <string>


std::string fragmentShader = "#version 330 core\n"
        "out vec3 color;\n"
        "void main(){\n"
        "  color = vec3(1,0,0);\n"
        "}";

std::string vertexShader = "#version 330 core\n"
        "layout(location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position.xyz = position;\n"
        "   gl_Position.w = 1.0;\n"
        "}";


extern "C" {

GLuint LoadShaders(){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    char const * VertexSourcePointer = vertexShader.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    char const * FragmentSourcePointer = fragmentShader.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

GLuint programID;
GLuint VAO;
// This will identify our vertex buffer
GLuint VBO;
GLint position_loc;
static const GLfloat vert[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
};

JNIEXPORT void JNICALL Java_somebody_ndkxperiment_RendererWrapper_onSurfaceCreatedNative(
        JNIEnv *env,
        jobject /* this */
) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0, 1.0, 0.0, 1.0);
    programID = LoadShaders();
    position_loc = glGetAttribLocation(programID, "position");
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vert, GL_STATIC_DRAW);
    glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
    glUseProgram(programID);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(position_loc);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

};
