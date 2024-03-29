#include "Program.h"

#include <GL/glew.h>
#include <glm/ext.hpp>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sstream>

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
		unsigned int id = glCreateShader(type);

		const GLchar* src = source.c_str();
		glShaderSource(id, 1, &src, 0);
		glCompileShader(id);

		GLint compile_status = GL_TRUE;
		glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);

		if (compile_status != GL_TRUE) {
			GLint log_size;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_size);
			char* log = (char*)std::malloc(log_size * sizeof(char));
			if (log != nullptr) {
				glGetShaderInfoLog(id, log_size, &log_size, log);

				spdlog::error("Failed to compile {} shader:\n{}", glShader2Str(type), log);
				std::free(log);
			}

			glDeleteShader(id);

			return 0;
		}

		return id;

	}

	static bool linkProgram(unsigned int programId)
	{
		glLinkProgram(programId);

		GLint link_status = GL_TRUE;
		glGetProgramiv(programId, GL_LINK_STATUS, &link_status);

		if (link_status != GL_TRUE) {
			GLint log_size;
			char* log;
			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &log_size);

			log = (char*)std::malloc((size_t)log_size + 1);
			if (log != nullptr) {
				glGetProgramInfoLog(programId, log_size, &log_size, log);
				spdlog::error("Failed to link program:\n{}", log);
				std::free(log);
			}

			return false;
		}

		return true;
	}

	Program::Program(const std::string& compute_src)
	{
		m_handle = glCreateProgram();

		auto compute = compileShader(compute_src, GL_COMPUTE_SHADER);

		glAttachShader(m_handle, compute);

		bool linkSuccess = linkProgram(m_handle);

		glDeleteShader(compute);

		if (!linkSuccess)
		{
			glDeleteProgram(m_handle);
		}

		fetchUniformLocations();
	}

	Program::Program(const std::string& vertex_src, const std::string& fragment_src)
	{
		m_handle = glCreateProgram();

		auto vertex = compileShader(vertex_src, GL_VERTEX_SHADER);
		auto fragment = compileShader(fragment_src, GL_FRAGMENT_SHADER);

		glAttachShader(m_handle, vertex);
		glAttachShader(m_handle, fragment);

		bool linkSuccess = linkProgram(m_handle);

		glDeleteShader(vertex);
		glDeleteShader(fragment);

		if (!linkSuccess)
		{
			glDeleteProgram(m_handle);
		}

		fetchUniformLocations();
	}

	Program::Program(const std::string& vertex_src, const std::string& geometry_src, const std::string& fragment_src)
	{
		m_handle = glCreateProgram();

		auto vertex = compileShader(vertex_src, GL_VERTEX_SHADER);
		auto geometry = compileShader(geometry_src, GL_GEOMETRY_SHADER);
		auto fragment = compileShader(fragment_src, GL_FRAGMENT_SHADER);

		glAttachShader(m_handle, vertex);
		glAttachShader(m_handle, geometry);
		glAttachShader(m_handle, fragment);

		bool linkSuccess = linkProgram(m_handle);

		glDeleteShader(vertex);
		glDeleteShader(geometry);
		glDeleteShader(fragment);

		if (!linkSuccess)
		{
			glDeleteProgram(m_handle);
		}

		fetchUniformLocations();
	}

	Program::~Program()
	{
		glDeleteProgram(m_handle);
	}

	static std::string retrieveInclude(const std::string& includeLine, const std::string& startPath)
	{
		char startGuard = '\"';
		size_t startGuardPos = includeLine.find(startGuard);
		if (startGuardPos == std::string::npos)
		{
			startGuard = '<';
			startGuardPos = includeLine.find(startGuard);
			if (startGuardPos == std::string::npos)
			{
				spdlog::warn("Include first guard not found. Nothing will be included.");
				return "";
			}
		}

		size_t endGuardPos = includeLine.find(startGuard == '\"' ? '\"' : '>', startGuardPos + 1);
		if (endGuardPos == std::string::npos)
		{
			spdlog::warn("Include second guard not found. Nothing will be included.");
			return "";
		}

		const std::string includePath = includeLine.substr(startGuardPos + 1, endGuardPos - startGuardPos - 1);
		std::ifstream stream(startPath + includePath);
		std::stringstream includeContent;
		if (stream.is_open())
			includeContent << stream.rdbuf();
		else
			spdlog::warn("Include {} not found. Nothing will be included.\nInclude path was evaluated at {}.",
				includePath, startPath + includePath);

		return includeContent.str();
	}

	static std::string loadShaderFile(const std::string& path, std::span<std::string> defines)
	{
		std::ifstream stream(path);
		std::stringstream shader;
		if (stream.is_open())
		{
			size_t folderPathEnd = path.find_last_of("\\/");
			const std::string folderPath = folderPathEnd == std::string::npos ? "./"
				: path.substr(0, folderPathEnd + 1);

			std::string line;
			bool isFirstLine = true;
			while (std::getline(stream, line))
			{
				if (isFirstLine)
				{
					if (line.starts_with("#version"))
					{
						shader << line << "\n";
						for (const auto& def : defines)
							shader << "#define " << def << " 1\n";
					}
					else
					{
						spdlog::warn("Loading of {} was cancelled as it does not specify GLSL version on first line.",
							path);
						return "";
					}

					isFirstLine = false;
					continue;
				}

				if (line[0] == '#')
				{
					if (line.starts_with("#include"))
						shader << retrieveInclude(line, folderPath) << "\n";
					else
						shader << line << "\n";
				}
				else
					shader << line << "\n";
			}
		}

		return shader.str();
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& compute_path, std::span<std::string> defines)
	{
		auto compute_src = loadShaderFile(compute_path, defines);

		spdlog::debug("Generating program from:\n- Compute: {}", compute_path);

		return std::make_shared<Program>(compute_src);
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& vertex_path, const std::string& fragment_path,
												std::span<std::string> defines)
	{
		auto vertex_src = loadShaderFile(vertex_path, defines);
		auto fragment_src = loadShaderFile(fragment_path, defines);

		spdlog::debug("Generating program from:\n- Vertex: {}\n- Fragment: {}", vertex_path, fragment_path);

		return std::make_shared<Program>(vertex_src, fragment_src);
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& vertex_path, const std::string& geometry_path,
												const std::string& fragment_path, std::span<std::string> defines)
	{
		auto vertex_src = loadShaderFile(vertex_path, defines);
		auto geometry_src = loadShaderFile(geometry_path, defines);
		auto fragment_src = loadShaderFile(fragment_path, defines);

		spdlog::debug("Generating program from:\n- Vertex: {}\n- Geometry: {}\n- Fragment: {}", vertex_path,
			geometry_path, fragment_path);

		return std::make_shared<Program>(vertex_src, geometry_src, fragment_src);
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& compute_path)
	{
		return fromFiles(compute_path, std::span<std::string>());
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& vertex_path, const std::string& fragment_path)
	{
		return fromFiles(vertex_path, fragment_path, std::span<std::string>());
	}

	std::shared_ptr<Program> Program::fromFiles(const std::string& vertex_path,
												const std::string& geometry_path,
												const std::string& fragment_path)
	{
		return fromFiles(vertex_path, geometry_path, fragment_path, std::span<std::string>());
	}

	void Program::bind()
	{
		glUseProgram(m_handle);
	}

	void Program::fetchUniformLocations()
	{
		int uniform_count = 0;
		glGetProgramiv(m_handle, GL_ACTIVE_UNIFORMS, &uniform_count);

		for (int i = 0; i != uniform_count; ++i) {
			char name[1024] = {};
			int len = 0;
			int discard = 0;
			GLenum type = GL_NONE;

			glGetActiveUniform(m_handle, i, sizeof(name), &len, &discard, &type, name);

			m_uniformLocations.emplace(name, glGetUniformLocation(m_handle, name));
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
		glProgramUniform1i(m_handle, location, v0);
	}

	void Program::setUniform(const char* name, float v0) const
	{
		int location = getUniformLocation(name);
		glProgramUniform1f(m_handle, location, v0);
	}

	void Program::setUniform(const char* name, float v0, float v1, float v2) const
	{
		int location = getUniformLocation(name);
		glProgramUniform3f(m_handle, location, v0, v1, v2);
	}

	void Program::setUniform(const char* name, const glm::vec3& v) const
	{
		setUniform(name, v.x, v.y, v.z);
	}

	void Program::setUniform(const char* name, float v0, float v1, float v2, float v3) const
	{
		int location = getUniformLocation(name);
		glProgramUniform4f(m_handle, location, v0, v1, v2, v3);
	}

	void Program::setUniform(const char* name, const glm::mat3& matrix, bool transpose) const
	{
		int location = getUniformLocation(name);
		glProgramUniformMatrix3fv(m_handle, location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}

	void Program::setUniform(const char* name, const glm::mat4& matrix, bool transpose) const
	{
		int location = getUniformLocation(name);
		glProgramUniformMatrix4fv(m_handle, location, 1, transpose ? GL_TRUE : GL_FALSE, glm::value_ptr(matrix));
	}
}