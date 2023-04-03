# 样式配置

我看之前有很多人找不到settings.json在哪，其实在设置里面点击右上角的转换按钮就可以打开。

![img](vscode配置.assets/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAaXR5YW5nZXI=,size_20,color_FFFFFF,t_70,g_se,x_16.png)


```c
{
  "code-runner.runInTerminal": true, //终端显示
  "editor.mouseWheelZoom": true, //缩放类似ccatia
  "explorer.confirmDragAndDrop": false,
  // 英文Monaco，中文思源黑体，字号14，行高20，去除斜体的注释样式
  "editor.fontFamily": "Monaco,'思源黑体','Courier New', monospace",
  "editor.fontSize": 14, //大小
  "editor.lineHeight": 20, //行高
  "workbench.colorTheme": "One Dark Pro", //主题
  "editor.tokenColorCustomizations": {
    "textMateRules": [
      {
        "name": "Comments",
        "scope": "comment, punctuation.definition.comment",
        "settings": {
          "fontStyle": ""
        }
      },
      {
        "name": "js/ts italic",
        "scope": "entity.other.attribute-name.js,entity.other.attribute-name.ts,entity.other.attribute-name.jsx,entity.other.attribute-name.tsx,variable.parameter,variable.language.super",
        "settings": {
          "fontStyle": ""
        }
      },
      {
        "name": "js ts this",
        "scope": "var.this,variable.language.this.js,variable.language.this.ts,variable.language.this.jsx,variable.language.this.tsx",
        "settings": {
          "fontStyle": ""
        }
      }
    ]
  },
  "scm.alwaysShowProviders": true,
  "explorer.confirmDelete": false,
  "git.autofetch": true,
  "git.confirmSync": false,
  "terminal.integrated.profiles.windows": {
    "PowerShell": {
      "source": "PowerShell",
      "icon": "terminal-powershell",
      "args": ["-NoExit", "/C", "chcp 65001"]
    },

    "Command Prompt": {
      "path": [
        "${env:windir}\\Sysnative\\cmd.exe",
        "${env:windir}\\System32\\cmd.exe"
      ],
      "args": [],
      "icon": "terminal-cmd"
    },
    "Git Bash": {
      "source": "Git Bash"
    },
    "Ubuntu (WSL)": {
      "path": "C:\\Windows\\System32\\wsl.exe",
      "args": ["-d", "Ubuntu"]
    }
  },
  "terminal.integrated.defaultProfile.windows": "PowerShell",
  "update.showReleaseNotes": false,
  "debug.onTaskErrors": "debugAnyway",
  "cmake.configureOnOpen": true,
  "files.associations": {
    "*.sln": "cpp"
  },
  "extensions.autoUpdate": "onlyEnabledExtensions",
  "leetcode.endpoint": "leetcode-cn",
  "leetcode.nodePath": "C:\\Program Files\\nodejs\\node.exe",
  "leetcode.workspaceFolder": "C:\\Users\\16658\\.leetcode",
  "workbench.iconTheme": "vscode-icons",
  "editor.formatOnSave": true,
  "gulp.autoDetect": "on",
  "workbench.startupEditor": "none",
  "files.autoGuessEncoding": true,
  "code-runner.executorMap": {
    
    "javascript": "node",
    "java": "cd $dir && javac $fileName && java $fileNameWithoutExt",
    "c": "cd $dir && gcc $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "cpp": "cd $dir && g++ *.cpp -o $workspaceRoot/build/$fileNameWithoutExt && $workspaceRoot/build/$fileNameWithoutExt",   //生成exe位置
    //"c": "cd $dir && gcc *.cpp -o $fileNameWithoutExt && $dir$fileNameWithoutExt"
    //"cpp": "cd $dir && g++ *.cpp -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "objective-c": "cd $dir && gcc -framework Cocoa $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "php": "php",
    "python": "python -u",
    "perl": "perl",
    "perl6": "perl6",
    "ruby": "ruby",
    "go": "go run",
    "lua": "lua",
    "groovy": "groovy",
    "powershell": "powershell -ExecutionPolicy ByPass -File",
    "bat": "cmd /c",
    "shellscript": "bash",
    "fsharp": "fsi",
    "csharp": "scriptcs",
    "vbscript": "cscript //Nologo",
    "typescript": "ts-node",
    "coffeescript": "coffee",
    "scala": "scala",
    "swift": "swift",
    "julia": "julia",
    "crystal": "crystal",
    "ocaml": "ocaml",
    "r": "Rscript",
    "applescript": "osascript",
    "clojure": "lein exec",
    "haxe": "haxe --cwd $dirWithoutTrailingSlash --run $fileNameWithoutExt",
    "rust": "cd $dir && rustc $fileName && $dir$fileNameWithoutExt",
    "racket": "racket",
    "scheme": "csi -script",
    "ahk": "autohotkey",
    "autoit": "autoit3",
    "dart": "dart",
    "pascal": "cd $dir && fpc $fileName && $dir$fileNameWithoutExt",
    "d": "cd $dir && dmd $fileName && $dir$fileNameWithoutExt",
    "haskell": "runhaskell",
    "nim": "nim compile --verbosity:0 --hints:off --run",
    "lisp": "sbcl --script",
    "kit": "kitc --run",
    "v": "v run",
    "sass": "sass --style expanded",
    "scss": "scss --style expanded",
    "less": "cd $dir && lessc $fileName $fileNameWithoutExt.css",
    "FortranFreeForm": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "fortran-modern": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "fortran_fixed-form": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "fortran": "cd $dir && gfortran $fileName -o $fileNameWithoutExt && $dir$fileNameWithoutExt",
    "sml": "cd $dir && sml $fileName"
  } // 控制是否显示源代码管理提供程序部分,即使只有一个已注册的提供程序。
}

```



