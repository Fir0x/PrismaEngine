set(PRIVATE_FILES
	"private/APIHandle.cpp"
	"private/ByteBuffer.cpp"
	"private/FrameBuffer.cpp"
	"private/Program.cpp"
	"private/rhiDefs.cpp"
	"private/rhiDefs.h"
	"private/Texture.cpp"
	"private/utils.cpp"
	"private/VertexArray.cpp"
)

set(PUBLIC_FILES
	"public/APIHandle.h"
	"public/ByteBuffer.h"
	"public/FrameBuffer.h"
	"public/Program.h"
	"public/rhiDefs.h"
	"public/rhiDefs.h"
	"public/Texture.h"
	"public/utils.h"
	"public/VertexArray.h"
	"public/VertexBufferLayout.h"
)

set(ALL_FILES
	${PRIVATE_FILES}
	${PUBLIC_FILES}
)

add_library(rhi STATIC ${ALL_FILES})

target_link_libraries(rhi PUBLIC
	global_config
	core
	glew
	opengl32
)

target_link_libraries(rhi PRIVATE
	spdlog
	stb
)

target_compile_definitions(rhi PUBLIC GLEW_STATIC)