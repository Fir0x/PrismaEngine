#pragma once

#include <glm/glm.hpp>
#include <map>
#include <optional>
#include <string>

#include "Program.h"
#include "Texture.h"

#include "utils.h"

namespace BerylEngine
{
	class Material
	{
	private:
		std::shared_ptr<Program> m_program;

	public:
		Material(std::shared_ptr<Program> program);

		template<typename... Args>
		void setUniform(Args&&... args) const
		{
			m_program->setUniform(FWD(args)...);
		}

		void bind() const;
	};
}