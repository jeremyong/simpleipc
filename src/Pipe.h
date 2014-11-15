#pragma once

#include <unistd.h>

namespace sipc {
class Pipe {
public:
    Pipe() {
        pipe(fds_);
    }
private:
    int fds_[2];
};
}
