<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 16:17:04
 * @LastEditTime: 2022-01-08 16:09:50
-->
- [2.4 Apollo激光雷达感知模块](#24-apollo激光雷达感知模块)
  - [2.4.1 激光雷达感知算法原理](#241-激光雷达感知算法原理)
  - [2.4.2 激光雷达感知模块的输入输出](#242-激光雷达感知模块的输入输出)
  - [2.4.3 激光雷达感知模块仿真实践](#243-激光雷达感知模块仿真实践)

## 2.4 Apollo激光雷达感知模块
在自动驾驶技术中，感知模块负责获取自动驾驶车辆周围环境信息，是自动驾驶车辆的“眼睛”，下游模块通过感知得到的环境信息来进行下一步决策。

<div align=center><img src=./fig/perception.png width=200/></div>

常用的感知传感器包括激光雷达、摄像头、毫米波雷达等，因为激光雷达传感器具备准确的障碍物定位能力等优点，Apollo 目前采取以其为主的自动驾驶感知方案。

激光雷达感知模块接受来自激光雷达驱动的点云信息，利用这些点云信息进行障碍物的检测以及跟踪，得到的结果会被输出到感知融合模块进行下一步处理。

<div align=center><img src=./fig/lidar_pipeline.png width=500/></div>
<div align=center><img src=./fig/lidar_in_out.png width=500/></div>

### 2.4.1 激光雷达感知算法原理
激光雷达感知模块接收到点云数据之后，通过高精度地图 ROI（The Region of Interest）过滤器过滤 ROI 之外的点云，去除背景对象，例如：路边建筑物、树木等，过滤后的点云数据通过障碍物检测深度学习模型进行 3D 障碍物的检测和分类，然后对得到的障碍物进行跟踪，最终得到障碍物的形状、位置、类别、速度等信息。

<div align=center><img src=./fig/detection_pipeline.png width=500/></div>

Apollo 使用深度卷积神经网络对障碍物进行精确检测和分割。Apollo CNN 分割检测算法包括以下四个部分：
  - 通道特征提取
  - 基于 CNN 的障碍物预测
  - 障碍物聚类
  - 后处理

**通道特征提取**  
给定点云数据帧，Apollo 构建其鸟瞰视图（即，投影到 XY 平面），它是局部坐标系中的 2D 网格。根据 x 和 y 坐标，可以将相对于原点（即，LiDAR 传感器）的预先定义范围内的每个点都量化到 2D 网格中的一个 cell。在量化之后，Apollo 为网格中每个 cell 中的点计算其 8 个统计值，这些需要计算的统计值如下所示：
  - cell 中点的最大高度; cell 中最高点的亮度
  - cell 中点的平均高度; cell 中点的平均亮度。
  - cell 中点的数量; 表示单元是空还是以被占据的二进制数值
  - 相对于原点，cell 中点的角度; cell 中点到原点的距离

**基于 CNN 的障碍物预测**  
基于上述通道特征，Apollo 使用一个全卷积神经网络（Convolutional Neural Network）来预测 cell 中障碍物的属性，包括
  - 相对于物体中心的偏移量-称为中心偏移
  - objectness（是否是目标的概率)
  - positiveness（有效目标概率）
  - 以及物体高度

如图所示，网络的输入是一个 W×H×C 通道的图形，这里：
  - W 表示网格的列数
  - H 表示网格的行数
  - C 表示特征通道的数量。

Apollo 使用的全卷积神经网络包括三个部分，分别为：
  - 特征编码器: 将通道特征图像作为输入，并连续地对其空间分辨率进行下采样以提高特征抽象程度
  - 特征解码器: 对编码的特征图像逐渐上采样，使其大小与到输入的 2D 网格的空间分辨率一致，这可以恢复特征图像的空间细节，以便于 cell 障碍物属性预测 (下采样和上采样是以带非线性激活层（例如，ReLu）的卷积/反卷积层堆栈实现的)
  - 障碍物属性预测器

<div align=center><img src=./fig/network.png width=500/></div>

**障碍物聚类**
在基于 CNN 的预测之后，Apollo 可获得每个 cell 的预测信息。Apollo 使用包含以下 5 个属性的 cell 目标属性图：
  - 中心偏移量
  - objectness（是否包含目标）
  - positiveness（有效目标概率）
  - 目标高度
  - 类别概率

为了生成障碍物，Apollo 基于 cell 的中心偏移预测结果构建有向图，并搜索连接的组件。
  - 如图 3 所示，每个 cell 由图中的一个节点表示，图的有向边则基于 cell 的预测中心偏移量构建，指向单元格对应的父节点。
  - 根据此有向图，Apollo 使用压缩 Union Find（并查集）算法来高效地查找连接的组件，每个组件都是候选障碍物目标簇。
  - Objectness 是描述一个 cell 是一个有效目标的概率。因此，Apollo 将 objectness 值小于 0.5 的 cell 定义为非目标 cell。因此，Apollo 为每个候选目标簇过滤掉空 cell 和非目标 cell。

<div align=center><img src=./fig/cell.png width=500/></div>

  - 红色箭头表示针对每个 cell 预测的目标中心偏移方向。
  - 使用蓝色覆盖的区域表示 objectness 概率不小于 0.5 的目标 cell。
  - 红色实线多边形内的 cell 组成一个候选目标簇。
  - 红色五角星表示连接组件对应子图的根结点（cell）。

一个候选目标簇可以由多个相邻的组件组成，这些组件的根节点彼此相邻。

Apollo 对候选目标簇内各个 cell 的类别概率求和来计算各类候选障碍物的概率，包括车辆、行人、自行车和未知的障碍物。

具有最大平均概率的障碍物类型即为该目标簇的 最终分类结果。

**后处理**
聚类之后，Apollo 获得一组候选目标簇，每个候选目标簇包括几个 cell。在后处理中，通过对计算该簇所包含的 cell 的 positiveness 和目标高度的均值，Apollo 首先计算出每个候选簇的检测置信度。然后，Apollo 移除比预测目标高度高很多的点，并收集每个候选簇有效 cell 内的点。最后，Apollo 移除置信度非常低或者包含点数比较少的候选簇，输出最终障碍簇/分割。

### 2.4.2 激光雷达感知模块的输入输出
<div align=center><img src=./fig/module_in_out.png width=500/></div>

### 2.4.3 激光雷达感知模块仿真实践
**步骤一：进入 Apollo 环境并启动 Dreamview**
```bash
#进入 Apollo Docker 环境。
./apollo.sh
#在 Docker 环境里启动 Dreamview。
bash scripts/bootstrap.sh
#如果需要关闭 Dreamview，请您执行以下命令：
./scripts/bootstrap.sh stop
```

**步骤二：选择车型和地图**
  - 在浏览器中输入网址 http://localhost:8888，打开 Dreamview。
  - 选择相应的模式、车辆和地图信息。

<div align=center><img src=./fig/dreamview.png width=500/></div>

**步骤三：启动所需模块**
```bash
# 修改 channel 信息
vim /apollo/modules/perception/production/dag/dag_streaming_perception.dag
# 将 channel: "/apollo/sensor/lidar128/compensator/PointCloud2" 修改为 channel: "/apollo/sensor/velodyne64/compensator/PointCloud2"
vim /apollo/modules/perception/production/conf/perception/lidar/velodyne128_segmentation_conf.pb.txt
# 将 lidar2novatel_tf2_child_frame_id: "velodyne128" 修改为 channel: lidar2novatel_tf2_child_frame_id: "velodyne64"。
```
最后在 Module Controller 标签页启动 Perception 模块。注意：Perception 模块启动一般需要 2 分钟左右时间。如需确定感知模块是否已启动成功，您可以在 Docker 环境下，命令行输入：
```bash
tail -f /apollo/data/log/mainboard.INFO
```
该命令表示实时显示 cyber 日志的尾部。当屏幕中该日志显示如下信息时，则可以确定感知模块已启动完毕。

<div align=center><img src=./fig/tail_info.png width=500/></div>

**步骤四：下载并使用 Cyber 播放数据包**
```bash
# 在您本地电脑上下载 Apollo 的传感器原始数据包 demo_sensor_data.tar.xz并解压
tar -xvf demo_sensor_data.tar.xz # 解压后的 record 的大小为 7.6 GB。
# 为了在 Docker 中可以访问 record，将下载的数据包复制到 /apollo/data/bag 目录下`。
# 进入 docker 环境后，播放数据包。
cyber_recorder play -f /path/to/your_record
# 查看 channel 信息：在 docker 环境下，用 cyber_monitor 命令，查看激光雷达相关 channel 是否正常输出，并使用上下方向键选择 channel，使用右方向键查看 channel 详细数据：
cyber_monitor
```
启动之后，请检查如下 channel 是否正常输出，绿色代表正常输出：

<div align=center><img src=./fig/channel.png width=500/></div>

如果激光雷达感知模块启动成功，检测的障碍物信息会输出在 /apollo/perception/obstacles 通道里面，并在 Dreamview 上面可视化障碍物信息：

<div align=center><img src=./fig/msg_1.png width=500/></div>
<div align=center><img src=./fig/msg_2.png width=500/></div>

如果以上步骤都正常执行，则可以在 Dreamview 中看见下面的画面。

<div align=center><img src=./fig/results.png width=500/></div>

**步骤五：点云可视化**  
如果您想对点云进行可视化的查看，可以利用 CyberVisualizer 工具。CyberVisualizer 是基于 Cyber 开发的传感器原始数据可视化工具。
```bash
cyber_visualizer
```
1. 点击左上角的 Show PointCloud。
2. 在左侧 Title 中，双击 PointCloud2，出现 ChannelName 和 Action。
3. 点击 Action 后的 Play。
4. 点击 Play 后，可以看见以下画面。

<div align=center><img src=./fig/pointcloud.png width=500/></div>

您可以利用鼠标对点云的视角进行放大、缩小等操作，来仔细查看点云的变化。激光雷达的感知就是对这些点云进行处理，最终实现目标识别。