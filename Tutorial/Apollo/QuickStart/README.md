<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-19 20:43:31
 * @LastEditTime: 2022-01-11 11:14:55
-->
- [2. 快速入门](#2-快速入门)
  - [2.1 Dreamview](#21-dreamview)
  - [2.2 CyberRT](#22-cyberrt)
  - [2.3 Perception_Vision](#23-perception_vision)
  - [2.4 Perception_Lidar](#24-perception_lidar)
  - [2.5 Perception_Fusion](#25-perception_fusion)
  - [2.6 Localization](#26-localization)
  - [2.7 Planning](#27-planning)
  - [2.8 Prediction](#28-prediction)
  - [2.9 Control](#29-control)

# 2. 快速入门

## 2.1 [Dreamview](./Dreamview/README.md)
Dreamview是一个web应用程序，提供如下功能：
  - 可视化显示当前自动驾驶车辆模块的输出信息，如：规划路径、车辆定位、车架信息等
  - 为使用者提供人机交互接口以监测车辆硬件状态，并可以对模块进行开关操作，如启动自动驾驶车辆
  - 提供调试工具，如：PnC监视器可以高效的跟踪模块输出的问题

不过，Dreamview的大部分功能，主要是为了在实际上车调试中使用的，我们在快速入门阶段，仅使用用Dreamview的可视化功能将Record数据包的数据可视化。

## 2.2 [CyberRT](./CyberRT/README.md)
Apollo Cyber RT 是一个开源高性能的运行时框架，专为自动驾驶场景而设计。针对自动驾驶的高并发、低延迟、高吞吐量进行了大幅优化。主要具有如下优势：
  - 能够加速开发：包括具有数据融合功能且定义明确的任务接口，一系列开发工具以及大量的传感器驱动程序
  - 能够简化部署：具有高效自适应的消息通信机制，具有资源意识的可配置用户级调度程序，可移植且依赖更少
  - 能够为自动驾驶赋能：为自动驾驶搭建了专门的模块

## 2.3 [Perception_Vision](./Perception_Vision/README.md)
本小节主要介绍Apollo视觉感知模块，主要包含Apollo视觉感知模块的整体结构以及各个模块的主要组成部分，最终对视觉感知模块的输入输出有一个比较清晰的认识。

## 2.4 [Perception_Lidar](./Perception_Lidar/README.md)
本小节主要介绍Apollo激光雷达感知模块的流程及算法，对算法的基本原理以及该模块的处理流程、输入输出有一个大致的了解。

## 2.5 [Perception_Fusion](./Perception_Fusion/README.md)
本章节主要介绍Apollo感知融合模块的基本原理、输入输出以及channel信息

## 2.6 [Localization](./Localization/README.md)
本小节主要介绍Apollo的定位模块以及Apollo (Multi-sensor Fusion)的原理

## 2.7 [Planning](./Planning/README.md)
规划是自动驾驶中重要的模块。规划模块基于预测模块输入的障碍物信息、地图定位信息、路径导航信息对车辆的未来的运动轨迹进行规划，保证自动驾驶车辆高效、安全、舒适的行至目标位置。

本小节主要介绍规划模块的基本原理以及输入输出，帮助开发者快速了解规划模块的运作机制，方便开发者开展后续的模块开发任务

## 2.8 [Prediction](./Prediction/README.md)
本小节为开发者介绍 Apollo 预测模块的基本知识，包括预测模块在自动驾驶系统中的主要作用，预测模块的基本组成以及预测模块的输入输出。

## 2.9 [Control](./Control/README.md)
本小节为开发者介绍 Apollo 控制模块的基本知识、Apollo 控制能力、控制模块的组成及其输入输出。