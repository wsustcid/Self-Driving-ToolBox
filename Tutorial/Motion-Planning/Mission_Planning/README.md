<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-09-27 09:13:42
 * @LastEditTime: 2021-11-25 10:46:54
-->
- [3. 驾驶环境中的任务规划](#3-驾驶环境中的任务规划)
  - [3.1 创建路网地图](#31-创建路网地图)
  - [3.2 Dijkstra](#32-dijkstra)
  - [3.3 A*](#33-a)
    - [3.3.1 启发式搜索](#331-启发式搜索)
    - [3.3.2 算法描述](#332-算法描述)
    - [3.3.3 考虑其他评价指标](#333-考虑其他评价指标)
  - [4. 补充阅读材料](#4-补充阅读材料)

# 3. 驾驶环境中的任务规划
在本节中，我们将讨论无人驾驶中的任务规划。首先我们回顾一下自动驾驶任务的目标：为自动驾驶车辆找到一条从起点到达终点的最优路线，在寻找过程中，低层级的细节信息，比如道路规则以及其它智能体都被剥离出来等待后续任务处理。任务规划可以看做是无人驾驶问题中最高层级的规划问题，因为其要规划的尺度空间是千米级的，且无需关注低层级的约束，比如障碍物约束、或车辆动力学约束。但任务规划器需要关注路网的一些信息，比如速度限制、道路长度等。


## 3.1 创建路网地图
**图的概念**  
我们使用图的概念来对路网进行表示。图由点集$V$和边集$E$组成：
  - 在任务规划器中，V中的每一个点代表路网中的一个给定点（通过对路网离散采样获得）
  - 边集代表由路网中的两点连接成的一段道路片段 （根据道路规则对采样点进行连接）
  - 更进一步的，我们使用有向图来表示某些道路的单向通行要求

基于此定义，一系列连续的边就构成了路网中从某点到另一点的路径。
<div align=center><img src=./figs/graph_def.png width=400></div>

**BFS**  
我们可以使用广度优先搜索来对无权图的最优路径进行搜索（假设每段路径距离相同）
<div align=center><img src=./figs/bfs.png width=400></div>


## 3.2 Dijkstra
本节我们主要关注如何解决加权图的路径搜索问题，因为在实际任务中，道路的长度、交通情况、速度限制以及天气情况等都会影响一段道路上的遍历开销，我们使用Dijkstra算法来解决此问题。
<div align=center><img src=./figs/dijkstra.png width=400></div>

 - Dijkstra和BFS的主要区别在于不再使用队列存储Open Set，而是使用最小堆进行存储。（最小堆按照和key对应的value对key进行排序）
 - 基于最小堆，Dijsktra对顶点的处理顺序不再是基于加入顺序，而是基于每个顶点累加的cost
 - 还有一个最主要的操作就是cost的更新：当我们发现一个顶点已经存在于open Set中，但从当前节点出发路径更短，则更新此节点的累加cost


## 3.3 A*
上节提到使用Dijkstra解决了有向图的搜索问题，但Dijkstra几乎要搜索图中所有的边，这个小规模地图中是可以接受的，但如果扩展到城市级别的路网地图，效率将十分低下。本节我们探讨使用启发式搜索的方式来进一步提升搜索效率。

### 3.3.1 启发式搜索  
启发式搜索是指对于从图中任意给定顶点距离终点的剩余花费的估计。我们当然无法知道准确的值，否则我们就可以直接知道答案了，因此我们需要能够快速计算且合理的估计。最简单的方式是直接使用两点间的直线距离/欧几里得距离
 $$ h(v) = || t-v || $$
<div align=center><img src=./figs/euclidean_heuristic.png width=400></div>

  - 注意这个估计值永远都是underestimate的，因为这是两点间的最短距离，这也是启发式搜索的基本要求。
  - 满足此要求的估计被称作 admissible heuristics

### 3.3.2 算法描述
A* 算法与Dijkstra算法整体流程基本相似，具体不同之处为图中标蓝部分
<div align=center><img src=./figs/A_star.png width=400></div>

  - 对于在最小堆中排序的衡量指标，不在仅仅使用从起点到当前节点累加花费，而是再多叠加一个该节点距离终点的启发值
  - 这种修改可以使得整个搜索过程优先搜索最有可能包含在最优路径中的节点

### 3.3.3 考虑其他评价指标
在之前对于路径开销的度量中，我们仅仅使用距离作为唯一考量指标，但其实还有很多其他因素需要考虑：
  - 比如交通情况、速度限制、以及天气状况等
  - 相比于使用距离，使用时间可以很好的将这些因素纳入考虑
  - 因此我们可以将距离权重替换为时间估计，这时admissible heuristics可以用直线距离除以最大速度，这个便是完成时间的下限值，因为不管在何种天气或交通状况下，汽车都不能超过其限速。

<div align=center><img src=./figs/time_heuristic.png width=400></div>


## 4. 补充阅读材料
  - [1]. Steven M Lavalle, Planning Algorithms,  2006, Cambridge University Press. Chapter 2 covers discrete planning over graphs including Dijkstra's and A*.
  - [2]. N. J. Nilsson, “Artificial intelligence: A modern approach,” Artificial Intelligence, vol. 82, no. 1-2, pp. 369–380, 1996. Read Chapters 3.4-3.5 for an overview of search algorithms in graphs.