## 步骤

# (1).配置编译器

按快捷键**Ctrl+Shift+P调出命令面板，输入C/C++，选择“Edit Configurations(UI)”进入配置**。这里配置两个选项： - 编译器路径：D:/mingw-w64/x86_64-8.1.0-win32-seh-rt_v6-rev0==**/mingw64/bin/g++.exe**== **==再选择gcc-x64==**

出现配置完成后，此时在侧边栏可以发现多了一个.vscode文件夹，并且里面有一个==**c_cpp_properties.json文件**==，内容如下，说明上述配置成功。现在可以通过Ctrl+<`快捷键打开内置终端并进行编译运行了。

```c++
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
                // "C:/Users/16658/Desktop/Test/include",    //头文件的路径在此插入这两行
                // "C:/Users/16658/Desktop/Test/src"   //源文件的路径在此插入这两行

            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "C:/mingw64/bin/g++.exe",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```



# (2).配置构建任务

创建一个tasks.json文件来告诉VS Code如何构建（编译）程序。该任务将调用g++编译器基于源代码创建可执行文件。 ==**按快捷键Ctrl+Shift+P调出命令面板，输入tasks，选择“Tasks:Configure Default *Build Task*”：**==

==**再选择“C/C++: g++.exe build active file”**==

此时会出现一个名为tasks.json的配置文件，内容如下：



# 配置多文件编译调试(一定从主函数进入调试)

tasks.json**修改一下就行**

```c++
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "C/C++: g++.exe 生成活动文件",//任务的名字，可以自己设置
			"command": "C:/mingw64/bin/g++.exe",
			"args": [
				"-fdiagnostics-color=always",
				"-g",//添加gdb调试选项
				"${file}",//在下面添加
                // "-I","C:/Users/16658/Desktop/Test/include/*.h",  //在此插入："-I","头文件路径",
                // "-I","C:/Users/16658/Desktop/Test/src/*.cpp",    //在此插入："-I","源文件路径",   其中 -I（大写i）表示你的头文件路径， -L 表示库文件路径，-l（小写L) 代表库文件 
				// "${fileDirname}\\studenSystem.cpp", //添加这一行就够了，即为了让编译器找到对应的.cpp文件，如果有其他.cpp文件，继续按照这种方式添加就可以了  // studenSystem.cpp需要对应修改
				//"${fileDirname}\\*.cpp",
                "-o",//指定生成可执行文件的名称
				"${workspaceFolder}\\build\\${fileBasenameNoExtension}.exe",  // 工作区文件夹\\生成exe文件的位置\\无扩展类型的文件名.exe
                //  "${fileDirname}\\${fileBasenameNoExtension}.exe" y
			],
			"options": {
				"cwd": "C:\\mingw64\\bin"  // 文件位置就是你的mingw64的bin文件夹所在位置
				
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "编译器: C:/mingw64/bin/g++.exe"
		}
	]
}
```



# (3).配置调试设置

这里主要是为了在.vscode文件夹中产生一个launch.json文件，用来配置调试的相关信息。==**点击菜单栏的*Debug*-->*Start Debugging*：****选择C++(GDB/LLDB)：**==

==修改launch.json==

**粘贴,修改下数据就行**

```c++
{
    "version": "0.2.0",
    "configurations": [
      {
        "name": "g++.exe - 生成和调试活动文件",
        "type": "cppdbg",
        "request": "launch",
        "program": "${workspaceFolder}\\build\\${fileBasenameNoExtension}.exe",    // 生成exe位置
        //"program": "${fileDirname}/${fileBasenameNoExtension}.exe",//一般的  
        "args": [],
        "stopAtEntry": false, 
        "cwd": "${workspaceRoot}",  // 调试程序时的工作目录，一般为${workspaceRoot}即代码所在目录 
        "externalConsole": false,   // 调试时是否显示控制台窗口，一般设置为true显示控制台
        "MIMode": "gdb",
        "miDebuggerPath": "C:\\mingw64\\bin\\gdb.exe",
        "setupCommands": [
          {
            "description": "为 gdb 启用整齐打印",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
          },
          {
            "description": "将反汇编风格设置为 Intel",
            "text": "-gdb-set disassembly-flavor intel",
            "ignoreFailures": true
          }
        ],
        "preLaunchTask": "C/C++: g++.exe 生成活动文件"
      }
    ]
  }
