add_executable(grid_example

	grid.cc
	function.cc function.hh
)

target_link_libraries(grid_example

	Qt5::Widgets
)
