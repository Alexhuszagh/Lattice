//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief HTTP methods.
 */

#pragma once

#include <lattice/config.h>

#ifdef DELETE
#   undef DELETE
#endif

LATTICE_BEGIN_NAMESPACE

// OBJECTS
// -------


/**
 *  \brief HTTP request methods.
 */
enum method_t: unsigned int
{
    STOP    = 0,
    GET     = 1,
    HEAD    = 2,
    POST    = 3,
    DELETE  = 4,
    OPTIONS = 5,
    PATCH   = 6,
    PUT     = 7,
    TRACE   = 8,
    CONNECT = 9,
};

LATTICE_END_NAMESPACE
