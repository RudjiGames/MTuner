--
-- Copyright (c) 2017 Milos Tosic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

local scriptDir = path.getdirectory(debug.getinfo(2, "S").source:sub(2)) .. "/.."
local relativePath = scriptDir
for v=1,6,1 do
	relativePath = relativePath .. "/.."
	local globals_script = path.getabsolute(relativePath) .. "/build/globals.lua"
	if os.isfile(globals_script) then dofile (globals_script) break end
end

solution "MTuner"
	configurations { "debug", "release", "retail" }
	setPlatforms()

	startproject("MTuner")

	loadProject( "MTunerDLL" )
	loadProject( "MTunerCmd" )
	loadProject( "MTunerInject" )
	loadProject( "MTuner" )

