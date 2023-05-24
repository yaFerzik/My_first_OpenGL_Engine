#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Mesh.h"

class FrameBuffer
{
public:
	unsigned int FBO;
	unsigned int framebufferTexture;
	unsigned int RBO;
	int slot;

	unsigned int vao;

	FrameBuffer(int slot);

	void Activate();

	void Deactivate();

	void Draw(Shader shader);
};

#endif