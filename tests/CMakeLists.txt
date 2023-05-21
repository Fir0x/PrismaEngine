enable_testing()

add_executable(
	vector_tests
	"vectors/vector3f_tests.cpp"
	"vectors/vector2f_tests.cpp"
	"vectors/vector4f_tests.cpp"
	"vectors/vector2i_tests.cpp"
)

target_link_libraries(
	vector_tests
	GTest::gtest_main
	glm
)

include(GoogleTest)
gtest_discover_tests(vector_tests)