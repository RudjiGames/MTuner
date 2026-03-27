--
-- Copyright 2025 Milos Tosic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

dofile("../../../zidar/zidar.lua")
dofile("MTuner.lua")

solution "MTuner"
	setPlatforms()

	projectLoad( "MTuner" )
	projectLoad( "MTunerDLL" )
	projectLoad( "MTunerCmd" )
	projectLoad( "MTunerInject" )
	
	startproject "MTuner"
