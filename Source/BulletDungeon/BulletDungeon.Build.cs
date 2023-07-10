// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BulletDungeon : ModuleRules
{
	public BulletDungeon(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core",
			"PhysicsCore",
			"GameplayTags",
			"GameplayTasks",
			"GameplayAbilities",
			"AIModule",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Paper2D"
			
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
