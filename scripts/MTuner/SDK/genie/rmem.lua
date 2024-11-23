--
-- Copyright 2023 Milos Tosic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

function projectExtraConfigExecutable_linker()
	configuration { "gmake" }
		if getTargetCompiler() == "mingw-gcc"	or	-- on windows, we patch heap functions, no need to wrap malloc family of funcs
		   getTargetCompiler() == "mingw-clang"	then
			linkoptions { "-Wl,--wrap=_malloc_init--export-all-symbols" }
			links { "psapi" }
		else 
			local wrap = "-Wl,--wrap=malloc,--wrap=realloc,--wrap=calloc,--wrap=free,--wrap=memalign,--wrap=reallocalign"
			if getTargetOS() ~= "linux" and getTargetOS() ~= "orbis" then
				wrap = wrap .. "--export-all-symbols,--wrap=_expand"
			end
			if getTargetOS() ~= "osx" then
				linkoptions { wrap }
			end
		end
		
	configuration { "vs*", "orbis" }
		linkoptions { "-Wl,--wrap=_malloc_init,--wrap=malloc,--wrap=realloc,--wrap=calloc,--wrap=free,--wrap=memalign,--wrap=reallocalign" }

	configuration { "vs*", "not orbis" }
		linkoptions { "/ENTRY:rmemEntry" }

	configuration {}
end

function projectExtraConfigExecutable_manual()
	configuration { "windows", "gmake" }
		if getTargetOS() ~= "orbis" and getTargetOS() ~= "android" then
			linkoptions { "-Wl,--export-all-symbols" }
		end
		if "mingw" == _OPTIONS["gcc"] then
			links { "psapi" }
		end
	configuration {}		
end

function projectAdd_rmem() 
	addProject_lib("rmem")
end

function projectExtraConfig_rmem()
    configuration { "vs20* or mingw*", "not orbis", "not durango", "not winphone*", "not winstore*" }
 		removeflags {
			"NoFramePointer"
        }
end
