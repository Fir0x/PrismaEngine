add_subdirectory(core)
add_subdirectory(geometry)
add_subdirectory(input)
add_subdirectory(rendering)
add_subdirectory(RHI)
add_subdirectory(scene)

add_executable(PrismaEngine main.cpp)

target_link_libraries(PrismaEngine PUBLIC
	global_config
)

target_link_libraries(PrismaEngine PRIVATE
	glew
	spdlog
	imgui
	geometry
	input
	scene
	rhi
	rendering
)