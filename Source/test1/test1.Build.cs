// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class test1 : ModuleRules
{
	public test1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "UMG", "GameplayTasks"});
	}
}
