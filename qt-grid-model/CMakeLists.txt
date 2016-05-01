add_library(qt-grid-model

	qt-grid-model.cc qt-grid-model.hh
	grid_model.cc grid_model.hh
)

target_include_directories(qt-grid-model INTERFACE ..)

target_link_libraries(qt-grid-model

	Qt5::Core
)
