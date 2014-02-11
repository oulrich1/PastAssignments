solution "p4 Maze Solution"
	configurations {"Release", "Debug"}

	-- defines "SHADERS_PATH"

	-- http://linux.die.net/man/1/magick++-config
	-- `Magick++-config --cxxflags --cppflags --ldflags --libs`
	-- g++ main.cpp `Magick++-config --cxxflags --cppflags --ldflags --libs` 


	-- project "SOIL"
	-- 	kind "StaticLib"
	-- 	language "C++"
	-- 	files {"./lib/soil/**.cpp"}
	-- 	includedirs {"./include/**"}
	-- 	location "build/soil-lib"
	-- 	targetdir "build/lib"
	-- 	targetname "SOIL"

	project "Lib"
		kind "StaticLib"
		language "C++"
		files {"./lib/angel/**.cpp"}
		includedirs {"./include/**"}
		location "build/common-lib"
		targetdir "build/lib"
		targetname "common-lib"

	project "Maze"
		kind "ConsoleApp"
		language "C++"
		files {"main.cpp", "./src/**.cpp"}
		links {	 "Lib",  "pthread",
				"glut", "GLEW", "GL", "GLU","m" }
		libdirs {"build/lib"}
		buildoptions {	"-std=c++11", 
						"-Wall", "-pedantic", 
						"-Wno-unused-function", 
						"-Wno-unused-but-set-variable", 
						"-Wno-sign-compare"}
		includedirs {"include/**"}
		location "build/maze"
		targetdir "bin"
		targetname "maze"


	configuration "Debug"
		defines { "DEBUG_ON" }

