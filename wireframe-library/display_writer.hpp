// Copyright Victor Adamse 2018.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file License.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt)

#ifndef WFLIB_DISPLAY_WRITER_HPP
#define WFLIB_DISPLAY_WRITER_HPP

/// @file

#include <cstdint>

namespace wflib {
/// \brief
/// display writer
/// \details
/// abstract object that receives the output from a wireframe object
/// meant to be inheritet by a custom class that can use the incoming
/// data to write to something else.
    class display_writer {
    public:
        /// \brief
        /// Write pixel
        /// \details
        /// function is called by wireframe object to draw pixels
        /// inhert this class and override this function.
        /// you can use this function to write on your own display
        virtual void Write(int16_t x, int16_t y) = 0;
    };
}
#endif //WFLIB_DISPLAY_WRITER_HPP
