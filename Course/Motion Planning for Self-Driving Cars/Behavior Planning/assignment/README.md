<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-13 21:25:21
 * @LastEditTime: 2021-10-14 15:01:48
-->

# Module 5 Graded Quiz
1. True or false, behavioural planning does not need to take dynamic obstacles into consideration, as it is too low level and should be handled by the local planner.
- [ ] True
- [x] False

2. As an autonomous vehicle approaches an intersection, which of the following best describes the role of a behavioural planner?
- [ ] Plan a path to the required goal state subject to static/dynamic obstacles and kinodynamic constraints
- [ ] Navigate through the map to find the most efficient path to the required destination.
- [x] Plan when and where to stop, how long to stay stopped for, and when to proceed through the intersection
- [ ] Determine the throttle angle, brake, and steering angle required to track the reference path through the intersection

3. What is the primary output of a behavioural planning module?
- [x] The driving maneuver to be executed in the current environment
- [ ] A sequence of waypoints that correspond to a feasible, collision-free trajectory
- [ ] The throttle, brake, and steering angle values required for tracking the reference trajectory
- [ ] The sequence of road segments to be traversed to reach the destination

4. Which of the following are common inputs to the behavioural planner?
- [x] A mission plan
- [x] High definition roadmap
- [x] Localization information
- [ ] A default path in the current lane to follow

5. Which of the following are a disadvantage of using finite state machines for behavioural planning?
- [ ] As the number of states decreases, it becomes more computationally complex to evaluate state transitions
- [x] As the number of states increases, it becomes increasingly complicated to define all possible transition conditions
- [ ] Finite state machines can only handle uncertainty when there are many states available
- [ ] None of the above

6. Which portion of the intersection best describes when the ego vehicle is on the intersection?
- [x] The interior of the intersection
- [ ] The lane exiting the intersection
- [ ] The lane preceding the intersection
- [ ] None of the above

7. Which of the following can increase the size of the "approaching", "at", and "on" zones of an intersection?
- [ ] The size of the ego vehicle
- [ ] The number of dynamic obstacles present
- [x] The size of the intersection
- [x] The speed of the ego vehicle

8. For a 2-lane, 4-way intersection, which of the following maneuvers are absolutely required?
- [x] Decelerate to stop
- [ ] Merge to lane
- [ ] Track speed
- [ ] Stop

9. For this question, let us use our finite state machine discussed in Module 5 Lesson 2. Suppose the car has entered the "Stop" state while at the intersection. Which of the following is the correct transition condition for the vehicle to enter the "Track Speed" state?
- [ ] Ego.Position == Approaching
- [ ] Ego.Velocity >= 0
- [x] Ego.StopTime >= 3.0 sec
- [ ] Ego.StopTime < 3.0 sec
<div align=center><img src=./9.png width=600></div>

10.  For this question, let us use our finite state machine discussed in Module 5 Lesson 2. Suppose the car has entered the "Track speed" state before reaching any zone of the intersection. Which of the following is the correct transition condition for the vehicle to enter the "Decelerate to Stop" state?
- [ ] Ego.Position != Approaching
- [ ] Ego.StopTime < 3.0 sec
- [x] Ego.Position == Approaching
- [ ] Ego.Velocity >= 0
<div align=center><img src=./10.png width=600></div>

11. Which of the following are the key aspects of dynamic objects that we focus upon in behavioural planning?
- [x] Time to collision
- [ ] Distance to collision point
- [x] Distance to dynamic object
- [ ] Maximum velocity

12. Which of the following best describes the "Follow Leader" maneuver?
- [ ] In a safe and comfortable manner, decelerate to a complete stop to avoid the leading vehicle
- [ ] When a lead vehicle is performing a lane change, we wait until it is safe and follow them into the adjacent lane
- [ ] Accelerate to the speed of the lead vehicle, passing the lead vehicle if they are below our reference speed
- [x] Follow the speed of, and maintain a safe distance from the lead vehicle

13. True or false, using the state machine developed in L3, when the ego vehicle is in the "Stop" state when in the presence of dynamic obstacles, it should transition to the "Track Speed" state after 3 seconds have elapsed.
- [ ] True
- [x] False

14. True or false, using the state machine developed in L3, suppose the ego vehicle is "at" the intersection, and is currently in the "Stop" state and 3 seconds have elapsed. Suppose the only dynamic obstacle is "on" the intersection has a heading of 180 degrees relative to the ego heading, and suppose the ego vehicle intends to drive straight. Which state will the state machine transition to?
- [ ] Follow Leader
- [ ] Stop
- [x] Track Speed
- [ ] Decelerate to Stop

15. True or false, using the state machine developed in L3, suppose the ego vehicle is "at" the intersection, and is currently in the "Stop" state and 3 seconds have elapsed. Suppose the only dynamic obstacle is "on" the intersection has a heading of 180 degrees relative to the ego heading, and suppose the ego vehicle intends to turn left. Which state will the state machine transition to?
- [x] Stop
- [ ] Track Speed
- [ ] Decelerate to Stop
- [ ] Follow Leader

16. Which of the following are disadvantages of using a single state machine to handle multiple scenarios?
- [x] Rule explosion when adding new scenarios to the state machine
- [x] Complicated to create and maintain all possible cases
- [x] The amount of computation time required at each step
- [ ] Not able to handle a small set of scenarios

17. True or false, an example of a hierarchical state machine in the behavioural planning context involves superstates representing each potential scenario and substates representing the maneuvers to be handled in each scenario.
- [x] True
- [ ] False

18. Following the hierarchical state machine introduced in Module 5 Lesson 4, if we are exiting the intersection and we are currently in the "Intersection Scenario" superstate, which substates of the "Intersection Scenario" will allow us to change to a different superstate?
- [ ] Follow Leader
- [ ] Stop
- [ ] Declerate to Stop
- [x] Track Speed
<div align=center><img src=./18.png width=600></div>

19. True or false, the hierarchical state machine is immune to the effects of rule explosion.
- [ ] True
- [x] False

20. True or false, the hierarchical state machine limits the amount of computation time at each time step by restructuring the search space more efficiently.
- [x] True
- [ ] False

21. Which of the following are some issues with the state machine approaches presented in Lessons 1-4?
- [ ] State machines are unlikely to handle situations that have not been explicitly programmed
- [ ] The state machines discussed are only able to handle noise in very limited situations
- [x] The number of hyperparameters required increases as the behaviours get more complex, and inputs get more noisy
- [ ] There is no method to handle multiple scenarios when using state machines

22. What is an advantage of rule based systems over state machines?
- [ ] Rule based systems can handle multiple scenarios
- [x] Rule based systems do not duplicate transitions, as rules can apply throughout significant portions (or all of) the ODD
- [ ] Rule based systems do not require as much attention as state machines do, as rules do not impact one another
- [ ] None of the above

23. True or false, fuzzy logic systems are more robust to environmental noise than traditional discrete systems, such as a finite state machine.
- [x] True
- [ ] False

24. True or false, reinforcement learning involves clustering unlabeled data to inform the behavioural planner on the best course of action in each scenario.
- [x] True
- [ ] False

25. Which of the following are some of the shortcomings of reinforcement learning approaches for behavioural planning?
- [x] It is challenging to perform rigorous safety assessment or safety guarantees of learned systems, as they are largely black boxes
- [ ] Reinforcement learning do not generalize well to scenarios that weren't explicitly programmed
- [ ] The model simplicity used for reinforcement learning means the results transfer poorly to real-world scenarios
- [ ] Reinforcement learning is unable to handle continuous variables, such as the distance to a dynamic obstacle, and these are commonly used in behavioural planning
