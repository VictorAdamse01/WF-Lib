// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "wireframe-library/wireframe.hpp"
#include "wf_from_serial.hpp"
#include "hwlib_display_writer.hpp"
#include <cstdio>

int main() {
    //kill watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;

    //setup oled
    auto scl = hwlib::target::pin_oc(1,13);
    auto sda = hwlib::target::pin_oc(1,12);
    auto i2c = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);
    auto display = hwlib::glcd_oled(i2c, 0x3c);
    display.clear(hwlib::buffering::unbuffered);

    //setup buttons
    auto button1 = hwlib::target::pin_in(1,27);
    auto button2 = hwlib::target::pin_in(3,8);
    uint8_t button_timer;

    wflib::rendermode r_mode = wflib::rendermode::parallel;
    wflib::axis rotate_axis = wflib::axis::y;

    //display writer to pass the output from the wireframe to the actual oled via hwlib
    hwlib_display_writer wf_display(display);

    //the wireframe object
    wf_from_serial serial_wf(wf_display);

    //start waiting for data from the serial bus
    serial_wf.Read(display);

    //center the wireframe object to the middle of the screen
    serial_wf.Center();

    //rescale the wireframe to better fit the screen
    serial_wf.Scale_towards(35);

    //loop that rotates and redraws the wireframe on the screen
    for(;;){
        display.clear(hwlib::buffering::buffered);


        if(button_timer <= 0){
            //change rendermode when button 1 is pressed
            if(button1.get()){
                if(r_mode == wflib::rendermode::parallel){
                    r_mode = wflib::rendermode::perspective;
                }else{
                    r_mode = wflib::rendermode::parallel;
                }
                button_timer = 10;
            //change rotate axis when button 2 is pressed
            }else if(button2.get()){
                if(rotate_axis == wflib::axis::x){
                    rotate_axis = wflib::axis::y;
                }else if(rotate_axis == wflib::axis::y){
                    rotate_axis = wflib::axis::z;
                }else{
                    rotate_axis = wflib::axis::x;
                }
                button_timer = 10;
            }
        }else{
            button_timer--;
        }

        //rotate wireframe
        serial_wf.Rotate(0.1,rotate_axis);

        //draw wireframe
        serial_wf.Draw(r_mode);


        display.flush();
    }
}