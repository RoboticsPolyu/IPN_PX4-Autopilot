
add_subdirectory(mathematics)

px4_add_module(
	MODULE modules__mc_mpc_control
	MAIN mc_mpc_control
	COMPILE_FLAGS
	SRCS
		mc_mpc_control.cpp
		mc_mpc_control.hpp
	DEPENDS
		mathlib
	)
