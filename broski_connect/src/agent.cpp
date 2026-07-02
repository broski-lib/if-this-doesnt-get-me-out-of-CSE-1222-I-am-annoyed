#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/support/status.h>
#include <iostream>
#include <memory>
#include <string>

#include "service.grpc.pb.h"
#include "service.pb.h"
#include <grpcpp/grpcpp.h>

using broski_connect::AdminService;
using broski_connect::SendCommandRequest;
using broski_connect::SendCommandResponse;

class AdminClient {
public:
  AdminClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(AdminService::NewStub(channel)) {}

  void SendRemoteCommand(const std::string &command) {
    SendCommandRequest request;
    request.set_command(command);

    SendCommandResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub_->SendCommand(&context, request, &response);

    if (status.ok()) {
      std::cout << "Response Recieved (" << (response.exit_code()) << "):\n";
      std::cout << response.output() << std::endl;
    } else {
      std::cerr << "RPC Failed: " << status.error_message() << std::endl;
    }
  }

private:
  std::unique_ptr<AdminService::Stub> stub_;
};

int main(int argc, char *argv[]) {

  AdminClient client(
      grpc::CreateChannel("0.0.0.0:5000", grpc::InsecureChannelCredentials()));

  std::cout << "Sending command to server...\n";
  client.SendRemoteCommand("pwd");

  return 0;
}
