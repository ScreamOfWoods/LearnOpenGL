#ifndef VERTEX_LAYOUT_H
#define VERTEX_LAYOUT_H

#include <glad/glad.h>
#include <vector>
#include <iostream>

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned int size;
	unsigned char normalized;
};

class VertexLayout
{
	private:
		std::vector<struct VertexBufferElement> elements;
		unsigned int stride;
	public:
		VertexLayout() : stride(0) {};
		void push(unsigned int count)
		{
			elements.push_back({ GL_FLOAT, count, sizeof(float), GL_FALSE });
			stride += count * sizeof(float);
		}

		inline const std::vector<struct VertexBufferElement> getElements() const { return elements; }
		inline unsigned int getStride() const { return stride; }

};

#endif //VERTEX_LAYOUT_H
