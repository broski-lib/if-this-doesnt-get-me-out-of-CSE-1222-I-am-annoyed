#include "service.grpc.pb.h"
#include "service.pb.h"
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/support/status.h>
#include <grpcpp/support/sync_stream.h>
#include <string>

using broski_connect::AdminService;
using grpc::Status;

class AdminServiceImpl final : public broski_connect::AdminService::Service {
  Status ListDevices(
      grpc::ServerContext *context,
      const broski_connect::ListDevicesRequest *request,
      broski_connect::ListDevicesResponse *response) override {

    // TODO!

    return Status::OK;
  };

  Status GetDevice(
      grpc::ServerContext *context,
      const broski_connect::GetDeviceRequest *request,
      broski_connect::Device *response) override {

    // TODO!

    return Status::OK;
  };

  Status DispatchCommand(
      grpc::ServerContext *context,
      const broski_connect::DispatchCommandRequest *request,
      broski_connect::DispatchCommandResponse *response) override {

    // TODO!

    return Status::OK;
  };

  Status StreamJobOutput(
      grpc::ServerContext *context,
      const broski_connect::StreamJobRequest *request,
      grpc::ServerWriter<broski_connect::CommandOutputChunk> *response)
      override {

    // TODO!

    return Status::OK;
  };
};

class AgentServiceImpl final : public broski_connect::AgentService::Service {};

void run_server() {
  std::string addr{"[::]:5000"};
  AdminServiceImpl admin_service;
  AgentServiceImpl agent_service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::ServerBuilder builder;

  builder.AddListeningPort(addr, grpc::InsecureServerCredentials());

  builder.RegisterService(&admin_service);
  builder.RegisterService(&agent_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << addr << std::endl;
  server->Wait();
}

int main(int argc, char *argv[]) {
  run_server();
  return 0;
}
