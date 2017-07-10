//  :copyright: (c) 2015 Huu Nguyen.
//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief Cookie support for persistent sessions.
 */

#include <lattice/cookie.hpp>

#include <pycpp/url.h>
#include <sstream>

PYCPP_USING_NAMESPACE

namespace lattice
{
// OBJECTS
// -------


/** \brief Special case of type 1 cookies, with leading and trailing quotes.
 */
bool encode_version_one_cookie(const std::string &cookie)
{
    if (!cookie.empty()) {
        return (cookie.front() == '"' && cookie.back() == '"');
    }
    return false;
}


std::string cookies_t::encode() const
{
    std::stringstream stream;
    for (const auto &item: *this) {
        stream << url_encode(item.first) << "=";
        if (encode_version_one_cookie(item.second)) {
            stream << item.second;
        } else {
            stream << url_encode(item.second);
        }
        stream << "; ";
    }

    return stream.str();
}


cookies_t::operator bool() const
{
    return !empty();
}

}   /* lattice */
