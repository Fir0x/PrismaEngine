set(PRIVATE_FILES
	"private/utils.cpp"
)

set(PUBLIC_FILES
	"public/utils.h"
)

set(ALL_FILES
	${PRIVATE_FILES}
	${PUBLIC_FILES}
)

add_library(core_utils STATIC ${ALL_FILES})

target_link_libraries(core_utils PUBLIC
	global_config
)

target_link_libraries(core_utils PRIVATE
	spdlog
)