```



**g++.exe  和  gdb**









![image-20220722213426727](vscode配置.assets/image-20220722213426727.png)







![image-20220723155622612](vscode配置.assets/image-20220723155622612.png)

----------



**工程目录:**

[GitHub - hattonl/cpp-project-structure: C++工程目录结构规范示例](https://github.com/hattonl/cpp-project-structure#todo)

# vscode自动生成项目目录结构

![image-20220724135558344](vscode配置.assets/image-20220724135558344.png)



效果:

![image-20220724164410338](vscode配置.assets/image-20220724164410338.png)

代码:

**看配置样式**







# 规范

## 顶层目录结构

```
project_name
├── deploy
├── build
├── doc
├── 3rdparty
├── include
│   └── project_name
├── project_name
├── tools
├── scripts
├── platforms
├── test
├── LICENSE
├── CMakeLists.txt
├── build.sh
├── toolchain.cmake
├── .gitignore
├── readme.md
└── sample
```

- **deploy :** 用于存放部署、交付的文件，其包含子目录bin、lib、include分别存放本项目最总生成的可执行文件、库文件以及对外所提供的头文件。
- **build :** 用于存放build时cmake产生的中间文件，其包含子目录release和debug。
- **doc :** 用于存放项目的相关文档。
- **3rdparty :** 用于存放第三方库，每个第三库以单独目录的形式组织在3rdparty目录下。其中每个第三方目录下又有 `include` 和 `lib` 分别存放第三方库的头文件和库文件。
- **include/project_name :** 用于存放每个模块以及整个工程对外的头文件。具体格式如下文。
- **project_name :** 存放源码文件，以及内部头文件。具体格式如下文。
- **tools :** 包含一些支持项目构建的工具，如编译器等，一般情况下使用软链接。
- **scripts :** 包含一些脚本文件，如使用Jenkins进行自动化构建时所需要的脚本文件，以及一些用于预处理的脚本文件。
- **platforms :** 用于一些交叉编译时所需要的工具链等文件，按照平台进行划分来组织子目录。每个子目录下存放 `toolchain.cmake` 等用于指定平台的文件。
- **test :** 分模块存放测试代码。
- **LICENSE :** 版权信息说明。
- **CMakeLists.txt :** cmake文件。
- **build.sh :** build脚本文件。
- **.gitignore :** 指明git忽略规则。
- **readme.md :** 存放工程说明文件。
- **sample :** 存放示例代码。

## 源文件目录结构说明

结构示例：

```
# example modules tree
project_name
├── module_1
│   ├── dir_1
│   │   ├── something.cc
│   │   └── something.h
│   ├── dir_2
│   ├── module_1.cc
│   ├── CMakeLists.txt
│   └── README.md
├── module_2
│   ├── dir_1
│   ├── dir_2
│   ├── module_2.cc
│   ├── CMakeLists.txt
│   └── README.md
├── module_3
├── main.cc
└── CMakeLists.txt
```

1. 总源码文件目录以 `project_name` 命名，即与项目同名，存放在项目根目录下。
2. 源码文件分模块进行组织，分别以各个模块进行命名存放在 `project_name` 目录下，如示例中的 `module_1` 、`module_2`。
3. 在每个子模块目录下，只包含源文件以及该模块内部所调用的头文件。
4. 每个子模块的根目录下存放该模块的主要功能逻辑代码，如 `module_1.cc`。另外，可按照功能再划分子目录进行源码组织，但不可以出现模块嵌套的情况。
5. 若要包含内部头文件时，包含路径要从 `project_name` 开始路径要完整，如`#include "project_name/module1/dir_1/somthing.h"`，以防止头文件名称冲突的情况，同时遵循了[Google C++编码规范](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)。

