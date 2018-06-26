## Wireframe Library (arduino)

this is a library for drawing wireframes on some sort of screen. A wireframe can be created in a few different ways by adding vertices and triangles.
The library is meant for use with an arduino or some sort of microcontroller, but can be used for other things.

This library does not write its output directly to the hardware. I used the HWLIB library for this
The demo project I created is meant for use in combination with HWLIB. 
https://github.com/wovo/hwlib


## Functionalities

- Add vertices/edges/triangles to create a wireframe.
- Rotate the wireframe.
- Scale the wireframe.
- Scale the wireframe to fit a certain distance.
- Center the wireframe.


## using the library

1. create your own class that inherits from "display_writer" and override the Write() function. This is where you write your own code that will do something with the outcoming pixels.
See "hwlib_display_writer" for reference.

2. create a wireframe object, and give a reference to your own display_writer as a parameter.

3. add edges/triangles to your wireframe by using:
  Add_edge_by_vertices(), Add_triangle()
  
4. Draw the the wireframe with the Draw() function.

5. You can use the other functions off the "wireframe" class to adjust your wireframe to your needs.
