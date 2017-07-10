//  :copyright: (c) 2015 Huu Nguyen.
//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Lattice
 *  \brief HTTP/HTTPS request.
 */

#pragma once

#include <lattice/adapter.hpp>
#include <lattice/auth.hpp>
#include <lattice/connection.hpp>
#include <lattice/cookie.hpp>
#include <lattice/digest.hpp>
#include <lattice/dns.hpp>
#include <lattice/header.hpp>
#include <lattice/method.hpp>
#include <lattice/multipart.hpp>
#include <lattice/parameter.hpp>
#include <lattice/proxy.hpp>
#include <lattice/redirect.hpp>
#include <lattice/response.hpp>
#include <lattice/ssl.hpp>
#include <lattice/timeout.hpp>
#include <lattice/url.hpp>

#include <sstream>

namespace lattice
{
// OBJECTS
// -------


/**
 *  \brief HTTP request object.
 */
class request_t
{
public:
    request_t() = default;
    request_t(const request_t &other) = default;
    request_t & operator=(const request_t&) = default;
    request_t(request_t&&) = default;
    request_t & operator=(request_t&&) = default;

    // EXPLICIT OPTIONS
    void set_method(method_t);
    void set_url(const Url&);
    void set_url(Url&&);
    void set_parameters(const parameters_t&);
    void set_parameters(parameters_t&&);
    void set_header(const Header&);
    void set_timeout(const timeout_t&);
    void set_auth(const authentication_t&);
    void set_digest(const Digest&);
    void set_multipart(const multipart_t&);
    void set_multipart(multipart_t&&);
    void set_proxy(const Proxy&);
    void set_proxy(Proxy&&);
    void set_body(const body_t&);
    void set_body(body_t&&);
    void set_payload(const payload_t&);
    void set_payload(payload_t&&);
    void set_cookies(const cookies_t&);
    void set_redirects(const redirects_t&);
    void set_certificate_file(const CertificateFile&);
    void set_certificate_file(CertificateFile&&);
    void set_revocation_lists(const RevocationLists&);
    void set_revocation_lists(RevocationLists&&);
    void set_ssl_protocol(ssl_protocol_t);
    void set_verify_peer(const verify_peer_t&);
    void set_verify_peer(verify_peer_t&&);
    void set_cache(const dns_cache_t&);

    // LATTICE_FWDING OPTIONS
    void set_option(method_t);
    void set_option(const Url&);
    void set_option(Url&&);
    void set_option(const parameters_t&);
    void set_option(parameters_t&&);
    void set_option(const Header&);
    void set_option(const timeout_t&);
    void set_option(const authentication_t&);
    void set_option(const Digest&);
    void set_option(const multipart_t&);
    void set_option(multipart_t&&);
    void set_option(const Proxy&);
    void set_option(Proxy&&);
    void set_option(const body_t&);
    void set_option(body_t&&);
    void set_option(const payload_t&);
    void set_option(payload_t&&);
    void set_option(const cookies_t&);
    void set_option(const redirects_t&);
    void set_option(const CertificateFile&);
    void set_option(CertificateFile&&);
    void set_option(const RevocationLists&);
    void set_option(RevocationLists&&);
    void set_option(ssl_protocol_t);
    void set_option(const verify_peer_t&);
    void set_option(verify_peer_t&&);
    void set_option(const dns_cache_t&);

    // ACCESS
    method_t get_method() const;
    const Url& get_url() const;
    const parameters_t& get_parameters() const;
    const Header& get_header() const;
    const timeout_t& get_timeout() const;
    const Digest& get_digest() const;
    const redirects_t& get_redirects() const;
    const CertificateFile& get_certificate_file() const;
    const RevocationLists& get_revocation_lists() const;
    ssl_protocol_t get_ssl_protocol() const;
    const verify_peer_t& get_verify_peer() const;
    const dns_cache_t get_dns_cache() const;

    // CONNECTIONS
    template <typename... Ts>
    std::string message(Ts&&... ts) const;
    std::string method_name() const;

    response_t exec();

    template <typename Connection>
    void open(Connection&) const;

    template <typename Connection>
    void reset(Connection&, const response_t&);

    template <typename Connection>
    response_t exec(Connection&);

protected:
    Url url;
    parameters_t parameters;
    Header header;
    Digest digest;
    multipart_t multipart;
    Proxy proxy;
    timeout_t timeout;
    redirects_t redirects;
    CertificateFile certificate;
    RevocationLists revoke;
    method_t method = static_cast<method_t>(0);
    ssl_protocol_t ssl = static_cast<ssl_protocol_t>(0);
    verify_peer_t verifypeer;
    dns_cache_t cache = nullptr;

