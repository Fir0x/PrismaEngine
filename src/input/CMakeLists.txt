set(PRIVATE_FILES
	"private/inputManager.cpp"
)

set(PUBLIC_FILES
	"public/inputManager.h"
)

set(ALL_FILES
	${PRIVATE_FILES}
	${PUBLIC_FILES}
)

add_library(input STATIC ${ALL_FILES})

target_link_libraries(input PUBLIC
	global_config
	glfw
	scene
	rendering
)