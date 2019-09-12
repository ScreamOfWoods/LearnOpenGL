#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
	private:
		unsigned int bufferID;
	public:
		VertexBuffer(const void* data, unsigned int size);
		~VertexBuffer();
		void bind() const;
		void unbind() const;
		unsigned int getBufferID() const;
};

#endif //VERTEX_BUFFER_H
