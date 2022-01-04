<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-12-31 15:09:25
 * @LastEditTime: 2022-01-04 21:37:25
-->
- [MindSpore](#mindspore)
  - [使用MindSpore训练手写数字识别模型](#使用mindspore训练手写数字识别模型)
    - [手写数字识别概述](#手写数字识别概述)
    - [华为AI解决方案](#华为ai解决方案)
    - [MindSpore构建训练模型](#mindspore构建训练模型)
    - [ModelArts实践手写数字识别训练](#modelarts实践手写数字识别训练)
  - [MindSpore 模型快速调优攻略](#mindspore-模型快速调优攻略)
    - [调试调优背景介绍](#调试调优背景介绍)
    - [MindSpore调试调优](#mindspore调试调优)
    - [MindSpore云上调试调优](#mindspore云上调试调优)
    - [MindSpore调试调优实践](#mindspore调试调优实践)
  - [参考资源](#参考资源)


# MindSpore

## 使用MindSpore训练手写数字识别模型
**课程目标：**
  - 了解深度神经网络如何识别手写数字
  - 了解MindSpore基本功能和特性
  - 了解MindSpore模型开发和训练的基本组件和使用方法
  - 学会使用MindSpore开发一个简单的识别手写数字模型
  - 学会ModelArts平台进行手写数字识别模型的训练

### 手写数字识别概述
手写数字识别常用于在计算机视觉领域衡量算法表现的基准任务。

**MNIST数据集**
  - 训练集：60000张；测试集：10000张
  - 所有图片为标准化后的黑白图像，尺寸 28*28*1

 **LeNet-5深度神经网络**
  - LeNet-5及其之后的变体定义了现代卷机神经网络的基本结构，是入门级的神经网络模型，主要由输入层，卷积层，池化层，全连接层组成。
  - 输入层：数据输入
  - 卷积层：局部特征提取
  - 池化层：通过下采样降低特征图的分辨率，降低输出对位置和形变的敏感度，保留关键特性，减少参数和计算量
  - 全连接层：将局部特征通过权值矩阵组装成完整图像，完成特征空间到真实类别空间的映射，类似分类器

**深度学习的"学习"过程**
  - 所谓深度学习，就是要通过求解一个映射函数F(x, W)，使其映射值与真实标签的误差最小
  - 这个函数F，一般就是我们的神经网络，而其具体体现，就是其参数矩阵W
  - 为了衡量误差，就要定义损失函数Loss
  - 为了最小化误差，并对权重矩阵进行更新，我们使用梯度下降法，沿着梯度的反方向对W进行更新

### 华为AI解决方案
<div align=center><img src=./figs/华为AI解决方案.png width=500></div>
<div align=center><img src=./figs/ModelArts全周期AI工作流.png width=500></div>

**自动微分**
  - 图方法-TensorFlow：实现简单，容易优化并行，图结构可编程性难度大
  - 运算符重载-PyTorch: 容易理解，但运行开销大
  - 源码转换- MindSpore: 结合上述两种方式，兼顾可编程性和性能

**On-Device执行**
  - 业界主流计算框架都采用主从控制模式
  - MindSpore采用主处理器运行模式，而非协处理器模式，让神经网络训练过程完整的在芯片上执行，减少host- device之间的消耗
  - 在host完成图编译，然后将完整图下发给910GPU，所有的矩阵运算都在910上运行，不再需要host-device 之间的交互 
<div align=center><img src=./figs/on-Device.png width=500></div>

**动静态图执行模型**
  - 一行代码实现两种模式的切换，调试时使用动态模式，运行时使用静态模式
<div align=center><img src=./figs/动静态图执行.png width=500></div>

### MindSpore构建训练模型

**MindSpore基本组件**
<div align=center><img src=./figs/基本组件.png width=500></div>

**Tensor**
  - Tensor: 主要有两种，一种是普通的tensor，另一种是承载权重和偏置的parameter，可以与numpy.ndarray无缝转换
  - tensor的定义需要两个参数：一个是其中存放的数据，另一个数据的类型，如`t1 = Tensor(np.zeros([1,2,3]), ms.float32)`;
  - tensor 和numpy一样同样具有一些常用的如shape, dim 等方法
  - Initializer: 权重初始化模块，常见的有Normal, Uniform 等类，可以通过别称直接调用即可，如将参数设定为 `weight_init='normal'`

**算子**
  - 算子用于执行最基础的计算
<div align=center><img src=./figs/算子.png width=500></div>

**Cell**
  - cell是可以复用的网络模块，一个大的cell中可以包含多个小的cell，小的cell之间可以通过输入输出连接起来
<div align=center><img src=./figs/Cell.png width=500></div>
<div align=center><img src=./figs/Cell_2.png width=500></div>

**定义前向网络**  
主要就是在construct中将不同的层次结构连接起来
<div align=center><img src=./figs/构建网络.png width=500></div>

**定义损失函数**
<div align=center><img src=./figs/构建损失函数.png width=500></div>

**数据集的导入与预处理**  
<div align=center><img src=./figs/数据处理.png width=500></div>

**Model-用于模型训练和推理的高阶API**
  - 通过传入前向网络net，损失函数loss和优化器optimizer，完成model的初始化
  - 调用train，eval和predict进行训练，评估和推理
  - 调用train接口进行训练时，包含两层循环，外层循环为数据集多代（epoch）循环，内层循环为epoch内多步（step）迭代
  - model接口通过回调模块可以获取训练过车中的模型参数，出发callback的时机有：begin, end, epoch_begin, epoch_end, step_begin, step_end
<div align=center><img src=./figs/model.png width=500></div>


### ModelArts实践手写数字识别训练
使用ModelArts的基本流程如下：准备数据 -> 准备执行脚本 -> 上传至obs -> 创建训练作业 -> 运行训练作业 -> 运行成功查看结果
  - 在华为云官网的首页，点击控制台，可以选择 obs服务和modelArts服务
  - 在obs文件内创建四个子文件夹：dataset用于存放训练数据；train文件夹用于存放训练脚本；output存放模型文件；log存放训练记录
  - 然后创建训练作业：在算法来源中设定AI引擎和代码目录以及启动脚本
  - ...

<div align=center><img src=./figs/训练作业.png width=500></div>


## MindSpore 模型快速调优攻略
课程目标：
  - 使用MindSpore调试调优工具完成跨框架模型迁移、模型精度、性能调试调优
  - 体验MindSpore智能IDE的高效开发
  - 体验MindSpore的动静统一调试
  - 体验MindSpore的端云协同训练

### 调试调优背景介绍
主要用于解决两大问题：
  - 使用MindCoverter帮助用户从其他框架切换到MindSpore
  - 使用MindInsight帮助用户基于MindSpore进行研究开发，解决模型训练、推理过程中可能遇到的问题

### MindSpore调试调优
<div align=center><img src=./figs/mindinsight工具包.png width=500></div>
<div align=center><img src=./figs/mindinsight使用.png width=500></div>

**生态迁移工具**
  - MindConveter是一种基于模型（计算图）的生态迁移框架，可以将TensorFlow的pb模型，其他框架的ONNX(Open Neural Network Exchange)模型文件生成MindSpore模型定义脚本以及权重文件，使用时需要填入四个必须参数：model_file, shape, input_nodes, output_nodes
  - 导出ONNX模型时训练阶段的算子会丢失（如dropout），因此转换后需要用户手动补回

<div align=center><img src=./figs/ONNX.png width=500></div>

**模型精度调优工具**
  - MindSpore调试器是为图模式训练提供的调试工具，因为在图模式的训练过程中，用户无法从python层获取到计算图中间节点的结果
  - 使用MindSpore调试器，在Mindinsight调试器界面结合计算图，查看图节点的输出结果；并且可以设置监测点，监测训练异常强抗，比如检查张量溢出，在异常发生时追踪错误原因，或查看权重等参数的变化情况

**模型性能调优工具**
  - Profiler为MindSpore提供了性能调优能力，在算子性能、迭代性能、数据处理性能等方面提供了易用、丰富的调试功能，帮助用户快速定位性能瓶颈点，提升网络性能
  - 具体来讲，Profiler在MindSpore侧训练脚本中为用户提供性能数据收集的启动接口和数据分析接口，最终生成性能数据文件
  - 在Mind Insight侧为用户提供可视化界面，将通过多个维度展示性能数据以及统计分析结果

<div align=center><img src=./figs/profiler_1.png width=500></div>
<div align=center><img src=./figs/profiler_2.png width=500></div>

**训练过程可视工具**
  - 首先在训练脚本中，根据summary collector的接口配置训练数据收集的路径和训练数据收集的周期
  - 然后为模型定义部分添加summary 算子, 比如通过ScalerSummary记录标量数据，根据TensorSummary记录张量数据，Image Summary 记录图片数据等
  - 最后通过mindinsight start --port 9001 --summary-base-dir ./ 启动mindinsight来查看训练过程

<div align=center><img src=./figs/调试调优总结.png width=500></div>

### MindSpore云上调试调优
  - MindSpore还提供了pycharm的IDE插件，利用代码补全，TreeView，搜索等功能提升开发效率
  - IDE支持配置ModelArts密钥，可直接将本地训练代码部署至云端执行
  - 支持一键启动ModelArts云上MindSpore训练作业与MindInsight可视化作业
  - 支持独立启动MindInsight可视化作业

### MindSpore调试调优实践
<div align=center><img src=./figs/调优示例-1.png width=500></div>
<div align=center><img src=./figs/调优示例-2.png width=500></div>
<div align=center><img src=./figs/调优示例-3.png width=500></div>


## 参考资源
  - [MindSpore开源社区](https://www.mindspore.cn)
  - [MindSpore代码](https://gitee.com/mindspore/mindspore)
  - [MindSpore架构](https://www.mindspore.cn/doc/note/zh-CN/r1.2/design/mindspore.html)
  - [MindInsight架构](https://www.mindspore.cn/doc/note/zh-CN/r1.2/design/mindinsight.html)
  - [MindConverter使用指南](https://gitee.com/mindspore/mindinsight/blob/master/mindsinght/mindconverter/README_CN.md)
  - [调试器使用指南](https://www.mindspore.cn/tutorial/training/zh-CN/r1.2/advanced_use/debugger.html)
  - [性能调试器使用指南](https://www.mindspore.cn/tutorial/training/zh-CN/r1.2/advanced_use/performance_profiling.html)
