find_package(Boost REQUIRED)

add_executable(multi-index-complexity EXCLUDE_FROM_ALL
	multi-index-complexity.cc
)

target_link_libraries(multi-index-complexity
	benchmark # Google benchmark, assumed in path

	pthread
)
