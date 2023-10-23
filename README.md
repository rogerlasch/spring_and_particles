# Spring Simulation - Practical Example

This is a project simulating particles connected by springs, developed as a practical example to understand the behavior of springs in a physical system. The project provides C++ source code that demonstrates how to create particles, apply forces, calculate spring forces, and play sounds for each particle.

## Introduction

This project was developed as part of a study on spring simulations and physical systems. The main motivation is to provide a practical and didactic example for understanding how springs work in a simulated system. You can use this code as a foundation to further explore the subject and customize simulation parameters to suit your needs.

## Prerequisites

- C++ compiler compatible with C++20 or higher, or with support for std::format.

- FMOD library (for sound playback).

## Project Structure

The project consists of four header files:


- `G_START.h`: This file contains the `G_STARTER` structure that configures the execution environment, functions for generating timestamps, input values, and log recording.

- `PARTICLE.h`: Here, you'll find the `particle` class that represents the particles in the simulation. Each particle has an identifier, mass, position, velocity, forces, and the ability to play sounds.

- `SOUND.h`: This file contains functions for initializing the FMOD sound system.

- `SPRING.h`: It contains the `Spring` structure that represents a spring, including information about the connected particles, rest length, stiffness, and damping.

- `vector3d.h`: Here, you'll find the definition of the `vector3d` class used to represent three-dimensional vectors and perform operations with them.

## Configurable Parameters

You can customize the simulation by adjusting the following parameters:

- Mass.

- Position.

- Spring length.

- Spring stiffness.

- Spring damping.

- Gravity.

- Time step.

- Number of iterations.

## Compilation

- Compile the program with your favorite compiler. If the executable doesn't work, remember that GitHub sometimes corrupts binary files for reasons that have not been identified yet. If you have Visual Studio tools installed, simply open a developer prompt, navigate to the folder, and run the `build.bat` script.

## Interrupting the Simulation

- You can stop the simulation at any time by pressing `Ctrl+C`.

## Sound and Results

### Sound

Each particle has its own sound. Sound spatialization is done using FMOD.

- `p1.ogg`: Corresponds to the first configured particle.

- 
`p2.ogg`: Corresponds to the second configured particle.
### Results

When the simulation ends, either by reaching the end or being interrupted with `Ctrl+C`, a log file is generated. This log displays, in seconds, the stage of the simulation, along with the particle's ID, position, and corresponding velocity.

Please note that only dynamic particles are recorded, as static particles remain stationary.

## A Simple Pendulum

Now, let's simulate a simple pendulum, where one of the particles is anchored while the other moves.

Run the application and enter the following parameters when prompted:

### Particle 1:

- Mass: 0

- X: 50

- Y: 50

- Z: 50

### Particle 2:

- Mass: 5

- X: 60

- Y: 50

- Z: 50

### Spring:

- Length: 5

- Stiffness: 50

- Damping: 0.67

### Environment Properties:

- Gravity: -9.81

Time Step: 0.2

Iterations: 250

### Execution

After configuring the parameters above, observe how particle 2 is pulled due to the spring tension and the force of gravity. The sound, resembling jingle bells, moves from side to side until it gradually centers as the pendulum loses velocity. You can check the particle's position in the log after the execution is complete.

## Thank You

If you enjoyed this project, please consider giving a star to the repository. Feel free to contact me at rogerlasch@gmail.com for feedback or suggestions. Your opinion is valuable to me.
