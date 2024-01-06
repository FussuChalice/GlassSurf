// preferences/listener.cpp
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "listener.h"

void HTTP_Conection::Start()
{
	ReadRequest();
	CheckDeadline();
}

void HTTP_Conection::ReadRequest()
{
	auto self = shared_from_this();

	http::async_read(
		socket_, 
		buffer_, 
		request_, 
		[self](beast::error_code error_code, std::size_t bytes_transferred) {
			boost::ignore_unused(bytes_transferred);

			if (!error_code) {
				self->ProcessRequest();
			}
		});
}

void HTTP_Conection::ProcessRequest()
{
	response_.version(request_.version());
	response_.keep_alive(false);

	switch (request_.method()) {
		case http::verb::get:
			response_.result(http::status::ok);
			response_.set(http::field::server, "Beast");
			CreateResponse();
			break;

		default:
			// We return responses indicating an error if
			// we do not recognize the request method.
			response_.result(http::status::bad_request);
			response_.set(http::field::content_type, "text/plain");
			beast::ostream(response_.body())
				<< "Invalid request-method '"
				<< std::string(request_.method_string())
				<< "'";
			break;
	}
}

void HTTP_Conection::CreateResponse()
{
	/*if (request_.target() == "/change_theme/")*/
}

void HTTP_Conection::WriteResponse()
{
	auto self = shared_from_this();

	response_.content_length(response_.body().size());

	http::async_write(
		socket_,
		response_,
		[self](beast::error_code ec, std::size_t)
		{
			self->socket_.shutdown(tcp::socket::shutdown_send, ec);
			self->deadline_.cancel();
		});
}

void HTTP_Conection::CheckDeadline()
{
	auto self = shared_from_this();

	deadline_.async_wait(
		[self](beast::error_code error_code) {
			if (!error_code) {
				// Close socket to cancel any outstanding operation.
				self->socket_.close(error_code);
			}
	});
}

void HTTP_Listener(tcp::acceptor& acceptor, tcp::socket& socket)
{
	acceptor.async_accept(socket, [&](beast::error_code error_code) {
		if (!error_code) {
			std::make_shared<HTTP_Conection>(std::move(socket))->Start();
		}
		HTTP_Listener(acceptor, socket);
	});
}
