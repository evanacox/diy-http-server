#include "util/log.hh"
#include <boost/asio.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/asio/completion_condition.hpp>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>

namespace util = ec::util;
namespace asio = boost::asio;
using boost::asio::ip::tcp;

std::string daytime_string() {
  std::time_t now = std::time(0);
  return ctime(&now);
}

int main() {
  asio::io_context context;
  tcp::acceptor acceptor(context, tcp::endpoint(tcp::v4(), 8080));

  util::ok("Starting up!");

  boost::system::error_code ec;

  while (true) {
    tcp::socket socket(context);
    acceptor.accept(socket);

    auto ip_string = socket.remote_endpoint().address().to_string();
    util::open("Got connection from '{}'", ip_string);

    socket.write_some(asio::buffer("Hi! What's your name?\n"), ec);

    asio::streambuf buffer;
    asio::read_until(socket, buffer, "\n");

    std::string message;
    std::istream is(&buffer);
    is >> message;

    util::info("Got message '{}' from '{}", message, ip_string);

    asio::write(socket, asio::buffer("It's good to meet you "));
    asio::write(socket, asio::buffer(message));

    util::done("Connection from '{}' closed!", ip_string);
  }

  return 0;
}
