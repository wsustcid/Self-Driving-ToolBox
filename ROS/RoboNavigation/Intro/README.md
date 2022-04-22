<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-03-13 21:20:12
 * @LastEditTime: 2022-04-21 22:48:30
-->
- [1. 快速入门](#1-快速入门)
  - [1.1 移动机器人技术领域简介](#11-移动机器人技术领域简介)
  - [1.2 常见的移动机器人](#12-常见的移动机器人)
  - [1.3 常用的传感器](#13-常用的传感器)
  - [1.4 基于ROS的机器人控制](#14-基于ros的机器人控制)

## 1. 快速入门
### 1.1 移动机器人技术领域简介
**建图导航的延承与技术发展**  
移动机器人中的问题可以大致可以三个部分：建图、定位和导航（或者说运动控制）。建图和定位一起做就是SLAM，建图和导航一起做或者说三个同时做就是探索，定位和导航一起做就是主动定位。
  - SLAM是被动的，仅仅处理所获取的传感器的信息
  - Exploration actively giudes the robot to cover the environment with its sensors.
  - 换句话说，探索时主动引导机器人，利用其传感器搜索整个环境。

**ROS在移动机器人中的应用**  
应用面很广，现在几乎所有的机器人基本都用ROS了。


### 1.2 常见的移动机器人
**差速机器人**
  - Turtle Bot: Bugger, Waffle
  - Pioneer

**全向机器人**
  - 麦克纳姆轮
  - 全向轮

**Ackerman Steering**
  - ROS 里面已经有了Ackerman control


### 1.3 常用的传感器
  - 摄像头
  - 惯性测量计IMU
  - 麦克风阵列
  - 力/力矩传感器
  - 环境监测传感器
  - 射频传感器（RFID)
  - Range Finder
    - 2D Range Finder: 二维的激光雷达
    - 3D Range Finder: 奥比中光, Real Sense D435


### 1.4 基于ROS的机器人控制
**移动机器人ROS功能包核心构成**  
在ROS中，不管底层是哪一种机器人平台，其功能包一般都是由以下四个子功能包组成，以turtlebot为例：
  - `turtlebot_bringup`: 通常用于使用U转串数据线连上之后，可以启动该机器人。该功能包核心操作两个话题，一个是用于接收上位机发送控制命令给底盘的`cmd_vel`,一个是发布底层编码器获取的odom里程计信息
  - `turtlebot_capabilities`: 该机器人包含的一些核心功能, 比如建图等
  - `turtlebot_descripiton`: urdf机器人描述文件，用于可视化，以及坐标系之间的标定关系
  - `turtlebot_teleop`: 控制节点，用于远程操控


**控制机器人**  
```bash
## 准备工作：Linux + ROS 安装

## 控制真实环境中的机器人
# 1. 安装turtlebot相关功能包/驱动
sudo apt-get install ros-indigo-turtlebot-*
# 2. 启动turtlebot
roslaunch turtlebot_bringup minimal.launch
# 3. 启动键盘控制
roslaunch turtlebot_teleop keyboard_teleop.launch

## 在仿真中控制机器人
# 1. 启动turtlebot在gazebo中的仿真
roslaunch turtlebot_gazebo turtlebot_word.launch # 包括环境仿真、机器人仿真、传感器仿真等
# 2. 启动键盘控制 
roslaunch turtlebot_teleop keyboard_teleop.launch
# 注意/depthimage_to_laserscan
rosrun tf tf_echo /base_link /odom
```

**常用命令**  
```bash
# 查看已连接设备和端口
lsusb 
ls /dev/ttyUSB0
# 添加端口权限
sudo chmod +666 /dev/ttyACM0

## 常用ROS命令
roscd turtlebot # ls launch 查看都有哪些launch文件可以使用
rosnode list # 查看已启动节点
rosnode info /node_name # 查看节点信息：其订阅节点，发布节点、服务等
# 然后逐个启动launch文件测试了解这个机器人的基本功能
rostopic list

roswtf # 显示一些异常信息，比如一些发布话题未被订阅

rosparam list # 显示参数列表
rosparam get/set

rosservice list
rosservice call 
```
注：
  - 连接设备之后，当有多个usb转串口设备，其接口都会在`/dev`下面，其名字要么是`ttyACM0`，或者`ttyUSB0`。当有两个usb设备时，因为插入顺序的不同，launch文件启动时设置其端口号就有可能启动机器时找不到设备。为了更改该端口名，可以更改 `/etc/udev/rules.d`内的SYMLINK


参考资料：
  - [turtlebot3建图导航](https://blog.csdn.net/weixin_51331359/article/details/121598373)