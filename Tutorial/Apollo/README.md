<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-12 10:07:00
 * @LastEditTime: 2022-01-08 14:56:52
-->
- [Apollo 简明教程](#apollo-简明教程)
  - [1. 安装说明](#1-安装说明)
  - [2. 快速入门](#2-快速入门)
  - [3. 数据格式](#3-数据格式)
  - [4. 模块解析](#4-模块解析)
  - [5. 实车实践](#5-实车实践)
  - [参考资料](#参考资料)

# Apollo 简明教程
[Apollo](https://apollo.auto/) 是由百度公司开发的用于加速自动驾驶车辆的开发、测试、与部署的一个高性能且灵活的软件框架。

Apollo 自动驾驶开放平台为开发者提供了丰富的车辆、硬件选择，强大的环境感知、高精定位、路径规划、车辆控制等自动驾驶软件能力以及高精地图、仿真、数据流水线等自动驾驶云服务，帮助开发者从 0 到 1 快速搭建一套自动驾驶系统。

**发展历史**  
整个[ApolloAuto](https://github.com/ApolloAuto/apollo)项目自2017年4月开始，至今已经发布了十余个版本，各版本的详细架构图参见[这里](https://github.com/ApolloAuto/apollo/blob/r6.0.0/README.md)
<div align=center><img src=./Doc/apollo_history.png width=600 /></div>

**版本介绍**
  - Apollo 1.0 主要功能为跟踪给定的GPS Waypoint 实现封闭场地内按照规定路线行驶，主要用来确认各硬件模块可以正常工作。上层软件主要包括定位模块、控制模块和人机接口，中间层为一个实时的机器人操作系统，RTOS，底层硬件包括计算单元、GPS/IMU, HMI设备以及 Drive-by-wire Vehicle
  - Apollo 1.5 主要用于固定车道的巡航，通过加入激光雷达，让车辆具备了对周围环境的感知能力，能够更好的定位和规划路径，上层软件增加了地图引擎，感知、规划模块以及一个端到端模块
  - Apollo 2.0 支持车辆能够在简单的城区道路上自主行驶：主要包括自动巡航、避障、交通灯停车、变道等。上层软件更新了端到端系统，硬件部分添加了相机、Radar以及一个黑盒子
  - Apollo 2.5 增加了对高速公路场景的支持
  - Apollo 3.0 应该是从软硬件层面第一个功能完整的版本，主要测试场景为封闭场地内的低速场景
  - Apollo 3.5 对各软硬件部分都进行了全面的升级，能够实现复杂驾驶场景下的导航，比如住宅区与城市道路，目前车辆拥有了360度的感知能力，配合升级后的感知算法，能够处理城区道路的各种变化条件。比如基于场景的规划器能够处理多种复杂场景，包括无保护转向、住宅区域的狭窄街道、以及停车标志前停车等。软件层面将RTOS上层的 runtime framework更换为专门定制的Apollo Cyber RT Framework
  - Apollo 5.0 主要面向实现基于地理围栏的无人驾驶的量产方案，移除了端到端模块，并增加了更多的场景，比如靠边停车，穿过光秃秃的十字路口
  - Apollo 5.5 增强了复杂城区道路的驾驶能力，实现了 curb-to-curb driving，距离城市道路下全自动驾驶更近了一步，也解决了拥堵场景
  - Apollo 6.0 采用了新的深度学习模型，以增强某些阿波罗模块的能力。通过Apollo Data Pipeline，与新添加的数据管道服务无缝配合，以更好地服务于Apollo开发人员。并且，在硬件上加入了麦克风: 阿波罗6.0也是集成某些功能的第一个版本，作为对无人驾驶技术不断探索和实验的证明。

**软件架构**  
<div align=center><img src=./Doc/apollo_3_5_software_architecture.png width=400 /></div>


## 1. [安装说明](./Installation/README.md)
本章节首先介绍了为了运行Apollo所需要的基础开发环境，包括Ubuntu Linux 以及Docker等，然后提供了两种安装方式：通过安装包安装Apollo-EDU版本，以及通过源码编译的方式安装最新版本。前者适合在快速入门阶段使用，后者适合深入研究各模块最新细节时使用。

Apollo 开放平台为开发者提供了预先编译好的Apollo安装包，开发者在下载好安装包并安装好Apollo之后，可以通过两种方式在本地电脑上实践Apollo：
  - 基于Apollo可视化交互工具Dreamview做本地的仿真实践
  - 基于云端仿真平台Dreamland进行在线仿真实践

## 2. [快速入门](./QuickStart/README.md)
本章节首先对Dreamview进行了简要的介绍，然后通过使用Dreamview对录制好的数据进行回放，使大家对Apollo能够实现的功能有一个大致的印象。

然后对Apollo Cyber RT 的使用进行了简要的介绍。Apollo Cyber RT 是专为自动驾驶场景而设计的高性能运行实时框架，它提供了多种开发工具用于辅助开发，包括：
  - 用来播放数据包的命令行工具cyber_recorder
  - 用来在终端中实时显示channel信息列表的命令行工具cyber_monitor
  - 用来显示channel数据的可视化工具cyber_visualizer.

最后基于仿真环境Apollo核心的几大模块进行了具体实践。主要包括：视觉感知模块，激光雷达感知模块，感知融合模块，定位模块，规划模块，预测模块以及控制模块。

本章节的主要目的是把demo先跑起来，对整个项目框架和实现功能、各个子模块的功能和使用方法有一个大致的了解和熟悉，学会使用，明确输入输出。

## 3. 数据格式
对整个项目涉及的一些基础概念有初步的了解，否则后续全是新概念，也不容易看懂。

## 4. 模块解析
从自己最熟悉的小模块甚至小功能入手，尝试修改这个小功能，相当于扎开一个小洞口，以该点向外辐射和该点相关的功能，之后逐步扩展开来。

## 5. 实车实践
主要包括硬件和软件两个部分，硬件方面
  - 首先需要一台配置有线控功能的车辆，包括但不限于 brake-by-wire, steering-by-wire, throttle-by-wire and shift-by-wire (Lincoln MKZ)
  - 一台具有八核处理器以及16GB内存的工控机 （最低要求）
  - NVIDIA Turing GPU
注意：如果要在实际车辆上运行Apollo，推荐从1.0版本安装，方便确认各硬件模块都能够正常工作，然后再根据具体项目需求安装合适的版本。

硬件安装
- 详见 [Hardware installation guide](https://github.com/ApolloAuto/apollo/blob/master/docs/quickstart/apollo_3_5_hardware_system_installation_guide.md)

软件安装
[官方安装步骤](https://github.com/ApolloAuto/apollo/blob/master/docs/quickstart/apollo_software_installation_guide.md)

## 参考资料
  - [Apollo开放平台](https://apollo.auto/developer_cn.html)
  - [Apollo开放平台文档](https://apollo.auto/document_cn.html?target=/Apollo-Homepage-Document/Apollo_Doc_CN_6_0/)
  - [Apollo项目源码](https://github.com/ApolloAuto/apollo)
  - [Apollo开发者社区](https://apollo.auto/developer/index_cn.html#/)