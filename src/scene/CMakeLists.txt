set(PRIVATE_FILES
	"private/Camera.cpp"
	"private/DirectionalLight.cpp"
	"private/PointLight.cpp"
	"private/Scene.cpp"
	"private/SceneObject.cpp"
	"private/SceneView.cpp"
	"private/Transform.cpp"
)

set(PUBLIC_FILES
	"public/Camera.h"
	"public/DirectionalLight.h"
	"public/PointLight.h"
	"public/Scene.h"
	"public/SceneObject.h"
	"public/SceneView.h"
	"public/Transform.h"
)

set(ALL_FILES
	${PRIVATE_FILES}
	${PUBLIC_FILES}
)

add_library(scene STATIC ${ALL_FILES})

target_link_libraries(scene PUBLIC
	global_config
	glew
	glfw
	glm
	rendering
)

target_link_libraries(scene PRIVATE
	rhi
	geometry
	spdlog
	glm
)