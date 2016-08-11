-- Clean by just deleting entire visual_studio directory
if _ACTION == "clean" then
  os.rmdir("../visual_studio")
  os.exit()
end

local dependencies = {}
local projects = {}
local layers = {{}, {}, {}, {}} -- 4 layers total

---------------------------------------------------------------------------
-- Call this to add a new external dependency.
---------------------------------------------------------------------------
-- Name - The name this dependency will be referred to as throughout this
--        premake file. This is what you put into your project.
-- Debug Links - The names of any additional links needed when this
--               dependency is used in a project (Debug mode)
-- Release Links - The names of any additional links needed when this
--                 dependency is used in a project (Release mode).
-- Include directories - The folders in which to find headers for this.
--                       This is relative to "../framework/".
-- Library directories - The folders in which to find the library for this.
--                       This is relative to "../framework/".
-- Runtime Files - Files that need to be in the exe directory when the
--                 executable runs. This is relative to "../framework".
--                 Note that backslashes must be used in this path because
--                 of limitations with visual studio post-build commands.
---------------------------------------------------------------------------
function RegisterDependency(name, debugLinks, releaseLinks, incDirs, libDirs, runtimeFiles)
  dependencies[name] =
    { name = name, debugLinks = debugLinks, releaseLinks = releaseLinks,
      includeDirs = incDirs, libraryDirs = libDirs, runtimeFiles = runtimeFiles }
end

RegisterDependency("SFML",
                  {"sfml-graphics-s-d.lib", "sfml-system-s-d.lib", "sfml-window-s-d.lib", "opengl32.lib", "freetype.lib", "jpeg.lib", "winmm.lib", "gdi32.lib"},
                  {"sfml-graphics-s.lib", "sfml-system-s.lib", "sfml-window-s.lib", "opengl32.lib", "freetype.lib", "jpeg.lib", "winmm.lib", "gdi32.lib"},
                  {"SFML/SFML64bit/include/**"},
                  {"SFML/SFML64bit/lib"})

-------------------------------------
-- Add all other dependencies here --
-------------------------------------

RegisterDependency("Lua",
                  {"lua51.lib"},
                  {"lua51.lib"},
                  {"lua/include/**"},
                  {"lua/bin/**"},
                  {"lua\\bin\\lua51.dll"})

RegisterDependency("DbgHelp",
                  {"dbghelp.lib"},
                  {"dbghelp.lib"},
                  {"DebugHelper/x64/**"},
                  {"DebugHelper/x64/**"})

RegisterDependency("JSON",
                  {"json_vc71_libmtd"},
                  {"json_vc71_libmt"},
                  {"JSON/**"},
                  {"JSON/**"})

