<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 16:17:04
 * @LastEditTime: 2022-01-11 11:27:04
-->
- [2.8 Apollo预测模块](#28-apollo预测模块)
  - [2.8.1 预测模块的原理](#281-预测模块的原理)
  - [2.8.2 预测模块仿真实践](#282-预测模块仿真实践)

## 2.8 Apollo预测模块
预测模块通过障碍物的历史状态信息，来预测障碍物的未来轨迹。感知模块作为预测模块的上游，提供障碍物的位置、朝向、速度、加速度等信息，预测模块根据这些信息，给出障碍物未来的预测轨迹，供下游规划模块进行自车轨迹的规划。

### 2.8.1 预测模块的原理
预测模块主要有四个子模块组成，分别是：信息容器（container）、场景选择（scenario）、评估器（evaluator）和预测器（predictor）。
  - 信息容器：储存上游信息，为之后的轨迹预测提供输入，当期储存的主要有：感知信息、定位信息以及自车轨迹规划信息。
  - 场景选择：预测模块针对不同的场景采用不同的预测方法（如巡航、路口等场景），便于后续扩展，提高算法的泛化能力。
  - 评估器：评估器基于障碍物的状态信息，结合预测模型，给出障碍物预测轨迹的概率或短预测时域的轨迹信息。
  - 预测器：预测器直接或结合评估器的结果给出障碍物的完整预测时域的预测轨迹。

<div align=center><img src=./fig/planning.png width=500></div>

**预测模块的输入输出**  
<div align=center><img src=./fig/planning_in_out.png width=500></div>

<div align=center><img src=./fig/planning_infoflow.png width=500></div>

### 2.8.2 预测模块仿真实践
```bash
# 进入 docker 环境并启动Dreamview
./scripts/bootstrap.sh
# 在Dreamview的右上角的 --vehicle--选择对应的车型（教程使用mkz_example）, --map--选择对应的地图（教程使用sunnyvale loop）。

# 在Dreamview上打开prediction按钮
```

当使用Apollo时遇到预测模块的问题需要调试代码时，可以基于本地环境进行初步验证，通常的做法是本地播放record，屏蔽record中原有的预测消息，观察调试后带来的效果，具体的步骤如下：

```bash
cyber_recorder play -f docs/demo_guide/demo_3.5.record -k /apollo/prediction
```

打开prediction按钮，观察可视化结果：图中主车为图像中间的蓝色车辆，主车左侧的绿色几何体为障碍物，障碍物中绿色圆点连接而成的曲线即障碍物的预测轨迹，调试时可根据预测轨迹的形态，定位预测模块问题；如果默认视角看不清可视化结果，可以在Layer Menu中切换视角至near，方便近距离观察

<div align=center><img src=./fig/planning_demo.png width=500></div>