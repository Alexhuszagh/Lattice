//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Example
 *  \brief Simple HTTP PUT request.
 */

#include "lattice.hpp"

#include <iostream>


int main(int argc, char *argv[])
{
    lattice::Parameters parameters = {
        {"param1", "value1"},
        {"param2", "value2"},
    };
    lattice::Url url = {"http://httpbin.org/put"};
    lattice::Timeout timeout(1000);
    auto response = lattice::Put(url, parameters, timeout);

    if (response.ok()) {
        std::cout << "Body:\n"
                  << "------------------\n"
                  << response.body()
                  << "------------------\n"
                  << "Encoding: " << response.encoding() << "\n"
                  << "------------------\n";
    } else {
        std::cout << "Response was not successful, error code: "
                  << response.status() << std::endl;
    }

    return 0;
}
