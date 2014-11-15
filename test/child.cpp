#include <MQueue.h>
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Hi from the child process" << std::endl;
    sipc::MQueue mqueue{argv[1]};
    mqueue.Attach();
    std::string msg = mqueue.Receive();
    std::cout << msg << std::endl;
    return 0;
}
