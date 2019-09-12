#include <glad/glad.h>
#include <elementBuffer.h>

ElementBuffer::ElementBuffer(const unsigned int* data, unsigned int count)
	:count(count)
{
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

ElementBuffer::~ElementBuffer()
{
	glDeleteBuffers(1, &bufferID);
}

void ElementBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}

void ElementBuffer::unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int ElementBuffer::getBufferID() const { return bufferID; }
unsigned int ElementBuffer::getCount() const { return count; }
