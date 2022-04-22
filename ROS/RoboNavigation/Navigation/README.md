<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-04-20 22:22:31
 * @LastEditTime: 2022-04-22 15:01:22
-->

## 3. 自主导航实践

### 3.1 [ROS导航功能包集](http://wiki.ros.org/navigation/Tutorials)move_base
move_base 主要功能为基于已有地图实现移动机器人的自主导航，其模块组成如下：
<div align=center><img src=./fig/move_base_modular.png width=500></div>

输入包括：
  - 地图信息：map_server
  - 定位信息：pose：可以使用amcl，该模块一般需要 sensor 和 odom 作为输入；odom如果有机器人平台的话，一般通过/mobile_base发布，如果没有机器人，可以通过scan_matcher通过匹配（激光/视觉/IMU）对实现运动的估计
  - 目标位置：goal
  - tf变换

输出主要为：
  - 移动机器人控制信息：cmd_vel

算法流程：
  - 从map_server生成Global Costmap：基于全局代价地图，使用全局规划器利用A*等全局路径规划算法得到全局路径
  - 全局路径送给局部路径规划器，同时sensor获取的环境信息生成Local Costmap，通过局部路径规划生成cmd_vel，被mobile_base接收
  - 一般还需要一个 Recovery Behavior，机器人卡死时进行恢复。

### 3.2 利用Rviz进行导航状态观察
用好rviz工具，可视化调参后的状态变化。
```bash
roslaunch turtlebot_stage turtlebot_in_stage.launch
```

### 3.3 导航参数动态调整
用好rqt工具，里面包含了所有命令行的可视化操作，包括rossevice, rosparam等可以用于可视化调参
```bash
rqt # 
```

### 3.4 多传感器导航框架与参数文件设置
可以通过launch文件载入参数文件的方式进行参数设置，同时，要敢于善于调参，只要参数存在，就说明是可以调整的。


### 3.5 [actionlib](http://wiki.ros.org/actionlib)
ROS Topic 只管发，不管是否被订阅，ROS service 发完后要求有回应，但如果要求机器人移动到某个位置，如果用ros service，收到指令后没法立即回应，因为还没有移动到目标位置，此时需要action client发布命令，action server执行命令。client发布目标位置，server执行，并实时反馈执行结果，通过client还可以中途取消任务。

### 3.6 [smach](http://wiki.ros.org/smach)