#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "RenderTarget.h"

namespace TEngine::Graphics
{
	struct RenderObject;

	class MirrorEffect
	{
	public:

		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void DebugUI();

		void SetFocus(const Math::Vector3& focusPosition);
		void SetSize(float size);
		const Texture& GetMirrorImage() const;

		//const Camera& GetLightCamera() const;

	private:
		
		RenderTarget mMirrorRenderTarget;
		float mSize = 100.0f;
	};
}
