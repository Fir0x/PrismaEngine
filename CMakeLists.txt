cmake_minimum_required(VERSION 3.11)

project(
	PrismaEngine
	VERSION 0.2.0
	LANGUAGES CXX)

include(FetchContent)

message(STATUS "Start dependencies configuration")

FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_TAG 3.3.8
)

FetchContent_Declare(
	glew
	URL https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download
	DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
	glm
	GIT_REPOSITORY https://github.com/g-truc/glm
	GIT_TAG 0.9.9.8
)

FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui
	GIT_TAG v1.89.5
)

FetchContent_Declare(
	spdlog
	GIT_REPOSITORY https://github.com/gabime/spdlog
	GIT_TAG v1.11.0
)

FetchContent_Declare(
	stb
	GIT_REPOSITORY https://github.com/nothings/stb
)

FetchContent_MakeAvailable(
	glfw
	glew
	glm
	imgui
	spdlog
	stb
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_library(glew STATIC IMPORTED)
set_property(TARGET glew PROPERTY
	IMPORTED_LOCATION ${glew_SOURCE_DIR}/lib/Release/x64/glew32s.lib
)
get_target_property(LOCATIONTEST glew IMPORTED_LOCATION)
target_include_directories(glew INTERFACE ${glew_SOURCE_DIR}/include)
target_compile_definitions(glew INTERFACE GLEW_STATIC)

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${stb_SOURCE_DIR}/)

add_library(imgui STATIC
	"${imgui_SOURCE_DIR}/imconfig.h"
	"${imgui_SOURCE_DIR}/imgui.cpp"
	"${imgui_SOURCE_DIR}/imgui.h"
	"${imgui_SOURCE_DIR}/imgui_draw.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp"
	"${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h"
	"${imgui_SOURCE_DIR}/imgui_internal.h"
	"${imgui_SOURCE_DIR}/imgui_tables.cpp"
	"${imgui_SOURCE_DIR}/imgui_widgets.cpp"
	"${imgui_SOURCE_DIR}/imstb_rectpack.h"
	"${imgui_SOURCE_DIR}/imstb_textedit.h"
	"${imgui_SOURCE_DIR}/imstb_truetype.h"
)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
target_link_libraries(imgui PUBLIC glfw)

message(STATUS "Dependencies configuration done")

set(CMAKE_CXX_STANDARD 20)

add_library(global_config INTERFACE)
include_directories(global_config INTERFACE src)

add_subdirectory(src)