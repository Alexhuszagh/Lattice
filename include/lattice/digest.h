//  :copyright: (c) 2015 Huu Nguyen.
//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief Weakly encrypted authentication for requests.
 *
 *  \warning Digest authentication, although popular, is insecure
 *  and should be considered deprecated and broken beyond repair.
 */

#pragma once

#include <lattice/auth.h>
#include <lattice/config.h>
#include <lattice/crypto.h>
#include <unordered_map>
#include <vector>

LATTICE_BEGIN_NAMESPACE

// FORWARD
// -------

class parameters_t;
struct url_t;

// OBJECTS
// -------


/**
 *  \brief Case-insensitive hash for ASCII.
 */
struct lowercase_hash
{
    size_t operator()(const std::string& string) const;
};


/**
 *  \brief Case-insensitive key_equal for ASCII.
 */
struct lowercase_equal_to
{
    bool operator()(const std::string&, const std::string&) const;
};


/**
 *  \brief Authorization string for requests.
 */
struct digest_t: authentication_t
{
    using authentication_t::authentication_t;
};


/**
 *  \brief Quality of protection directive.
 */
class quality_of_protection_t: public std::vector<std::string>
{
protected:
    typedef std::vector<std::string> Base;

public:
    using Base::Base;
    quality_of_protection_t(const std::string &qop);

    bool auth() const;
    bool authint() const;

    explicit operator bool() const;
};


/**
 *  \brief Authenticate challenge sent from the server.
 *
 *  \format
 *      Digest nonce="42148a112dd92b7e5b6ac4769c2a6693", opaque="35fa82343c10f5a83c7d9b8bb29d8518", realm="me@kennethreitz.com", qop=auth
 */
class digest_challenge_t: public std::unordered_map<
        std::string,
        std::string,
        lowercase_hash,
        lowercase_equal_to
    >
{
public:
    typedef std::unordered_map<std::string, std::string, lowercase_hash, lowercase_equal_to> base;
    using base::base;
    digest_challenge_t(const std::string& string);

    // DATA
    const std::string & realm() const;
    const std::string & nonce() const;
    const std::string & cnonce();
    std::string nc() const;
    digest_algorithm_t algorithm() const;
    quality_of_protection_t qop() const;
    std::string header(const url_t& url,
        const parameters_t& parameters,
        const digest_t& digest,
        const std::string& body,
        const std::string& method);

    explicit operator bool() const;

protected:
    uint64_t nonce_counter = 0;
    std::string client_nonce;
};

LATTICE_END_NAMESPACE