## 头文件目录结构说明

```
# example include tree
include
└── project_name
    ├── module_1
    │   ├── module_1_header_1.h
    │   └── module_1_header_2.h
    ├── module_2
    │   └── module_2.h
    └── project_name.h
```

1. （公共）头文件目录以 `include/project_name` 命名，即文件目录为两级，存放在项目根目录下。该目录只包含所有对外的头文件。
2. 头文件同样分模块进行组织，分别以各个模块进行命名存放在 `include/project_name` 目录下，如示例中的 `module_1` 、`module_1`。
3. `include/project_name` 目录下最多只包含一级子目录，即最多按照模块再划分一级，模块内的功能头文件不再以功能进行划分。
4. 若要包含外部头文件时，包含路径同样要从 `project_name` 开始路径要完整，如`#include "project_name/module_2/module_2.h"`。

## 其他

1. 针对头文件的包含，顶层 `CMakeLists.txt` 只指定 `${CMAKE_SOURCE_DIR}\include` 和 `${CMAKE_SOURCE_DIR}`，以保证所有的包含规则都是从工程根目录开始包含。
2. 添加 `include` 目录使得公共头文件和对内部文件可以分离开，使多个模块之间合作开发时项目内部结构更加清晰。
3. （暂时）在 `3rdparty` 下存放的工程中用到的第三方库和第三方源码。第三方库尽量不要直接把静态连接库直接放到git仓库中，应该另外提供链接以便下载，或者提供文档说明库的名称和版本自行安装下载，或者提供git仓库自行编译。第三方源码一般为开源的，只提供git链接。









# 用wls + clang + cmake的配置不用 c++的编译配置



**写好cmake就行**

launch.json

```
{
  "version": "0.2.0",
  "configurations": [
    {
      "type":"lldb",
      "request": "launch",
      "name": "Debug",
      "program": "${command:cmake.launchTargetPath}",
      "args": [],
      "cwd": "${workspaceFolder}",
      "internalConsoleOptions": "neverOpen",
      "console": "integratedTerminal" 

    }
  ]
}
```







# 调试



**step into：单步执行，遇到子函数就进入并且继续单步执行（进入子函数）；**



**step over：在单步执行时，在函数内遇到子函数时不会进入子函数内单步执行，而是将子函数整个执行完再停止，也就是把子函数整个作为一步。有一点,经过我们简单的调试,在不存在子函数的情况下是和step into效果一样的（越过子函数，但子函数会执行）。**



**step out：当单步执行到子函数内时，用step out就可以执行完子函数余下部分，并返回到上一层函数。**



