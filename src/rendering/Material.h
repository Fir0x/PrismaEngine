#pragma once

#include <glm/glm.hpp>

#include "../RHI/Program.h"
#include "../RHI/Texture.h"

#include "../core/utils.h"

namespace BerylEngine
{
	class Material
	{
	public:
		enum class BlendMode
		{
			None,
			Alpha,
			Add,
		};

		enum class DepthMode
		{
			None,
			Standard,
			Reversed
		};

		enum class CullMode
		{
			None,
			Frontface,
			Backface
		};

		Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode, bool writeDepth,
					CullMode cullMode);

		Material(std::shared_ptr<Program> program, DepthMode depthMode, bool writeDepth, CullMode cullMode);
		Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode, bool writeDepth);
		Material(std::shared_ptr<Program> program, BlendMode blendMode, bool writeDepth, CullMode cullMode);
		Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode, CullMode cullMode);

		Material(std::shared_ptr<Program> program, DepthMode depthMode, CullMode cullMode);
		Material(std::shared_ptr<Program> program, BlendMode blendMode, CullMode cullMode);
		Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode);

		Material(std::shared_ptr<Program> program, bool writeDepth, CullMode cullMode);
		Material(std::shared_ptr<Program> program, DepthMode depthMode, bool writeDepth);
		Material(std::shared_ptr<Program> program, BlendMode blendMode, bool writeDepth);

		Material(std::shared_ptr<Program> program, CullMode cullMode);
		Material(std::shared_ptr<Program> program, DepthMode depthMode);
		Material(std::shared_ptr<Program> program, bool writeDepth);
		Material(std::shared_ptr<Program> program, BlendMode blendMode);

		Material(std::shared_ptr<Program> program);

		template<typename... Args>
		void setUniform(Args&&... args) const
		{
			m_program->setUniform(FWD(args)...);
		}

		void setTexture(int unit, std::shared_ptr<Texture> texture);

		void bind() const;

	private:
		std::shared_ptr<Program> m_program;
		std::vector<std::pair<int, std::shared_ptr<Texture>>> m_textures;
		BlendMode m_blendMode;
		DepthMode m_depthMode;
		bool m_writeDepth;
		CullMode m_cullMode;
	};
}