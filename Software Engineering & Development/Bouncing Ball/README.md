## Glowscript Bouncing Ball Project  
This project can be found at: https://www.glowscript.org/#/user/bauer0313/folder/MyPrograms/program/BouncingBallProject

Programming using Glowscript VPython (https://www.glowscript.org/docs/VPythonDocs/index.html)

Physics Project: Bouncing a ball (a simple warm up application)  
In this project you will create a simple ball in 3D and drop it from a specific height above a floor. Recalling the simple equations of physics for the movement of bodies under a gravity.  
𝑝1=𝑝0+𝑣0𝑡+12𝑎0𝑡2 , 𝑣1=𝑣0+𝑎0𝑡  

Note in this simple project, the acceleration due to gravity is constant and directed down. Each p represents the balls position in 3D so it is a point that can be represented as a VPython 3D vector. This is also true of the velocity (v). You can define the acceleration a (also a 3D vector) something like a=vector(0.0,-C,0.0) where C is a small value such as .001 and the initial value for velocity v to be velocity(0.0,0.0,0.0).  

Your project is really just a simple loop where you update the position and velocity vectors each iteration using some value for t. Start with t=.1 and modify it to make the simulation “look” right. Also we can simulate the reduction of the height of the bounce, resulting from energy loss when contacting with the table, by multiplying the velocity by .9 or there about. In order to get the ball to actually stop you need to add code to halt the process. There are various methods for stopping the animation.  

See https://www.glowscript.org/docs/VPythonDocs/vector.html for vector operations in VPython.
