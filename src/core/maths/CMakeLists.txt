set(PUBLIC_FILES
	"public/Vector2.h"
	"public/Vector3.h"
	"public/Vector4.h"
	"public/mat3f.h"
	"public/mat4f.h"
	"public/matrix.h"
	"public/utils.h"
)

set(PRIVATE_FILES
 
)

add_library(core_maths INTERFACE ${PUBLIC_FILES} ${PRIVATE_FILES})

target_link_libraries(core_maths INTERFACE
	global_config
)