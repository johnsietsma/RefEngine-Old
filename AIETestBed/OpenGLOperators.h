#pragma once

#include <memory>

class Buffer;
class VBO;

class OpenGLOperators
{
public:
	void BindBuffer(std::shared_ptr<Buffer> pBuffer);
private:
	void BindBufferImpl(std::shared_ptr<VBO> pBuffer);

};

