<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-20 22:22:39
 * @LastEditTime: 2022-04-21 22:24:08
-->

## 2. SLAM 实践
<div align=center><img src=./fig/problem_formulation.png width=500></div>

### 2.1 定位的基本概念
在ROS的Navigation功能包集中，其定位模块使用的是AMCL(Adaptive Monte Carlo Localization)方法。定位的主要任务就是基于环境地图，通过一系列(时序)传感器的实时测量值，获取机器人的位姿估计。本质上也可以看做将采集到的数据，在数据库中进行匹配的过程。 

### 2.2 常见的SLAM建图技术
**SLAM算法分类**  
  - 传统激光：Gmapping, HectorSLAM
  - 视觉：OrbSLAM, DSO
  - 视觉架构下的激光建图: Cartographer
  - 拓扑与语义地图

<div align=center><img src=./fig/slam_tf.png width=500></div>


### 2.3 算法实践
```bash
## 功能包安装
# gmapping
sudo apt-get install ros-indigo-gmapping
# hectorSLAM
sudo apt-get install ros-indigo-hector-slam
# cartographer
sudo apt-get install ros-kinetic-cartographer*
```

可以参考这个例子[turtlebot3建图导航](https://blog.csdn.net/weixin_51331359/article/details/121598373)进行一些建图实践操作。