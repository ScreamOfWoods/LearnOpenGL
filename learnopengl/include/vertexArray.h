#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <vertexLayout.h>
#include <vertexBuffer.h>

class VertexArray
{
	private:
		unsigned int arrayID;	
	public:
		VertexArray();
		~VertexArray();
		
		void addBuffer(const VertexBuffer& vb, const VertexLayout& layout);
		void bind() const;
		void unbind() const;
		
};

#endif //VERTEX_ARRAY_H
