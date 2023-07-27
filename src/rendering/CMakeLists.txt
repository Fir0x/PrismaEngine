set(PRIVATE_FILES
	"private/GUIRenderer.cpp"
	"private/Material.cpp"
	"private/MeshRenderer.cpp"
)

set(PUBLIC_FILES
	"public/GUIRenderer.h"
	"public/Material.h"
	"public/MeshRenderer.h"
)

set(ALL_FILES
	${PRIVATE_FILES}
	${PUBLIC_FILES}
)

add_library(rendering STATIC ${ALL_FILES})

target_link_libraries(rendering PUBLIC
	global_config
	geometry
	rhi
	core
	glfw
)

target_link_libraries(rendering PRIVATE
	glew
	imgui
)