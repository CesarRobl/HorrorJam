// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HorrorJam : ModuleRules
{
	public HorrorJam(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HorrorJam",
			"HorrorJam/Variant_Platforming",
			"HorrorJam/Variant_Platforming/Animation",
			"HorrorJam/Variant_Combat",
			"HorrorJam/Variant_Combat/AI",
			"HorrorJam/Variant_Combat/Animation",
			"HorrorJam/Variant_Combat/Gameplay",
			"HorrorJam/Variant_Combat/Interfaces",
			"HorrorJam/Variant_Combat/UI",
			"HorrorJam/Variant_SideScrolling",
			"HorrorJam/Variant_SideScrolling/AI",
			"HorrorJam/Variant_SideScrolling/Gameplay",
			"HorrorJam/Variant_SideScrolling/Interfaces",
			"HorrorJam/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
