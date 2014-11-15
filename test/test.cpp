#include <Link.h>
#include <iostream>

int main() {
    sipc::Link link{"./bin/child", "/mymq"};
    std::cout << "Hi from parent process." << std::endl;
    sipc::MQueue &mqueue = link.GetMQueue();
    mqueue.Send("hi there");
    return 0;
}
