/*** 
 * @copyright: VTEL
 * @Date: 2021-02-03 14:41:22
 * @Author: WXN
 * @LastEditTime: 2021-02-03 15:44:41
 * @LastEditors: your name
 * @Description: 
 * @FilePath: /opengl/demo1/opengl.cpp
 */
#include <iostream>
// #include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define GLFW_INCLUDE_NONE
int main(void)
{
    glfwInit();
    // 设置opengl 的版本号
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    

    return 0;
}