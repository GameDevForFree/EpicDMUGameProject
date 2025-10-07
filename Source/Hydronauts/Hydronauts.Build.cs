// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Hydronauts : ModuleRules
{
	public Hydronauts(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
