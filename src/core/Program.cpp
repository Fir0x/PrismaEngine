#include "Program.h"

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sstream>

#include "glErrors.h"

namespace BerylEngine
{
	static std::string glShader2Str(GLenum shaderType)
	{
		switch (shaderType)
		{
		case GL_VERTEX_SHADER:
			return "vertex";
		case GL_GEOMETRY_SHADER:
			return "geometry";
		case GL_FRAGMENT_SHADER:
			return "fragment";
		case GL_COMPUTE_SHADER:
			return "compute";
		default:
			return "unknown type";
		}
	}

	static unsigned int compileShader(const std::string& source, unsigned int type)
	{
		unsigned int id = glCreateShader(type); GL_AFTER_CHECK();

		const GLchar* src = source.c_str();
		GL_CALL(glShaderSource(id, 1, &src, 0));
		GL_CALL(glCompileShader(id));

		GLint compile_status = GL_TRUE;
		GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status));

		if (compile_status != GL_TRUE) {
			GLint log_size;
			GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_size));
			char* log = (char*)std::malloc(log_size * sizeof(char));
			if (log != nullptr) {
				GL_CALL(glGetShaderInfoLog(id, log_size, &log_size, log));

				spdlog::error("Failed to compile {} shader:\n{}", glShader2Str(type), log);
				std::free(log);
			}

			GL_CALL(glDeleteShader(id));

			return 0;
		}

		return id;

	}

	static bool linkProgram(unsigned int programId)
	{
		GL_CALL(glLinkProgram(programId));

		GLint link_status = GL_TRUE;
		GL_CALL(glGetProgramiv(programId, GL_LINK_STATUS, &link_status));

		if (link_status != GL_TRUE) {
			GLint log_size;
			char* log;
			GL_CALL(glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &log_size));

			log = (char*)std::malloc((size_t)log_size + 1);
			if (log != nullptr) {
				GL_CALL(glGetProgramInfoLog(programId, log_size, &log_size, log));
				spdlog::error("Failed to link program:\n{}", log);
				std::free(log);
			}

			return false;
		}

		return true;
	}

	Program::Program(const std::string& compute_src)
	{
		m_id = glCreateProgram(); GL_AFTER_CHECK();

		auto compute = compileShader(compute_src, GL_COMPUTE_SHADER);

		GL_CALL(glAttachShader(m_id, compute));

		bool linkSuccess = linkProgram(m_id);

		GL_CALL(glDeleteShader(compute));

		if (!linkSuccess)
		{
			GL_CALL(glDeleteProgram(m_id));
		}

		fetchUniformLocations();
	}

	Program::Program(const std::string& vertex_src, const std::string& fragment_src)
	{
		m_id = glCreateProgram(); GL_AFTER_CHECK();

		auto vertex = compileShader(vertex_src, GL_VERTEX_SHADER);
		auto fragment = compileShader(fragment_src, GL_FRAGMENT_SHADER);

		GL_CALL(glAttachShader(m_id, vertex));
		GL_CALL(glAttachShader(m_id, fragment));

		bool linkSuccess = linkProgram(m_id);

		GL_CALL(glDeleteShader(vertex));
		GL_CALL(glDeleteShader(fragment));

		if (!linkSuccess)
		{
			GL_CALL(glDeleteProgram(m_id));
		}

		fetchUniformLocations();
	}

	Program::Program(const std::string& vertex_src, const std::string& geometry_src, const std::string& fragment_src)
	{
		m_id = glCreateProgram(); GL_AFTER_CHECK();

		auto vertex = compileShader(vertex_src, GL_VERTEX_SHADER);
		auto geometry = compileShader(geometry_src, GL_GEOMETRY_SHADER);
		auto fragment = compileShader(fragment_src, GL_FRAGMENT_SHADER);

		GL_CALL(glAttachShader(m_id, vertex));
		GL_CALL(glAttachShader(m_id, geometry));
		GL_CALL(glAttachShader(m_id, fragment));

		bool linkSuccess = linkProgram(m_id);

		GL_CALL(glDeleteShader(vertex));
		GL_CALL(glDeleteShader(geometry));
		GL_CALL(glDeleteShader(fragment));

		if (!linkSuccess)
		{
			GL_CALL(glDeleteProgram(m_id));
		}

		fetchUniformLocations();
	}

	Program::~Program()
	{
		GL_CALL(glDeleteProgram(m_id));
	}

	static std::string loadShaderFile(const std::string& path)
	{
		std::ifstream stream(path);
		std::stringstream shader;
		if (stream.is_open())
			shader << stream.rdbuf();

		return shader.str();
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& compute_path)
	{
		auto compute_src = loadShaderFile(compute_path);

		spdlog::debug("Generating program from:\n- Compute: {}", compute_path);

		return std::make_shared<Program>(compute_src);
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& vertex_path, const std::string& fragment_path)
	{
		auto vertex_src = loadShaderFile(vertex_path);
		auto fragment_src = loadShaderFile(fragment_path);

		spdlog::debug("Generating program from:\n- Vertex: {}\n- Fragment: {}", vertex_path, fragment_path);

		return std::make_shared<Program>(vertex_src, fragment_src);
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& vertex_path,
												const std::string& geometry_path,
												const std::string& fragment_path)
	{
		auto vertex_src = loadShaderFile(vertex_path);
		auto geometry_src = loadShaderFile(geometry_path);
		auto fragment_src = loadShaderFile(fragment_path);

		spdlog::debug("Generating program from:\n- Vertex: {}\n- Geometry: {}\n- Fragment: {}", vertex_path,
						geometry_path, fragment_path);

		return std::make_shared<Program>(vertex_src, geometry_src, fragment_src);
	}

	void Program::use()
	{
		GL_CALL(glUseProgram(m_id));
	}

	void Program::fetchUniformLocations()
	{
		int uniform_count = 0;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &uniform_count);

		for (int i = 0; i != uniform_count; ++i) {
			char name[1024] = {};
			int len = 0;
			int discard = 0;
			GLenum type = GL_NONE;

			glGetActiveUniform(m_id, i, sizeof(name), &len, &discard, &type, name);

			m_uniformLocations.emplace(name, glGetUniformLocation(m_id, name));
		}
	}

	int Program::getUniformLocation(const char* name) const
	{
		if (m_uniformLocations.find(name) == m_uniformLocations.end())
			return -1;

		return m_uniformLocations.at(name);
	}

	void Program::setUniform(const char* name, int v0) const
	{
		int location = getUniformLocation(name);
		GL_CALL(glProgramUniform1i(m_id, location, v0));
	}

	void Program::setUniform(const char* name, float v0) const
	{
		int location = getUniformLocation(name);
		GL_CALL(glProgramUniform1f(m_id, location, v0));
	}

	void Program::setUniform(const char* name, float v0, float v1, float v2) const
	{
		int location = getUniformLocation(name);
		GL_CALL(glProgramUniform3f(m_id, location, v0, v1, v2));
	}

	void Program::setUniform(const char* name, const glm::vec3& v) const
	{
		setUniform(name, v.x, v.y, v.z);
	}

	void Program::setUniform(const char* name, float v0, float v1, float v2, float v3) const
	{
		int location = getUniformLocation(name);
		GL_CALL(glProgramUniform4f(m_id, location, v0, v1, v2, v3));
	}

	void Program::setUniform(const char* name, const glm::mat3& matrix, bool transpose) const
	{
		int location = getUniformLocation(name);
		GL_CALL(glProgramUniformMatrix3fv(m_id, location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix)));
	}

	void Program::setUniform(const char* name, const glm::mat4& matrix, bool transpose) const
	{
		int location = getUniformLocation(name);
		GL_CALL(glProgramUniformMatrix4fv(m_id, location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix)));
	}
}