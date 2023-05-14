set(PUBLIC_FILES
	"public/vec2f.h"
	"public/vec3f.h"
	"public/vec4f.h"
	"public/vec2i.h"
)

set(PRIVATE_FILES
)

add_library(core_maths INTERFACE ${PUBLIC_FILES} ${PRIVATE_FILES})

target_link_libraries(core_maths INTERFACE
	global_config
)