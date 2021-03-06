//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Example
 *  \brief Simple GET request with cookies.
 */

#include <lattice.h>
#include <iostream>

LATTICE_USING_NAMESPACE


int main(int argc, char *argv[])
{
    cookies_t cookies = {
        {"name", "value"},
    };
    auto cache = create_dns_cache();
    url_t url = {"http://httpbin.org/cookies/set"};
    timeout_t timeout(1000);
    redirects_t redirects(5);

    // set cookies
    auto response = Get(url, cookies, timeout, redirects, cache);
    if (response.ok()) {
        // delete the cookies
        url = {"http://httpbin.org/cookies/delete"};
        cookies = {{"name", ""}};
        response = Get(url, cookies, timeout, redirects, cache);
        if (response.ok()) {
            std::cout << "Successfully set and deleted cookies" << std::endl;
        } else {
            std::cout << "Could not delete the set cookies, error code: "
                      << response.status()  << std::endl;
        }
    } else {
      std::cout << "Could not set the cookies, error code: "
                << response.status()  << std::endl;
    }

    return 0;
}
