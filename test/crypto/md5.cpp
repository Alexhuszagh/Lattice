//  :copyright: (c) 2015-2016 The Regents of the University of California.
//  :license: MIT, see licenses/mit.md for more details.
/*
 *  \addtogroup LatticeTests
 *  \brief MD5 algorithm unittests.
 */

#include "lattice.hpp"

#include <gtest/gtest.h>


// TESTS
// -----


TEST(Md5, Md5)
{
    std::string bytes = "012345";
    std::string digest = {-42, -87, -87, 51, -56, -86, -4, 81, -27, 90, -64, 102, 43, 110, 77, 74};

    EXPECT_EQ(digest, lattice::MD5(bytes));
}


TEST(Md5, Md5Hex)
{
    std::string bytes = "012345";
    std::string digest = "D6A9A933C8AAFC51E55AC0662B6E4D4A";
    EXPECT_EQ(digest, lattice::MD5_HEX(bytes));
}
