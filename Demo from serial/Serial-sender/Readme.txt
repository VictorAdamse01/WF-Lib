This is a Clion project I made to read an STL file and send it to the arduino on COM2.

I used the windows "Open file" and "Read file" functions to send the data over the serial COM2 port.
The program asks for a filename. the file is then read.

STL files have a header, with a name and a 32bit integer that tells how many triangles are in the file.
the STL file is read as an array of chars (8 bits).
It takes the 4 characters that tell how many triangle are in the file and send them to the arduino.

Each triangle in the STL file is made of 50 chars, for the wireframe we only need the 3 points(36 chars, 4 for each float) (9 floats, three times (x,y,z)
So we are cutting out only these chars and sending them to the arduino.

this way only the neccesary data is send instead of the entire file, this saves time since the serial port is not super fast.