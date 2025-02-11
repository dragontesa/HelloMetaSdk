// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class OculusXRScene : ModuleRules
	{
		public OculusXRScene(ReadOnlyTargetRules Target) : base(Target)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"OculusXRHMD",
					"OculusXRAnchors",
					"OVRPluginXR",
				});

			PrivateIncludePaths.AddRange(
				new string[] {
					// Relative to Engine\Plugins\Runtime\Oculus\OculusVR\Source
					"OculusXRHMD/Private",
					"OculusXRAnchors/Private"
				});

			PublicIncludePaths.AddRange(
				new string[] {
					"Runtime/Engine/Classes/Components",
				});
		}
	}
}
