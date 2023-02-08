#include "Material.h"

namespace BerylEngine
{
	Material::Material(std::shared_ptr<Program> program)
	{
		m_program = program;
	}

	void Material::bind() const
	{
		m_program->use();
	}
}