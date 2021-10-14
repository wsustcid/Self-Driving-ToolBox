<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-13 21:33:37
 * @LastEditTime: 2021-10-14 17:16:19
-->

# Module 6 Graded Quiz

1. True or false, a kinematic model gives the equations of motion for our robot, while disregarding the impacts of mass and inertia.
- [x] True
- [ ] False

2. True or false, a dynamic model is a model used exclusively for rotating robots.
- [ ] True
- [x] False

3. For the bicycle model, the state of the robot contains which of the following values?
- [ ] Curvature
- [x] X Position
- [x] Y Position
- [x] Heading

4. For this image, assuming each path is of equal length, what input parameter to the bicycle model is being varied across each path?
- [x] Steering Angle
- [ ] Velocity

5. True or false, implementing trajectory propagation recursively is slower than computing the entire sum at each step.
- [ ] True
- [x] False

6. Why is collision checking computationally challenging in exact form?
- [ ] It requires perfect information about the surroundings
- [ ] It requires heavy geometric computation in a continuous domain
- [ ] The problem scales with the number of obstacles in a given scene
- [x] All of the above

7. What is the swath of an autonomous vehicle as it drives along a path?
- [x] The union of all sets of space occupied by the autonomous vehicle as it traverses the path
- [ ] The entire region surrounding an autonomous vehicle that is safe for traversal in a given driving situation
- [ ] The region surrounding an autonomous vehicle that is occupied by static obstacles in a given driving situation

8. Suppose the ego vehicle is currently at the origin, (0.0, 0.0, 0.0), and one of the points in its footprint is at (0.5, 0.5). One point along the ego vehicle's path is (3.0, 2.0, pi/4).  After performing rotation and translation on this footprint point relative to this path point, what is the footprint point's corresponding position?
- [ ] (3.0, 3.0)
- [x] (3.0, 2.707)
- [ ] (3.707, 3.0)
- [ ] (3.707, 2.0)

9. True or false, swath-based collision checking sweeps the ego vehicle's footprint along its path, and checks to see if any obstacles lie within this set of space.
- [ ] True
- [x] False

10. Which of the following is not true about circle based collision checking?
- [ ] It uses the friction circle to estimate how close the ego vehicle can be to nearby obstacles
- [ ] It uses circles to quickly estimate collision points by checking if the distance to an obstacle is less than any circle radius
- [x] It relies on discretizing the path into a sequence of points that the circles can be rotated and translated to
- [ ] It conservatively approximates the vehicle footprint using multiple circles

11. To generate a set of arcs in the trajectory rollout algorithm, which input needs to be varied in our bicycle model?
- [ ] Velocity
- [x] Steering Angle
- [ ] Angular Acceleration
- [ ] Heading

12. What is the objective function used in the trajectory rollout algorithm for determining which trajectory to select from the trajectory set?
- [ ] Minimize the total absolute jerk along the path
- [x] Minimize the distance from end of trajectory to goal
- [ ] Maximize the distance from obstacles along the path
- [ ] Minimize the integral of heading changes along the path

13. True or false, for a fixed velocity, larger steering angles will result in larger curvatures in our bicycle model.
- [x] True
- [ ] False

14. True or false, the trajectory rollout algorithm finds an optimal path to the goal state according to the kinematic model.
- [ ] True
- [x] False

15. True or false, the trajectory rollout planner is always able to find a path to the goal state, if one exists.
- [ ] True
- [x] False

16. True or false, linear velocity is a higher-order term in the kinematic bicycle model.
- [ ] True
- [x] False

17. What is the purpose of dynamic windowing?
- [ ] To allow the trajectory rollout algorithm to see farther ahead into the planning process.
- [ ] To improve the maneuverability of the vehicle when performing trajectory rollout.
- [x] To ensure the angular acceleration and linear acceleration lie below a set threshold

18. Suppose we have a bicycle model travelling at constant velocity v = 1.0 m/s, and length L = 1.0 m. If the time between planning cycles is 0.1 seconds, the previous steering angle delta_ 1 was 0.0 rad, and the current steering angle is 0.5 rad, what is the approximate angular acceleration?
- [ ] 13.12 rad/s^2

19. Suppose we have a bicycle model travelling at constant velocity v = 1.0 m/s, and length L = 1.0 m. If the time between planning cycles is 0.1 seconds, and the previous steering angle delta_ 1 was 0.0 rad. If the maximum angular acceleration is 2.5 rad/s^2, can a path with delta_2 = 0.2 rad be selected this iteration?
- [x] A. Yes
- [ ] B. No

20. Suppose we have a bicycle model travelling at constant steering angle delta = 0.0 rad, and length L = 1.0 m. If the time between planning cycles is 0.1 seconds, the previous velocity was 20.0 m/s, and the current velocity is 20.5 m/s, what is the approximate linear acceleration?
- [ ] 5 m/s^2