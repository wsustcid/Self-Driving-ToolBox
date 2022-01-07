<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 11:00:09
 * @LastEditTime: 2022-01-06 11:00:10
-->
- [2.1 Dreamview](#21-dreamview)
  - [2.1.1 界面布局及特性](#211-界面布局及特性)
  - [2.1.2 使用Dreamview查看数据包](#212-使用dreamview查看数据包)

## 2.1 Dreamview
### 2.1.1 界面布局及特性
该应用程序的界面分为多个区域：标题、侧边栏、主视图和工具视图。

**标题**  
标题包含 5 个下拉列表，可以进行如图所示的操作：
<div align=center><img src=./fig/标题栏.png width=600></div>

**侧边栏和工具视图**  
<div align=center><img src=./fig/侧边栏和工具视图.png width=600></div>
如图所示，左侧侧边栏控制着显示在下方工具视图中的模块：

Tasks选项，具体可以操作的 tasks 有：
  - Quick Start：当前选择的模式支持的指令：Setup：开启所有模块；Reset All：关闭所有模块；Start Auto：开始车辆的自动驾驶。在实车中，Start Auto 就是让车辆进入自动驾驶模式的按钮。
  - Others：工具经常使用的开关和按钮
  - Module Delay：从模块中输出的两次事件的时间延迟。
  - Console：从 Apollo 平台输出的监视器信息。

<div align=center><img src=./fig/tasks.png width=600></div>

Module Controller：监视硬件状态和对模块进行开关操作
  - 启动和停止这些模块功能，不仅可以用 Dreamview 上的这些可视化按钮启动，也可以通过命令行来启动。在后续的各个模块的实践中，您可以看到用命令行启动各个模块的说明。
  - 注意：在本文档中，只是播放数据包，所以这些模块的开与关都不影响车辆的运行。

<div align=center><img src=./fig/module_controller.png width=600></div>

Layer Menu:显式控制各个元素是否显示的开关
  - Layer Menu 中的功能，在本 Demo 演示中也是可以使用的
  - 您可以在主视图中展示多种从 Layer Menu 选择的视图模式，包括默认视图，近距离视图，俯瞰视图以及地图视图
  - 视图操作：放大/缩小：滚动鼠标滚轮或使用两根手指滑动; 移动：按下右键并拖拽或或使用三根手指滑动
  - 您可以通过在下面红框里的开关，开启和关闭对应的模块的可视化功能。

<div align=center><img src=./fig/layer_menu.png width=600></div>

Route Editing
  - 在向 Routing 模块发送寻路信息请求前，用于编辑路径信息的可视化工具。

主视图
  - 主视图在 web 页面中以动画的方式展示 3D 计算机图形

下表列举了主视图中涉及到的各个元素，部分元素没有出现在本 Demo 中，仅供开发者参考。

<div align=center><img src=./fig/主视图元素_1.png width=250><img src=./fig/主视图元素_2.png width=350></div>


障碍物信息

<div align=center><img src=./fig/障碍物信息_1.png width=195><img src=./fig/障碍物信息_2.png width=350></div>


Planning决策-决策栅栏区
  - 决策栅栏区显示了 Planning 模块对车辆障碍物做出的决策。每种类型的决策会表示为不同的颜色和图标，如下图所示：
  
<div align=center><img src=./fig/决策栅栏区_1.png width=285><img src=./fig/决策栅栏区_2.png width=350></div>


线路变更是一个特殊的决策，因此不显示决策栅栏区，而是将路线变更的图标显示在车辆上

<div align=center><img src=./fig/线路变更决策.png width=250></div>

在优先通行的规则下，当在交叉路口的停车标志处做出让行决策时，被让行的物体在头顶会显示让行图标

<div align=center><img src=./fig/让行物体.png width=100></div>

Planning决策-停止原因
  - 如果显示了停止决策栅栏区，则停止原因展示在停止图标的右侧。可能的停止原因和对应的图标为：

<div align=center><img src=./fig/决策原因_1.png width=250><img src=./fig/决策原因_2.png width=238></div>


### 2.1.2 使用Dreamview查看数据包
本小节通过Dreamview播放Apollo提供的record数据包，进一步观察、学习Apollo自动驾驶。注意在实践前需要确保按照【使用安装包安装Apollo】搭建好了Apollo的运行环境。
```bash
## 1. 进入Apollo Docker，启动容器
cd ~/apollo_edu
./apollo.sh
## 2. 启动Dreamview
bash scripts/bootstrap.sh
## 3. 下载Apollo数据包
wget https://apollo-system.cdn.bcebos.com/dataset/6.0_edu/demo_3.5.record
## 4. 播放数据包
cyber_recorder play -f demo_3.5.record --loop # 选项 --loop 用于设置循环回放模式
## 5. 使用 Dreamview 查看数据包：在浏览器中输入 http://localhost:8888，访问 Apollo Dreamview
```

注意，我们这里仅使用Dreamview将record数据包的数据可视化，但Dreamview 的大部分的功能，主要是为了在实际上车调试中使用的