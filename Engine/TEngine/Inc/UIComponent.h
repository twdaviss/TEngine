#pragma once

#include "Component.h"

namespace TEngine
{
	class UIComponent : public Component
	{
	public:
		virtual void Render() = 0;
	};
}
