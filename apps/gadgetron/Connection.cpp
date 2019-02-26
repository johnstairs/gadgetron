
#include <iostream>
#include <memory>

#include "Context.h"

#include "connection/Core.h"
#if !(_WIN32)
#include <cstdlib>
#include <unistd.h>
#include <wait.h>
#endif

using namespace Gadgetron::Server::Connection;

namespace Gadgetron::Server::Connection {

#if _WIN32 || !NDEBUG
    void handle(const Gadgetron::Core::Context::Paths& paths, std::unique_ptr<std::iostream> stream) {
        auto thread = std::thread(handle_connection, std::move(stream), paths);
        thread.detach();
    }
#else
    void handle(const Gadgetron::Core::Context::Paths& paths, std::unique_ptr<std::iostream> stream) {
        auto pid = fork();
        if (pid == 0) {
            handle_connection(std::move(stream), paths);
            std::exit(0);
        }
        auto listen_for_close = [](auto pid) {int status; waitpid(pid,&status,0);};
        std::thread t(listen_for_close,pid);
        t.detach();

    }
#endif
}
