#include "Buffer.h"
#include <iostream>

Buffer::Buffer(){};

Buffer::~Buffer(){};

void Buffer::append(const char* _msg, int _size) {
    for (int i=0; i<_size; ++i) {
        if (_msg[i] == '\0'){
            break;
        }
        buf.push_back(_msg[i]);
    }
}

ssize_t Buffer::size() const {
    return buf.size();
}

const char* Buffer::c_str() const {
    return buf.c_str();
}

void Buffer::clear() {
    buf.clear();
}

void Buffer::getline() {
    buf.clear();
    std::getline(std::cin, buf);
}