#pragma once

extern "C" {
#include <sys/types.h>
#include <unistd.h>
}
#include "MQueue.h"

namespace sipc {
class Link {
public:
    Link(const char* child, const char* mqueue_name)
        : mqueue_{mqueue_name} {
        pid_ = fork();
        if (pid_ == 0) {
            // child
            std::cout << "forking process with name " << child << std::endl;
            int err = execl(child, child, mqueue_name);
            if (err == -1) {
                std::cout << "something went wrong" << std::endl;
            }
            exit(1);
        } else {
            mqueue_.Create();
        }
    }

    MQueue& GetMQueue() { return mqueue_; }
    bool IsChild() const { return is_child_; }
    bool IsParent() const { return !is_child_; }
private:
    pid_t pid_;
    MQueue mqueue_;
    bool is_child_ = false;
};
}
