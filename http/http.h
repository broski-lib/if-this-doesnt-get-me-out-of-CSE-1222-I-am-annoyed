#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/socket.h>
#include <unordered_map>
#include <vector>

// =============================================================================
// Public HTTP Namespace API
// =============================================================================
namespace http {

// -----------------------------------------------------------------------------
// Constants & Types
// -----------------------------------------------------------------------------
constexpr std::string_view DEFAULT_PORT = "8080";
constexpr int LISTEN_BACKLOG = 10;    // max pending connections
constexpr int MAX_BUFFER_SIZE = 1024; // in bytes
constexpr std::string_view HEADER_DELIMITER = "\r\n\r\n";

using header_map = std::unordered_map<std::string, std::string>;

// Standard HTTP methods
//
// SECURITY: TRACE should be avoided when implementing server.
enum class HTTP_METHOD {
  GET,
  HEAD,
  OPTIONS,
  TRACE,
  DELETE,
  PUT,
  POST,
  CONNECT,
};

// -----------------------------------------------------------------------------
// Classes
// -----------------------------------------------------------------------------
class HTTPResponse {
public:
  int status_code;
  std::string status;
  http::header_map headers;
  std::vector<char> body;

  HTTPResponse(
      const std::string &status,
      const http::header_map &headers,
      std::vector<char> body);
};

// -----------------------------------------------------------------------------
// Utility Functions
// -----------------------------------------------------------------------------
constexpr std::string_view to_string(HTTP_METHOD method) {
  switch (method) {
  case HTTP_METHOD::GET:
    return "GET";
  case HTTP_METHOD::HEAD:
    return "HEAD";
  case HTTP_METHOD::OPTIONS:
    return "OPTIONS";
  case HTTP_METHOD::TRACE:
    return "TRACE";
  case HTTP_METHOD::DELETE:
    return "DELETE";
  case HTTP_METHOD::PUT:
    return "PUT";
  case HTTP_METHOD::POST:
    return "POST";
  case HTTP_METHOD::CONNECT:
    return "CONNECT";
  }
  throw std::invalid_argument("Unknown HTTP method");
}

// -----------------------------------------------------------------------------
// Helper Functions
// -----------------------------------------------------------------------------

// get sockaddr, IPv4 or IPv6
void *get_in_addr(sockaddr *sa);

// -----------------------------------------------------------------------------
// HTTP Parsing
// -----------------------------------------------------------------------------

/// Creates a request HTTP header, copying the optional headers for safe re-use.
std::string create_request_message_header(
    HTTP_METHOD method,
    std::string_view host,
    std::string_view path,
    const std::optional<std::unordered_map<std::string, std::string>> &headers);

// -----------------------------------------------------------------------------
// Core Network Functions
// -----------------------------------------------------------------------------

// Returns established socket file descriptor. Returns -1 on error.
int connect_tcp(std::string addr_string, std::string addr_port);

// Returns established socket file descriptor. Returns -1 on error.
int listen_tcp(std::string addr_string, std::string addr_port);

HTTPResponse
get(std::string addr_string, std::string addr_port, std::string path = "/");

} // namespace http
