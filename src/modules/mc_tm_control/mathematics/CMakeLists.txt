
px4_add_library(Mathematics
	Mathematics.cpp
	Mathematics.hpp
)
target_include_directories(Mathematics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

px4_add_unit_gtest(SRC Mathematics.cpp LINKLIBS Mathematics)
