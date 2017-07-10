//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Example
 *  \brief Follow relative redirects from GET request.
 */

#include <lattice.hpp>

#include <iostream>


int main(int argc, char *argv[])
{
    lattice::url_t url = {"http://httpbin.org/redirect/1"};
    lattice::timeout_t timeout(1000);
    lattice::redirects_t redirects(5);
    auto response = lattice::Get(url, timeout, redirects);

    if (response.ok()) {
        std::cout << "Body:\n"
                  << "------------------\n"
                  << response.body()
                  << "------------------\n"
                  << "Encoding: " << response.encoding() << "\n"
                  << "------------------\n";
    } else {
        std::cout << "Response was not successful, error code: "
                  << response.status();
    }

    return 0;
}
