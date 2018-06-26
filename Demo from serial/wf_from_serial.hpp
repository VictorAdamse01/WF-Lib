// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef WF_FROM_SERIAL_HPP
#define WF_FROM_SERIAL_HPP

#include "hwlib-ostream.hpp"
#include "wireframe-library/wireframe.hpp"

//a triangle arrives in 37 chars,
//first 36 are the 9 floats (3 times (x,y,z)) since a float is 4 bytes/chars
//the final char is the delimiter byte to indicate if it is the final triangle
union triangle{
    float f[9];
    char c[36];
    unsigned long l;
};

union starter{
    char c[4];
    unsigned long l;
};

class wf_from_serial : public wflib::wireframe {
private:
    hwlib::cin_using_uart_getc stream;

public:
    wf_from_serial(wflib::display_writer & display, wflib::vertex position = wflib::vertex(0,0,0)):
        wireframe(display,position)
    {}

    void Read(hwlib::glcd_oled &display);
};


#endif //WF_FROM_SERIAL_HPP