    std::stringstream method_header() const;
    std::stringstream method_header(const response_t&) const;
};


// FUNCTIONS
// ---------


template <typename T>
void set_option(request_t& request, T&& t)
{
    request.set_option(std::forward<T>(t));
}


template <typename T, typename... Ts>
void set_option(request_t& request, T&& t, Ts&&... ts)
{
    set_option(request, std::forward<T>(t));
    set_option(request, std::forward<Ts>(ts)...);
}


template <typename... Ts>
response_t Delete(Ts&&... ts)
{
    request_t request;
    set_option(request, DELETE, std::forward<Ts>(ts)...);

    return request.exec();
}


template <typename... Ts>
response_t Get(Ts&&... ts)
{
    request_t request;
    set_option(request, GET, std::forward<Ts>(ts)...);

    return request.exec();
}


template <typename... Ts>
response_t Head(Ts&&... ts)
{
    request_t request;
    set_option(request, HEAD, std::forward<Ts>(ts)...);

    return request.exec();
}


template <typename... Ts>
response_t Options(Ts&&... ts)
{
    request_t request;
    set_option(request, OPTIONS, std::forward<Ts>(ts)...);

    return request.exec();
}


template <typename... Ts>
response_t Patch(Ts&&... ts)
{
    request_t request;
    set_option(request, PATCH, std::forward<Ts>(ts)...);

    return request.exec();
}


template <typename... Ts>
response_t Post(Ts&&... ts)
{
    request_t request;
    set_option(request, POST, std::forward<Ts>(ts)...);

    return request.exec();
}


template <typename... Ts>
response_t Put(Ts&&... ts)
{
    request_t request;
    set_option(request, PUT, std::forward<Ts>(ts)...);

    return request.exec();
}


template <typename... Ts>
response_t Trace(Ts&&... ts)
{
    request_t request;
    set_option(request, TRACE, std::forward<Ts>(ts)...);

    return request.exec();
}


// IMPLEMENTATION
// --------------


template <typename... Ts>
std::string request_t::message(Ts&&... ts) const
{
    std::stringstream stream;

    // get our formatted body
    std::string body;
    if (method == POST && parameters) {
        body += parameters.post();
    } else if (multipart) {
        body += multipart.string();
    }

    // get formatted headers
    auto headers = method_header(std::forward<Ts>(ts)...);
    if (!body.empty()) {
        headers << "Content-Length: " << body.size() << "\r\n";
    }

    // get first line
    if (method == POST) {
        stream << method_name() << " " << url.path()
               << " HTTP/1.1\r\n"
               << headers.str()
               << "\r\n" << body;
    } else {
        stream << method_name() << " " << url.path() << parameters.get()
               << " HTTP/1.1\r\n"
               << headers.str()
               << "\r\n" << body;
    }

    // end message with double CRLF
    stream << "\r\n";
    if (!body.empty()) {
        stream << "\r\n";
    }

    return stream.str();
}


/**
 *  \brief Make request to server.
 *
 *  To avoid compiling external libraries into lattice, misuse inline
 *  to keep this in the header.
 */
inline response_t request_t::exec()
{
    auto service = url.service();
    if (service == "http") {
        http_connection_t connection;
        return exec(connection);
    } else if (service == "https") {
        https_connection_t connection;
        return exec(connection);
    } else {
        throw std::runtime_error("Network scheme " + service + " is not supported.");
    }

    return response_t();
}


template <typename Connection>
response_t request_t::exec(Connection& connection)
{
    open(connection);
    response_t response;
    do {
        connection.write(message());
        response = response_t(connection);
        if (response.unauthorized() && digest) {
            // using digest authentication
            connection.write(message(response));
            response = response_t(connection);
            return response;
        } else if ((method = response.redirect(method)) != STOP) {
            reset(connection, response);
        } else {
            break;
        }
    } while (redirects--);

    return response;
}


template <typename Connection>
void request_t::open(Connection& connection) const
{
    // set options
    connection.set_verify_peer(verifypeer);
    if (certificate) {
        connection.set_certificate_file(certificate);
    }
    if (revoke) {
        connection.set_revocation_lists(revoke);
    }
    if (int_t(ssl)) {
        connection.set_ssl_protocol(ssl);
    }
    if (cache) {
        connection.set_cache(cache);
    }

    // open and set timeout
    if (!proxy) {
        connection.open(url);
    } else {
        connection.open(Url(proxy));
    }
    if (timeout) {
        connection.set_timeout(timeout);
    }
}


template <typename Connection>
void request_t::reset(Connection& connection, const response_t& response)
{
    // check if we need to reset connection
    bool reconnect = header.close_connection();
    reconnect |= response.headers().close_connection();

    Url newurl(response.headers().at("location"));
    if (newurl.absolute()) {
        // reconnect if the service or host changes
        reconnect |= url.service() != newurl.service();
        reconnect |= url.host() != newurl.host();
        url = newurl;
    } else {
        url.set_path(newurl.path());
    }

    // reset connection
    if (reconnect) {
        connection.close();
        open(connection);
    }
}

}   /* lattice */
