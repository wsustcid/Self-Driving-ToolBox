<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-11-19 20:43:31
 * @LastEditTime: 2022-01-06 16:24:05
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

## 2.5 [Perception_Fusion](./Perception_Fusion/README.md)

## 2.6 [Localization](./Localization/README.md)

## 2.7 [Planning](./Planning/README.md)

## 2.8 [Prediction](./Prediction/README.md)

## 2.9 [Control](./Control/README.md)