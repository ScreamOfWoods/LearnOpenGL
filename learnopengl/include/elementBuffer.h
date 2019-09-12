#ifndef ELEMENT_BUFFER_H
#define ELEMENT_BUFFER_H

class ElementBuffer
{
	private:
		unsigned int bufferID;
		unsigned int count;
	public:
		ElementBuffer(const unsigned int* data, unsigned int count);
		~ElementBuffer();
		void bind() const;
		void unbind() const;
		unsigned int getBufferID() const;
		unsigned int getCount() const;
};

#endif //VERTEX_BUFFER_H
