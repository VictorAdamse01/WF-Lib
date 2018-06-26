// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#include "wireframe.hpp"

using namespace wflib;

void wireframe::Draw(rendermode r_mode){
    for(uint8_t i = 0; i < used_edges; i++) {
        Draw_line(vertices[edges[i].a].Get_screen_space(r_mode,screen_width,screen_height),
                  vertices[edges[i].b].Get_screen_space(r_mode,screen_width,screen_height));
    }
}

void wireframe::Rotate(float rad, axis rotate_axis ){
    for (uint8_t i = 0; i < used_vertices; ++i) {
        vertices[i]-=position;
        vertices[i].Rotate(rad,rotate_axis);
        vertices[i]+=position;
    }
}

void wireframe::Scale(const float amount = 1){
    for (uint8_t i = 0; i < used_vertices; ++i) {
        vertices[i]-= position;
        vertices[i]*= amount;
        vertices[i]+= position;
    }
}

void wireframe::Scale_towards(const uint8_t range = 30){
    uint8_t max_distance = 0;
    for (uint8_t i = 0; i < used_vertices; ++i) {
        uint8_t dist = vertices[i].Distance_from(position);
        if(dist > max_distance){
            max_distance = dist;
        }
    }
    Scale(float(range) / max_distance);
}

void wireframe::Center(){
    float min_x = 999, max_x = -999, min_y = 999, max_y = -999, min_z = 999, max_z = -999;
    for(uint8_t i = 0; i < used_vertices; i++){
        if(vertices[i].x < min_x) min_x = vertices[i].x;
        if(vertices[i].x > max_x) max_x = vertices[i].x;
        if(vertices[i].y < min_y) min_y = vertices[i].y;
        if(vertices[i].y > max_y) max_y = vertices[i].y;
        if(vertices[i].z < min_z) min_z = vertices[i].z;
        if(vertices[i].z > max_z) max_z = vertices[i].z;
    }
    vertex center((min_x+max_x)/2,(min_y+max_y)/2,(min_z+max_z)/2);
    center -= position;
    for (uint8_t j = 0; j < used_vertices; ++j) {
        vertices[j] -= center;
    }
}

void wireframe::Add_vertex(vertex p){
    if(used_vertices < max_vertices) {
        vertices[used_vertices] = p + position;
        used_vertices++;
    }
}

void wireframe::Add_edge_by_index(edge edge_){
    if(used_edges < max_edges) {
        edges[used_edges] = edge_;
        used_edges++;
    }
}

void wireframe::Add_edge_by_vertices(vertex vertex_a, vertex vertex_b) {
    if(used_edges < max_edges) {
        edge e(0, 0);
        bool found_a = false;
        bool found_b = false;
        for (uint8_t i = 0; i < used_vertices; i++) {
            if (vertex_a == vertices[i] - position) {
                e.a = i;
                found_a = true;
            }
            if (vertex_b == vertices[i] - position) {
                e.b = i;
                found_b = true;
            }
        }
        if (!found_a && used_vertices < max_vertices) {
            e.a = used_vertices;
            Add_vertex(vertex_a);
        }
        if (!found_b && used_vertices < max_vertices) {
            e.b = used_vertices;
            Add_vertex(vertex_b);
        }
        if(found_a && found_b){
            for (uint8_t j = 0; j < used_edges; ++j) {
                if(e == edges[j]){
                    return;
                }
            }
        }
        Add_edge_by_index(e);
    }
}

void wireframe::Add_triangle(vertex point_a, vertex point_b, vertex point_c){
    Add_edge_by_vertices(point_a,point_b);
    Add_edge_by_vertices(point_b,point_c);
    Add_edge_by_vertices(point_c,point_a);
}

void wireframe::Draw_line(const screen_point point_a, const screen_point point_b){
    if (abs(point_a.y - point_b.y) < abs(point_a.x - point_b.x)) {
        if (point_a.x > point_b.x) {
            Draw_line_low(point_b.x, point_b.y, point_a.x, point_a.y);
        } else {
            Draw_line_low(point_a.x, point_a.y, point_b.x, point_b.y);
        }
    }else {
        if (point_a.y > point_b.y) {
            Draw_line_high(point_b.x, point_b.y, point_a.x, point_a.y);
        } else {
            Draw_line_high(point_a.x, point_a.y, point_b.x, point_b.y);
        }
    }
}

void wireframe::Draw_line_low(const int16_t & x0,const int16_t & y0,const int16_t & x1,const int16_t & y1){
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    int16_t yi = 1;
    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    auto D = int16_t(2*dy - dx);
    int16_t y = y0;

    for(int16_t x = x0; x != x1; x++) {
        display.Write(x,y);
        if (D > 0) {
            y = y + yi;
            D = uint16_t(D - 2 * dx);
        }
        D = uint16_t(D + 2 * dy);
    }
}

void wireframe::Draw_line_high(const int16_t & x0,const int16_t & y0,const int16_t & x1,const int16_t & y1){
    int16_t dx = x1 - x0;
    int16_t dy = y1 - y0;
    int16_t xi = 1;
    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    auto D = int16_t(2*dx - dy);
    int16_t x = x0;

    for(int16_t y = y0; y != y1; y++) {
        display.Write(x,y);
        if (D > 0) {
            x = x + xi;
            D = int16_t(D - 2 * dy);
        }
        D = int16_t(D + 2 * dx);
    }
}