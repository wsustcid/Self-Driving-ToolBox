<!--
 * @Author: Shuai Wang
 * @Github: https://github.com/wsustcid
 * @Version: 1.0.0
 * @Date: 2021-10-13 20:43:28
 * @LastEditTime: 2021-11-25 17:13:07
-->

# Module 4 Graded Quiz
1. Which of the following best describes an example of a maneuver-based prediction assumption for motion prediction?
- [ ] Certain vehicle models restrict vehicle maneuverability, reducing the prediction space
- [ ] The kinodynamic constraints on a vehicle restricts its potential set of motions
- [ ] The behaviour of other agents on the road reduces the space of potential actions
- [x] The operating domain of a vehicle restricts the number of feasible or probable maneuvers it can take

2. Which of the following best describes an example of an interactions-aware prediction assumption for motion prediction?
- [ ] The kinodynamic constraints on a vehicle restricts its potential set of motions
- [x] The behaviour of other agents on the road reduces the space of potential actions
- [ ] The operating domain of a vehicle restricts the number of feasible or probable maneuvers it can take
- [ ] Engine dynamics are affected by pedestrian motion, restricing the space of potential actions

3. Which of the following are aspects of pedestrian motion?
- [x] Low top speed, but rapid changes in direction and speed are possible
- [ ] They often have designated lanes on roads due to their slower speed
- [x] Potential to leave designated areas unpredictably
- [ ] High top speed, but must obey the rules of the road

4. Which of the following are scenarios for which constant velocity estimation provides a useful estimate?
- [ ] Roundabouts
- [x] Straight roads
- [ ] Turns and curved roads
- [ ] Traffic light controlled intersections

5. Which of the following are issues with constant velocity prediction?
- [x] Ignores regulatory elements
- [ ] Computationally expensive
- [x] Doesn't fully account for vehicle kinodynamics
- [x] Ignores the shape of the road

6. Which of the following are position-based assumptions for map-aware prediction algorithms?
- [x] Vehicles driving down a lane are likely to follow that lane
- [ ] A high-curvature road segment necessitates a slower vehicle speed
- [ ] Stop signs will cause vehicles to decelerate to a complete stop
- [x] Lane changes can be predicted based on the state of the blinker light of a vehicle

7. Which of the following are velocity-based assumptions for map-aware prediction algorithms?
- [x] A yellow light will cause vehicles to reduce their velocity as they approach an intersection
- [x] A high-curvature road segment necessitates a slower vehicle speed
- [x] Stop signs will cause vehicles to decelerate to a complete stop
- [ ] Lane markings enforce constraints on the location of vehicles in the road

8. True or false, the more constraints added to our prediction model, the less generalizable it is to all possible traffic scenarios.
- [x] True
- [ ] False

9. True or false, in the case of the multi-hypothesis prediction approach, the most likely nominal behaviour of a dynamic obstacle based on its state, appearance, and track information is taken as the object's predicted motion.
- [ ] True
- [x] False

10. Which of the following are properties of multi-hypothesis prediction approaches?
- [ ] Can result in ambiguous predictions
- [ ] Provides a maximum likelihood estimate based on the information present in the current traffic scenario
- [x] Provides a probability distribution over nominal predictions based on the state of the environment.
- [x] Offers alternative predictions, allowing for fast replanning in case new information arises

11. At a high level, what best describes the two fundamental steps in computing time to collision?
- [ ] Estimating the first vehicle position, then estimating the other vehicle's velocity
- [ ] Running trajectory rollout to generate potential paths, then checking each path for intersection points
- [x] Compute the location of a collision point along the predicted paths of the dynamic objects, then compute the amount of time to reach said collision point
- [ ] None of the above

12. True or false, the simulation based approach propogates the movement of every vehicle in the scene over a given time horizon into the future, where the state is computed at multiple time steps along the horizon.
- [x] True
- [ ] False

13. In estimation-based approaches, which of the following are some of the common simplifying assumptions used in the swath intersection computation?
- [x] Identifying collision points based on path intersection points
- [x] Estimating spatial occupancy using simple geometric primitives
- [x] Assuming a constant speed profile along an object's predicted path
- [ ] Assuming the objects ignore regulatory elements

14. Suppose two vehicles are approximated with a single circle each. The center of one circle is at (1.0 m, 3.0 m) and the other is at (4.0 m, 2.0 m). If the radius of both collision checking circles is 1.5 m, will a collision be detected?
- [ ] Yes
- [x] No

15. Suppose two vehicles, a leading vehicle and a following vehicle, are moving along a straight line. The center of the leading vehicle is 20 m ahead of the center of the following vehicle. The leading vehicle is moving at 15 m/s, and the following vehicle is moving at 20 m/s. The distance from the center to the front bumper of both vehicles is 2.5 m, and the distance from the center to the rear bumper of both vehicles is 2.5 m. What is the time to collision in this scenario? 
- 3