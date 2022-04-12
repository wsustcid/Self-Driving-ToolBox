<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-03-24 10:21:37
 * @LastEditTime: 2022-04-12 10:34:39
-->
- [2. Autoware 建图模块](#2-autoware-建图模块)
  - [2.1 高精地图与经典建图算法概述](#21-高精地图与经典建图算法概述)
  - [2.2 map_file模块介绍及源码解析](#22-map_file模块介绍及源码解析)
  - [2.3 Ndt_mapping模块介绍及源码解析](#23-ndt_mapping模块介绍及源码解析)
  - [2.4 实践：基于Ndt_mapping算法建立点云地图](#24-实践基于ndt_mapping算法建立点云地图)
  - [2.5 实践:：AutowareTools与Vectormap的绘制](#25-实践autowaretools与vectormap的绘制)

## 2. Autoware 建图模块
### 2.1 高精地图与经典建图算法概述
**高精地图定义**    
高精地图是数据精度为分米甚至厘米级，包含空间信息、语义信息和时间信息的数据体。
  - 空间信息：点云地图
  - 语义信息：车道线、停止线、转向路标、速度标识、人行横道、路牙
  - 时间信息：语义信息的升级，比如红绿灯信息，早晚可变车道信息，白天关闭晚上打开的路灯等随时间变化的语义信息

**高精地图格式**  
不同格式间的高精地图可以相互转化的
  - Vector map
  - lanelet2
  - opendrive
  - Nds 

**点云地图创建原理**  
输入点云数据一般基于激光雷达坐标系，激光雷达坐标系和车身坐标系为刚性连接，因此：
  1. 如果将车辆起始位置当成地图坐标系的原点
  2. 那么在之后的运动过程中的某些间隔均匀的时刻，如果能够准确的获取车辆的位姿变化
  3. 就能将原本基于激光雷达坐标系的点云信息转换到地图坐标系下，进而就构成了点云地图的一部分。
  4. 以此往复，就会构成一张庞大的点云地图

综上，点云地图创建的核心就是实时获取车辆的位姿变化，以实现点云信息到地图坐标系的坐标变换。

**实时获取车辆位姿变化方式**  
  - RTK差分定位：成本较高，需要搭建基站，不能够有遮挡
  - 激光SLAM匹配算法：存在累积误差，长时间使用会存在漂移
  - 轮速计定位：存在累积误差，长时间使用会造成漂移 
  
实际使用时，通常根据不同场景混用。

**点云地图上语义信息标注工具**  
  - Autoware tools：免费
  - Unity插件版：免费
  - VTD
  - RoadRunner

**高精地图的生产流程**  
主要包括数据融合、点云地图建立、降采样去噪、语义信息标注四大步骤：
  1. 首先会进行数据融合:通常将相机和激光雷达数据进行融合形成RGB点云数据，用于车道信息的提取。有些高级别激光雷达也可以直接清晰的显示车道信息。
  - 2. 建立点云地图：SLAM算法或RTK直接投影
  - 3. 降采样去噪：主要目的是去除移动障碍物，可以建图后去除也可以建图时直接识别进行剔除
  - 4. 语音信息标注：也有一些通过边建图边语义识别路况信息的系统，目的是为了降低后面手工语义信息标注的工作量

**经典建图算法概述**
  - 视觉slam(VIO): orbslam、vins、svo、dso 
  - 激光slam(2d): gmapping、hector、Karto、cartographer2d 
  - 激光slam(3d): loam系、cartographer3d、**Ndt**

**3D点云建图算法分类**  
之前已经提到，建图的关键在于位姿变化的准确估计，对于slam算法而言，位姿变化的计算是通过点云特征匹配优化后得出的，因此，可以根据特征匹配形式进行分类：
  - **Scan to Scan:** loam系：Loam会将输入scan中的点云根据曲率大小分为*平面点*和*边缘点*，之后的匹配优化过程也是针对当前输入scan和上一scan的平面点和边缘点来研究进行的。根据*边缘点的距离优化公式*和*平面点的距离优化公式*来构造优化方程求解位姿变化量。Lego-loam、lio-sam等都是基于这一原理来进行位姿优化求解的，只不过他们引入了更多传感器并加入了回环检测。
  - **Scan to Map** :Cartographer、Ndt：二者都是通过当前scan同已经建好的map(或者submap)来进行特征匹配的，和loam提取有曲率特征的点云不同，Cartographer将当前scan通过hit的方式来和上一次建好的submap来进匹配优化; 而Ndt则是将map网格化后计算每个网格的均值方差，并通过当前scan中的每个点落在map网格中的正态分布概率来进行匹配优化的。

 
### 2.2 map_file模块介绍及源码解析
**如何看源码**  
不论多大的模块或是多小的模块，分析其源码主要通过一下三个步骤完成：
  - 模块简介：首先要对模块要有整体的了解，了解该模块功能，特别是其输入和输出的接口，在ros里面就是订阅了哪些topic，发布了哪些topic，整理出框架图
  - 关键function解析: 要仔细研究有助于理解该模块的关键cpp文件中的函数，要有的放矢，不重要函数只要知道它的功能即可，把精力放在关键函数的执行过程上。当然，对于复杂算法，还要先了解其算法的原理流程，才能将具体代码实现和算法流程对应上
  - 代码解析: 通过实际操作，小幅度修改，看输入输出，看是不是和自己理解的一致。

**map_file模块功能介绍**  
map_file模块主要负责读取pcd点云文件和csv语义地图文件，解析并将其转换成描述地图信息的topic发送给rviz和其他功能模块。首先以`autoware_quickstart_examples/new_map.launch`为例，启动后通过在rviz中观察或通过`rosnode list -> rosnode info xx`发现，其分别通过`points_map_loader`和`vector_map_loader`两个节点将原始的点云pcd文件和语义信息csv文件转化为了高精地图信息，即输入为文件，输出为`/points_map`和`/vector_map`topic，进一步通过`rostopic info`等一系列命令可以进一步查看话题的相关信息，了解节点构成和输入输出。其模块功能组成如下：
  <div align=center><img src=./fig/map_file_modular.png width=500></div>

**map_file关键函数解析**  
接下来就继续深入剖析具体的代码文件，看其如何实现的。具体代码文件路径和核心函数如下图所示：
<div align=center><img src=./fig/map_file_function.png width=500></div>

注意，在模块功能简介部分你已经了解了模块的输入输出，所以在核心文件中看源码的时候你可以直接搜对应的topic关键字，这样就能快速定位到你要看的地方。然后环环相扣，可以通过变量名，函数名一步步从小到大。也可以反之，从大到小看。

**points_map_loader.cpp**   
具体算法流程比较简单，无需关注当前不使用的的情况，仅考虑`area=noupdate`的情况：
  - 首先main函数通过命令行读入pcd文件地址；然后创建发布话题`points_map`
  - 通过`create_pcd()`函数以点云地址为输入，然后使用`pcl::io::loadPCDFile`不断读入点云文件，并拼接为一个大的点云文件pcd
  - 最后通过`publish_pcb()`将 `sensor_msgs::PointCloud2 pcd`发布出去

**vector_map_loader.cpp**  
该节点的核心处理流程为读取分别csv文件中各语义元素的定义要素，然后创建对应的语义元素msg并发布，最后再总的语义元素集合msg，定义将各元素话题并进行汇总，并发布出去
  - 核心实现方式为利用模板函数 `template<class T, class U> U createObjectArray(const std::string&file_path)`，读取csv文件中的元素，将其转为为T类型，然后将多个T存入vector，构成U发布出去
  - 之所以读取CSV元素行内容直接就可以存为T，是因为T具体类型的.msg定义都是和具体CSV中各列元素一一对应的，将多行T存入vector，就构成U的data部分
  - 每种U都是具体某个CSV文件的集合，作为一个语义元素进行发布
  - 然后还有一个vector_map话题订阅各子语义元素话题，汇总成 MarkerArray 发布出去，供rviz可视化


### 2.3 Ndt_mapping模块介绍及源码解析

**ndt_mapping 模块介绍**  
ndt_mapping模块主要负责基于传感器输入的点云、imu、里程计等信息，基于ndt匹配优化算法，建立点云地图(虚线为可选输入topic)。

<div align=center><img src=./fig/ndt_mapping_modular.png width=500></div>

**ndt_mapping关键函数解析**  
<div align=center><img src=./fig/ndt_mapping_function.png width=500></div>

**ndt_mapping.cpp**  
输入为订阅话题`/points_raw`和`/_imu_topic`，输出为发布话题`/ndt_map`和`/current_pose`，核心代码为接收到两个订阅话题的数据后，通过对应的回调函数对位姿进行估计，并通过计算旋转矩阵对点云进行一系列的处理和位姿变换，最终形成总的map点云和车辆位姿
  - 核心实现过程就是pcl库的调用和位姿变换矩阵的使用


### 2.4 实践：基于Ndt_mapping算法建立点云地图 
```bash
# 建图
source install/setup.bash
roslaunch autoware_quickstart_examples my_mapping.launch
# 显示
rviz # 添加pointCloud2 topic 输出，设置size=0.1
# 数据包播放
rosbag play simcity_lidar_imu.bag

# 尝试改动参数，重新编译运行查看输出
```

**点云地图的保存**  
刚才学到的只是通过rviz可视化`/ndt_map`话题的数据，那么如何对该结果进行保存呢？
```bash
rosbag record -o map.bag /ndt_map # 注意在快结束的时候执行
rosbag info map.bag
rosrun pcl_ros bag_to_pcd map.bag /ndt_mapp pcd 
```


### 2.5 实践:：AutowareTools与Vectormap的绘制
Autoware Tools 分为[网页版](https://tools.tier4.jp)和本地版，v1.12 对应vector_map类型的地图，v1.13 对应lanelet2类型的地图。

**使用方法**  
  1. file -> import 导入地图文件
  2. 使用上方工具栏实现基本元素的绘制
  3. 要想编辑某个元素，需要先在右侧的元素框中将其选中，才可编辑
  4. export -> adas map 保存

**参考链接**
  - [Autoware矢量地图在线标注方法](http://xchu.net/2019/08/20/autoware-vector-map-builder-guide/)


