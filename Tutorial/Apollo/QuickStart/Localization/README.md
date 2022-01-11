<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 16:17:04
 * @LastEditTime: 2022-01-11 10:44:28
-->
- [2.6 Apollo定位模块](#26-apollo定位模块)
  - [2.6.1 MSF 定位模块原理](#261-msf-定位模块原理)
  - [2.6.2 MSF定位模块仿真实践](#262-msf定位模块仿真实践)
  - [2.6.3 MSFVisualizer定位可视化实践](#263-msfvisualizer定位可视化实践)


## 2.6 Apollo定位模块
高精度、高鲁棒性的定位系统是自动驾驶系统不可或缺的基础模块。Apollo 定位模块针对不同的应用需求提供了三种不同实现方式的定位模块。

**RTK（Real Time Kinematic）定位模块**  
利用 GPS + IMU 实现的全局定位导航系统，在 GPS 信号良好的情况下可以实现厘米级定位精度。

**MSF（Multi-Sensor Fusion）定位模块**  
结合 GPS + IMU + Lidar 实现的多传感器融合全局定位导航系统，利用多传感器优缺点的互补，实现高精度、高鲁棒性的定位能力。对于 GPS 失效或者 Lidar 地图环境变更场景具备一定的冗余处理能力。本模块可提供城市道路、高速、部分隧道等场景下的定位能力。

**NDT（Normal Distribution Transform）定位模块**  
结合 GPS + IMU + Lidar 实现的简单融合定位系统，其中 lidar 定位采用开源 NDT 算法实现。本系统依赖 GPS 信号质量，具备简单城市场景下的高精度，鲁棒的定位能力。

### 2.6.1 MSF 定位模块原理
这里重点介绍 （Multi-Sensor Fusion）定位模块实现原理，系统框图如下图所示：
<div align=center><img src=./fig/module.png width=600></div>

  - MSF 定位系统以多种传感器数据和离线制作的高精度 Lidar 定位地图为输入
  - 其中 GNSS Localization 模块以车端 GPS 信号和基站数据为输入，输出高精度 RTK 定位结果
  - LiDAR Localization 模块以在线 lidar 扫描数据和高精度 Lidar 定位地图为输入，提供高精度 lidar 定位结果
  - SINS 模块利用IMU数据进行惯性导航
  - 后端采用 error-state Kalman filter 融合多种传感器量测信息。输出高精度的车辆位置和姿态。

详情参见 [Robust and Precise Vehicle Localization Based on Multi-Sensor Fusion in Diverse City Scenes](https://ieeexplore.ieee.org/document/8461224)

**MSF Localizer 订阅和发布的主要 Channel**

<div align=center><img src=./fig/module_in_out.png width=500></div>

### 2.6.2 MSF定位模块仿真实践
**1. 启动 Apollo Docker 环境**
```bash
# 启动终端，进入 Apollo 安装路径：
cd apollo
# 执行脚本进入 Apollo Docker 环境：
./apollo.sh
#出现以下提示，证明您已经进入 docker 环境：
[user@in-runtime-docker:/apollo]$ 
```
**2. 下载并解压数据包**
```bash
# 下载定位 demo 数据 demo-localization-data-3.5.tar.gz。
wget https://apollo-system.cdn.bcebos.com/dataset/localization/demo-localization-data-3.5.tar.gz
# 执行以下命令解压数据：
tar -xvf demo-localization-data-apollo-3.5.tar.gz
```
解压后得到以下文件：
```bash
- data
 |- local_map           # MSF Localization 定位地图
 |- ndt_map             # NDT Localization 定位地图
 |- params              # 车辆参数
 |- records             # bag 数据
```

**3. 将数据包复制到指定目录**  
为了在 Docker 中可以访问下载的数据包，将下载的数据包`demo-localization-data-3.5`复制到 `DATA_PATH=/apollo/data/bag` 目录下

**4. 配置参数**  
```bash
# 配置传感器外参: 运行以下命令，拷贝车辆参数到定位模块目录下：
# DATA_PATH 为下载的 demo 数据的路径
cp -r DATA_PATH/params/* /apollo/modules/localization/msf/params/

# params 文件夹下包含以下文件：
- gnss_params
|- ant_imu_leverarm.yaml:               #杆臂值
- velodyne_params
|- velodyne128_novatel_extrinsics.yaml: #IMU -> LiDAR 坐标变换
|- velodyne128_height.yaml:             #LiDAR 相对于地面的高度

#配置地图参数： 打开 /apollo/modules/localization/conf/localization.conf 文件并修改 --map_dir 字段：
vim /apollo/modules/localization/conf/localization.conf
# 移动到第五行，修改 --map_dir 字段
--map_dir=DATA_PATH
```

**5. 启动 MSF Localizer**  
```bash
cyber_launch start /apollo/modules/localization/launch/msf_localization.launch
```

**6. 播放数据包**
```bash
cd DATA_PATH/records
cyber_recorder play -f record.*
``` 

**7. 使用 Cyber Monitor 查看 Channel**
```bash
# 在 Apollo docker 环境中运行以下命令：
cyber_monitor
#如果 recorder 数据包正常，可以看到定位发出的 topic 消息。 当看到以下 topic 显示绿色时，定位模块运行正常：
/apollo/localization/msf_lidar
/apollo/localization/msf_status
/apollo/localization/pose
```

**8. 使用 DreamView 查看定位状态**
```bash
# 启动 DreamView: 注意确保启动dreamview前其处于关闭状态，最好先stop以下再启动
./scripts/bootstrap.sh
# 在 Dreamview 中选择车辆模型和地图:在浏览器中打开 http://localhost:8888，在左边栏选择 Module Controller，在右上角的下拉框中选择对应的车辆模型和地图：
# 车辆模型选择 Mkz Example，
# 地图选择 Sunnyvale Big Loop。
# 左边栏选择 Layer Menu: 在 Position 中同时勾选 Localization 和 GPS。
```

如果 recorder 数据包和地图正常，可以看到以下图像：

<div align=center><img src=./fig/msf_demo.png width=500></div>

网页正中是地图和汽车，其中黑白的背景是地图，颜色表示环境中反射值：颜色越亮表示反射值越高，颜色越暗表示反射值越低，纯黑色表示没有被激光雷达扫描到的区域。

白色车辆模型表示经过 MSF 融合算法得到的位置坐标，蓝色方框表示 GPS 位置，可以在视频中看到蓝色方框在不停跳动，但车辆位置比较稳定，说明融合定位算法提供了更好的平滑性。

### 2.6.3 MSFVisualizer定位可视化实践
**步骤一：在本地安装 X-Server**  
```bash
# 1. 启动 Apollo Docker 环境
cd apollo
./apollo.sh
# 2. 为 docker 配置 X-Server。
sudo apt-get update
sudo apt install x11-xserver-utils
```

**步骤二：启动定位模块**  
可视化工具受消息触发后才会运行，启动可视化工具前，请您先启动定位模块。参见上一小节内容

**步骤三：可视化工具使用**  
```bash
cyber_launch start /apollo/modules/localization/launch/msf_visualizer.launch
```

第一次运行时，可视化工具需要生成可视化需要的图像，等待较久的时间是正常的。当弹出如下图所示的窗口时，说明可视化工具运行正常，其中灰色背景表示地图，绿色细线表示原始点云数据，红色粗线圆圈表示 LiDAR 定位的置信度，绿色粗线圆圈表示 MSF 定位的置信度。

<div align=center><img src=./fig/msf_visual.png width=500></div>