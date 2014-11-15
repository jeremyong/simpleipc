#pragma once

extern "C" {
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
}
#include <iostream>
#include <string>

namespace sipc {
class MQueue {
public:
    MQueue(const char* name) : name_{name} {}
    ~MQueue() {
        if (mq_ != (mqd_t) -1) {
            mq_close(mq_);
        }
    }
    MQueue(const MQueue&) = delete;
    MQueue(MQueue&&) = delete;
    MQueue& operator=(const MQueue&) = delete;
    MQueue& operator=(MQueue&&) = delete;

    bool Create() {
        const int o_flags = O_CREAT | O_RDWR;
        mq_ = mq_open(name_.c_str(), o_flags);
        mq_attr attr;
        mq_getattr(mq_, &attr);
        max_size_ = attr.mq_msgsize;
        std::cout << "made mq with id " << mq_ << std::endl;
        return mq_ != (mqd_t) -1;
    }

    bool Attach() {
        const int o_flags = O_RDWR;
        mq_ = mq_open(name_.c_str(), o_flags);
        mq_attr attr;
        mq_getattr(mq_, &attr);
        max_size_ = attr.mq_msgsize;
        return mq_ != (mqd_t) -1;
    }

    void Send(const std::string& message) {
        if (mq_ == -1) return;
        std::cout << "Sending message" << std::endl;
        ssize_t bytes_sent = mq_send(mq_, message.c_str(), message.size(), 0);
        std::cout << bytes_sent << " bytes sent" << std::endl;
    }

    std::string Receive() {
        char buf[max_size_];
        ssize_t bytes_read = mq_receive(mq_, buf, max_size_, 0);
        std::cout << bytes_read << " bytes read" << std::endl;
        return std::string{buf};
    }

private:
    std::string name_;
    mqd_t mq_ = -1;
    size_t max_size_ = 0;
};
}
