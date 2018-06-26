#ifndef HWLIB_DISPLAY_WRITER_HPP
#define HWLIB_DISPLAY_WRITER_HPP

#include "wireframe-library/wireframe.hpp"
#include "hwlib.hpp"

class hwlib_display_writer : public wflib::display_writer{
private:
    hwlib::window & display;
public:
    explicit hwlib_display_writer(hwlib::window & display):
            display(display)
    {}

    void Write(int16_t x, int16_t y) override {
        display.write(hwlib::location(x,y),hwlib::black,hwlib::buffering::buffered);
    }
};

#endif //HWLIB_DISPLAY_WRITER_HPP
