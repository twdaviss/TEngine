#pragma once

namespace TEngine::Graphics
{
	class VertexShader final
	{
	public:
		template<class VertexType>
		void Initialize(const std::filesystem::path& filepath)
		{
			Initialize(filepath, VertexType::Format);
		}
		void Initialize(const std::filesystem::path& filepath, uint32_t format);
		void Terminate();
		void Bind();

	private:
		ID3D11VertexShader* mVertexShader = nullptr;
		ID3D11InputLayout* mInputLayout = nullptr;
	};

}