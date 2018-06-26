This is a Clion project I made that uses my library in combination with hwlib to draw a wireframe on an oled-display.

I made the class "hwlib_display_writer" that inherits from "display_writer". 
this class receives pixel coordinates as output from the wireframe library, and writes them on the oled via hwlib.

In main.cpp the oled and some buttons are setup via hwlib. 
Then the wireframe is created by simply creating an object "wireframe" and inserting values.
each line is added as a set of 2 vertices (3d points(x,y,z))

then the wireframe is drawn on the screen.
buttons can be used to rotate the wireframe and change the rotation axis.
