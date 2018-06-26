// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef WFLIB_WIREFRAME_HPP
#define WFLIB_WIREFRAME_HPP

///@file

#include "edge.hpp"
#include "screen_point.hpp"
#include "vertex.hpp"
#include "display_writer.hpp"
#include <cstdint>

#define max_vertices 64
#define max_edges 128

namespace wflib {

    /// \brief
    /// wireframe object
    /// \details
    /// the main wireframe object.
    /// has a position in world space (if you want multiple wireframes next to each other)
    /// stores a reference to the display writer object it uses as output
    /// has an array of vertices and edges that make up the wireframe

    class wireframe {
    private:
        display_writer & display;

        uint8_t used_vertices = 0;
        uint8_t used_edges = 0;

        vertex position;

        const uint16_t screen_width;
        const uint16_t screen_height;

        vertex vertices[max_vertices];
        edge edges[max_edges];

        //functions used for drawing one of the lines
        void Draw_line(screen_point point_a, screen_point point_b);

        void Draw_line_low(const int16_t &x0, const int16_t &y0, const int16_t &x1, const int16_t &y1);

        void Draw_line_high(const int16_t &x0, const int16_t &y0, const int16_t &x1, const int16_t &y1);

    public:
        /// \brief
        /// constructor
        /// \details
        /// reference to a display writer, position of the wireframe, screen width & height
        explicit wireframe(display_writer &display, vertex position = vertex(0, 0, 0), uint8_t screen_width = 128,
                           uint8_t screen_height = 64) :
                display(display),
                position(position),
                screen_width(screen_width),
                screen_height(screen_height) {}

        /// \brief
        /// Draw wireframe
        /// \details
        /// Draws the wireframe via the display writer on something
        void Draw(rendermode r_mode = rendermode::parallel);

        /// \brief
        /// Rotate wireframe
        /// \details
        /// rotates the wireframe around an axis in radials
        /// rotates around the position of the wireframe
        void Rotate(float rad,axis rotate_axis = axis::y);

        /// \brief
        /// Scale wireframe
        /// \details
        /// scale the entire wireframe.
        /// using the position of the wireframe as the center point
        void Scale(float amount);

        /// \brief
        /// scales object to fit range
        /// \details
        /// rescales the wireframe to fit the range
        /// int range is the max range a vertex can have from the center point
        /// wireframe can get smaller or bigger with this function
        void Scale_towards(uint8_t range);

        /// \brief
        /// Center wireframe
        /// \details
        /// Centers the wireframe to the position of the wireframe
        /// using the outmost points in every direction to get the objects center
        void Center();

        /// \brief
        /// Add vertex
        /// \details
        /// adds a single vertex to the array.
        /// this is the most basic way of adding a point.
        /// using the Add_edge_by_vertices or Add_triangle function
        /// automatically calls this function when necessary
        void Add_vertex(vertex vert);

        /// \brief
        /// Add edge by index
        /// \details
        /// Adds an edge index(a,b) to the array
        /// this is the most basic way of adding an edge
        /// using the Add_edge_by_vertices or Add_triangle function
        /// automatically calls this function when necessary
        void Add_edge_by_index(edge edge_index);

        /// \brief
        /// Add edge by vertices
        /// \details
        /// Adds an edge vertices(a,b) to the wireframe
        /// this function checks if given vertices or the edge itself
        /// already exis and only adds the new values.
        /// automatically gets the correct indexes for the edge
        void Add_edge_by_vertices(vertex vertex_a, vertex vertex_b);

        /// \brief
        /// Add triangle
        /// \details
        /// adds a triangle vertices(a,b,c) to the wireframe
        /// calls the add_edge_by_vertices for each line in the triangle
        void Add_triangle(vertex point_a, vertex point_b, vertex point_c);

        /// \brief
        /// Clear wireframe
        /// \details
        /// clears the wireframe
        /// resetting both arrays back to empty
        void Clear() {
            used_vertices = 0;
            used_edges = 0;
        }

        /// \brief
        /// number of used edges
        /// \details
        /// returns the number of currently used edges in the wireframe
        uint8_t Get_used_edges() { return used_edges; }

        /// \brief
        /// number of used vertices
        /// \details
        /// returns the number of currently used vertices in the wireframe
        uint8_t Get_used_vertices() { return used_vertices; }

        /// \brief
        /// get vertex from array
        /// \details
        /// returns a vertex from the array
        vertex Get_vertex(int index){ return  vertices[index];}

        /// \brief
        /// get edge from array
        /// \details
        /// returns an edge from the array
        edge Get_edge(int index){ return edges[index];}
    };
}

#endif //WFLIB_WIREFRAME_HPP
