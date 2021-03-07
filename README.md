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
- **光栅化阶段**  把图元映射为最终屏幕上相应的像素，生成供片段着色器使用的片段,在片段着色器运行之前会执行裁剪(Cliping)，裁剪会丢弃超出你视图以为的所有像素，用来提升执行效率。
- **片段着色器** 计算一个像素的最终颜色，片段着色器包含3D场景数据(比如光照，阴影，光的颜色等等)。

### 渲染三角形

#### 顶点输入

​	因为渲染的是三角形，所以创建三个顶点

```c++
flot vertices[] = {
-0.5f,-0.5f,0.0f,
0.5f,-0.5f,0.0f,
0.0f,0.5f,0.0f
}
```

- **标准化设备坐标** 一旦你的顶点坐标在顶点着色器中处理过，他们就应该是标准化设备坐标了，标准化坐标是一个x,y和z值在-1.0和1.0的一段小空间，

 顶点缓冲对象(vertex buffer object,VBO)中存储大量顶点，这个缓冲中有独一无二的ID,使用glGenBuffers函数和一个缓冲ID生成一个VBO对象

``` cpp
unsigned int VBO;
glGenBuffers(1,&VBO);
```

 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上

```cpp
glBindBuffer(GL_ARRAY_BUFFER,VBO);
```

绑定到GL_ARRAY_BUFFER目标上后，然后我们使用的任何缓冲调用会用来配置当前绑定的缓冲,我们可以调用glBufferData函数，把之前定义的顶点数据复制到缓冲的内存中去，glBufferData是用来把用户定义的数据复制到当前绑定缓冲的函数，它的第一个参数是目标缓冲类型，第二个参数是指定传输数据的大小，第三个参数是我们希望发送的实际数据，第四个参数指定了希望显卡如果管理我们给定的数据。**GL_STATIC_DRAM：数据不会或者几乎不会改变** **GL_DYNAMIC_DRAM：数据会变改变许多** **GL_STREAM_DRAM: 数据每次绘制时都会改变**   

```cpp
glBufferData(GL_ARRAY_BUFFER,sizeof(vertices).vertices,GL_STATIC_DRAM);
```

#### 顶点着色器

 使用顶点着色器语言(OPenGL Shading Language) 编写顶点着色器。然后编译这个着色器.下面是一个基础的顶点着色器源代码

```
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);
}
```

#### 编译顶点着色器

```cpp
#define GRTSTR(x) #x
const char* vertexShaderSource = GERSTR(#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0);

// 创建着色器对象，还是使用ID来引用
unsinged int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER); 

//把着色器源码附加到着色器对象上，编译它
glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
glCompileShader(vertexShader);

//检测是否编译成功
int success;
char infoLog[512];
glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);
if(!success){
	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
  std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

#### 片段着色器

 片段着色器所做的是计算像素最后的颜色输出

> 在计算机图形中颜色被表示为有4个元素的数组：红色、绿色、蓝色和alpha(透明度)分量，通常缩写为RGBA。当在OpenGL或GLSL中定义一个颜色的时候，我们把颜色每个分量的强度设置在0.0到1.0之间。比如说我们设置红为1.0f，绿为1.0f，我们会得到两个颜色的混合色，即黄色。这三种颜色分量的不同调配可以生成超过1600万种不同的颜色！

```cpp
#define GET_STR(x) #x

#version 330 core
out vec4 FragColor;

void main()
{
	FragColot = vec4(1.0f,0.5f,0.2f,1.0f);

  // 编译片段着色器编译顶点着色器类似，我们使用GL_FRAGMENT_SHADER常量作为着色器类型
  unsigned int fragmentShader;
  gragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
  glCompileShader(fragmentShader);
}
```

片段着色器只需要一个输出变量，这个变量是一个4分量向量，它表示最终的输出颜色，声明变量用`out`

#### 着色器程序

- **着色器对象** 着色器对象是把多个着色器合并之后最终链接完成的版本，如果要使用刚才的着色器我们必须把它们链接成为着色器对象，然后再渲染对象的时候激活这个着色器。

  ```cpp
  // 创建一个着色器对象
  unsigned int shaderProgram;
  // glCreateProgram 创建一个程序，返回新创建程序的ID引用，
  shaderProgram = glCreateProgram();
  // 把之前编译的着色器附加到程序对象上
  glAttachShader(shaderProgram,vertexShader);
  glAttachShader(shaderProgram,fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  }
  
  // 激活程序对象
  glUseProgram(shaderProgram);
  
  //删除着色器对象
  glDeleteShader(vextexShader);
  glDeleteShader(fragmentShader);
  ```

#### 链接顶点属性

```cpp
/**
* 配置顶点属性 顶点属性大小 数据类型 数据是否被标准化 步长 位置数据在缓冲中的的起始位置偏移量
**/
glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

// 以顶点属性值位置值作为参数
glEnableVertexAttribArray(0)
```

#### 顶点数组对象

 一个顶点数据对象会存储以下内容

- glEnableVertexAttribArray 和 glDisableVertexAttribArray 
- 通过 glVertexAttribPointer 设置的顶点属性配置
- 通过 glVertexAttribPointer 调用与顶点属性关联的顶点缓冲对象

```cpp
// ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
// 1. 绑定VAO
glBindVertexArray(VAO);
// 2. 把顶点数组复制到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

// ..:: 绘制代码（渲染循环中） :: ..
// 4. 绘制物体
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
someOpenGLFunctionThatDrawsOurTriangle();
```

