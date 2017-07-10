//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief HTTP URL object.
 */

#pragma once

#include <string>
#include <initializer_list>


namespace lattice
{
// OBJECTS
// -------


/**
 *  \brief URL class instance.
 */
struct Url: std::string
{
    Url() = default;
    Url(const Url &other) = default;
    Url & operator=(const Url&) = default;
    Url(Url&&) = default;
    Url & operator=(Url&&) = default;

    Url(const char *cstring);
    Url(const char *array, size_t size);
    Url(const std::string &string);
    Url(std::initializer_list<char> list);

    // GETTERS
    std::string service() const noexcept;
    std::string host() const noexcept;
    std::string path() const noexcept;
    std::string directory() const noexcept;
    std::string file() const noexcept;

    // SETTERS
    void set_service(const std::string &service);
    void set_host(const std::string &host);
    void set_path(const std::string &path);
    void set_directory(const std::string &directory);
    void set_file(const std::string &file);

    // PROPERTIES
    bool relative() const noexcept;
    bool absolute() const noexcept;

    explicit operator bool() const;
};

}   /* lattice */
