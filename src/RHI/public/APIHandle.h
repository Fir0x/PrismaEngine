#pragma once

#include "core/public/utils.h"

namespace BerylEngine
{
	template <class T>
	class APIHandle : NonCopyable
	{
	public:
		explicit APIHandle(T handle)
			: m_handle(handle)
		{
		}

		APIHandle(APIHandle&& other)
			: m_handle(other.m_handle)
		{
		}

		APIHandle& operator=(APIHandle&& other) {
			m_handle = other.m_handle;
			return *this;
		}

		T get() const
		{
			return m_handle;
		}

		virtual bool isValid() const = 0;

	protected:
		T m_handle;
	};

	/// <summary>
	/// OpenGL API handle
	/// </summary>
	class GLHandle : public APIHandle<unsigned int>
	{
	public:
		GLHandle(unsigned int handle);
		// Inherited via APIHandle
		virtual bool isValid() const override;
	};
}