--[[RegisterDependency("DirectX",
                   {"d3d11", "d3dx11", "dxgi", "d3dcompiler", "dxguid", "Windowscodecs.lib"},
                   {"d3d11", "d3dx11", "dxgi", "d3dcompiler", "dxguid", "Windowscodecs.lib"},
                   {},
                   {})

RegisterDependency("D3DX",
                  {"d3dx11d.lib"},
                  {"d3dx11.lib"},
                  {"D3DX11/include/**"},
                  {"D3DX11/bin/**"})

RegisterDependency("DirectXTK",
                  {"DirectXTKd.lib"},
                  {"DirectXTK.lib"},
                  {"DirectXToolKit/include/**"},
                  {"DirectXToolKit/bin/**"})

RegisterDependency("FBX",
                  {"libfbxsdk-md_debug.lib", "libfbxsdk_debug.lib"},
                  {"libfbxsdk-md_release.lib", "libfbxsdk_release.lib"},
                  {"FBX/include"},
                  {"FBX/lib"})
          
RegisterDependency("NVTT",
                  { "bc6hd.lib", "bc7d.lib", "nvcored.lib", "nvimaged.lib", "nvmathd.lib", "nvthreadd.lib", "nvttd.lib", "squishd.lib" },
                  { "bc6h.lib", "bc7.lib", "nvcore.lib", "nvimage.lib", "nvmath.lib", "nvthread.lib", "nvtt.lib", "squish.lib" },
                  {"nvtt/include"},
                  {"nvtt/lib"})

RegisterDependency("Wwise",
                  {"ws2_32.lib", "AkConvolutionReverbFXd.lib","AkFlangerFXd.lib","AkTremoloFXd.lib","AkMemoryMgrd.lib","AuroHeadphoneFXd.lib","IOSONOProximityMixerd.lib","AkMotionGeneratord.lib","AkSineSourced.lib","AkSoundSeedWindd.lib","AkStereoDelayFXd.lib","AkGuitarDistortionFXd.lib","AkRumbled.lib","AkSoundEngined.lib","AkSilenceSourced.lib","iZTrashBoxModelerFXd.lib","AkSoundSeedImpactFXd.lib","AkRoomVerbFXd.lib","iZTrashDelayFXd.lib","McDSPFutzBoxFXd.lib","AkParametricEQFXd.lib","AuroPannerMixerd.lib","AkToneSourced.lib","McDSPLimiterFXd.lib","AkCompressorFXd.lib","CrankcaseAudioREVModelPlayerFXd.lib","AkAudioInputSourced.lib","AkMusicEngined.lib","AkSoundSeedWooshd.lib","iZTrashMultibandDistortionFXd.lib","iZHybridReverbFXd.lib","AkPitchShifterFXd.lib","iZTrashDynamicsFXd.lib","iZTrashDistortionFXd.lib","AkPeakLimiterFXd.lib","AkDelayFXd.lib","AkGainFXd.lib","AkVorbisDecoderd.lib","AkMeterFXd.lib","AkMatrixReverbFXd.lib","iZTrashFiltersFXd.lib","AkSynthOned.lib","AkMP3Sourced.lib","AkStreamMgrd.lib","AkHarmonizerFXd.lib","AkTimeStretchFXd.lib","AkExpanderFXd.lib","CommunicationCentrald.lib"},
                  {"AkAudioInputSource.lib", "AkCompressorFX.lib", "AkConvolutionReverbFX.lib", "AkDelayFX.lib", "AkExpanderFX.lib", "AkFlangerFX.lib", "AkGainFX.lib", "AkGuitarDistortionFX.lib", "AkHarmonizerFX.lib", "AkMatrixReverbFX.lib", "AkMemoryMgr.lib", "AkMeterFX.lib", "AkMotionGenerator.lib", "AkMP3Source.lib", "AkMusicEngine.lib", "AkParametricEQFX.lib", "AkPeakLimiterFX.lib", "AkPitchShifterFX.lib", "AkRoomVerbFX.lib", "AkRumble.lib", "AkSilenceSource.lib", "AkSineSource.lib", "AkSoundEngine.lib", "AkSoundSeedImpactFX.lib", "AkSoundSeedWind.lib", "AkSoundSeedWoosh.lib", "AkStereoDelayFX.lib", "AkStreamMgr.lib", "AkSynthOne.lib", "AkTimeStretchFX.lib", "AkToneSource.lib", "AkTremoloFX.lib", "AkVorbisDecoder.lib", "AuroHeadphoneFX.lib", "AuroPannerMixer.lib", "CrankcaseAudioREVModelPlayerFX.lib", "IOSONOProximityMixer.lib", "iZHybridReverbFX.lib", "iZTrashBoxModelerFX.lib", "iZTrashDelayFX.lib", "iZTrashDistortionFX.lib", "iZTrashDynamicsFX.lib", "iZTrashFiltersFX.lib", "iZTrashMultibandDistortionFX.lib", "McDSPFutzBoxFX.lib", "McDSPLimiterFX.lib", "SFlib.lib"},
                  {"Wwise/include"},
                  {"Wwise/de/**", "Wwise/re/**"})

RegisterDependency("FreeType",
                  {"freetype_d.lib"}, 
                  {"freetype.lib"},
                  {"freetype/incude"}, 
                  {"freetype/lib"});

RegisterDependency("stb",
                  {},
                  {},
                  {"stb/include"},
                  {})
                  ]]

---------------------------------------------------------------------------
---------------------------------------------------------------------------
-- Call these to add new projects to the solution.
---------------------------------------------------------------------------
-- Name - The name of this project. Has to match the src directory name.
--
-- Kind - How to compile this project. There are only 4 valid kinds:
--        "StaticLib", "WindowedApp", "ConsoleApp", "SharedLib".
--        RegisterLibrary automatically sets it to "StaticLib"
--
-- Layer - Where this project lies in the compilation order. All projects
--         depend on each layer below them. (All layers are ints)
--         1: First Compiled, Core
--         2: System Libraries
--         3: Systems and components
--         4: Sandboxes and Executables
--         Executables are always in Layer 4
--
-- dependencyNames - (Optional) Names of registered dependencies for this project.
--                   If not specified, defaults to empty list {}.
--
-- flags - (Optional) Any premake flags that should be specified for this project.
--         For a list go here: https://bitbucket.org/premake/premake-dev/wiki/flags
--         If not specified, defaults to empty list {}.
--
-- pchinfo - (Optional) A 2-element table with the precompiled header's header
--           and path relative to your project directory.
--           For example, {"precompiled.h", "precompiled/precompiled.cpp"}
--           will use src/myproject/precompiled/precompiled.cpp as a
--           precompiled header. If not specified, is not included in the table.
---------------------------------------------------------------------------
function RegisterExecutable(name, kind, dependencyNames, flags, pchinfo, language)
  local tempTable = {}

  tempTable.name = name
  tempTable.kind = kind
  tempTable.layer = 4
  tempTable.flags = flags or {}
  tempTable.dependencyNames = dependencyNames or {}
  if type(pchinfo) == "table" and table.maxn(pchinfo) == 2 then
    tempTable.pchinfo = pchinfo
  end
  tempTable.language = language or "C++"

  projects[name] = tempTable
  table.insert(layers[4], name)
