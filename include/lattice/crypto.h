//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief Cryptographic algorithms (**weak**) for requests.
 */

#pragma once

#include <lattice/config.h>

LATTICE_BEGIN_NAMESPACE

// OBJECTS
// -------


/**
 *  \brief Various digest algorithms for digest authentication.
 */
enum digest_algorithm_t
{
    md5_digest_algorithm        = 0,
    md5_sess_digest_algorithm   = 1,
    sha1_digest_algorithm       = 2,
};

LATTICE_END_NAMESPACE
