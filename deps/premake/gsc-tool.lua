gsc_tool = {
	source = path.join(dependencies.basePath, "gsc-tool/src"),
}

function gsc_tool.import()
	links { "xsk-gsc-iw5", "xsk-gsc-utils" }
	gsc_tool.includes()
end

function gsc_tool.includes()
	includedirs {
		gsc_tool.source,
		path.join(gsc_tool.source, "iw5"),
		path.join(gsc_tool.source, "utils"),
		path.join(gsc_tool.source, "gsc"),
		path.join(dependencies.basePath, "gsc-tool/include"),
	}
end

function gsc_tool.project()
	project "xsk-gsc-utils"
		kind "StaticLib"
		language "C++"

		files {
			path.join(gsc_tool.source, "utils/**.hpp"),
			path.join(gsc_tool.source, "utils/**.cpp"),
		}

		includedirs {
			gsc_tool.source,
			path.join(gsc_tool.source, "utils"),
		}

		zlib.includes()

	project "xsk-gsc-iw5"
		kind "StaticLib"
		language "C++"

		filter "action:vs*"
			buildoptions "/Zc:__cplusplus"
		filter {}

		files {
			path.join(gsc_tool.source, "stdinc.hpp"),
			path.join(gsc_tool.source, "stdinc.cpp"),

			path.join(gsc_tool.source, "iw5/iw5_pc.hpp"),
			path.join(gsc_tool.source, "iw5/iw5_pc.cpp"),
			path.join(gsc_tool.source, "iw5/iw5_pc_code.cpp"),
			path.join(gsc_tool.source, "iw5/iw5_pc_func.cpp"),
			path.join(gsc_tool.source, "iw5/iw5_pc_meth.cpp"),
			path.join(gsc_tool.source, "iw5/iw5_pc_token.cpp"),

			path.join(gsc_tool.source, "gsc/misc/*.hpp"),
			path.join(gsc_tool.source, "gsc/misc/*.cpp"),
			path.join(gsc_tool.source, "gsc/*.hpp"),
			path.join(gsc_tool.source, "gsc/*.cpp"),
		}

		includedirs {
			gsc_tool.source,
			path.join(gsc_tool.source, "iw5"),
		}
end

table.insert(dependencies, gsc_tool)
