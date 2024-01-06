// preferences/listener.h
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef PREFERENCES_LISTENER_H_
#define PREFERENCES_LISTENER_H_

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class HTTP_Conection : public std::enable_shared_from_this<HTTP_Conection> {
public:
	HTTP_Conection(tcp::socket socket, ) : socket_(std::move(socket)) {}

	/**
	 * @brief Start processing an HTTP connection.
	 *
	 * Initiates the processing of an HTTP connection by calling ReadRequest and CheckDeadline.
	 */
	void Start();

private:
	tcp::socket socket_;

	beast::flat_buffer buffer_{ 8192 };

	http::request<http::dynamic_body> request_;
	http::response<http::dynamic_body> response_;

	net::steady_timer deadline_{
		socket_.get_executor(), std::chrono::seconds(60) 
	};

	/**
	 * @brief Read an HTTP request asynchronously.
	 *
	 * Asynchronously reads an HTTP request from the socket and invokes ProcessRequest
	 * upon successful completion.
	 */
	void ReadRequest();

	/**
	 * @brief Process the received HTTP request.
	 *
	 * Determines the HTTP method in the request and handles it accordingly. Calls
	 * CreateResponse for supported methods and generates an error response for
	 * unsupported methods.
	 */
	void ProcessRequest();

	/**
	 * @brief Create an HTTP response.
	 *
	 * Creates an HTTP response based on the processed HTTP request. Currently, the
	 * CreateResponse function is a placeholder and needs to be implemented based
	 * on the specific requirements of the application.
	 */
	void CreateResponse();

	/**
	 * @brief Write the HTTP response asynchronously.
	 *
	 * Asynchronously writes the HTTP response to the socket and shuts down the
	 * socket and cancels the deadline upon completion.
	 */
	void WriteResponse();

	/**
	 * @brief Check the deadline for the HTTP connection.
	 *
	 * Checks the deadline for the HTTP connection asynchronously. If the deadline
	 * expires, the socket is closed to cancel any outstanding operations.
	 */
	void CheckDeadline();
};

/**
 * @brief Asynchronously accept incoming connections.
 *
 * Initiates an asynchronous operation to accept incoming connections. For each
 * accepted connection, a new instance of HTTP_Conection is created to handle
 * the connection asynchronously.
 *
 * @param acceptor The TCP acceptor for accepting connections.
 * @param socket The TCP socket for handling accepted connections.
 */
void HTTP_Listener(tcp::acceptor& acceptor, tcp::socket& socket);

#endif // !PREFERENCES_LISTENER_H_
