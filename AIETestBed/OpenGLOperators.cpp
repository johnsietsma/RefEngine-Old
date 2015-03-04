#include "OpenGLOperators.h"

#include <iostream>

template<typename Child>
Child* CastBufferType(Buffer* b, Child* c) {
	return static_cast<Child*>(b);
}

void OpenGLOperators::BindBuffer(std::shared_ptr<Buffer> pBuffer)
{
	BindBufferImpl(CastBufferType(pBuffer, pBuffer));
}

void OpenGLOperators::BindBufferImpl(std::shared_ptr<VBO> pBuffer)
{
	std::cout << "VBO" << std::endl;
};
