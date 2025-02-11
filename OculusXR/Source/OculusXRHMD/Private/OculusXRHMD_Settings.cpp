// Copyright Epic Games, Inc. All Rights Reserved.

#include "OculusXRHMD_Settings.h"

#if OCULUS_HMD_SUPPORTED_PLATFORMS

namespace OculusXRHMD
{

//-------------------------------------------------------------------------------------------------
// FSettings
//-------------------------------------------------------------------------------------------------

FSettings::FSettings() :
	BaseOffset(0, 0, 0)
	, BaseOrientation(FQuat::Identity)
	, PixelDensity(1.0f)
	, PixelDensityMin(0.5f)
	, PixelDensityMax(1.0f)
	, SystemHeadset(ovrpSystemHeadset_None)
	, SuggestedCpuPerfLevel(EOculusXRProcessorPerformanceLevel::SustainedLow)
	, SuggestedGpuPerfLevel(EOculusXRProcessorPerformanceLevel::SustainedHigh)
	, FoveatedRenderingMethod(EOculusXRFoveatedRenderingMethod::FixedFoveatedRendering)
	, FoveatedRenderingLevel(EOculusXRFoveatedRenderingLevel::Off)
	, bDynamicFoveatedRendering(true)
	, bSupportEyeTrackedFoveatedRendering(false)
	, XrApi(EOculusXRXrApi::OVRPluginOpenXR)
	, ColorSpace(EOculusXRColorSpace::Rift_CV1)
	, HandTrackingSupport(EOculusXRHandTrackingSupport::ControllersOnly)
	, HandTrackingFrequency(EOculusXRHandTrackingFrequency::LOW)
	, ColorScale(ovrpVector4f{1,1,1,1})
	, ColorOffset(ovrpVector4f{0,0,0,0})
	, bApplyColorScaleAndOffsetToAllLayers(false)
	, bLateLatching(false)
	, bSupportExperimentalFeatures(false)
{
	Flags.Raw = 0;
	Flags.bHMDEnabled = true;
	Flags.bUpdateOnRT = true;
	Flags.bHQBuffer = false;
#if PLATFORM_ANDROID
	Flags.bCompositeDepth = false;
	Flags.bsRGBEyeBuffer = true;
	//oculus mobile is always-on stereo, no need for enableStereo codepaths
	Flags.bStereoEnabled = true;
	CurrentShaderPlatform = EShaderPlatform::SP_VULKAN_ES3_1_ANDROID;
#else
	Flags.bCompositeDepth = true;
	Flags.bsRGBEyeBuffer = false;
	Flags.bStereoEnabled = false;
	CurrentShaderPlatform = EShaderPlatform::SP_PCD3D_SM5;
#endif

	Flags.bSupportsDash = true;
	Flags.bFocusAware = true;
	Flags.bRequiresSystemKeyboard = false;
	Flags.bInsightPassthroughEnabled = false;
	Flags.bAnchorSupportEnabled = false;
	EyeRenderViewport[0] = EyeRenderViewport[1] = FIntRect(0, 0, 0, 0);

	RenderTargetSize = FIntPoint(0, 0);
}

TSharedPtr<FSettings, ESPMode::ThreadSafe> FSettings::Clone() const
{
	TSharedPtr<FSettings, ESPMode::ThreadSafe> NewSettings = MakeShareable(new FSettings(*this));
	return NewSettings;
}

void FSettings::SetPixelDensity(float NewPixelDensity)
{
	if (Flags.bPixelDensityAdaptive)
	{
		PixelDensity = FMath::Clamp(NewPixelDensity, PixelDensityMin, PixelDensityMax);
	}
	else
	{
		PixelDensity = FMath::Clamp(NewPixelDensity, ClampPixelDensityMin, ClampPixelDensityMax);
	}
}

void FSettings::SetPixelDensityMin(float NewPixelDensityMin)
{
	PixelDensityMin = FMath::Clamp(NewPixelDensityMin, ClampPixelDensityMin, ClampPixelDensityMax);
	PixelDensityMax = FMath::Max(PixelDensityMin, PixelDensityMax);
	SetPixelDensity(PixelDensity);
}

void FSettings::SetPixelDensityMax(float NewPixelDensityMax)
{
	PixelDensityMax = FMath::Clamp(NewPixelDensityMax, ClampPixelDensityMin, ClampPixelDensityMax);
	PixelDensityMin = FMath::Min(PixelDensityMin, PixelDensityMax);
	SetPixelDensity(PixelDensity);
}


} // namespace OculusXRHMD

#endif //OCULUS_HMD_SUPPORTED_PLATFORMS
