set(PUBLIC_FILES
	"public/Vector2.h"
	"public/Vector3.h"
	"public/Vector4.h"
	"public/Matrix3.h"
	"public/Matrix4.h"
	"public/Quaternion.h"
	"public/utils.h"
)

set(PRIVATE_FILES
	"private/Quaternion.cpp"
)

add_library(core_maths STATIC ${PUBLIC_FILES} ${PRIVATE_FILES})

target_link_libraries(core_maths INTERFACE
	global_config
)