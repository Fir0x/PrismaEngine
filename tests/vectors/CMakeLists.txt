add_executable(
	vector_tests
	"vector3f_tests.cpp"
	"vector2f_tests.cpp"
	"vector4f_tests.cpp"
	"vector2i_tests.cpp"
)

target_link_libraries(
	vector_tests
	GTest::gtest_main
	core_maths
	glm
)

gtest_discover_tests(vector_tests)