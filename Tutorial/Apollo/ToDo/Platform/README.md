- [无人驾驶仿真实践](#无人驾驶仿真实践)
  - [1. Apollo](#1-apollo)
    - [1.1 平台架构介绍](#11-平台架构介绍)
    - [1.3 平台安装](#13-平台安装)
    - [1.4 仿真使用](#14-仿真使用)
    - [1.5 实战](#15-实战)
  - [2. Apollo ROS 原理与实践](#2-apollo-ros-原理与实践)
    - [2.1 背景介绍](#21-背景介绍)
    - [2.2 ROS 概述](#22-ros-概述)
    - [2.3 Apollo ROS 原理](#23-apollo-ros-原理)
    - [2.4 ROS 深入介绍](#24-ros-深入介绍)
    - [2.5 Apollo 框架使用](#25-apollo-框架使用)
  - [参考文献](#参考文献)


# 无人驾驶仿真实践
## 1. Apollo 
### 1.1 平台架构介绍
<div align=center><img src=./figs/apollo_6_0.png width=600></div>

  1. 最底层是车辆平台；若要运行Apollo，该车辆平台需要支持线控 (Drive by Wire Vehicle)。
  2. 车辆平台之上是各种传感器以及高性能计算单元, 和一个Black Box;
  3. 在往上便是Apollo核心的软件层：最底层是一个实时操作系统(RTOS), 然后是一个 Runtime Framework (ROS), 最后核心的算法模块
  4. 最上层便是云服务：高精地图、仿真等

**接入不同于参考硬件的Driver**
<div align=center><img src=./figs/module_driver_camera.png width=300><img src=./figs/module_driver_lidar.png width=275></div>

**Build**
  1. 在Ubuntu环境下下载Apollo源码并安装Docker (Docker CE)
  2. 拉取Apollo发布镜像并创建Apollo运行容器
  3. 在容器内从源代码编译Apollo
  4. 启动Apollo

**RTK寻迹测试**
  - 核心代码：`modules/tools/record_play/rtk_recorder.py` 用来录制轨迹即GPS点和一些车辆信息(速度、朝向、加速度等)，最后形成一个csv文件
  - 核心代码：`modules/tools/record_play/rtk_player.py` 用来控制车辆跟随之前csv文件中的记录的信息运行

**From HD Map to Relative Map**
  - 相对地图：以车辆坐标系建立的车辆周围的环境信息，比如车道线

**一些常用工具**
  - Relative Map Viewer: 离线查看录制的相对地图
  - DBC File转化工具，生成Protobuf。gen_vehicle_protocol:告诉你有哪些信号可以控制
  - Teleop: 提供一些基本的控制指令用来测试信号传输是否成功
  - Topic 监控工具：Diagnostics
  - 代码调试配置工具：configuration
  - rosbag tool
  - 交通灯模拟工具：修改高精地图中红绿灯的状态
  - Sim & Dreamview: 障碍物模拟、障碍物topic数据回放

**核心问题解答**
  - 如何生成openDRIVE格式的高精地图文件，比如自带的base_map.xml？
  - 如何在Planning模块中使用自己的代码？
  - DreamView的使用？


### 1.3 平台安装


### 1.4 仿真使用

**官网在线仿真**
  1. 接入自己的决策规划算法
  2. 按固定格式压缩
  3. 根据压缩包创建仿真任务 (https://apollo.auto)
  4. 查看任务运行结果


### 1.5 实战
还是遵循从易到难的实践思路，先搭建一个最小系统，验证最基本功能，确保整个系统可以运行，然后逐个尝试更复杂功能及模块。

**创建自己的planner**
  - 将新的Planner配置添加到modules/planning/conf/planning_config.pb.txt中
  - 在module/planninig/planning.cc中注册新的planner



## 2. Apollo ROS 原理与实践
### 2.1 背景介绍
**自动驾驶底层框架为何选用ROS**
 - 开发工具包：完整的包管理和工程结构；庞大的基础库；多语言接口支持；
 - 计算调度模型：消息驱动的异步运行模型；抽象的P2P通信接口；自定义消息格式
 - 调试工具：可视化的调试工具；消息查看、存储、回放工具；

### 2.2 ROS 概述
注意不是把概念的理解的多透彻，用法了解的多全面就是好的。重要的是多上手多实践，把一个功能用熟了，其他功能都会触类旁通，否则概念了解的再清楚，复习了再多遍，也写不出程序。

ROS是一个松耦合的框架，各个节点之间是一个解耦合的关系。节点可以理解成一个算法模块，节点之间相互独立且需要相互通信。

Roscore中的节点管理器 Master: 管理各个节点之间逻辑关系：发现对方、建立通讯连接并互相传输数据；
  - 假设一个感知Perception Node A 拟向 Obstacle Topic 发布消息，Planning Node 拟向 Obstacle Topic 订阅消息。这两个节点在启动时都会向Master注册一下，声明自己会向某个话题发布消息或会订阅某个话题的消息。当Master节点发现Perception 已经启动时，会向Planing发送一个消息，高度他Perception已经启动了，然后Planning 就会向Perception发出一个建立连接的请求，然后Perception 的数据通过topic传输给Planning (基于TCP的通信链路)。因此roscore起到一个中转站的作用，用于建立连接，一旦建立连接，和roscore之间的链接就会断开。
  - Topic 里面处理的数据类型用MSG描述；每个topic也会有自己的作用域，如果直接/topic就是一个全局的话题，否则前面会再自动加一个节点名作为自己的NameSpace
 
  /rosout是Roscore中的一个隐藏的记录日志相关的节点，所有节点发生的log都会被rosout订阅，并进行分级并打印到日志文件中。

更详细的教程参考ETH的ppt和课程作业
https://rsl.ethz.ch/education-students/lectures/ros.html
https://www.youtube.com/watch?v=aL7zLnaEdAg

### 2.3 Apollo ROS 原理
**ROS存在的问题**
  - 大数据量传输存在性能瓶颈：Message只能处理较小的数据类型，但在自动驾驶中，图像(4x5x10)、Lidar(7x10)产生的数据量非常大，这种大数据量的传输在现有的ROS框架下存在明显的性能瓶颈，最直观的表现就是时延。
  - 单中心的网络存在单点风险：节点之间的管理依靠roscore,一旦崩溃，其它节点也会存在失效的风险。
  - 数据格式缺乏向后兼容：ROS现有的数据格式不具有很好的兼容性：Message数据类型需要事先定义好，一旦某个消息类型在上游进行了修改，那么下游所有用到这个类型的节点也都要做对应的修改，并且之间录制的一些数据也要做批量的转换才能使用。

**Apollo平台对ROS的改进**
  - 通信性能优化：很多数据不仅是一对一的传输关系，经常是一对多。比如一帧camera图像，同时会被多个节点订阅，如定位、感知、预测等。传统的方案会将同一个数据复制多次，Apollo中通过共享内存的通信减少传输中数据的拷贝，显著提高传输效率。
  - 去中心化网络拓扑：使用RTPS服务发现协议实现完全的P2P网络拓扑
    - (1). sub节点启动,通过组播向网络注册：会向当前网络中的所有节点发送一个信息，告诉大家现在有一个新的节点要启动；
    - (2). 通过节点发现，两两建立unicast：
    - (3). 向新加入的节点发送历史拓扑消息：在这个节点加入之前，每个节点都维护了该节点和其他节点的链接关系，供这个新节点更新自己的拓扑结构
    - (4). 收发双方建立实际连接，开始通信
  - 数据兼容性扩展：原生ROS中发送者和接收者在建立消息连接之前，都要预先进行一个消息的定义，才能建立实际的链接。使用Protobuf消息格式与ROS深度集成

### 2.4 ROS 深入介绍


**ROS的其他两种通讯方式**
 - 基于消息的发布订阅模型
 - 一个节点可以启动一个server去注册一项服务，另外一个节点在使用这项服务的时候，可以通过call service 实现实时的数据通信交互。基于Message 的通信交互，是一种被动的行为，而client向server发送服务请求的时候，会等待server的一个响应，然后根据具体的响应进行响应的操作。
 - parameter通讯方式：用来实时获取或设定全局参数


### 2.5 Apollo 框架使用

**Apollo技能图谱**
<div align=center><img src=./assets/figs/apollo_skills_basic.png width=300><img src=./assets/figs/apollo_skills_planning.png width=300></div>

  - [详见](http://taylorliu.com/topics/data/apollo-v2.pdf)


## 参考文献
  - [Apollo的仿真平台](https://azure.apollo.auto/)
  - [百度Apollo决策规划模块相关资料汇总](https://guyuehome.com/34285)
  - 自动驾驶决策控制及运动规划史上最详细最接地气综述 - 知乎
https://zhuanlan.zhihu.com/p/260707853
