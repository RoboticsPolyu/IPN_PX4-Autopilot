
add_subdirectory(mathematics)

px4_add_module(
	MODULE modules__mc_fm_control
	MAIN mc_fm_control
	COMPILE_FLAGS
	SRCS
		MulticopterForceMomentsControl.cpp
		MulticopterForceMomentsControl.hpp
	DEPENDS
		# PositionControl
		# Takeoff
		# controllib
		# geo
		# SlewRate
	)
