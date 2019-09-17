#include <glad/glad.h>
#include <vertexArray.h>
#include <vector>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &arrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &arrayID);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexLayout& layout)
{
	bind();
	vb.bind();
	const std::vector<struct VertexBufferElement>& elements = layout.getElements();
	unsigned int offset = 0;

	for(unsigned int i = 0; i < elements.size(); i++) {
		const struct VertexBufferElement& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, 
				element.normalized, layout.getStride(), (const void*) offset);
		offset += element.count * element.size;
	}
}

void VertexArray::bind() const
{
	glBindVertexArray(arrayID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
