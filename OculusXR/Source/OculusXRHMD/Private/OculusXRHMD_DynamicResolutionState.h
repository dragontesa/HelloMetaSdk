// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "OculusXRHMDPrivate.h"

#if OCULUS_HMD_SUPPORTED_PLATFORMS
#include "OculusXRHMD_Settings.h"
#include "DynamicResolutionState.h"

namespace OculusXRHMD
{

//-------------------------------------------------------------------------------------------------
// FDynamicResolutionState
//-------------------------------------------------------------------------------------------------

class FDynamicResolutionState : public IDynamicResolutionState
{
public:
	FDynamicResolutionState(const OculusXRHMD::FSettingsPtr InSettings);

	// ISceneViewFamilyScreenPercentage
	virtual void ResetHistory() override;
	virtual bool IsSupported() const override;
	virtual void SetupMainViewFamily(class FSceneViewFamily& ViewFamily) override;

protected:
	//[UE 5.1 MIG]virtual float GetResolutionFractionApproximation() const override;
	virtual DynamicRenderScaling::TMap<float> GetResolutionFractionsApproximation() const override;
	//[UE 5.1 MIG]virtual float GetResolutionFractionUpperBound() const override;
	virtual DynamicRenderScaling::TMap<float> GetResolutionFractionsUpperBound() const override;
	virtual void SetEnabled(bool bEnable) override;
	virtual bool IsEnabled() const override;
	virtual void ProcessEvent(EDynamicResolutionStateEvent Event) override;

private:
	const OculusXRHMD::FSettingsPtr Settings;
	float ResolutionFraction;
	float ResolutionFractionUpperBound;
};

} // namespace OculusXRHMD

#endif //OCULUS_HMD_SUPPORTED_PLATFORMS
