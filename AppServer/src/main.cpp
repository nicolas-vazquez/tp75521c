#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <mongoose/Server.h>
#include "controllers/accounts/AccountController.h"
#include "controllers/matchs/MatchsController.h"

using namespace std;
using namespace Mongoose;

volatile static bool running = true;

void handle_signal(int sig) {
    if (running) {
        cout << "Exiting..." << endl;
        running = false;
    }
}

int main() {
    srand(time(NULL));

    signal(SIGINT, handle_signal);

    Server server(8083);

    AccountController accountController;
    server.registerController(&accountController);

    MatchsController matchsController;
    server.registerController(&accountController);

    server.setOption("enable_directory_listing", "false");
    server.start();

    cout << "Server started, routes:" << endl;
    accountController.dumpRoutes();

    while (running) {
        sleep(10);
    }

    server.stop();
    return EXIT_SUCCESS;
}
