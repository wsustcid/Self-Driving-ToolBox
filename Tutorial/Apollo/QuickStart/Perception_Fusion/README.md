<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 16:17:04
 * @LastEditTime: 2022-01-08 16:41:22
-->
- [2.5 Apollo感知融合模块](#25-apollo感知融合模块)
  - [2.5.1 感知融合模块的原理](#251-感知融合模块的原理)
  - [2.5.2 感知融合模块仿真实践](#252-感知融合模块仿真实践)
  - [2.5.3 进阶：配置感知融合模块](#253-进阶配置感知融合模块)

## 2.5 Apollo感知融合模块
在 Apollo 感知模块里，多传感器融合是一个重要的环节，并且也是感知的最后环节。在感知模块里，不同的传感器各有各的优缺点，而 Apollo 感知模块则是把各个传感器的优点结合起来，在目标级别上进行融合。

下图表示了摄像头（Camera）、毫米波雷达（Radar）和激光雷达（Lidar）传感器在不同任务和不同条件下的性能。其中，
  - 摄像头：对于分类任务尤其准确，
  - 毫米波雷达：在穿透性、距离估计和极端天气抗干扰性具有卓越的性能，
  - 激光雷达：擅长目标检测任务。

如果能有效将三种传感器进行融合感知，就能在各种情况下都能达到优良的性能。

<div align=center><img src=./fig/sensors.png width=500></div>

### 2.5.1 感知融合模块的原理
Apollo 感知融合模块能支持对摄像头、毫米波雷达和激光雷达传感器感知的结果进行目标级融合。
  - 通过对各传感器检测算法输出的障碍物分析，结合每个障碍物的传感器来源、位置、形状、速度、类别等信息，以及历史目标跟踪的信息，过滤掉一些检测不准确的障碍物。
  - 并且感知融合模块根据各个传感器的优缺点，调整障碍物的类别、位置、形状、速度等属性，最终融合输出，得到当前帧的结果。

<div align=center><img src=./fig/fusion_flow.png width=500></div>

**感知融合模块输入输出channel说明**
<div align=center><img src=./fig/module_in_out.png width=500></div>

### 2.5.2 感知融合模块仿真实践
**步骤一：进入Docker 环境并启动 Dreamview**
```bash
# 进入 Apollo Docker 环境。
./apollo.sh
# 在 Docker 中启动 Dreamview。
bash scripts/bootstrap.sh
# 如果需要关闭 Dreamview 则执行命令：
./scripts/bootstrap.sh stop
```

**步骤二：启动 Apollo 感知模块**
1. 在浏览器输入网址 http://localhost:8888/，打开 Dreamview 仿真界面。
2. 选择车型和地图。
   - 在 Dreamview 的右上角的 --vehicle-- 中，选择 Mkz Example，
   - 在 --map-- 中 选择 San Mateo。车辆和地图的选择均是为了示范。
3. 点击左侧的 Module Controller，进入模块选择界面。
4. 点击 Transform 按钮，启动 Transform 模块:该模块为感知模块提供必需的坐标转换信息。
5. 点击 Perception 按钮，启动感知模块。

等待约 2 分钟之后，感知模块启动完毕。如需确定感知模块是否已启动成功，还可以在 docker 环境下，命令行输入：
```bash
tail -f /apollo/data/log/mainboard.INFO
```
该命令表示实时显示 cyber 日志的尾部。当屏幕中该日志显示v2x_fusion时，则感知模块启动完毕

**步骤三：准备数据包并播放**
```bash
# 下载 record 数据包：数据包里存放了我们路测时采集的数据，包括定位、感知、预测规划等模块的信息。我们提供了 Apollo 传感器原始数据包 demo_sensor_data_for_vision.tar.xz 测试数据包供开发者进行测试。
tar -xvf demo_sensor_data_for_vision.tar.xz

# 为了在 docker 中可以访问 record，将下载的数据包复制到 /apollo/data/bag 目录下。

# 待感知模块启动完毕，就可以播放数据，数据也可以自己录制。Apollo 目前支持由cyber_recorder 录制的数据包。
cyber_recorder play -f /apollo/data/bag/demo_sensor_data_for_vision.record
```

**步骤三：感知融合效果演示**

激光雷达感知
  - 由于这里采用的激光雷达传感器是环绕 360 度视角的，因此可以检测到四周的障碍物。但是，激光雷达获取的点云随着距离的增大而变得稀疏，对于距离比较远的障碍物难以识别到。不同品牌不同型号激光雷达的有效距离有所差异，这里展示的激光雷达有效距离约为 120m。
  - 实际上 Apollo 还会在激光雷达有效范围的基础上，再缩小激光雷达检测算法的输出范围。超过 90m 距离的障碍物，Apollo 激光雷达感知模块就不会进行识别。

<div align=center><img src=./fig/lidar_perception.png width=500></div>

视觉感知（启动视觉感知参考视觉感知模块实践文档）
  - 视觉感知的检测范围受限于摄像头的视野范围，为方便对比，这里只使用了前向摄像头。
  - 下图是前向摄像头感知的结果，可以看到，视觉感知算法只识别图片里的障碍物，但是检测距离比激光雷达感知要更远，比如图中最远处的车辆，激光雷达感知是识别不到的，但视觉感知可以识别到。
  - 此外，由于激光雷达点云没有颜色信息，所以对于障碍物类别的判断不如视觉感知准确。

<div align=center><img src=./fig/camera_perception.png width=500></div>

融合感知
  - 综合了激光雷达感知和视觉感知的优势，就形成了下图的融合感知结果。
  - 具体融合策略是近距离以激光雷达检测结果为主，远距离补充视觉感知的结果。融合感知模块不仅拥有激光雷达感知对于障碍物位置的精准检测能力，还能有视觉感知在远距离障碍物检测上的加成。

<div align=center><img src=./fig/fusion_perception.png width=500></div>

### 2.5.3 进阶：配置感知融合模块
如果您已经比较熟悉 Apollo 或者想根据实际需求进行配置，那么您可以根据已有的传感器方案，选择需要使用的传感器进行障碍物检测。

Apollo 感知默认启动视觉感知和激光雷达感知模块进行融合，不启动毫米波雷达感知。
  - 如果需要关闭某个传感器感知模块，需要编辑感知启动文件，文件路径为 `apollo/modules/perception/production/dag/dag_streaming_perception.dag`，只要删除对应的 component，就能关闭该传感器感知模块。
  - 如果要启动某个传感器感知，除了在上述文件里添加对应的 component 之外，还需要确认该传感器是否在感知融合模块配置的白名单里。FusionComponent 的配置文件路径为`apollo/modules/perception/production/conf/perception/fusion/fusion_component_conf.pb.txt`。

以下是文件中参与融合的传感器配置，依次为激光雷达和两个前向摄像头：
```bash
fusion_main_sensors: "velodyne128"
fusion_main_sensors: "front_6mm"
fusion_main_sensors: "front_12mm"
# 增加传感器参与融合，比如需要开启前向毫米波雷达感知，需要在文件里增加：
fusion_main_sensors: "radar_front"
# 开启后向毫米波雷达感知则增加：
fusion_main_sensors: "radar_rear"
```