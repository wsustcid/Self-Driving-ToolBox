<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-03-22 19:47:22
 * @LastEditTime: 2022-04-09 17:24:23
-->

## 1. Autoware概述
### 1.1 Autoware简介
Autoware 是2015年发布的世界上第一款开源的自动驾驶框架，如今主要分为两大版本：基于ROS 1的AutoWare.ai 和基于 ROS2 的AutoWare.auto
  - AutoWare属于顶层的应用层，其底层操作系统为Linux（Ubuntu)，中间件为ROS，其次是上层的Autoware定位感知、规划、控制等功能模块

<div align=center><img src=./fig/AutoWare_System.png width=600></div>

### 1.2 环境配置介绍
**方案1: 简洁源码安装：基于 Ubuntu18.04+ROS Melodic**
  - 1. 进入ROS工作空间（可以新建一个单独为autoware使用）
  - 2. `git clone https://gitee.com/ren_sixu/autoware.test.git` 并进入autoware.test文件夹
  - 3. `colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release`
  - 4. 上述编译过程会提示缺少某些package，缺什么装什么，然后重新编译

**需要安装的包：**
```bash
colcon
nmea-navsat-driver
libpugixml-dev
libgeographic-dev
jsk-rviz-plugins
automotive-navigation-msgs
automotive-platform-msgs
velodyne-pointcloud
grid-map-cv
grid-map-msgs
grid-map-ros
qpoases-vendor
```
**忽略暂时无法通过的包**
  - colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release --packages-ignore lanelet2_python
  
**单独编译某个包**  
特别是当仅修改了某个包时，此时仅需要单独编译该包即可：
  - colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release --packages-select autoware_quickstart_examples


**方案2:常规安装**
  - 参考 https://gitee.com/ren_sixu/autoware.test 下的Readme.md


### 1.3 文件代码结构
1. 首先编译后会看到四个文件夹：
  - `src`: 是原来就有的，存储核心的代码文件
  - `log`: 编译后出现：存储编译过程中输出信息，后续Debug的输出信息都在这里
  - `build`：编译后出现：编译过程中的中间文件
  - `install`: 编译后出现：源码编译后生成的可执行文件和配置文件，实际部署时不会公布src内的源码，只需要移植install即可

2. 接下来重点分析src：
```bash
src
├── autoware # 核心代码：由各种ros package组成，其文件结构和常规ros项目类似
│   ├── common # 较为通用的功能
│   ├── core_perception # 感知模块：里面的每个文件夹都是一个package
│   ├── core_planning # 规控模块
│   ├── documentation # 文档（包括快速入门例程）
│   ├── messages # 消息数据结构的定义接口
│   ├── simulation # 仿真相关
│   ├── utilities # 常用的工具
│   └── visualization # 可视化相关
├── car_demo # 车辆仿真相关
│   ├── build_demo.bash
│   ├── car_demo
│   ├── Dockerfile
│   ├── prius_description
│   ├── prius_msgs
│   ├── README.md
│   └── run_demo.bash
├── citysim # 驾驶场景仿真相关
│   ├── cmake
│   ├── CMakeLists.txt
│   ├── media
│   ├── models
│   ├── plugins
│   ├── README.md
│   └── worlds
├── drivers # 实车测试相关
│   ├── awf_drivers
│   └── ds4
└── vendor # 实车测试相关
    ├── lanelet2
    └── mrt_cmake_modules
```

3. 继续深入分析每个功能包，以`core_perception/gnss_localizer`包为例：
```bash
## 典型的ROS功能包构成
├── CHANGELOG.rst
├── CMakeLists.txt # 编译文件
├── interface.yaml
├── launch # 启动文件
│   ├── fix2tfpose.launch
│   └── nmea2tfpose.launch
├── nodes # 节点代码文件
│   ├── fix2tfpose
│   │   └── fix2tfpose.cpp
│   └── nmea2tfpose
│       ├── nmea2tfpose_core.cpp
│       ├── nmea2tfpose_core.h
│       └── nmea2tfpose_node.cpp
├── package.xml # 包信息，主要是包的的依赖信息
└── test # 单元测试
    ├── nmea_test.cpp
    └── nmea_test.test
```
注意：
  - CMakeLists中包括 install命令，会先编译可执行文件，再把可执行文件放至install文件夹里面。因此修改launch文件后需要重新编译，因为如果使用colcon运行时调用的是install里面的编译好的可执行文件，因此直接改动无法起效果，每改动一次都要重新编译一次。


### 1.4 demo的配置与运行
熟悉了代码结构，接下来就可以实际运行一些代码，来实际体验一些功能，以一些简单的例子进行快速入门，了解整个项目的运行机制。可以通过运行`autoware_quickstart_examples`，逐个启动各launch文件，观察输出是否符合预期，通过在rviz中check某些topic查看各模块所起到的功能效果，对整个系统功能有一个大致的了解。

