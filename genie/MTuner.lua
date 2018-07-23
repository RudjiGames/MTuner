--
-- Copyright (c) 2017 Milos Tosic. All rights reserved.
-- License: http://www.opensource.org/licenses/BSD-2-Clause
--

function projectDependencies_MTuner()
	return { "rmem", "rdebug", "rqt" }
end 

function projectExtraConfig_MTuner()
 	configuration { "*-gcc* or osx" }
 		buildoptions {
			"-fopenmp",	
 		}

	configuration { "osx" }
		links {	
			"gomp", 	
		}

	configuration {}
end

function projectAdd_MTuner() 
	addProject_qt("MTuner")
end

