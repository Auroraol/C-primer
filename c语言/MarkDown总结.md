# 预科班学习总结
## 第一节课

### 必备的软件
* 开发工具 - [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com/zh-hans/vs/)
* 英语工具 - [有道词典](https://cidian.youdao.com/m/#/)
* 解答工具 - [向日葵远程工具](https://sunlogin.oray.com/download?categ=personal)
* 压缩工具 - [7zip](https://www.7-zip.org/download.html)

### 电脑常识
* 文件后缀名
* dos命令
* path环境变量
* 压缩与解压

### 编译器与IDE

* #### 编译器

  * ######   GCC

* #### IDE（集成开发环境）

  * ######  C_Free

  * ###### Code Blocks（CB）

  * ###### Dev C++

  * ###### Visual C++ 6.0（不推荐使用）

  * ###### CLang

  * ###### CLion（跨平台）

  * ###### XCode

  * ###### turbo C（了解就行）

  * ###### Visual Studio 2022（好用，非常好用）:sunglasses:

### Visual Studio 2022 的安装

<img src=".\img\vsinstall2.png" style="zoom: 33%;" />

<img src=".\img\vsinstall1.png" style="zoom: 33%;" />



## 第二节课

### Visual Studio 2022 的基本操作

* ###### 创建新项目

* ###### 项目介绍

  * 解决方案管理器
  * 添加文件
  * 添加项目

* 项目属性

  * 平台工作集
  * 字符集
  * 语言标准
  * SDL检查

* 项目管理器

  * Debug和release
  * x64和x86
  * 调试和运行项目
  * 注意：一旦更改所有配置属性得重新配置

* ###### 压缩项目文件

* ###### 其他窗口

  * 错误列表
  * 输出

### Visual Studio 2022 的其他操作

* ###### 个人爱好

  * 设置字体，行号

* ###### 个人模板

  * 如何创建模板
  * 如何使用模板

* ###### 代码片段管理器

* ###### 快捷键操作

### 代码规范

* ###### 命名规则

  * 驼峰式  -  tuoFengShi
  * 帕斯卡  -  PaSiKa
  * 匈牙利  -  xx_XiongYaLi

## 第三节课

### MarkDown语法学习

* ###### 标题

  ```markdown
  # 这是一级标题
  ## 这是二级标题
  ### 这是三级标题
  #### 这是四级标题
  ##### 这是五级标题
  ###### 这是六级标题
  ```

* ###### 文本样式

  ```markdown
  *斜体文本*
  _斜体文本_
  **粗体文本**
  __粗体文本__
  ***粗斜体文本***
  ___粗斜体文本___
  ~~删除线~~
  ```

  ==这叫什么来着？==

* ###### 图片显示

  ```markdown
  ![图片1](图片路径)
  ```

* ###### 代码片段

  ```markdown
  ```c
  #include <stdio.h>
  
  int main()
  {
      printf("hello MarkDown");
      return 0;
  }
  ```
  ```
  
* ###### 链接

  ```markdown
  [百度一下](https://www.baidu.com)
  ```

* ###### 表格

  ```markdown
  | 数据类型 | 占用字节数 |
  | -------- | ---------- |
  | char     | 1          |
  | int      | 4          |
  | float    | 4          |
  | double   | 8          |
  ```

* ###### 其它操作

  ```markdown
  注脚[^1]
  
  
  [^1]:注脚内容
  ```