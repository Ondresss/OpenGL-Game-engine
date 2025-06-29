#include "../headers/VertexBuffer.h"
#include "../headers/Renderer.h"
VertexBuffer::VertexBuffer(const void *data, size_t size)
{
    glGenBuffers(1,&this->buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER,this->buffer_id);
    glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&this->buffer_id);
}
void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER,this->buffer_id);
}
void VertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}