// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef WFLIB_EDGE_HPP
#define WFLIB_EDGE_HPP
/// @file
#include <cstdint>

namespace wflib {

/// \brief
/// edge object
/// \details
/// an edge consists of 2 indexes (a,b)
/// indexes point to an array of vertices
    class edge {
    public:
        uint8_t a;
        uint8_t b;

        /// \brief
        /// constructor
        /// \details
        /// int a, b
        /// the indexes of the edge
        explicit edge(uint8_t a = 0, uint8_t b = 0) :
                a(a), b(b) {}

        /// \brief
        /// == operator
        /// \details
        /// compares 2 edges, if the indexes are the same but in reversed order
        /// it is still considered as equal
        bool operator==(const edge &rhs) const {
            return (a == rhs.a && b == rhs.b) || (a == rhs.b && b == rhs.a);
        }
    };
}
#endif //INC_EDGE_HPP