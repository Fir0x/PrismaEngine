add_executable(
	quaternion_tests
	"quaternion_tests.cpp"
)

target_link_libraries(
	quaternion_tests
	GTest::gtest_main
	core_maths
)

gtest_discover_tests(quaternion_tests)