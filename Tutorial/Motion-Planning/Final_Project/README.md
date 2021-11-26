<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-11 19:51:34
 * @LastEditTime: 2021-11-26 20:54:37
-->

- [8. 项目实践](#8-项目实践)
  - [8.1 项目准备](#81-项目准备)
    - [8.1.1 CARLA 安装](#811-carla-安装)
    - [8.1.1 Linux (Ubuntu 16.04 or later)](#811-linux-ubuntu-1604-or-later)
    - [8.1.2 Windows 7 (64-bit) or later](#812-windows-7-64-bit-or-later)
    - [8.1.3 MacOs](#813-macos)
    - [8.1.2 项目文件下载](#812-项目文件下载)
  - [8.2 实施步骤](#82-实施步骤)
    - [8.2.1 运动规划器实现](#821-运动规划器实现)
    - [8.2.2 仿真测试](#822-仿真测试)
    - [8.2.3 结果评测](#823-结果评测)
    - [8.2.4 参考答案](#824-参考答案)

# 8. 项目实践
本项目的主要任务为沿着给定路网的一系列点集控制车辆运动直至到达目标点。具体主要包含三种任务场景：
  - 首先是静止的障碍物将会堵塞你当前车道：可以使用圆形逼近车辆足迹然后进行碰撞检查，然后移除碰撞路径，进而实现避障
  - 其次是动态障碍物影响：将会遇到一个前车，以低于限速的速度行驶，你必须根据前车速度跳着本车速度来避免碰撞
  - 最后是路口停车标志的影响：通过构建一个在状态机来处理停车标志，即拥有减速至停车，停止后短暂等待，然后继续前进通过路口

完成上述任务之后，可以继续扩展，完成更加复杂的交通场景，比如换道超车等

## 8.1 项目准备
### 8.1.1 CARLA 安装
为完成本项目，需要先安装Carla仿真器，这里提供了对应环境的详细安装教程和安装文件，根据教程一步步进行安装测试即可。

注意：
  - 这里提供的Carla仿真器是基于原始的Carla安装包，且额外包含了本项目将要使用的地图，因此为完成本项目，需要使用此处提供的安装包

### 8.1.1 Linux (Ubuntu 16.04 or later)
   1. 从[这里](doc/CarlaUE4Ubuntu.tar.gz) 下载Carla仿真器
   2. 按照[本教程](doc/CARLA-Setup-Guide-_Ubuntu_.pdf) 进行安装测试

### 8.1.2 Windows 7 (64-bit) or later
   1. 从[这里](doc/CarlaUE4Windows.zip) 下载Carla仿真器
   2. 按照[本教程](doc/CARLA-Setup-Guide-_Windows-x64_.pdf) 进行安装测试

### 8.1.3 MacOs
因为Carla并没有Mac版本，因此并无法直接安装到Mac系统中，最好的方式是创建一个包含Linux或Windows的双系统：
  - [Install Windows on your Mac with Boot Camp](https://support.apple.com/en-ca/HT201468)
  - [Dual-Boot between Ubuntu and MacOS](https://help.ubuntu.com/community/MactelSupportTeam/AppleIntelInstallation)

注意，并不推荐使用虚拟机运行其他系统，因为其没有对应的硬件虚拟化来运行carla所需的Unreal Engine。因此，对于本课程，最好的方式还是创建可以直接启动的双系统。

### 8.1.2 项目文件下载
从[此处](./doc/Course4FinalProject.zip)下载项目所需的代码文件，并将其解压至仿真器文件夹内的 `PythonClient/Course4FinalProject`文件内，放至其他位置运行时可能会出现问题。

## 8.2 实施步骤
### 8.2.1 运动规划器实现
在本项目中，主要任务为通过完善 "behavioural_planner.py", "collision_checker.py",  "local_planner.py", "path_optimizer.py", and "velocity_planner.py" 类文件，来分别实现 行为规划、路径生成、静态障碍检查、路径选择以及速度生成，最终构建成一个完整的运动规划器。

**行为规划**  
在本项目中，将实现一个状态机，通过在 Lane Following, decelerate to stop sign 以及staying stopped 状态之间进行状态转移来处理停车标志。
  - 首先完成`get_closest_index()` 以及 `get_goal_index()`这两个函数，分别让行为规划器知道其相对于全局路径的位置，以及 距离全局路径当前的目标点
  - 然后完成` transition_state() `函数，完成状态机的整个逻辑

**路径生成**  
在本部分，生成螺旋线路径的主要代码都已经给出，我们只需要完成`get_goal_state_set()`来计算目标状态集用于接下来的路径生成。具体包括
  - `thetaf()`: 计算给定螺旋线上不同弧长位置上的车辆航向角
  - `optimize_spiral()`：将给定路径建模成优化问题
  - `sample_spiral()`：完成优化问题后，对最终的路径进行采样，从而生成离散的路径点

**静态障碍物检测**  
主要任务为完善` collision_check()` 函数，实现在给定路径上基于圆的路径检查，包括在每一个路径点上计算圆的位置等。

**路径选择**  
本部分的主要任务为通过对生成的路径利用目标函数进行评估，从而选出最优路径。主要目标为消除会与静态障碍发生碰撞的点，然后选出最接近全局路径中心线的路径
  - 主要需要完成`collision_checker.py` 中的 `select_best_path_index()`函数

**速度生成**  
本部分的速度规划器不会处理一些边界条件，但常规的处理stop sign, 前方动态障碍，以及实现常规的车道保持等都会包括。
  - 主要包含在`compute_velocity_profile()`函数中

完成以上所有文件的TODO部分后，我们就可以消除`module7.py`中对应函数的注释，然后运行仿真器进行相关代码测试。

### 8.2.2 仿真测试
```python
# 1. 启动仿真器
./CarlaUE4.sh /Game/Maps/Course4 -windowed -carla-server -benchmark -fps=30 # for ubuntu
#CarlaUE4.exe /Game/Maps/Course4 -windowed -carla-server -benchmark -fps=30 # for windows

# 2. 运行规划器
python3 module_7.py


#  若仿真器运行速度较慢，可以通过关闭 live plotting 或 修改其刷新速度来加快运行速度
# 可以通过修改 options.cfg 的 live_plotting 和 live_plotting_preiod 参数实现
```
<div align=center><img src=../Doc/figs/project_demo.png width=600></div>

### 8.2.3 结果评测
当仿真运行完毕后，将会生成`controller_output/trajectory.txt` 以及 `controller_output/collision_count.txt`两个文件，可以将这两个文件提交进行评分，来检验你实现的运动规划器是否真的能够产生到达目标位置的无碰撞路径，并且不会偏移waypoints太远，同时也需要实现在stop sign前实现完全停车。

### 8.2.4 [参考答案](./Final-Project-Solution-Slides.pdf)