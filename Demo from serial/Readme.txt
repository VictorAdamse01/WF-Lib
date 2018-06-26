This is a Clion project I made that uses my library in combination with hwlib and the serial input project.

the serial input project needs to send the data of an STL file for this application to show anything on the arduino

I made the class "hwlib_display_writer" that inherits from "display_writer". 
this class receives pixel coordinates as output from the wireframe library, and writes them on the oled via hwlib.

I made the class "wf_from_serial" that inherits from "wireframe" this class has a "Read" function that when called
will wait on input data to build a wireframe. I used the hwlib::istream to read input characters from the serial port.
it is read character by character. first it receives 4 bytes that tell how many triangle there are comming.
Then it reads 36 bytes for each triangle. all these bytes are stored in a union of 36 chars and 9 floats. 
So when all chars of a triangle are received they can be used as floats to call the "Add_triangle"
function of the library.

In main.cpp i made an oled and some buttons. and created a wf_from_serial that then waits on data from the serial port.
after that it will rotate on the screen and the buttons can be used to change the rendermode, and the rotation axis.