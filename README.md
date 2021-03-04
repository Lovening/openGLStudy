# openGL 学习笔记

*******

## macos搭建开发环境
- 系统版本  `10.15.7`
- 编辑器 `vscode`
  ### 下载安装库
  使用brew 下载 glew 和glfw，`brew install glew`和`brew install glfw3`
  ### 配置GLAD
  GLAD  是一个开源的库，使用[在线服务](https://glad.dav1d.de/)服务配置，Language选择C/C++，Profile 选择Core,然后Generate一个zip文件，将zip文件下载下来解压到本地工程目录使用。
  ### 测试环境
  使用demo1中的文件测试本地环境
## 第一个窗口

****

### 创建一个窗口

- 使用glfwCreateWindows来创建一个空白窗口

  ```cpp
  GLFWwindows * windows = glfwCreateWindows(800,900,"LearnOpenGl",NULL,NULL);
  ```

- 配置上下文

  ``` cpp
  glfwMakeContextCurrent(windows);
  ```

- GLAD 

  Glad 是用来管理Opengl函数指针的，在调用任何opengl的函数之前我们都需要初始化GLAD

  ```cpp
  //我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  ```

- 视口

  在开始渲染之前要告诉opengl渲染窗口尺寸的大小，通过调用glViewport来设置窗口维度

  ```cpp
  glViewport(0,0,800,600);
  ```

- 调整窗口大小

  注册回调函数，每次窗口改变时调用回调函数

  ```cpp
  void  framebuffer_size_callback(GLFWwindow* window, int width, int height) {
      glViewport(0, 0, width, height);
  }
  glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
  ```

- 渲染循环

  为了将窗口一直显示，我们在程序中加个while循环，能让我们在退出GLFW之前一直运行

  ```cpp
  while (!glfwWindowShouldClose(window)) {
       // input
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
          // -------------------------------------------------------------------------------
       glfwSwapBuffers(window);
       glfwPollEvents();
  }
  ```

  glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置)

- 清除资源

  ```cpp
  glfwTerminate();
  ```




## 三角形

*******************************************

​	在OpenGL中，任何事物都在3D空间，而屏幕和窗口在2D空间，3D坐标转化为2D坐标的的处理过程是由OpenGL的**图形渲染管线(Graphics Pipeline)**大多译为管线机。 

### 着色器(shader)

 图形渲染管线接受一组3D坐标，然后转化为2D屏幕输出，图形渲染管线可以分为几个阶段，每个阶段的输出都是下一个阶段的输入，这些阶段都有特定的函数，并且很容易执行，当今显卡有成千上万的小处理核心，他们在GPU上为每一个渲染管线运行着各自的小程序，这些小程序被称为色器。OpenGL的着色器使用**OpenGL着色器语言(OpenGL Shading Language,GLSL)**写成的。

- **顶点数据**   我们以数组形式传递三个坐标作为图形管线的输入，用来表示一个三角形，这个数组被成为顶点数据(vertex Data)，顶点数据是一些列顶点的集合，一个顶点(vertex)是一个3D坐标的数据集合，而顶点数据使用**顶点属性(vertex attribute)**表示的.

- **图元**    OpenGL需要你去指定这些数据所表示的渲染类型，指定渲染类型叫做图元(primitive),任何一个绘制指令的调用都将把图元传递给OpenGL,其中的几个图元为: `GL_POINTS` `GL_TRIANGLES` `GL_LINE_STRIP`
- **顶点着色器**   图形渲染管线的第一个部分是**顶点着色器(vertex shader)** ，它把一个单独的顶点作为输入，顶点着色器的主要目的是把3D坐标转化成另一种3D坐标.
- **图元装配(primitive Assembly)**  将顶点着色器输出的所有顶点作为输入，并所有点装配成指定图元形状
- **几何着色器(geometry shader)**   图元装配的输出会传给几何着色器,几何着色器把图元形式的一些列顶点的集合作为输入，它可以通过产生新顶点构造出新的图元来生成其他形状，
- **光栅化阶段**  把图元映射为最终屏幕上相应的像素，生成供片段着色器使用的片段







