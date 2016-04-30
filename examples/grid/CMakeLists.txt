add_executable(grid_example

	grid.cc
	function.cc function.hh
	data_model.cc data_model.hh
)

target_link_libraries(grid_example

	qt-binder

	Qt5::Widgets
)
