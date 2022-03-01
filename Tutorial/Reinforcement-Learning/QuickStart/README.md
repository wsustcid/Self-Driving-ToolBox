<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 0.0.0
 * @Date: 2022-03-01 15:20:01
 * @LastEditTime: 2022-03-01 22:44:36
-->
## 1. 快速入门
### 1.1 课程准备
**强化学习与监督学习的区别**
监督学习在基于数据的前提下，给定输入和输出，通过定义损失函数还是来训练一个从输入到输出的映射。但是，在很多问题中，我们是没有数据的！即没有问题的参考答案。比如训练一个广告推荐系统，只有通过不断搜集用户点击的数据，才能不断优化模型。这时就需要强化学习，二者的主要区别如下：
  - 监督学习通过学习来逼近参考答案；而强化学习通过不断试错来学习最优策略
  - 监督学习需要正确的答案；强化学习需要关于智能体动作的反馈
  - 监督学习模型并不影响输入数据；强化学习智能体能够影响自己的观测；

而与无监督学习相比：
  - 无监督学习只是学习、分析数据的内在结构；
  - 无监督学习并不需要反馈；
  - 无监督学习模型同样不会影响输入数据

**课程实践准备**
  - Google Colab
  - [Docker](https://github.com/yandexdataschool/Practical_RL/tree/master/docker#install-docker):need to switch to the "coursera" branch in your clone of the repository
  - [Manual](https://github.com/yandexdataschool/Practical_RL/issues/1)

**预备知识：**
  - [Machine Learning](https://colab.research.google.com/github/yandexdataschool/Practical_RL/blob/coursera/week1_intro/primer/recap_ml.ipynb): Numpy, Pandas, Matplotlib, Scikit-learn
  - [TensorFlow](https://colab.research.google.com/github/yandexdataschool/Practical_RL/blob/coursera/week1_intro/primer/recap_tensorflow.ipynb)
  - [PyTorch](https://colab.research.google.com/github/yandexdataschool/Practical_RL/blob/coursera/week1_intro/primer/recap_pytorch.ipynb)

### 1.2 强化学习介绍
强化学习的基本原理就是智能体通过观察环境，获取对环境的观测信息(Observation)，然后选取一个动作(Action)进行输出，作用于环境，最后得到环境对于该动作的反馈(Feedback)，用于修正下一次的动作。（注意，此过程的关键在于动作输出改变了环境，因此会影响你下一步获得的观测）
  - 对于一个书籍推荐系统，观测量可以是用户的个人信息，包括年龄、性别、兴趣爱好等；动作可以是推荐的书籍信息；反馈是用户是否进行了点击
  - 此类问题都可以建模为**多臂赌博机**问题，不再考虑自己给出一个最优的推荐，而是假设自己在玩赌博机，展示每一个广告则类似于摇动了一个赌博机，我们的目标是找到一个能够获得最大收益的赌博机，或寻找一个最优策略，是自己受益最大。

鉴于强化学习的上述属性，其很适合应用于机器人等动态系统：
  - 观测是传感器输入
  - 动作是电机驱动电压
  - 反馈是机器人移动了多远
  - 在失败前不断向前
 
其他应用：
  - 对话系统：学习如何让用户开心
  - 量化金融
  - 深度学习：优化不可微分的损失；寻找最优的网络结构

**实践：OpenAI Gym**    

### 1.3 黑箱优化