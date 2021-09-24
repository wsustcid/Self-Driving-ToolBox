- [自动驾驶汽车运动规划](#自动驾驶汽车运动规划)
  - [0. 课程介绍](#0-课程介绍)
  - [1. 规划问题](#1-规划问题)
  - [2. 规划建图](#2-规划建图)
  - [3. 驾驶环境中的任务规划](#3-驾驶环境中的任务规划)
  - [4. Dynamic Object Interactions](#4-dynamic-object-interactions)
  - [5. Principles of Behaviour Planning](#5-principles-of-behaviour-planning)
  - [6. Reactive Planning in Static Environments](#6-reactive-planning-in-static-environments)
  - [7. Putting it all together - Smooth Local Planning](#7-putting-it-all-together---smooth-local-planning)
  - [8. 阅读材料](#8-阅读材料)


# 自动驾驶汽车运动规划
<div align=center><img src=./assets/cover.png width=700></div>

自动驾驶是一个还在不断发展的领域，因此不仅需要学习无人驾驶相关的知识，机器人学、人工智能等领域的知识也需要持续跟进，只有这样才能保持自己的技术先进性。

## 0. 课程介绍
本课程主要包含以下几个方面的内容：
  - 规划复杂路网下的行车路线
  - 定义车辆在复杂交通场景下（如交叉路口、停车场、并线等）的高层级车辆行为及其状态转移
  - 设计一种轨迹规划方法
  - 计算车辆与静态障碍或匀速运动目标的碰撞时间
  - 在静态障碍场景下规划满足运动学约束的行车轨迹
  - 实现满足速度约束、曲率约束和动态障碍约束的速度规划
  - 规划车辆行为和执行运动指令使车辆能够安全的在真实世界中导航
  - 在Carla仿真器中测试自动驾驶算法并增加调试经验

运动规划问题是指通过对车辆的路径和速度进行规划使之能够从A点安全的到达B点：
  - 运动规划要求对周围环境中的车辆、行人以及其他障碍物都有很好的感知
  - 考虑到问题的复杂性，解决运动规划问题的常用做法是将其分解成几个小的子问题

在本课程中，我们将整个运动规划任务分层构建成三个阶段的任务：
  - 地图层级导航：与我们常见的在线导航软件所完成的路线规划任务类似
  - 行为规划：确保我们驾驶行为遵守道路的交通规则
  - 局部路径规划：确保最终规划出的路径是平滑的且能够避开所有障碍。


## 1. [规划问题](./Planning%20Problem/README.md)
本章节主要对自动驾驶运动规划问题的定义和基本概念进行了介绍：
  - 首先对自动驾驶运动规划问题中的三个核心概念进行了介绍:任务、场景以及行为。
  - 由于运动规划问题的核心还是解优化问题，因此，接下来分别对自动驾驶汽车运动规划过程中面临的约束条件和优化目标方程进行了初步的介绍。
  - 最后，对整个运动规划问题进行了明确的分层级划分：任务规划、行为预测、局部规划。分别对其问题的定义和现有方法进行了初步介绍。

## 2. [规划建图](./Mapping%20for%20Planning/README.md)

## 3. 驾驶环境中的任务规划

## 4. Dynamic Object Interactions

## 5. Principles of Behaviour Planning

## 6. Reactive Planning in Static Environments


## 7. Putting it all together - Smooth Local Planning


## 8. 阅读材料
  - S. M. LaValle. Planning Algorithms. Cambridge University Press, Cambridge, U.K., 2006. Available at http://planning.cs.uiuc.edu/.
  - S. Thrun, W. Burgard, and D. Fox, Probabilistic robotics. Cambridge, MA: MIT Press, 2010.
  - N. J. Nilsson, “Artificial intelligence: A modern approach,” Artificial Intelligence, vol. 82, no. 1-2, pp. 369–380, 1996. 
