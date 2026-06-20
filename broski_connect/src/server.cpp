#include "service.grpc.pb.h"
#include "service.pb.h"
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <string>

using broski_connect::AdminService;

class AdminServiceImpl final : public broski_connect::AdminService::Service {
  grpc::Status SendCommand(
      grpc::ServerContext *context,
      const broski_connect::SendCommandRequest *request,
      broski_connect::SendCommandResponse *reply) override {

    std::cout << "Received command: " << request->command() << std::endl;

    // Mocking execution logic
    reply->set_exit_code(0);
    reply->set_output("Executed successfully: " + request->command());

    return grpc::Status::OK;
  }
};

void run_server() {
  std::string addr{"[::]:5000"};
  AdminServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::ServerBuilder builder;

  builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << addr << std::endl;
  server->Wait();
}

int main(int argc, char *argv[]) {
  run_server();
  return 0;
}
