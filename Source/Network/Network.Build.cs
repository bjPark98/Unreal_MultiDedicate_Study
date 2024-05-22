// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Network : ModuleRules
{
	public Network(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Networking",
			"Sockets",
			"UMG",
			"AIModule",
			"Slate",
			"SlateCore"
		});
	}
}
