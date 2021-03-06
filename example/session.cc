//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup Example
 *  \brief Create session and respond to data from send from server.
 */

#include <lattice.h>
#include <iostream>

LATTICE_USING_NAMESPACE


/**
 *  Process data for request and send data to connection.
 */
void send_request(http_connection_t& connection)
{
    // create our options
    parameters_t parameters = {
        {"url", "http://httpbin.org/get"},
    };
    url_t url {"http://httpbin.org/redirect-to"};
    timeout_t timeout(1000);

    // create our request
    request_t request;
    set_option(request, GET, url, timeout, parameters);

    // send data and get response
    connection.write(request.message());
}


/**
 *  Follow redirect and resend data to new URL.
 */
void send_redirect(http_connection_t& connection, response_t &response)
{
    // create our options
    url_t url(response.headers().at("location"));
    timeout_t timeout(1000);

    // create our request
    request_t request;
    set_option(request, GET, url, timeout);

    // send data and get response
    connection.write(request.message());
}


/**
 *  Exit if request failed.
 */
void check_code(response_t& response, int code)
{
    if (response.status() != code) {
        std::cout << "Could not establish session, error code "
                  << response.status() << ", exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
    // initialize connection
    url_t url = {"http://httpbin.org"};
    http_connection_t connection;
    connection.open(url);

    // create our response and send initial request
    response_t response;
    send_request(connection);
    response = response_t(connection);
    check_code(response, 302);

    // follow redirect
    send_redirect(connection, response);
    response = response_t(connection);
    check_code(response, 200);

    std::cout << "Body:\n"
              << "------------------\n"
              << response.body()
              << "------------------\n"
              << "Encoding: " << response.encoding() << "\n"
              << "------------------\n";

    return 0;
}
