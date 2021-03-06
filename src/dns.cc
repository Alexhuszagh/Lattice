//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief Domain name lookups and address caching.
 */

#include <lattice/dns.h>
#include <cstdlib>
#include <cstring>

#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable:4800)
#endif

LATTICE_BEGIN_NAMESPACE

// OBJECTS
// -------


address_iterator_t::address_iterator_t(pointer ptr):
    ptr(ptr)
{}


auto address_iterator_t::operator*() -> reference
{
    return *ptr;
}


auto address_iterator_t::operator*() const -> const_reference
{
    return *ptr;
}


auto address_iterator_t::operator->() -> pointer
{
    return ptr;
}


auto address_iterator_t::operator->() const -> const_pointer
{
    return ptr;
}


auto address_iterator_t::operator++() -> address_iterator_t &
{
    ptr = ptr->ai_next;
    return *this;
}


auto address_iterator_t::operator++(int)
    -> address_iterator_t
{
    address_iterator_t copy(*this);
    operator++();

    return copy;
}


bool address_iterator_t::operator==(const address_iterator_t& other) const
{
    short sum = bool(ptr) + bool(other.ptr);
    switch (sum) {
        case 0:
            return true;
        case 1:
            return false;
        case 2:
            /* fallthrough */
        default: {
            return (
                ptr->ai_flags == other.ptr->ai_flags &&
                ptr->ai_family == other.ptr->ai_family &&
                ptr->ai_socktype == other.ptr->ai_socktype &&
                ptr->ai_protocol == other.ptr->ai_protocol &&
                ptr->ai_addrlen == other.ptr->ai_addrlen &&
                ptr->ai_addr == other.ptr->ai_addr &&
                ptr->ai_canonname == other.ptr->ai_canonname
            );
        }
    }
}


bool address_iterator_t::operator!=(const address_iterator_t& other) const
{
    return !operator==(other);
}


address_t::address_t(const addrinfo &info):
    family(info.ai_family),
    socket_type(info.ai_socktype),
    protocol(info.ai_protocol),
    address(*info.ai_addr),
    length(info.ai_addrlen)
{}


address_t::operator addrinfo() const
{
    addrinfo info;
    info.ai_family = family;
    info.ai_socktype = socket_type;
    info.ai_protocol = protocol;
    info.ai_addr = const_cast<sockaddr*>(&address);
    info.ai_addrlen = length;

    return info;
}


dns_lookup_t::dns_lookup_t(const std::string &host, const std::string &service)
{
    // initialize our hints
    struct addrinfo hints, *result;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // get our host and port
    std::string nodeString, portString;
    const char *node = host.data();
    const char *port = service.data();
    const size_t index = host.find(":");
    if (index != std::string::npos) {
        nodeString = host.substr(0, index);
        portString = host.substr(index+1);
        node = nodeString.data();
        port = portString.data();
    }

    if (getaddrinfo(node, port, &hints, &result)) {
        throw std::runtime_error("Unable to get address from getaddrinfo(): " + host + service);
    }

    info = result;
}


dns_lookup_t::~dns_lookup_t()
{
    if (info) {
        freeaddrinfo(info);
        info = nullptr;
    }
}


address_iterator_t dns_lookup_t::begin() const
{
    return address_iterator_t(info);
}


address_iterator_t dns_lookup_t::end() const
{
    return address_iterator_t(nullptr);
}

LATTICE_END_NAMESPACE

#ifdef _MSC_VER
#   pragma warning(pop)
#endif
