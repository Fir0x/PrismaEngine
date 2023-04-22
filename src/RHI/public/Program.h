#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <span>

#include <glm/glm.hpp>

#include "APIHandle.h"

namespace PrismaEngine
{
	struct ShaderSources
	{
		std::string vertexShader;
		std::string fragmentShader;
	};

	class Program
	{
	public:
		Program(const std::string& compute_src);
		Program(const std::string& vertex_src, const std::string& fragment_src);
		Program(const std::string& vertex_src, const std::string& geometry_src, const std::string& fragment_src);
		~Program();

		/**
		 * @brief Create a shader program with the following stage: compute
		 * @param compute_path 
		 * @param defines Shader definitions to add
		 * @return 
		*/
		static std::shared_ptr<Program> fromFiles(const std::string& compute_path, std::span<std::string> defines);
		/**
		 * @brief Create a shader program with the following stage: vertex, fragment
		 * @param vertex_path 
		 * @param fragment_path 
		 * @param defines Shader definitions to add
		 * @return 
		*/
		static std::shared_ptr<Program> fromFiles(const std::string& vertex_path, const std::string& fragment_path,
													std::span<std::string> defines);
		/**
		 * @brief Create a shader program with the following stage: vertex, geometry, fragment
		 * @param vertex_path 
		 * @param geometry_path 
		 * @param fragment_path 
		 * @param defines Shader definitions to add
		 * @return 
		*/
		static std::shared_ptr<Program> fromFiles(const std::string& vertex_path, const std::string& geometry_path,
													const std::string& fragment_path, std::span<std::string> defines);

		/**
		 * @brief Create a shader program with the following stage: compute
		 * @param compute_path 
		 * @return 
		*/
		static std::shared_ptr<Program> fromFiles(const std::string& compute_path);
		/**
		 * @brief Create a shader program with the following stage: vertex, fragment
		 * @param vertex_path 
		 * @param fragment_path 
		 * @return 
		*/
		static std::shared_ptr<Program> fromFiles(const std::string& vertex_path, const std::string& fragment_path);
		/**
		 * @brief Create a shader program with the following stage: vertex, geometry, fragment
		 * @param vertex_path 
		 * @param geometry_path 
		 * @param fragment_path 
		 * @return 
		*/
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

	private:
		GLHandle m_handle;
		std::unordered_map<std::string, int> m_uniformLocations;

		void fetchUniformLocations();
		int getUniformLocation(const char* name) const;
	};
}