// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include <hwlib.hpp>
#include "wf_from_serial.hpp"

void wf_from_serial::Read(hwlib::glcd_oled &display){
    starter s;
    for(uint8_t i = 0; i < 4; i++){
        while(!stream.char_available()){
            hwlib::wait_ms(1);
        }
        s.c[i] = stream.getc();
    }
    auto n_tris = uint16_t(s.l);
    display.write(hwlib::location(n_tris, 1), hwlib::buffering::unbuffered);
    for(uint8_t i = 0; i < n_tris; i++) {
        triangle tri;
        for(uint8_t j = 0; j < 36; j++) {
            while (!stream.char_available()){
                hwlib::wait_ms(1);
            }
            char c = stream.getc();
            tri.c[j] = c;
            if (j == 35) {
                Add_triangle(wflib::vertex(tri.f[0], tri.f[1], tri.f[2]),
                             wflib::vertex(tri.f[3], tri.f[4], tri.f[5]),
                             wflib::vertex(tri.f[6], tri.f[7], tri.f[8]));
                display.write(hwlib::location(i, 1), hwlib::buffering::unbuffered);
            }
        }
    }
}