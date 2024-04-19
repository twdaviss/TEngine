#include "Precompiled.h"
#include "RenderObject.h"

using namespace TEngine;
using namespace TEngine::Graphics;

void RenderObject::Terminate()
{
	meshBuffer.Terminate();
}