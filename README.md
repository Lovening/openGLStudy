# openGL 学习笔记
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

  













