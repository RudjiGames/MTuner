--
-- Copyright 2023 Milos Tosic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

local cp = (function(x) return debug.getinfo(2, "S").source:sub(2):match("(.*[/\\])")  end)()
while os.isdir(cp) do cp = path.getabsolute(cp .. "/..") local tp = cp .. "/build/build.lua"
if os.isfile(tp) then dofile (tp) break end end if RTM_ROOT_DIR == nil then
print("EROR: dependency missing - build. Cannot continue.") os.exit() end

solution "rmem"
	setPlatforms()

	addProject_lib("rmem")
	addProject_lib_sample("rmem", "linker", false)
	addProject_lib_sample("rmem", "manual", false)

