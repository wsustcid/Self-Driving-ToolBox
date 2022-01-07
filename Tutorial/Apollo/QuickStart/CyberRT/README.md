<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 11:10:49
 * @LastEditTime: 2022-01-06 16:14:05
-->
- [2.2 CyberRT](#22-cyberrt)
  - [2.2.1 常用术语](#221-常用术语)
  - [2.2.2 使用CyberRecorder播放数据包](#222-使用cyberrecorder播放数据包)
  - [2.2.3 使用CyberMonitor查看Channel数据](#223-使用cybermonitor查看channel数据)
  - [2.2.4 使用CyberVisualizer查看原始感知数据](#224-使用cybervisualizer查看原始感知数据)

## 2.2 CyberRT
### 2.2.1 常用术语
**Component**   
在自动驾驶中，模块（如感知、定位、控制系统等）在Cyber RT 下以 Component的形式存在。  
  - 不同的Component之间通过Channel进行通信。
  - Component的概念不仅解耦了模块，还为将模块拆分为多个子模块提供了灵活性。

**Channel**  
Channel用于管理Cyber RT中的数据通信。用户可以发布/订阅同一个Channel，实现P2P通信。

**Task**  
Task是Cyber RT中异步计算任务的抽象描述。

**Node**  
Node是Cyber RT的基本组成部分，每个模块都包含一个Node并通过 __Node__ ? 进行通信。
  - 通过在节点中定义Reader/Writer 或 Service/Client，模块可以具有不同类型的通信形式

**Reader/Writer**  
Reader/Writer主要在Node内创建，作为Cyber RT中的主要消息传输接口。

**Service/Client**  
除 Reader/Writer 外，Cyber RT还提供了用于模块通信的Service/Client模式，它支持节点的双向通信，即当服务发出请求时，客户端节点将收到响应。

**Paremeter**  
参数服务在Cyber RT中提供了全局参数访问接口。它是基于Service/Client模式构建的。

**服务发现**  
作为一个去中心化的框架，Cyber RT没有用于服务注册的主/中心节点。所有节点都被平等对待，可以通过“服务发现”找到其他服务节点。
  - 使用 UDP 用来服务发现

**CRoutine**  
参考协程(Coroutine)的概念，Cyber RT实现了Coroutine来优化线程和系统资源分配。

**Scheduler**  
为了更好的支持自动驾驶场景，Cyber RT提供了多种资源调度算法供开发者选择。

**Message**  
Message是Cyber RT中用于模块之间数据传输的数据单元

**Dag文件**  
Dag文件是模块拓扑关系的配置文件。可以在Dag文件中定义使用的Component和上游/下游通道

**Launch文件**  
Launch文件提供了一种启动模块的简单方法。通过在Launch文件中定义一个或多个dag文件，可以同时启动多个模块。

**Record文件**  
Record文件用于记录从Cyber RT中的Channel发送/接受的消息。回放Record文件可以帮助重现Cyber RT之前的操作行为。

### 2.2.2 使用CyberRecorder播放数据包
cyber_recorder 是 Apollo Cyber RT 提供的播放工具，可以用来播放 record 文件。Record 是 Apollo 记录数据的一种数据格式。以 .record 为后缀的文件就是我们说的 record 数据包。

接下来我们以传感器原始数据包 demo_sensor_data.tar.xz 为例介绍如何使用 cyber_recorder 播放数据包，后续我们仍然会基于此数据包学习cyber_monitor 以及 cyber_visualizer 的使用，因此，我们首先需要进入 Apollo docker 环境，将数据包下载至特定位置并解压，以便后续使用
```bash
# 进入docker
cd apollo_edu && ./apollo.sh
# 下载并解压数据包
mkdir record
wget https://apollo-system.cdn.bcebos.com/dataset/6.0_edu/demo_sensor_data.tar.xz
tar -xvf demo_sensor_data.tar.xz
```

注意，不管是cyber_recorder，还是cyber_monitor 以及 cyber_visualizer，都需要运行在Apollo docker环境内，且依赖于cyber RT的软件库，因此使用前我们需要配置cyber RT工具的运行环境（个人感觉类似于 source 下ROS的工作空间，官方文档中提示在个人终端环境下source,但并没有此文件夹，只有apollo docker 容器内有，但实测不source也可以）
```bash
source /apollo/cyber/setup.bash
```

接下来就可以运行cyber_recorder来播放录制的数据包
```bash
cyber_recoder play -f record/sensor_rbg.record --loop
```

### 2.2.3 使用CyberMonitor查看Channel数据
在上一节正在播放数据包的基础上，我们新打开一个终端，重新进入Apollo docker 容器，就可以启动cyber_monitor来查看chanel信息：
  - cyber_monitor 启动之后，会在终端中显示一个交互界面，cyber_monitor 自动从拓扑中收集所有 channel 信息并分两列显示：分别为 Channels（channel 名称）和 FrameRatio（数据频率）
  - channel 信息默认显示为红色，当有数据流经 channel 时，对应的行就会显示成绿色

```bash
. apollo_edu/apollo.sh
cyber_monitor
cyber_monitor -h # 获取帮助信息
cyber_monitor -c ChannelName # 仅监测一个指定的channel信息
```

其他常用命令
```python
ESC | q key ---- 退出
Backspace ---- 后退
h | H ---- 显示帮助页
PageDown | Ctrl+d ---- 上一页
PageUp | Ctrl+u ---- 下一页
Up, down or w, s keys ---- 上下移动当前的高亮行
Right arrow or d key ---- 进入高亮行, 显示高亮行数据的详细信息
Left arrow or a key ---- 从当前界面返回上一层界面
Enter key ---- 与 d 键相同
f | F ---- 显示数据帧频率
t | T ---- 显示 channel 消息类型
Space ---- 关闭|开启 channel (仅在 channel 有数据到达时有效；channel 关闭后会变成黄色)
i | I ---- 显示 channel 的 Reader 和 Writer 信息
b | B ---- 显示 channel 消息内容
n | N ---- 显示消息中 RepeatedField 的下一条数据
m | M ---- 显示消息中 RepeatedField 的上一条数据
```

### 2.2.4 使用CyberVisualizer查看原始感知数据
继续利用2.2.2节正在播放的数据包，重新打开一个终端，在 Apollo Docker 环境中执行如下命令运行 cyber_visualizer
```bash
cyber_visualizer
```

  - 播放数据包后，cyber_visualizer 会收到所有活动 channel 的信息（来自回放数据）并显示出来。当有数据流经 channel 时，在 ChannelNames 下会显示 channel 列表。您可以查看点云和相机数据
  - 单击工具栏中的选项，您可以开启参考网格、显示点云、添加图像或同时显示多个相机数据的功能。如果启用了 显示网格 选项，则可以双击 ChannelName 下方的 Grid 列表中的 Color 项来设置网格的颜色。默认颜色为灰色
  - 您还可以编辑 CellCount 的值来调整网格中的单元格数量。对于点云或图像，可以通过 ChannelName 和 Action 选项选择源 channel 来播放或停止来自相应 channel 的数据。
  - 要在 3D 点云场景中调整虚拟摄像机，可以在点云显示部分右键单击，将弹出一个对话框
  - 将鼠标放在摄像机 channel 的图像上，可以双击左键在左侧菜单栏突出显示对应的channel。右击图像，可以弹出删除摄像机通道的菜单。
  - 播放和暂停：单击 Play 时，将显示所有频道。当单击 Stop 时，所有 channel 信息将停止显示。