end

function RegisterLibrary(name, layer, dependencyNames, flags, pchinfo)
  local tempTable = {}

  tempTable.name = name
  tempTable.kind = "StaticLib"
  tempTable.layer = layer
  tempTable.flags = flags or {}
  tempTable.dependencyNames = dependencyNames or {}
  if type(pchinfo) == "table" and table.maxn(pchinfo) == 2 then
    tempTable.pchinfo = pchinfo
  end

  projects[name] = tempTable
  table.insert(layers[layer], name)
end

--------------------------------------------------
-- Register your executables and libraries here --
--------------------------------------------------
RegisterExecutable("GridGame", "WindowedApp", {"SFML", "DbgHelp"})

RegisterLibrary("MaypleEngine", 1)
RegisterLibrary("LuaBridge",1)

---------------------------------------------------------------------------
-- Functions for creating actual solution.
---------------------------------------------------------------------------
function AddRuntimeCopyCommands(runtimeFiles, runtimeDest)
  if runtimeFiles ~= nil then
    local copyCommands = { }
    for i = 1, #runtimeFiles do
      table.insert(copyCommands,
         "copy \"$(SolutionDir)..\\..\\framework\\" .. runtimeFiles[i]
         .. "\" \"" .. runtimeDest .. "\"")
    end
    postbuildcommands(copyCommands)
  end
end

function LinkDependencies(dependencyNames, runtimeDest)
  for i = 1, #dependencyNames do
    local dependency = dependencies[dependencyNames[i]]
    
    for i = 1, #dependency.includeDirs do
      includedirs("../framework/" .. dependency.includeDirs[i])
    end

    for i = 1, #dependency.libraryDirs do
      libdirs("../framework/" .. dependency.libraryDirs[i])
    end

    configuration "Debug"
      links(dependency.debugLinks)

    configuration "ReleaseSymbols"
      links(dependency.releaseLinks)

    configuration "Release"
      links(dependency.releaseLinks)

    if runtimeDest ~= nil then
      configuration "Debug"
        AddRuntimeCopyCommands(dependency.runtimeFiles, runtimeDest.."/Debug")
      configuration "ReleaseSymbols"
        AddRuntimeCopyCommands(dependency.runtimeFiles, runtimeDest.."/ReleaseSymbols")
      configuration "Release"
        AddRuntimeCopyCommands(dependency.runtimeFiles, runtimeDest.."/Release")
    end
  end
end

function LinkLowerLayers(layer, runtimeDest)
  for i = 1, layer - 1 do
    local projectnames = layers[i]

    configuration {}
    links(projectnames)

    for key, name in pairs(projectnames) do
      local proj = projects[name]
      LinkDependencies(proj.dependencyNames, runtimeDest)
    end
  end
end

