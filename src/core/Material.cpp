#include "Material.h"

#include <GL/glew.h>

namespace BerylEngine
{
	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode, bool writeDepth,
						CullMode cullMode)
		: m_program(program),
		m_blendMode(blendMode),
		m_depthMode(depthMode),
		m_writeDepth(writeDepth),
		m_cullMode(cullMode)
	{
		if (depthMode == DepthMode::None)
			writeDepth = false;
	}

	Material::Material(std::shared_ptr<Program> program, DepthMode depthMode, bool writeDepth, CullMode cullMode)
		: Material(program, BlendMode::None, depthMode, writeDepth, cullMode)
	{
	}

	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode, bool writeDepth)
		: Material(program, blendMode, depthMode, writeDepth, CullMode::Backface)
	{
	}

	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode, bool writeDepth, CullMode cullMode)
		: Material(program, blendMode, DepthMode::Standard, writeDepth, cullMode)
	{
	}

	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode, CullMode cullMode)
		: Material(program, blendMode, depthMode, true, cullMode)
	{
	}

	Material::Material(std::shared_ptr<Program> program, DepthMode depthMode, CullMode cullMode)
		: Material(program, depthMode, true, cullMode)
	{
	}

	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode, CullMode cullMode)
		: Material(program, blendMode, true, cullMode)
	{
	}

	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode, DepthMode depthMode)
		: Material(program, blendMode, depthMode, true)
	{
	}

	Material::Material(std::shared_ptr<Program> program, bool writeDepth, CullMode cullMode)
		: Material(program, DepthMode::Standard, writeDepth, cullMode)
	{
	}

	Material::Material(std::shared_ptr<Program> program, DepthMode depthMode, bool writeDepth)
		: Material(program, BlendMode::None, depthMode, writeDepth)
	{
	}

	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode, bool writeDepth)
		: Material(program, blendMode, DepthMode::Standard, writeDepth)
	{
	}

	Material::Material(std::shared_ptr<Program> program, CullMode cullMode)
		: Material(program, true, cullMode)
	{
	}

	Material::Material(std::shared_ptr<Program> program, DepthMode depthMode)
		: Material(program, depthMode, true)
	{
	}

	Material::Material(std::shared_ptr<Program> program, bool writeDepth)
		: Material(program, DepthMode::Standard, writeDepth)
	{
	}

	Material::Material(std::shared_ptr<Program> program, BlendMode blendMode)
		: Material(program, blendMode, true)
	{
	}

	Material::Material(std::shared_ptr<Program> program)
		: Material(program, true)
	{
	}

	void Material::setTexture(int unit, std::shared_ptr<Texture> texture)
	{
		auto existIt = std::find_if(m_textures.begin(), m_textures.end(),
			[&](const auto& p) { return p.second == texture; });
		if (existIt != m_textures.end())
			existIt->first = unit;
		else
			m_textures.emplace_back(unit, texture);
	}

	void Material::bind() const
	{
		switch (m_blendMode) {
		case BlendMode::None:
			glDisable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			break;

		case BlendMode::Alpha:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_CULL_FACE);
			break;

		case BlendMode::Add:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_COLOR, GL_ONE);
			glEnable(GL_CULL_FACE);
			break;
		}

		switch (m_depthMode) {
		case DepthMode::None:
			glDisable(GL_DEPTH_TEST);
			break;

		case DepthMode::Standard:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_GEQUAL);
			break;

		case DepthMode::Reversed:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			break;
		}

		switch (m_cullMode) {
		case CullMode::None:
			glDisable(GL_CULL_FACE);
			break;
		case CullMode::Frontface:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			break;

		case CullMode::Backface:
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			break;
		}

		glDepthMask(m_writeDepth ? GL_TRUE : GL_FALSE);

		for (const auto& texture : m_textures)
			texture.second->bindToUnit(texture.first);

		m_program->bind();
	}
}