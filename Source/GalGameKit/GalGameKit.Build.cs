// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GalGameKit : ModuleRules
{
	public GalGameKit(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Blutility" });
    }
}
