<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 16:17:04
 * @LastEditTime: 2022-01-11 11:13:58
-->
- [2.7 Apollo规划模块](#27-apollo规划模块)
  - [2.7.1 规划模块原理](#271-规划模块原理)
  - [2.7.2 规划模块仿真实践](#272-规划模块仿真实践)

## 2.7 Apollo规划模块
Apollo 规划模块的主要作用是结合障碍物、地图定位以及导航信息为自动驾驶车辆规划一条运动轨迹，这条轨迹由若干轨迹点组成，每个轨迹点均包含了位置坐标、速度、加速度、加加速度、相对时间等信息，这些信息为自动驾驶车辆的运动提供依据，参照规划的轨迹，自动驾驶车辆可以高效、安全、舒适的驶向目的地。

### 2.7.1 规划模块原理
Apollo 规划模块功能的实现是基于场景（scenario-based）实现的，针对不同的场景，规划模块通过一系列独立的 任务（task） 组合来完成轨迹的规划。开发者可以根据自己的使用需求，调整 `apollo/modules/planning/conf/scenario/` 下的配置文件，调配任务组合实现自己的规划要求。

<div align=center><img src=./fig/architecture-planning.png width=500></div>

Apollo 规划架构示意图如上，其中部分重要模块如下：
  - 状态机（Apollo FSM（Finite State Machine））：一个有限状态机，结合导航、环境等信息确定自动驾驶车辆的驾驶场景
  - 规划分发器（Planning Dispatcher）：根据状态机与车辆相关信息，调用合适当前场景的规划器
  - 规划器（Planner）：结合上游模块信息，通过一系列的任务组合，完成自动驾驶车辆的轨迹规划
  - 决策器 & 优化器（Deciders & Optimizers）：一组实现决策和优化任务的 task 集合。优化器用于优化车辆的轨迹和速度。决策器则基于规则，确定自动驾驶车辆何时换车道、何时停车、何时蠕行（慢速行进）或蠕行何时完成等驾驶行为。

**规划模块的输入输出**  
<div align=center><img src=./fig/plan_in.png width=300></div>
<div align=center><img src=./fig/plan_out.png width=300></div>


### 2.7.2 规划模块仿真实践
```bash
# 进入 docker 环境并启动Dreamview
./apollo.sh
./scripts/bootstrap.sh
#在浏览器输入网址，打开Dreamview: http://localhost:8888/

# 在Dreamview的右上角的 --vehicle--选择对应的车型（教程使用mkz_example）, 
# --map--选择对应的地图（教程使用sunnyvale loop）。
# 车辆选择后，程序会把会把calibration/data目录下对应的车型参数和传感器内外参文件拷贝到作用目录下。
```

**在Dreamview上本地调试规划模块**  
当使用Apollo时遇到规划模块的问题需要调试代码时，可以基于本地环境进行初步验证，通常的做法是本地播放record，屏蔽record中原有的规划消息，观察调试后带来的效果，具体的步骤如下：

播放数据包（docs/demo_guide/demo_3.5.record为record路径，通过-k /apollo/planning屏蔽原有的planning消息）：
```bash
cyber_recorder play -f docs/demo_guide/demo_3.5.record -k /apollo/planning
```

打开planning按钮，观察可视化结果：
  - 图中主车为图像中间的蓝色车辆，主车左侧的绿色几何体为障碍物，穿过主车的浅蓝色曲线即自动驾驶车辆的规划轨迹，可以观察轨迹的状态定性的分析规划问题；
  - 如果默认视角看不清可视化结果，可以在Layer Menu中切换视角至near，方便近距离观察
 
进一步精细化分析规划问题，可以打开PNC monitor，界面右侧会显示路径规划和速度规划的相关定量图线，供开发者做进行的分析和问题定位
<div align=center><img src=./fig/plan_demo.png width=500></div>

