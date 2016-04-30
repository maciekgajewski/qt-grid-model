add_library(qt-binder

	qt-binder.cc qt-binder.hh
)

target_include_directories(qt-binder INTERFACE ..)

target_link_libraries(qt-binder

	Qt5::Core
)
