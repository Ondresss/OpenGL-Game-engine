#pragma once
#include<unistd.h>
#include<stdlib.h>
class VertexBuffer {
private:
    unsigned int buffer_id;
public:
    VertexBuffer(const void* data,size_t size);
    ~VertexBuffer();

    void Bind();
    void UnBind();


};