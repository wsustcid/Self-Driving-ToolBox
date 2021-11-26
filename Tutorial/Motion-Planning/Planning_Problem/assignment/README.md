<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-12 15:29:22
 * @LastEditTime: 2021-11-18 19:42:55
-->

# Module 1 Graded Quiz
1. Which are examples of common scenarios in the autonomous driving motion planning problem? 
- [ ] A. Left and right turns 
- [ ] B. Driving up a hill 
- [ ] C. Lane changes 
- [x] D. A & C 

2. What are some examples of dynamic obstacles?
- [ ] A. Trees 
- [ ] B. Cyclists 
- [ ] C. Cars 
- [ ] D. Boulevards
- [x] E. B & C

3. True or false, the autonomous driving mission takes pedestrian behaviour into consideration.
- [ ] True
- [x] False

4. True or false, "Staying Stopped" is a maneuver that is useful for handling traffic light controlled intersections.
- [x] True
- [ ] False

5. Which of these are reasons for decomposing motion planning into a hierarchy of optimization problems?
- [x] A. More computationally efficient 
- [x] B. Can tailor each optimization problem to specific level of abstraction
- [ ] C. Generates higher-quality solutions than solving the problem in its entirety
- [ ] D. None of the above

6. True or false, instantaneous curvature is the inverse of the instantaneous turning radius at a point on a curve.
- [x] True
- [ ] False

7. Static obstacles constrain...
- [x] The locations the car can occupy
- [ ] The turning radius of the car
- [ ] The car's lateral velocity
- [ ] The car's longitudinal velocity

8. A leading vehicle in the ego vehicle's lane constrains...
- [ ] The car's lateral velocity
- [x] The car's longitudinal velocity
- [ ] The car's maximum jerk
- [ ] The turning radius of the car

9. True or false, the time gap is the amount of time that it would take for the ego vehicle to reach the current position of its leading vehicle. 
- [x] True
- [ ] False

10. True or false, the friction ellipse is always a tighter constraint than the comfort rectangle.
- [ ] True
- [x] False

11. To generate the shortest path to a point, we need to minimize...
- [ ] Angular velocity
- [x] Arc length
- [ ] Curvature

12. The integral of difference (IOD) term in a planning objective function can be used to...
- [ ] A. Improve path smoothness
- [ ] B. Track a reference velocity profile
- [ ] C. Track a reference path
- [x] D. B & C

13. True or false, jerk is the derivative of acceleration with respect to time.
- [x] True
- [ ] False

14. True or false, maximizing jerk increases the comfort of our planned trajectory.
- [ ] True
- [x] False

15. The _____ at each point in the path constrains the velocity that can be driven at that point, due to the lateral acceleration constraints.
- [ ] X position
- [x] Curvature
- [ ] Heading
- [ ] Y position

16. True or false, mission planning focuses on map-level navigation from the ego vehicle's current position to a final destination.
- [x] True
- [ ] False

17. What are some examples of the inputs a finite state machine might take in the context of behaviour planning for autonomous driving?
- [x] Traffic light transitions
- [ ] The number of passengers in the ego vehicle
- [x] Pedestrian locations
- [x] Vehicle positions

18. True or false, reinforcement learning relies on interacting with an environment during the learning process.
- [x] True
- [ ] False

19. What is a drawback of using a sampling-based method for path planning?
- [x] A. If run for a minimal number of iterations, it can generate poor quality paths
- [ ] B. It is often slow at exploring the workspace compared to other methods
- [ ] C. Sampling based methods are often computationally intractable
- [ ] D. None of the above

20. True or false, a conformal lattice planner selects goal points ahead of the car that are laterally offset from the centerline of the road, plans paths to each goal point, then selects the best collision-free path according to some objective function.
- [x] True
- [ ] False


