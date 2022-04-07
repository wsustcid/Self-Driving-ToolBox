- [Visual Studio Code Docs](#visual-studio-code-docs)
  - [1. My Setting file](#1-my-setting-file)
  - [2. C++ 编译](#2-c-编译)
    - [2.1 手动编译](#21-手动编译)
    - [2.2 自动编译](#22-自动编译)
    - [2.3 调试](#23-调试)
    - [2.4 gcc 版本切换](#24-gcc-版本切换)
  - [3. Python 调试](#3-python-调试)


# Visual Studio Code Docs
  - 官方文档：https://code.visualstudio.com/docs***

## 1. My Setting file
**常用插件**
  - python
  - c++
  - markdown all in one
  - koroFileHeader
  - latex workshop

**插件设置**  
ctrl+ship+p: 打开配置文件：preferences: Open settings (json)，配置相关插件
  - [settings.json](./settings.json)

**sftp.json**
打开项目文件夹，Ctrl+Shift+P 后，输入 sftp ，选择 Config 功能，然后 VSCode 会在当前目录下生成.VSCode 目录，并创建 sftp.json 文件，即为 sftp 要同步文件到其他机器的配置信息。
  - [sftp.json](./sftp.json)

**参考资料：**
  - https://zhuanlan.zhihu.com/p/96819625

注：现在已经可以登录账户同步了，所以每次新安装基本不用重复配置了。


## 2. C++ 编译
正常的文件组织结构:
```c++
project
  - bin
  - build
  - include // 存放头文件
  - src // 存放cPP文件
  Makefile
```

### 2.1 手动编译
通过修改Makefile, 然后终端make手动编译调试；或者在命令行单独编译单个文件：
```bash
# 1.命令编译时常规命令后加上-std=c++11
g++ test.cpp -o test -std=c++11

# 2.修改vim 的.bashrc文件,然后source
alias g++='g++ -std=c++11' # vim sudo ~/.bashrc
```

### 2.2 自动编译

**快速版本**
  - 首先设置编辑器编译配置：`terminal -> config default build task -> 选择对应的gcc版本 -> 对tasks.json进行配置修改`
  - 具体配置文件参考[]()
  - 然后 `ctrl + shift + N` 即可进行编译
  
```json
  "args": [
  "-std=c++17",
  "-I",
  "${fileDirname}\\includes", // 包含其他位置的头文件
      "-g",
      "${fileDirname}/*.cpp", // 参数 `${file} ` 只会编译你当前所处的文件,修改为这种即可编译当前文件所在文件夹下所有文件
      "-o",
      "${fileDirname}/${fileBasenameNoExtension}" //意思是编译后的文件直接与本文件同名,位于同一文件夹下; (我们可以修改到bin下)
  ```


**完整版本：**  
1. Click Run on the left, click to create a launch.json file, C++ (GDB/LLDB/默认配置), the launch.json file will be automatically generated and change the "program xxx" line: ` "program": "${workspaceFolder}/${fileBasenameNoExtension}",`
   - [launch.json](./launch.json)


2. Add build (compile, link, etc.) tasks (tasks.json) 
   - First, use the shortcut key ctrl+shift+p to open the command line and enter`Tasks: Run task`
   - Select No Configured tasks. Configure Tasks...
   - Select Create task.json file from template
   - Select Others
   - Change the generated default tasks.json file as follows (`g++ -g main.cpp -std=c++11 -o main.out`,)
   - [tasks.json](./tasks.json)

3. Add configuration library file support
   - ctrl+shift+p to call up the command line, select C/C++: Edit Configurations(UI)
   - Click c_cpp_properties.json to open the configuration file.
   -  add the required header file path to the IncludePath in the red box `/usr/include/` `"/usr/include/eigen3/"`
4. Use the shortcut key ctrl+shift+p to call up the command line, choose to execute our build task

5. ctrl + shift + n 编译

6. 命令行 ./xx 运行


**关于eigen库：**  
ubuntu已经默认安装了eigen3，位于 `/usr/include/eigen3/`，使用时只需要在配置文件中加入包含路径即可： "/usr/include/eigen3/"
```bash 
sudo apt-get install libeigen3-dev
```


### 2.3 调试
- 设置调试配置：`run->add configuration -> c++ -> 默认配置` 
- 设置断点,F5调试即可



### 2.4 gcc 版本切换
```bash
gcc -v # 用于查询当前版本
which gcc # 查询gcc所在位置（/usr/bin/gcc）

sudo apt-get install gcc-7 g++-7 ## 默认是5.4

# 设置多版本优先级
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-5 50 --slave /usr/bin/g++ g++ /usr/bin/g++-5
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 70 --slave /usr/bin/g++ g++ /usr/bin/g++-7

# 版本切换
sudo update-alternatives --config gcc
```

参考资料:
  - https://blog.csdn.net/uniqueyyc/article/details/85407693


## 3. Python 调试

**1. 设置解释器**  
使用`ctrl+shift+p` 打开控制面板，输入 `python: select interpreter`来选择想要使用的解释器，或者左下角状态栏切换现有解释器
   - 如果没有找到你期望的解释器，参考[Configuring Python environments](https://code.visualstudio.com/docs/python/environments).

设定解释器后，VS Code在`.vscode/settings.json`中存储该工作去的特殊配置，与用户的全局设定相分开。

**2. 运行代码**    
  - 设置好环境后直接点右上角的运行即可
  - 或者在编辑器的任意位置右键，选择：`Run Python File in Terminal`
  - 当然也可以仅运行部分代码：选中部分行的代码，按下`Shift+Enter`或右键后选择`Run Selection/Line in Python Terminal`
  - 如果有时想额外测试一些代码，可以`Ctrl+Shift+P -> Python: Start REPL`就在当前解释器环境下打开了一个终端样式的python解释器，可以直接编程测试
  - ！最便利的方式还是直接 F5 运行
 
**3. 调试代码**   
首先设置断点，然后按下F9进行调试：
  - 调试工具栏出现在页面上方：从左到右功能分别是：运行（F5），跳过（F10），跳入（F11），跳出（Shift+F11），重新开始（Ctrl+Shift+F5），以及停止（Shift+F5）
  - 左侧分别为变量栏：用来显示各种变量
  - WATCH栏用来监控变量值变化：可以通过选中某一变量，然后右键选择：Debug: add to watch
  - 编辑断点：在断点上右键，可以选择编辑断点，比如使用log message选项，可以添加一些输出信息（输出变量用{}括起来），而不用终止或修改程序，程序输出会在Debug console出现
  - 编辑断点-expression：可以写入一个条件表达式，程序仅当此表达式为真时此断电被触发，多用于循环语句中，在某一循环处触发断点，如：name=="Testuser"
  - BREAKINGPOINTS栏选中 Rasied Exceptions，程序会在发生异常处中断，可手动设置一个异常进行尝试：`raise ValueError()`
  - Debug Console：可以在这个窗口中继续操作变量



手动指定自己的解释器路径： File (Code on macOS) > Preferences > Settings menu command (Ctrl+,) to open your [Settings](https://code.visualstudio.com/docs/getstarted/settings), select Workspace. Then create or modify an entry for `python.pythonPath` with the full path to the Python executable (if you edit `settings.json` directly, add the line below as the setting):
```json
// for win
"python.pythonPath": "c:/python36/python.exe",
// macOS/Linux:
"python.pythonPath": "/home/python36/python",
// virtual env
"python.pythonPath": "/home/abc/dev/ala/venv/bin/python",
```