<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2022-01-06 16:17:04
 * @LastEditTime: 2022-01-07 15:42:52
-->
- [2.3 Apollo视觉感知模块](#23-apollo视觉感知模块)
  - [2.3.1 视觉感知模块的原理](#231-视觉感知模块的原理)
  - [2.3.2 视觉感知模块的输入输出](#232-视觉感知模块的输入输出)
  - [2.3.3 视觉感知模块仿真实践](#233-视觉感知模块仿真实践)

## 2.3 Apollo视觉感知模块
摄像头传感器因其具有信息丰富、观测距离远等特点，在障碍物检测和红绿灯检测等方向发挥着不可替代的作用，是对激光雷达感知结果的重要补充。
  - 但摄像头又有容易受环境影响、缺乏深度信息等缺点，给无人驾驶系统中的视觉感知算法带来了巨大的挑战
  - 因此，如何建立一套高精确率和高稳定性的视觉感知算法，是无人车感知模块的核心问题

视觉感知算法在 Apollo 平台上主要有 3 个应用场景，分别是红绿灯检测、车道线检测、基于摄像头的障碍物检测
<div align=center><img src=./fig/module.png width=500></div>

每个模块又可以分为 3 部分，分别是图像的预处理、神经网络模型以及后处理
  - 预处理：对上游信息做一些处理和整合，以方便把信息直接输入到模型中做预测。
  - 神经网络模型：主要涉及一些深度学习算法，包括目标检测、语义分割、图像分类等。
  - 后处理：为了优化模型效果，我们会利用一些传统的算法进一步优化网络模型的预测，让我们的算法可以在实车上跑得更加流畅。

### 2.3.1 视觉感知模块的原理
**红绿灯检测模块原理**  
红绿灯检测模块的主要作用是检测当前路况下在摄像头的视觉范围内的红绿灯的状态，这是一个典型的目标检测任务。如下图所示，红绿灯检测模块一共包含 4 个部分，分别是数据预处理、红绿灯位置检测、红绿灯识别和矫正。
  1. 通常红绿灯在图像中所占比例比较低，为了能够有效的检测出红绿灯，我们会借助高精地图给出的的信息预先从相机图像中将包含红绿灯区域的大致位置取出来。
  2. 红绿灯位置检测部分采用了一种常规的基于 CNN 的目标检测算法，模型接收的就是刚刚选取的区域，输出是红绿灯的边框以及红绿灯的类别。
  3. 检测完成后，需要对红绿灯的颜色做识别。我们训练了 3 个轻量级的卷积神经网络做分类，这 3 个网络分别对应检测结果的 3 个类别，竖着的、横着的和方形的。
  4. 最后，矫正器主要针对识别置信度不高的情况，通过查询前面几帧的检测状态对当前的红绿灯颜色进行矫正。

<div align=center><img src=./fig/traffic_light_detection.png width=500></div>

**车道线检测模块原理**  
我们把车道线检测算法当作分割问题，在图像中寻求对于语义上车道线存在位置的检测，即使它是模糊的、被光照影响的、甚至是完全被遮挡的，我们都希望能将它检测出来。

<div align=center><img src=./fig/lane_detection.png width=500></div>

车道线检测的网络结构如上图所示，主干是一个编码-解码结构的分割网络，用来输出车道线分割结果。在车道编码器的末端附加一个网络分支来检测消失点。
  - 该分支由卷积层和全连通层组成，其中卷积层为消失点任务转换车道特征，全连通层对整个图像进行全局汇总，输出消失点位置。
  - 车道线检测模型在遮挡情况下和转弯时都可以对车道线进行有效的检测。

**障碍物检测模块原理**  
障碍物检测部分采用的是基于单目视觉的障碍物检测算法，根据相机获取的图像得到障碍的类别和位置信息。
  - 这里使用 7 个变量来表示 3D 边框，分别是物体的长宽高，物体的位置 x，y，z 以及物体的旋转角度 $\theta$
  - 上图是 3D 障碍物检测模块的模型结构图，输入的是单张的图像信息，经过神经网络提取特征，最后接上检测模块（Apollo 有两个检测模型，分别是基于 YOLO 的 one-stage 检测方法和基于中心点检测的检测方法）。
  - 最终，通过模型可以得到障碍物的 3D 信息（长宽高、角度等），可以根据这些信息求出障碍物的3D边框

<div align=center><img src=./fig/obstacle_detection.png width=500></div>


### 2.3.2 视觉感知模块的输入输出
Apollo视觉感知模块的输入输出示意图如下所示
<div align=center><img src=./fig/module_in_out.png width=500></div>

下表列出了视觉感知模块各个 channel 的输入输出：
<div align=center><img src=./fig/channel_in_out.png width=500></div>

下表列出了视觉感知模块的相关参数以及修改建议：
<div align=center><img src=./fig/parameter.png width=500></div>

红绿灯检测模块输入输入如下表所示
<div align=center><img src=./fig/traffic_module_in_out.png width=500></div>

障碍物检测模块输入输入如下表所示
<div align=center><img src=./fig/obstacle_module_in_out.png width=500></div>

<div align=center><img src=./fig/obstacle_detection_demo.png width=500></div>

### 2.3.3 视觉感知模块仿真实践
视觉障碍物感知模块主要检测远处（>50m）的障碍物。但视觉障碍物感知结果不单独输出，而是跟激光雷达的检测结果融合后输出。

在本小节中为了让您直观地感受 Apollo 视觉感知模块的输出，我们通过修改配置文件，把视觉感知的结果单独输出，但注意完成本节视觉感知实践操作后，要将 channel 的修改复原，以免影响雷达感知的输出。

1. 首先我们需要下载数据包：因为我们并没有真实的车辆，如何进行仿真实践呢？与ros bag数据回放的原理类似，我们通过播放数据包，相关节点和channel便会发布数据，就如同当时车辆运行时采集到的一切数据的真实复现，这时我们就可以运行相关算法，基于上述数据完成特定功能后在Dreamview上查看结果
   ```bash
   # 下载数据包
   wget https://apollo-system.cdn.bcebos.com/dataset/6.0_edu/demo_sensor_data_for_vision.tar.xz
   # 解压数据包
   tar -xvf demo_sensor_data_for_vision.tar.xz
   # 将数据包复制到指定目录
   cp demo_sensor_data_for_vision.record /apollo/data/bag 
   ```

2. 接下来启动Dreamview，用于后续显示和控制调试
   ```bash
   # 进入docker
   ./apollo.sh
   # 启动Dreamview
   ./scripts/bootstrap.sh # 注意启动dreamview前最好确保已经关闭了Dreamview
   # 关闭dreamviw： ./scripts/bootstrap.sh stop
   ``` 

3. 选择车型和地图:车辆选择后，程序会把会把 calibration/data 目录下对应的车型参数和传感器内外参文件拷贝到作用目录下。地图选择后在 Dreamview 下便可以正常显示当前地图。
   - 在浏览器输入网址 http://localhost:8888/，打开 Dreamview
   - 在 Dreamview 右上角的 --vehicle-- 中，选择 mkz_example，
   - 在 Dreamview 右上角的 --map-- 中，选择 Sunnyvale Big Loop。

4. 启动所需模块：模块的启动有两种方式，一种是依靠dreamview上的模块控制按钮，也可以通过在终端执行命令，二者的效果是一致的
   ```bash
   # 启动Transform模块: Transform 模块为了发布传感器各坐标系变换供各模块调用
   cyber_launch start /apollo/modules/transform/launch/static_transform.launch
   # 启动 image decompression 模块：视觉模块依赖的输入是相机传感器采集到的图像数据，image decompression 模块可以将压缩的图像数据解压缩
   cyber_launch start modules/drivers/tools/image_decompress/launch/image_decompress.launch
   ``` 

5. 修改输出的 channel 名称：视觉障碍物检测默认的输出 channel 为 /perception/obstacles，不会在 Dreamview 上显示检测结果。如果想要在 Dreamview 上可视化结果，需要修改下面文件的一部分关键字
   ```bash
   # 打开文件
   vim modules/perception/production/conf/perception/camera/fusion_camera_detection_component.pb.txt
   # 定位到第 10 行，修改为：
   output_final_obstacles : true
   # 定位到第 11 行，修改为：
   output_obstacles_channel_name : "/apollo/perception/obstacles"
   ``` 

6. 启动视觉障碍物检测模块：注意：成功启动的判定标准是观察处理器的显存不再发生变化或者 cyber 日志尾部输出结束信息
   ```bash
   # 启动视觉障碍物检测模块
   mainboard -d modules/perception/production/dag/dag_streaming_perception_camera.dag
   # 在终端查看 GPU 的占用情况:当 mainboard 进程显存占用不再变化，证明模型已经完成启动
   watch -n 0.1 nvidia-smi
   # 查看cyber日志：当日志中出现 vanishing point时，说明启动完毕
   tail -f /apollo/data/log/mainboard.INFO
   ``` 

7. 播放数据包:等到感知模块成功启动后，执行如下命令
   ```bash
   # 播放数据包：-k 是为了屏蔽原始数据包中记录的障碍物检测输出，我们新算法的检测结果便会替代它
   cyber_recorder play -f /apollo/data/bag/demo_sensor_data_for_vision.record -k /apollo/perception/obstacles /apollo/prediction
   ``` 
   
如果在 Dreamview 可以看到障碍物，说明模块启动成功，如下图所示。图中的绿色框便是我们的视觉感知算法检测出的障碍物。
<aling=center><img src=./fig/perception_obstacle_demo.png width=500></div>

注意：完成视觉感知实践操作后，要将 channel 的修改复原，以免影响雷达感知的输出。


**其他模块的启动命令**
```bash
## 启动红绿灯检测模块
cyber_launch start /apollo/modules/perception/production/launch/perception_trafficlight.launch

## 启动车道线检测模块
mainboard -d ./modules/perception/production/dag/dag_streaming_perception_lane.dag
```