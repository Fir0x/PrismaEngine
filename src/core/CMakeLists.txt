add_subdirectory(maths)
add_subdirectory(utils)

add_library(core INTERFACE)
target_link_libraries(core INTERFACE
	core_utils
	core_maths
)