
add_subdirectory(mathematics)

px4_add_module(
	MODULE modules__mc_tm_control
	MAIN mc_tm_control
	COMPILE_FLAGS
	SRCS
		mc_trust_moments_control.cpp
		mc_trust_moments_control.cpp
	DEPENDS
		mathlib
	)
