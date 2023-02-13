#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <span>

#include <glm/glm.hpp>

namespace BerylEngine
{
	struct ShaderSources
	{
		std::string vertexShader;
		std::string fragmentShader;
	};

	class Program
	{
	private:
		unsigned int m_id;
		std::unordered_map<std::string, int> m_uniformLocations;

		void fetchUniformLocations();
		int getUniformLocation(const char* name) const;

	public:
		Program(const std::string& compute_src);
		Program(const std::string& vertex_src, const std::string& fragment_src);
		Program(const std::string& vertex_src, const std::string& geometry_src, const std::string& fragment_src);
		~Program();

		static std::shared_ptr<Program> fromFiles(const std::string& compute_path, std::span<std::string> defines);
		static std::shared_ptr<Program> fromFiles(const std::string& vertex_path, const std::string& fragment_path,
													std::span<std::string> defines);
		static std::shared_ptr<Program> fromFiles(const std::string& vertex_path, const std::string& geometry_path,
													const std::string& fragment_path, std::span<std::string> defines);

		static std::shared_ptr<Program> fromFiles(const std::string& compute_path);
		static std::shared_ptr<Program> fromFiles(const std::string& vertex_path, const std::string& fragment_path);
		static std::shared_ptr<Program> fromFiles(const std::string& vertex_path, const std::string& geometry_path,
													const std::string& fragment_path);

		void bind();

		void setUniform(const char* name, int v0) const;
		void setUniform(const char* name, float v0) const;
		void setUniform(const char* name, float v0, float v1, float v2) const;
		void setUniform(const char* name, const glm::vec3& v) const;
		void setUniform(const char* name, float v0, float v1, float v2, float v3) const;
		void setUniform(const char* name, const glm::mat3& matrix, bool transpose = false) const;
		void setUniform(const char* name, const glm::mat4& matrix, bool transpose = false) const;
	};
}