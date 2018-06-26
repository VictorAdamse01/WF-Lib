// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include "vertex.hpp"

using namespace wflib;

void vertex::Rotate(float rad,axis rotate_axis){
    float temp;
    if(rotate_axis == axis::x){
        temp = y;
        y = y*cos(rad) - z*sin(rad);
        z = temp*sin(rad) + z*cos(rad);
    }else if(rotate_axis == axis::y){
        temp = x;
        x = z*sin(rad) + x*cos(rad);
        z = z*cos(rad) - temp*sin(rad);
    }else{
        temp = x;
        x = x*cos(rad) - y*sin(rad);
        y = temp*sin(rad) + y*cos(rad);
    }
}

screen_point vertex::Get_screen_space(rendermode r_mode,const uint16_t & screen_width,const uint16_t & screen_height){
    if(r_mode == rendermode::perspective) {
        float f = Distance_from(vertex(0,0,-30)) / (z+40);
        return screen_point(int8_t(screen_width/2+x*f),int8_t(screen_height/2-y*f));
    }
    return screen_point(int8_t(screen_width/2 + x), int8_t(screen_height/2 -y));
}

uint8_t vertex::Distance_from(vertex point = vertex(0,0,0)){
    return uint8_t(sqrt((x-point.x)*(x-point.x)+
                        (y-point.y)*(y-point.y)+
                        (z-point.z)*(z-point.z)));
}

bool vertex::operator== (const vertex & rhs)const{
    return abs(x - rhs.x) < 0.01 && abs(y - rhs.y) < 0.01 && abs(z - rhs.z) < 0.01;
}

vertex vertex::operator-= (const vertex & rhs){
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

vertex vertex::operator+= (const vertex & rhs){
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

vertex vertex::operator+ (const vertex & rhs)const{
    return vertex(x+rhs.x,y+rhs.y,z+rhs.z);
}

vertex vertex::operator- (const vertex & rhs)const{
    return vertex(x-rhs.x,y+-rhs.y,z-rhs.z);
}

vertex vertex::operator*= (const float & rhs){
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}