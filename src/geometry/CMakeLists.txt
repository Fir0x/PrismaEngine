set(PRIVATE_FILES
	"private/meshUtilities.cpp"
	"private/StaticMesh.cpp"
)

set(PUBLIC_FILES
	"public/meshUtilities.h"
	"public/StaticMesh.h"
)

set(ALL_FILES
	${PRIVATE_FILES}
	${PUBLIC_FILES}
)

add_library(geometry STATIC ${ALL_FILES})

target_link_libraries(geometry PUBLIC
	global_config
	rhi
)

target_link_libraries(geometry PRIVATE
	core
	spdlog
)