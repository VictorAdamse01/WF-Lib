// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef WFLIB_SCREEN_POINT_HPP
#define WFLIB_SCREEN_POINT_HPP

///@file

#include <cstdint>

namespace wflib {

/// \brief
/// screen space point
/// \details
/// screen space point consists of 2 integers (x,y)
/// they can still be negative if the point is outside the screen
    class screen_point {
    public:
        int16_t x;
        int16_t y;

        /// \brief
        /// constructor
        /// \details
        /// int x, y
        /// the screen space coordinates of the point
        explicit screen_point(int16_t x = 0, int16_t y = 0) :
                x(x),
                y(y) {}
    };
}
#endif //WFLIB_SCREEN_POINT_HPP
