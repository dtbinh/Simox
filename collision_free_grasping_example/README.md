#Grasp Planner Evaluator

##Introduction
This is a simple example illustrating the capabilities of Simox, in a clustered environment, along with some functionalities for evaluating a grasp.

It is based on the Simox example *GrapPlanner* (`GraspPlanning/examples/GraspPlanner`).

##Installation
First you have to install the modified version of Simox from
https://github.com/nrontsis/Simox/tree/F%231_Collision_Free_Grasping

Compile and run with
```
mkdir build && cd build
cmake .. && make
cd bin
./GraspPlannerEvaluator
```

##Parameters
The program accepts the following parameters
1. scene
2. robot
3. object
4. endeffector
5. preshape

The robot and object definitions are included (or referenced) in the scene file. The parameters specify which robot and object of the ones that are included in the scene file should be chosen.
