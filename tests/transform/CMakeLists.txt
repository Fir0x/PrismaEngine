add_executable(
	transform_tests
	"transform_tests.cpp"
)

target_link_libraries(
	transform_tests
	GTest::gtest_main
	core_maths
	scene
)

gtest_discover_tests(transform_tests)