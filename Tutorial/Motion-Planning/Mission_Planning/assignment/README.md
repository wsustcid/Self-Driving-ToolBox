<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-12 22:17:42
 * @LastEditTime: 2021-11-25 11:15:01
-->

# Module 3 Graded Quiz
1. Which best describes the mission underlying an autonomous vehicle's mission planner?
- [ ] Compute the optimal vehicle behaviour for a given driving scenario
- [x] Navigate a road network to the desired destination from the ego vehicle's position
- [ ] Generate an optimal, collision-free path to the required destination

2. Which of these are examples of good values to optimize in a mission planner's objective function?
- [x] Distance travelled
- [ ] Distance from obstacles
- [x] Time to destination
- [ ] Deviation from the speed limit

3. What is a graph in the mission planning context?
- [ ] A plot of the car's throttle and steering actuation while executing a driving mission
- [ ] A chart of the different speeds reached during different road segments in a road network
- [x] A discrete mathematical structure used for representing the road network
- [ ] None of the above

4. True or false, Breadth-First Search (BFS) will explore the graph using a "last-in-first-out" data structure known as a stack.
- [ ] True
- [x] False

5. True or false, Breadth-First Search (BFS) will always find the optimal (shortest) path in an unweighted graph.
- [x] True
- [ ] False

6. True or false, Breadth-First Search (BFS) will always find the optimal (shortest) path in a weighted graph.
- [ ] True
- [x] False

7. In these graph search algorithms, what is the main purpose of keeping track of a "closed" set of graph vertices?
- [x] It allows us to avoid getting stuck in cycles
- [ ] It allows us to know how much of the graph has been searched
- [ ] It helps us keep track of which vertices we still need to search

8. What is a min heap data structure?
- [ ] A sorted list of autonomous driving mission priorities for a given driving scenario
- [x] A data structure that stores keys and values, and sorts the keys in terms of their associated values, from smallest to largest.
- [ ] A data structure that stores keys and values, and sorts the keys in  terms of their associated values, from largest to smallest. 
- [ ] A block of memory useful for dynamic memory allocation

9. True or false, in a min heap, the root of the heap (the first element) contains the node with the smallest value.
- [x] True
- [ ] False

10. In Dijkstra's algorithm, suppose during the process of adding vertices to the open set, we come across a vertex that has already been added to the open set. However, this time we have found a lower cost to reach this vertex than is presently stored in the open set's min heap. What should be done?
- [ ] Close the vertex, as we have now seen it twice during exploration
- [x] Update the cost of that vertex in the open set's min heap
- [ ] Nothing, as this is impossible under Dijkstra's algorithm
- [ ] Nothing, as the vertex is already in the open set

11. What is a search heuristic in the context of mission planning?
- [ ] A method that allows the autonomous vehicle to quickly identify obstacles in its surroundings
- [x] An estimate of the remaining cost to reach the destination
- [ ] Something that helps the autonomous vehicle efficiently change the autonomus driving mission depending on the situation
- [ ] A tool that autonomous vehicle's use for quickly identifying traffic congestion at a given intersection

12. Suppose I have a vertex at location (2.0, 3.0) and another at location (4.0, 5.0). What is the Euclidean distance between these two points (to three decimal places)?
- [x] 2.828

13. True or false, an admissable heuristic to the A* search algorithm will never underestimate the cost to reach the goal vertex.
- [ ] True
- [x] False

14. Is the heuristic function h(v) = 0 an admissible heuristic?
- [ ] No, as in this case A* degenerates into Dijkstra's
- [ ] Yes, and in this case A* degenerates into BFS
- [ ] No, as in this case A* degenerates into BFS
- [x] Yes, and in this case A* degenerates in DIjkstra's

15. True or false, the min heap in A* contains the sum of the cost to reach each vertex plus the estimate of the cost to reach the destination from said vertex, according to the search heuristic.
- [x] True
- [ ] False


