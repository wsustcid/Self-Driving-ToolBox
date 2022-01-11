<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 16:17:04
 * @LastEditTime: 2022-01-11 11:38:50
-->
- [2.9 Apollo 控制模块](#29-apollo-控制模块)
  - [2.9.1 Apollo 控制模块原理](#291-apollo-控制模块原理)
  - [2.9.2 基于Dreamland调试控制能力实践](#292-基于dreamland调试控制能力实践)


## 2.9 Apollo 控制模块
控制模块是整个自动驾驶软件系统中的执行环节，控制模块的目标是基于规划模块输出的目标轨迹和定位模块输出的车辆状态生成方向盘、油门、刹车控制命令，并通过 canbus 模块给车辆底层执行器。简单而言，就是告诉车辆该打多大方向盘、多大的油门开度、多大的刹车制动力。

### 2.9.1 Apollo 控制模块原理
控制模块由两个子模块组成：横向控制模块和纵向控制模块。

**横向控制模块**  
横向控制根据规划模块的轨迹生成方向盘指令。
  - 方向盘闭环：通过上游规划模块输出的目标方向盘角度和下游 canbus 模块返回的实际方向盘角度做差，作为控制器的方向盘闭环输出。
  - 方向盘开环：通过上游规划模块输出的目标道路曲率经过转换，输出控制器方向盘开环输出。
  - 车辆：是控制器的控制对象，通过方向盘开环、方向盘闭环生成的方向盘角度打方向盘。

<div align=center><img src=./fig/control_h width=500></div>

**纵向控制模块**  
纵向模块根据规划模块的轨迹生成油门、刹车指令。
  - 位置闭环：通过规划模块的目标车辆位置和定位模块给出的实际车辆位置做差，经过纵向位置控制器生成对应的速度偏差。
  - 速度闭环：结合位置闭环的结果，规划模块的目标速度以及 canbus 模块返回的实际车速，通过纵向速度控制器生成对应的加速度偏差。
  - 标定表：速度，加速度和油门、刹车对应关系表，通过输入速度、加速度可以查出对应的油门、刹车。

<div align=center><img src=./fig/control_v width=500></div>

**Apollo 控制模块输入输出**  
<div align=center><img src=./fig/control_module width=500></div>

<div align=center><img src=./fig/control_in_out width=500></div>

**参考文献**
  - "Vehicle dynamics and control." Rajamani, Rajesh. Springer Science & Business Media, 2011.
  - "Optimal Trajectory generation for dynamic street scenarios in a Frenet Frame", M. Werling et., ICRA2010


### 2.9.2 基于Dreamland调试控制能力实践
本小节为开发者介绍了基于DreamLand的Apollo控制能力实践，主要包含横、纵向控制器参数整定方法。能够帮助开发者学习如何使用dreamland并如何调试控制算法。

通过图片介绍如何使用dreamland进行任务的创建，并在任务的基础上调试控制算法。

**Dreamland任务创建**  
dreamland入口：[dreamland](https://studio.apollo.auto/login), 开发者需要登录以后，在仿真页面中申请仿真试用包，以启用仿真服务。

dreamland新建任务：
<div align=center><img src=./fig/dreamland_1 width=500></div>

新建任务后显示如下操作界面：
<div align=center><img src=./fig/dreamland_2 width=500></div>

根据需要选择相应的跑法、场景、代码库及分支、控制所需动力学模型。示例如下：
当前选择的是pnc跑法，选择直行场景、apollo代码库(当前是笔者自己的仓库，用户可以填选择自己的仓库)master分支、基于规则的动力学模型echo_lincoin：
<div align=center><img src=./fig/dreamland_3 width=500></div>

设置完成后点运行即可让百度云利用基于仿真场景，对开发者提供的 Git 分支的规划、控制等算法进行仿真测试。

仿真结束后，开发者可以在最终结果查看控制和规划算法在各个场景中的表现。

**基于Dreamland调试Apollo横向控制器**  
通过调节控制器参数可以达到用户想要的横向控制效果，横向控制器参数所在位置是/apollo/modules/control/conf/control_conf.pb.txt。 “所有”车辆的基础横向控制器调参步骤如下：

1. 将matrix_q 中所有元素设置为零；
2. 增加matrix_q中的第三个元素，它定义了航向误差加权，以最小化航向误差；
3. 增加matrix_q的第一个元素，它定义横向误差加权以最小化横向误差。
   
对于Lincoln MKZ，有四个元素是状态加权矩阵Q的对角线元素：
  - 横向位置偏差系数
  - 横向位置变化系数
  - 航向角偏差系数
  - 航向角变化系数

通过在横向控制器调参中列出的基本横向控制器调整步骤来调整系数，下面是一个例子：
```bash
lat_controller_conf {  
  matrix_q: 0.05  
  matrix_q: 0.0  
  matrix_q: 1.0  
  matrix_q: 0.0  
} 
```
对于其它车型，首先更新车辆相关的物理参数，如下所示：
```bash
lat_controller_conf {  
  cf: 155494.663  
  cr: 155494.663  
  wheelbase: 2.85  
  mass_fl: 520  
  mass_fr: 520  
  mass_rl: 520  
  mass_rr: 520  
  eps: 0.01  
  steer_transmission_ratio: 16  
  steer_single_direction_max_degree: 470  
}  
```

然后按照上面列出的基本横向控制器调整步骤进行参数调整。

**基于Dreamland调试Apollo纵向控制器**  
纵向控制器由级联的PID控制器组成，该控制器包括一个位置控制器和一个具有不同速度增益的高速/低速控制器。Apollo的纵向控制器调谐通过管理开环和闭环两种方式。
  - 开环：校准表生成，请参阅how_to_tune_control_parameters_cn.md的详细步骤;
  - 闭环：基于高速控制器->低速控制器->位置控制器的顺序。

通过调节控制器参数可以达到用户想要的纵向控制效果，纵向控制器参数所在位置是/apollo/modules/control/conf/control_conf.pb.txt。

高/低速控制器的参数整定

1. 将kp, ki, 和 kd 的值设为0
2. 开始增加kp的值，以减小阶跃响应对速度变化的上升时间
3. 增加ki以降低速度控制器稳态误差

高速控制器主要用于跟踪高于某一速度值的期望速度，参数整定示例如下：
```bash
high_speed_pid_conf {  
  integrator_enable: true  
  integrator_saturation_level: 0.3  
  kp: 1.0  
  ki: 0.3  
  kd: 0.0  
}
```

获得较高速度的相对准确的速度跟踪性能之后，就可以开始从起点开始调整低速PID控制器以获得一个舒适的加速率：

```bash
low_speed_pid_conf {  
  integrator_enable: true  
  integrator_saturation_level: 0.3  
  kp: 0.5  
  ki: 0.3  
  kd: 0.0  
}
```  

位置控制器参数整定

Apollo使用车辆的位置控制器来跟踪车辆轨迹基准与车辆位置之间的位置误差，一个位置控制器参数整定示例如下所示：

```bash
station_pid_conf {  
  integrator_enable: true  
  integrator_saturation_level: 0.3  
  kp: 0.3  
  ki: 0.0  
  kd: 0.0  
}
```