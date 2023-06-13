add_executable(
	matrix_tests
	"matrix3f_tests.cpp"
	"matrix4f_tests.cpp"
)

target_link_libraries(
	matrix_tests
	GTest::gtest_main
	core_maths
)

gtest_discover_tests(matrix_tests)