**demo 运行前的准备工作**  
  1. 首先需要下载官方数据集`sample_mariyama_150324.bag`，主要提供环境的点云数据和gps数据，用来模拟真实场景的输入，放入任意能找到的位置即可，通常可以和最顶层`src`并列
  2. 然后下载相关配置文件，主要包括`calibration, map, path, tf`等文件夹，放入`~/.autoware/data`文件夹下

**模块运行**  
```bash
# source 工作空间，使环境变量生效：echo $ROS_PACKAGE_PATH
cd xx/autoware.test
source install/step.bash # 注意每打开一个终端都要source一下

# 启动地图
roslaunch autoware_quickstart_examples my_map.launch
# 启动定位
roslaunch autoware_quickstart_examples my_localization.launch
# 启动rviz：可以看到加载出了高精地图点云地图
rviz -d xx/rosbag_demo/default.rviz
# 数据回放
rosbag play data/sample_moriyama_150324.bag

# 感知
roslaunch autoware_quickstart_examples my_detection.launch

# 任务规划：部分路段在.autoware/data/path文件中存了路标点 (200s之后)
roslaunch autoware_quickstart_examples my_mission_planning.launch
# 运动规划
roslaunch autoware_quickstart_examples my_motion_planning.launch

#
```

**现象分析**
  1. 建图和定位模块的主要研究内容就是研究坐标系之间的变换关系，主要有三种坐标系，世界坐标系 -> 地图坐标系 -> 车身坐标系，将世界坐标系和地图坐标系进行匹配主要是为了在地图中使用gps信号，因为gps是基于世界坐标系的。一般为了方便可以直接将二者进行重合。
     - 坐标系之间的配置在`.autoware/data/tf/tf.launch`文件中
     - 定位一般指的是找到base_link在map坐标系下的位置
     - 数据一发布，车辆立马找到了自己在地图中的位置 
  2. 感知模块的例子中只是展示了基于点云数据进行数据聚类的例子
  3. 任务规划模块启动后出现了很多全局路径点，是提前在data/path下面存好的，用来完成一些固定路线的寻迹
  4. 局部规划模块启动后多了 `local waypoints`用来对车辆的行进的局部路径进行规划，和`detection range`用来设置局部路径的安全区域，还出现了车轮行进的曲率；
     - 注意，行进中出现的人行道信息，红绿灯信息，stop line等都不是感知模块检测到的，而是高精地图中存储的语义信息

**注意：**
  - 上述是采用命令行的方式进行启动，也可以参考`documentation/autoware_quickstart_examples`下`README.md`中介绍的使用`roslaunch runtime_manager runtime_manager.launch`启动可视化UI的方式进行操作。


### 1.5 demo代码阅读
刚开始可以先从launch文件看起，看一下每个大模块启动时都调用了哪些模块，对各模块的功能和依赖关系有更明确的理解。至此就可以完成模块级别的功能了解。

1. `my_map.launch`的主要功能是读入构成高精地图的几种核心元素，其数据来源主要是`.autoware/data/`文件夹下的数据：
    - 通过`rosparam`读入`.yaml`配置文件，主要是baselink和velodyne之间的位姿变换关系
    - 使用`include`包含另一个`tf.launch`文件，载入word_to_map, map_to_mobilty之间的位姿变换关系
    - 使用`node`启动`map_file`包中的`points_map_load`载入pcd点云地图数据
    - 使用`node`启动`map_file`包中的`vector_map_load`载入csv存储的地图元素数据，包括车道线、人行道、停止线等信息

2. `my_localization.launch`分别启动几个launch文件实现车辆定位
    - 使用`setup.launch`完成对激光雷达与车辆相对位姿参数的载入
    - 使用`vehicle_model.launch`完成对车辆模型的载入
    - 使用`nmea2tfpose.launch` 完成对gps信号到tfpose的转换
    - 使用`ndt_matching`完成基于激光雷达的定位

3. `my_detection.launch`比较简单，启动了一个标定信息的发布节点，一个点云到图像的转换节点，一个基于雷达的欧式聚类节点

4. `my_mission_planning.launch`通过载入预定义waypoints的方式实现任务规划
   - 首先启动`vev_pose_connect.launch`实现 vel_pose_mux？？
   - 然后通过rostopic节点，向`/config/waypoint_replanner`话题发布了`autoware_config_msgs/ConfigWaypointReplanner`格式的消息，感觉是生成detection area
   - 接着使用`waypoint_loader.launch`导入waypoint定义文件
   - 最后启动一系列的`lane_planner`节点实现lane rule, lane stop, lane select

5. `my_motion_planning.launch`通过对waypoint纯跟踪的方式实现对车辆的局部路径规划和控制
   - 主要包括`pure_pursuit.launch`节点
   - 和一些vehicle_set、astar_avoid、velocity_set、twist_filter节点等
 
当然也可以利用一些rqt_graph等可视化和rosnode rostopic rosmsg等命令行工具，了解各个包之间、节点、话题之间的关系和功能定义。