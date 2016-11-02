// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class ProckFPS : ModuleRules {
    private string pythonHome = "python27";

    protected string PythonHome
    {
        get
        {
            return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "Env", "python27"));
        }
    }

    public ProckFPS(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "ProceduralMeshComponent" });

        //PrivateDependencyModuleNames.AddRange(new string[] { "CustomMeshComponent" });
        PrivateIncludePathModuleNames.AddRange(new string[] { "ProceduralMeshComponent" });

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            System.Console.WriteLine("Using Python at: " + PythonHome);
            PublicIncludePaths.Add(PythonHome);
            PublicAdditionalLibraries.Add(Path.Combine(PythonHome, "libs", string.Format("{0}.lib", pythonHome)));

        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            string mac_python = "/Library/Frameworks/Python.framework/Versions/2.7/";
            PublicIncludePaths.Add(Path.Combine(mac_python, "include"));
            PublicAdditionalLibraries.Add(Path.Combine(mac_python, "lib", "libpython2.7.dylib"));
            Definitions.Add(string.Format("UNREAL_ENGINE_PYTHON_ON_MAC=2"));

        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicIncludePaths.Add("/usr/include/python2.7");
            PublicAdditionalLibraries.Add("/usr/lib/python2.7/config-x86_64-linux-gnu/libpython2.7.so");
            Definitions.Add(string.Format("UNREAL_ENGINE_PYTHON_ON_LINUX"));
        }
    }
}
