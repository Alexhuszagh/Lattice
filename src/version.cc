//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief Lattice versioning.
 */

#include <lattice/version.h>

LATTICE_BEGIN_NAMESPACE

// CONSTANTS
// ---------

const std::string VERSION = std::to_string(MAJOR_VERSION) + "." + std::to_string(MINOR_VERSION) + "." + std::to_string(PATCH_VERSION);

LATTICE_END_NAMESPACE
