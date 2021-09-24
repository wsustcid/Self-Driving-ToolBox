- [1. 规划问题](#1-规划问题)
  - [1.1 运动规划中的任务、场景与行为](#11-运动规划中的任务场景与行为)
  - [1.2 运动规划中的约束条件](#12-运动规划中的约束条件)
  - [1.3 运动规划中的目标方程](#13-运动规划中的目标方程)
  - [1.4 分层运动规划](#14-分层运动规划)
    - [1.4.1 任务规划](#141-任务规划)
    - [1.4.2 行为规划](#142-行为规划)
    - [1.4.3 局部规划](#143-局部规划)
  - [1.5 补充阅读材料](#15-补充阅读材料)


# 1. 规划问题
## 1.1 运动规划中的任务、场景与行为
通常，复杂的运动规划任务被分层分解为多个不同层级的优化问题:
  - 每个优化问题被精准的裁剪定义用以解决不同范围和抽象层级下的问题(越高的层级，越抽象)
  - 并且，每个优化问题都有其自己的优化目标和其约束
<div align=center><img src=./figs/hierarchical_planner.png height=400 ></div>

而在解决规划问题之前，要明确三个重要的概念：任务、场景、行为，这三个基本概念构成了运动规划问题的核心。

**任务**
  - 是指在地图上规划出一条从A点到达B点的路径
  - 是最高层级的规划，其中低层级的细节被剥离出来后续单独处理
  - 其目标不仅仅是找到一条路径即可，还要保证这条路径是最高效的（以时间或距离为度量指标）

**与道路结构有关的场景**
道路结构通过车道边界和一些规则要素来影响具体驾驶场景
  - 车道保持: 车道保持是最简单的驾驶场景，其主要任务就是通过最小化与中心线的偏差，使车辆能够沿着车道中心线行驶，同时为了任务的高效性，还需要使车辆维持一定的参考速度
  - 车道变换: 车道变换是更复杂的驾驶场景，不同场景下有不同的变换路线，其变换路线取决与车辆的速度及加速度限制，并且可执行的时间域也影响车道变换的激进度
  - 左/右转: 左右转场景常发生在十字路口，与车道变换类似，其转向的具体路线与车道的弯曲程度有关，同时，周围环境的状态也决定了车辆是否拥有转向的能力。
  - U-Turn: U-Turn在执行高效的车辆掉头时非常有用，同样，U-Turn的具体路线与车辆的速度和加速度限制有关。注意：并不是所有的十字路口都是可以执行U-Turn的。

**与障碍物有关的场景**
  - 静态和动态障碍物同样影响驾驶场景
  - 静态障碍物限制了我们的行车轨迹可以占据的位置
  - 最重要的动态障碍物是自身车辆前方的车辆：为了安全起见，需要与其保持一定的时间间隔
  - 动态障碍物同样影响车辆转弯和车道变换：根据其位置和速度的不同，留给自动驾驶车辆的可执行时间也是不同的，因此我们需要利用估计和预测来计算这些时间窗口
  - 最后要注意的是，不同的动态障碍物在场景中有不同的特性和行为，如自行车、卡车和行人，要分别进行分析处理。

**行为**
  - 速度跟踪（参考速度或速度限制）
  - 减速至停车 （要保证舒适性）
  - 保持停车 （红灯）
  - Yield (Yield Sign)
  - 紧急停车
  - ...

**挑战**
  - 以上只是考虑了很小的一部分场景，主要考虑遵循交通规则进行行驶时所面临的一些常规场景
  - 但还有很多的边界情况使得整个驾驶任务更加复杂 （lane splitting, jaywalking）


## 1.2 运动规划中的约束条件
**运动学约束**
  - 车辆的运动学模型常被简化为两轮自行车模型
  - 自行车模型在路径规划过程中施加了曲率约束
  - 曲率约束是一个非完整性约束：其减少了移动机器人在任一点进行横向运动的自由度
<div align=center><img src=./figs/bicycle_model.png width=180 > <img src=./figs/curvature.png width=400></div>

**动力学约束**  
车辆的动力学约束主要关注于令车辆保持一个稳定、安全的状态
  - 摩擦力椭圆：表示车辆轮胎与地面之间能够产生的最大摩擦力的度量
  - 如果车辆引擎施加的力超过了轮胎产生的摩擦力，则轮胎与路面之间会产生滑动
  - 因此为了保证车辆的可控性和稳定性，车辆最好保持在摩擦力椭圆区域内
  - 更进一步的，在非紧急状态下，为了保证乘客的舒适度，最好把车辆加速度限制在如图所示的"舒适矩形"区域内，这就产生了一个对车辆可行加速度的一个更强的限制
<div align=center><img src=./figs/friction_ellipse.png width=200></div>

**车辆动力学与曲率的联合约束**
  - 摩擦力和舒适度约束产生了对车辆横向加速度的限制：$a_{lat} \leq a_{lat_{max}}$
  - 车辆的横向加速度是车辆瞬时转弯半径的函数 $a_{lat}=\frac{v^2}{r}$
  - 车辆瞬时曲率是其转弯半径的倒数： $\kappa = \frac{1}{r}$
  - 将上述三个等式联立，可得出车辆速度同时受限与路径曲率和横向加速度：
    $$v^2 \leq \frac{a_{lat_{max}}}{\kappa}$$

**静态障碍物产生的约束**
我们通常使用占据栅格地图来存储障碍物的位置，静态障碍物通过对规划空间的部分区域进行锁定来产生约束。在实际规划时，通过执行碰撞检测来判断静态障碍物约束是否满足：
  - Can check for collisions using the swath of the vehicle's path
  - 或者沿着车辆的行进路线检测最近的障碍物

**动态障碍物约束**  
   - 首先，不同的动态障碍物类别通常具有不同的行为特征和运动模型：为了处理行为的不确定性，基于这些行为产生的运动规划约束通常涉及预测操作。
   - 其次，动态障碍物会同时影响 *行为规划*层和 *局部规划*层的规划结果，前者影响我们我们机动决策，后者影响我们的速度个规划
     - 对于两辆车同时向着十字路口行驶的场景：避免二者产生碰撞的一种方式是跟踪两辆车之间产生的夹角，如果该角度随着时间的演进并未产生变化，则二者将会产生碰撞，此时我们行为规划器就需要产生减速决策来避免此种情况的发生
     - 对于自动驾驶汽车前方有Leading vehicle的场景：前方车辆对后方车辆的纵向速度产生了一个上限的约束，如果我们的速度规划规划出的速度超过了整个上限且二者仍然保持在同一车道的话，最终必然会产生碰撞。
  - 最后，我们应该在为了保证安全而采取保守的策略和为了能够使驾驶任务获得推进而采取的激进策略二者之间保持平衡
    - 最为保守的策略是根据周围智能体所有可能的行为来对车辆运动产生约束，这样会造成整个运动规划问题 over-constrained，最终无法找到可行解。

**道路规则交规元素产生的约束**
  - 首先最直观的是车道限制了我们行车路线
  - 另外，交规的存在让我们可以针对其他智能体的行为进行informed decision，并且基于对他们行为的预测可以进一步减少我们的搜索空间
  - 交规的隐含的要求车辆应尽可能的避免离开当前车道，除非这么做是合法的
  - 并且告知车辆在哪里进行转弯操作是安全的
  - 除此之外，同时存在一些软约束：比如与前方车辆保持一定的时间间隔
  - 最后，一些Regulatory elements，如交通等，交通标志（停止标志、限速标志等）同样对车辆的可允许行为做出了限制


## 1.3 运动规划中的目标方程
运动规划问题中的目标方程在主要起到两个方面的作用：首先是对当前的运动规划方案就是评分，其次是优化运动规划结果使其获得期望的特性。具体来讲，目标方程的设计主要考虑以下几个方面的指标：

**效率指标**
  - 路径长度：通过最小化路径弧长来产生到达终点的最小路径
    $$ s_f = \int_{x_i}^{x_f} \sqrt{1+(\frac{dy}{dx})^2 dx} $$
  - 行驶时间：最小化沿着规划路径时到达目的地的时间：
    $$ T_f = \int_{0}^{s_f} \frac{1}{v(s)} ds $$

**跟踪指标**  
  - 对于路径和速度跟踪：使用Integral Of Difference (IOD)项分别偏离参考路径和参考速度偏离的程度进行惩罚：
    $$\int_{0}^{s_f} || x(s) - x_{ref}(s) || ds$$
    $$\int_{0}^{s_f} || v(s) - v_{ref}(s) || ds$$
  - 对于速度：额外的使用折页损失对超过速度限制的部分进行惩罚：在对超速行为进行进一步惩罚的同时仍然鼓励车辆达到要求的参考速度
    $$\int_{0}^{s_f} (v(s) - v_{ref}(s) )_{+} ds$$

**平滑性指标**  
平滑性指标主要通过最小化沿着行驶轨迹的jerk实现：
  - Jerk 是加速度相对于时间的变化率 或者位置的三阶导数
  - 车辆轨迹的Jerk和乘客的舒适度息息相关
    $$\int_{0}^{s_f} || \overset{...}x(s)||^2 ds$$
    <div align=center><img src=./figs/jerk_demo.png width=600></div>

**曲率约束**  
  - 路径的结构同样影响规划出的速度
  - 如果规划出的路径具有较大的曲率，为了保证车辆工作在摩擦力椭圆中，则沿着此路径允许的最大速度值会被约束到到一个较小的区间
  $$\int_{0}^{s_f} ||\kappa(s)||^2 ds$$


## 1.4 分层运动规划
通过将规划问题分层分解为不同的子问题，可以限制每个运动规划过程所需要的信息和计算量，提升计算效率。但同时问题的分解也导致每个子问题会丢失一些domain information，相比于将问题的所有方面同时放入一整个规划任务中统一考虑，这样只能得到次优解。

### 1.4.1 任务规划
任务规划是最高层级规划，主要关注于无人驾驶的驾驶任务：在地图层级导航至目的地
  - 任务规划把低层级的细节进行了剥离
  - 也可以通过图搜索的方法进行解决，如Dijkstra, A*等

### 1.4.2 行为规划
行为规划主要关注为了遵守道路交通规则所需要的高层级决策行为，可以通过在给定驾驶场景下识别该机动行为是否安全来实现。行为规划器在做决策时需要将行人、车辆、自行车等纳入考虑，同时也关注交规元素，比如交通灯和停止标志。

**有限状态机**  
有限状态机由状态和状态之间的转移组成：
  - 状态基于对周围环境的感知构建
  - 转移基于驾驶场景的输入，比如交通灯改变了颜色
  - 但FSM是无记忆的，转移仅取决于输入和当前的状态，与过去的状态序列无关
<div align=center><img src=./figs/behavioral_planner_FSM.png width=400></div>

**基于规则的决策系统**  
基于规则的决策系统通过构建分层的规则来决定输出行为，具体来讲，规则的评估逻辑为：更高优先级的规则具有优先权。包含两个规则的示例场景如下：
  - 绿灯 & 十字路口 -> 直行
  - 行人 & 直行 -> 紧急停车
<div align=center><img src=./figs/behavioral_planner_RBS.png width=600></div>

**强化学习**  
强化学习通过最大化奖励函数$R$来确定最优的决策策略
  - 奖励函数是对所有时刻给定的动作序列质量的评估，并且根据距离当前时刻的远近对评估值施加相应的折扣
   $$ R = \sum_{t=0}^{\infty} \gamma^t R_{a_t} (s_t, s_{t+1}) $$

<div align=center><img src=./figs/behavioral_planner_RL.png width=300></div>

### 1.4.3 局部规划
局部规划器用于产生满足运动学约束的无碰撞路径，同时也要保证乘客的舒适性和速度安全性指标。为了降低问题的复杂度，通常将其分解为路径规划和速度生成个步骤完成。

**基于采样的规划器**
该方法通过对控制输入进行随机采样从而实现对工作空间的快速探索。
  - 通过对新的目标点进行碰撞检查，而后不断将其加入到已经探索过空间中；
  - 其优势是速度较快，但缺点是产生的路径往往质量较差

**基于变分的规划器**
该方法通过对 泛函 损失函数进行优化，从而获得最优的轨迹(Trajectory)，因此该方法是将轨迹规划和速度规划放到放到一起考虑同时解决的。
  - 其目标方程中包含对碰撞和车辆动力旭二的惩罚：$min_{\delta x}J(x+\delta x)$

**网格(Lattice)规划器**  
网格规划器通过限制机器人的可行动作来对搜索空间进行约束，机器人允许的动作的集合被称为控制集合
  - 通过控制集采样可以形成关于机器人轨迹的网格图，可以进一步通过Dijkstra或A*的方法进行搜索
  - 网格规划器通过限制控制动作可以使其轨迹满足道路结构

**速度生成**
<div align=center><img src=./figs/local_planner_velocity.png width=500></div>


## 1.5 补充阅读材料
  - P. Polack, F. Altche, B. Dandrea-Novel, and A. D. L. Fortelle, “[The kinematic bicycle model: A consistent model for planning feasible trajectories for autonomous vehicles](https://ieeexplore.ieee.org/abstract/document/7995816)” 2017 IEEE Intelligent Vehicles Symposium (IV), 2017.  Gives an overview of the kinematic bicycle model.
  - S. Karaman and E. Frazzoli, “[Sampling-based optimal motion planning for non-holonomic dynamical systems](http://amav.gatech.edu/sites/default/files/papers/icra2013.Karaman.Frazzoli.submitted.pdf),” 2013 IEEE International Conference on Robotics and Automation, 2013. Introduces the RRT* algorithm as an example of sampling-based planning.
  - N. Ratliff, M. Zucker, J. A. Bagnell, and S. Srinivasa, “[CHOMP: Gradient optimization techniques for efficient motion planning](https://kilthub.cmu.edu/articles/journal_contribution/CHOMP_Gradient_Optimization_Techniques_for_Efficient_Motion_Planning/6552254/1),” 2009 IEEE International Conference on Robotics and Automation, 2009. Introduces the CHOMP algorithm as an example of applying calculus of variations to planning.
  - M. Pivtoraiko, R. A. Knepper, and A. Kelly, “[Differentially constrained mobile robot motion planning in state lattices](https://www.ri.cmu.edu/pub_files/2009/3/ross.pdf),” Journal of Field Robotics, vol. 26, no. 3, pp. 308-333, 2009. Introduces the state lattice planning method.