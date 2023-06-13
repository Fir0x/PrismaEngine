add_executable(
	utils_test
	"utils_tests.cpp"
)

target_link_libraries(
	utils_test
	GTest::gtest_main
	core_maths
)

gtest_discover_tests(utils_test)