// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef WFLIB_VERTEX_HPP
#define WFLIB_VERTEX_HPP

///@file

#include "math.h"
#include "screen_point.hpp"

namespace wflib {

    enum rendermode{
        parallel,
        perspective
    };

    enum axis{
        x,y,z
    };

    /// \brief
    /// vertex object
    /// \details
    /// a vertex object is a point in 3d space
    /// has 3 floats (x,y,z)

    class vertex {
    public:
        float x;
        float y;
        float z;

        /// \brief
        /// constructor
        /// \details
        /// float x, y, z
        /// the world space coordinates of the vertex
        explicit vertex(float x = 0, float y = 0, float z = 0) :
                x(x),
                y(y),
                z(z) {}

        /// \brief
        /// Rotate vertex
        /// \details
        /// rotates the vertex around an axis in radials
        void Rotate(float rad,axis rotate_axis = axis::y);

        /// \brief
        /// get vertex as screen space
        /// \details
        /// returns the 2d screen coordinates of the vertex
        /// can be done in parallel or perspective view
        screen_point Get_screen_space(rendermode r_mode = rendermode::parallel, const uint16_t &screen_width = 128, const uint16_t &screen_height = 64);

        /// \brief
        /// Distance to vertex
        /// \details
        /// returns the distance of the vertex to a vertex (point)
        uint8_t Distance_from(vertex point);

        /// \brief
        /// == operator
        /// \details
        /// compares the vertex with another.
        /// since the vertex exists of 3 floats they don't have to be
        /// an identical match.
        bool operator==(const vertex &rhs) const;

        /// \brief
        /// += operator
        /// \details
        /// adds a vertex to the vertex
        vertex operator+=(const vertex &rhs);

        /// \brief
        /// -= operator
        /// \details
        /// subtracts a vertex from the vertex
        vertex operator-=(const vertex &rhs);

        /// \brief
        /// + operator
        /// \details
        /// returns the sum of 2 vertices
        vertex operator+(const vertex &rhs) const;

        /// \brief
        /// - operator
        /// \details
        /// subtracts a vertex from another
        vertex operator-(const vertex &rhs) const;

        /// \brief
        /// *= operator
        /// \details
        /// multiplies the vertex by a float
        vertex operator*=(const float &rhs);
    };
}
#endif //WFLIB_VERTEX_HPP