---------------------------------------------------------------------------
---------------------------------------------------------------------------
-- Call this to copy a directory.
---------------------------------------------------------------------------
-- src_dir - Source directory, which will be copied to dst_dir.
--
-- dst_dir - Destination directory.
--
-- filter - (Optional) - Defaults to "**". Only filter matches will be copied. 
--                       It can contain **(recursive) and *(filename).
--
-- single_dst_dir - (Optional) - defaults to false. Allows putting all files to
--                               dst_dir without subdirectories.
--                               Only useful with recursive (**) filter.
--
-- It uses the premake4 patterns (**=recursive match, *=file match)
-- NOTE: It won't copy empty directories!
-- Example: we have a file: src/test.h
--  os.copydir("src", "include") simple copy, makes include/test.h
--  os.copydir("src", "include", "*.h") makes include/test.h
--  os.copydir(".", "include", "src/*.h") makes include/src/test.h
--  os.copydir(".", "include", "**.h") makes include/src/test.h
--  os.copydir(".", "include", "**.h", true) will force it to include dir, makes include/test.h
---------------------------------------------------------------------------
function os.copydir(src_dir, dst_dir, filter, single_dst_dir)
  if not os.isdir(src_dir) then error(src_dir .. " is not an existing directory!") end
  filter = filter or "**"
  src_dir = src_dir .. "/"
  print('copy "' .. src_dir .. filter .. '" to "' .. dst_dir .. '".')
  dst_dir = dst_dir .. "/"
  local dir = path.rebase(".",path.getabsolute("."), src_dir) -- root dir, relative from src_dir
 
  os.chdir( src_dir ) -- change current directory to src_dir
    local matches = os.matchfiles(filter)
  os.chdir( dir ) -- change current directory back to root
 
  local counter = 0
  for k, v in ipairs(matches) do
    local target = iif(single_dst_dir, path.getname(v), v)
    --make sure, that directory exists or os.copyfile() fails
    os.mkdir( path.getdirectory(dst_dir .. target))
    if os.copyfile( src_dir .. v, dst_dir .. target) then
      counter = counter + 1
    end
  end
 
  if counter == #matches then
    print( counter .. " files copied.")
    return true
  else
    print( "Error: " .. counter .. "/" .. #matches .. " files copied.")
    return nil
  end
end

function AddProject(proj)
  if proj.kind == "StaticLib" then
    group "Libraries"
  else
    group "Executables"
  end

  project(proj.name)
    kind(proj.kind)
    location("../visual_studio/Projects/Application/" .. proj.name)
    targetname(proj.name)
    language(proj.language)

    -- Requires files to be in the same directory as project
    files 
    {
      "../src/" .. proj.name .. "/**.cpp",
      "../src/" .. proj.name .. "/**.h",
      "../src/" .. proj.name .. "/**.hpp",
    }

    objdir("../visual_studio/build/" .. proj.name)
    flags(proj.flags)

    ------------------------------------
    -- Precompiled Header Information --
    ------------------------------------
    if type(proj.pchinfo) == "table" then
      pchheader(proj.pchinfo[1])
      pchsource("../src/" .. proj.name .. "/" .. proj.pchinfo[2])
    elseif proj.language == "C++" then
      files { "../src/stdinc.h", "../src/stdinc.cpp" }
      pchheader "stdinc.h"
      pchsource "../src/stdinc.cpp"
    end

    local subdir
    local runtimeDest
    if proj.kind == "StaticLib" then
      subdir = "libs/"
      runtimeDest = nil
    else
      subdir = "bin/"
      runtimeDest = "$(SolutionDir)..\\bin\\"..proj.name
    end

    if proj.kind == "StaticLib" then
      includedirs 
      {
        "../framework",
        "../src",
        "../src/**",
        "../framework/**",
      }
    elseif proj.language == "C++" then
      libdirs 
      {
        "../framework/**",
      }

      LinkLowerLayers(proj.layer, runtimeDest)
      LinkDependencies(proj.dependencyNames, runtimeDest)
    end

    --------------------------------------
    -- Target Directory For Build Files --
    --------------------------------------
    configuration "Debug"
      targetdir("../visual_studio/" .. subdir .. proj.name .. "/Debug")

    configuration "ReleaseSymbols"
      targetdir("../visual_studio/" .. subdir .. proj.name .. "/ReleaseSymbols")

    configuration "Release"
      targetdir("../visual_studio/" .. subdir .. proj.name .. "/Release")

end

function AddProjects()
  for name, project in pairs(projects) do
    AddProject(project)
  end
end


---------------------------------------------------------------------------
-- Solution
---------------------------------------------------------------------------
-- Create the actual solution here
---------------------------------------------------------------------------
solution "GridGame"
  configurations {"Debug", "Release", "ReleaseSymbols"}
  architecture "x64"
  location "../visual_studio/Solution"
  language "C++"
  toolset "v140"
  startproject "GridGame"

  includedirs 
  {
    "../src",
    "../src/**",
    "../framework",
    "../framework/**"
  }

  debugdir "../Resources/"

  links {  }

  vpaths { ["*"] = "src" }

  flags { "FatalWarnings", "MultiProcessorCompile" }

  defines { "_CRT_SECURE_NO_WARNINGS", "SFML_STATIC" }

  -- Set linkoptions for ReleaseSymbols versions of executables
  configuration {"WindowedApp or ConsoleApp", "ReleaseSymbols"}
    linkoptions {"/OPT:REF", "/OPT:ICF", "/ignore:4099"}

    -- Debug has no optimizations
  configuration "Debug"
    flags { "Symbols" }
    defines {"DEBUG", "DEBUGLOGGING" }
    optimize "Debug"
    linkoptions {"/NODEFAULTLIB:msvcrt.lib", "/ignore:4099"}

  -- Release w/ Symbols has optimizations but still allows symbolic debug
  configuration "ReleaseSymbols"
    flags { "Symbols", "NoIncrementalLink" }
    defines { "RELEASE", "DEBUGLOGGING" }
    optimize "Speed"
    linkoptions {"/ignore:4099"}

  -- Typical Release mode
  configuration "Release"
    flags { "NoIncrementalLink" }
    defines { "RELEASE" }
    optimize "Speed"
    linkoptions {"/ignore:4099"}

  AddProjects()
