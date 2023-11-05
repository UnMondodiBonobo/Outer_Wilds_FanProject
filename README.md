# Outer_Wilds_FanProject
Unreal Engine 5 exercise project inspired by Mobius Interactive's Outer Wilds

Outer Wilds fan project is heavily inspired by Mobius Interactive’s Outer Wilds game 
released by Annapurna and it’s something I’m currently working on since I was bewitched 
by the game itself and by the freedom given to the player to explore and navigate this 
fantasy solar system. 

Implementation:

  1. I first started implementing the planet logic, which is simulated by physics laws but 
not entirely like the solar system because it would require a lot of tuning to get right. 
The first step was to create a mediator actor by trying to implement the mediator 
design pattern itself: the Solar System Mediator registers and unregisters planet 
structure couples with a logic of pivot-influenced planets like Sun-Earth, Earth-Moon, 
and so on. It has a Map of function pointers that triggers the right function 
depending on the planet class passed to it, then it applies gravitational forces and 
tangential velocity based on the calculations done by the GravityUtilsFunctionLibrary 
to keep the influenced planet of the couple on a circular trajectory around its pivot.

  2. The AtmosphereGravityComponent, on the other hand, allows all objects that 
implement a specific interface (GravitationalObjectInterface) to be pulled to the 
planet (or whatever object has the AtmosphereGravityComponent) applying the 
calculations made by the GravityUtilsFunctionLibrary, the same used by the 
mediator. The gravity function library also has a gravitational constant which is offset 
proportionally to the difference between the masses of the game planets and 
realistic planet masses, which were impossible to control due to their very large 
mass scale. For this reason, the gravitational constant is very large, and it is done to 
balance this difference between planet masses.

  3. Recently I started implementing the spaceship (which implements the 
GravitationalObjectInterface) using Unreal Engine Enhanced Input Component, 
Mapping contexts, and Input Actions to obtain a versatile input system that does not 
need to be refactored every time in the code (all inputs are handled in blueprint, and 
they add forces to the spaceship as thrusters
