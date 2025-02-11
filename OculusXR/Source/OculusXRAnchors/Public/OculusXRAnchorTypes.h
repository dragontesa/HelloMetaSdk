/*
Copyright (c) Meta Platforms, Inc. and affiliates.
All rights reserved.

This source code is licensed under the license found in the
LICENSE file in the root directory of this source tree.
*/

#pragma once

#include "OculusXRAnchorTypes.generated.h"

#define OCULUSXR_UUID_SIZE 16

typedef uint8 ovrpXRUuidArray[OCULUSXR_UUID_SIZE];

USTRUCT(BlueprintType)
struct OCULUSXRANCHORS_API FOculusXRUUID
{
	GENERATED_BODY()

	FOculusXRUUID();
	FOculusXRUUID(const ovrpXRUuidArray& UuidArray);
	
	bool operator==(const FOculusXRUUID& Other) const;
	bool operator!=(const FOculusXRUUID& Other) const;

	bool IsValidUUID() const;

	bool IsEqual(const FOculusXRUUID& Other) const;
	friend uint32 GetTypeHash(const FOculusXRUUID& Other);
	bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

	OCULUSXRANCHORS_API friend FArchive& operator<<(FArchive& Ar, FOculusXRUUID& UUID);
	bool Serialize(FArchive& Ar);

	FString ToString() const;

	uint8 UUIDBytes[OCULUSXR_UUID_SIZE];
};

template<>
struct TStructOpsTypeTraits<FOculusXRUUID> : public TStructOpsTypeTraitsBase2<FOculusXRUUID>
{
	enum
	{
		WithIdenticalViaEquality = true,
		WithNetSerializer = true,
		WithSerializer = true
	};
};

USTRUCT( BlueprintType )
struct OCULUSXRANCHORS_API FOculusXRUInt64
{
	GENERATED_BODY()

	FOculusXRUInt64() : FOculusXRUInt64(0) { }
	FOculusXRUInt64( const uint64& Value ) { this->Value = Value; }

	operator uint64() const { return Value; }
	bool operator==(const FOculusXRUInt64& Right) const;
	bool operator!=(const FOculusXRUInt64& Right) const;

	UPROPERTY()
	uint64 Value;
	
	bool IsEqual(const FOculusXRUInt64& Other) const
	{
		return Other.Value == Value;
	}

	friend uint32 GetTypeHash(const FOculusXRUInt64& Other)
	{
		return FCrc::MemCrc_DEPRECATED(&Other.Value, sizeof(Other.Value));
	}

	uint64 GetValue() const { return Value; };
	
	void SetValue(const uint64 Val) { Value = Val; };
};

template<>
struct TStructOpsTypeTraits<FOculusXRUInt64> : public TStructOpsTypeTraitsBase2<FOculusXRUInt64>
{
	enum
	{
		WithIdenticalViaEquality = true,
	};
};

UENUM(BlueprintType)
enum class EOculusXRSpaceQueryFilterType : uint8
{
	None = 0                  UMETA(DisplayName = "No Filter"),
	FilterByIds = 1			  UMETA(DisplayName = "Filter queries by UUIDs"),
	FilterByComponentType = 2 UMETA(DisplayName = "Filter queries by component type")
};

// This is used as a bit-mask
UENUM(BlueprintType)
enum class EOculusXRSpaceStorageLocation : uint8
{
	Invalid = 0		UMETA(DisplayName = "Invalid"),
	Local = 1 << 0 	UMETA(DisplayName = "Local")
};

UENUM(BlueprintType)
enum class EOculusXRSpaceStoragePersistenceMode : uint8
{
	Invalid = 0		UMETA(Hidden),
	Indefinite = 1	UMETA(DisplayName = "Indefinite"),
};

UENUM(BlueprintType)
enum class EOculusXRSpaceComponentType : uint8
{
	Locatable = 0				UMETA(DisplayName = "Locatable"),
	Storable = 1				UMETA(DisplayName = "Storable"),
	ScenePlane = 3				UMETA(DisplayName = "ScenePlane"),
	SceneVolume = 4				UMETA(DisplayName = "SceneVolume"),
	SemanticClassification = 5	UMETA(DisplayName = "SemanticClassification"),
	RoomLayout = 6				UMETA(DisplayName = "RoomLayout"),
	SpaceContainer = 7			UMETA(DisplayName = "SpaceContainer"),
	Undefined = 8				UMETA(DisplayName = "Not defined"),
};

USTRUCT(BlueprintType)
struct OCULUSXRANCHORS_API FOculusXRSpaceQueryInfo
{
	GENERATED_BODY()
public:
	FOculusXRSpaceQueryInfo() :
		MaxQuerySpaces(1024),
		Timeout(0),
		Location(EOculusXRSpaceStorageLocation::Local),
		FilterType(EOculusXRSpaceQueryFilterType::None)
	{}

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	int MaxQuerySpaces;

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	float Timeout;

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	EOculusXRSpaceStorageLocation Location;

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	EOculusXRSpaceQueryFilterType FilterType;

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	TArray<FOculusXRUUID> IDFilter;

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	TArray<EOculusXRSpaceComponentType> ComponentFilter;
};

USTRUCT(BlueprintType)
struct OCULUSXRANCHORS_API FOculusXRSpaceQueryResult
{
	GENERATED_BODY()
public:
	FOculusXRSpaceQueryResult() : Space(0), UUID(), Location(EOculusXRSpaceStorageLocation::Invalid) {}
	FOculusXRSpaceQueryResult(FOculusXRUInt64 SpaceHandle, FOculusXRUUID ID, EOculusXRSpaceStorageLocation SpaceLocation) : Space(SpaceHandle), UUID(ID), Location(SpaceLocation) {}

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	FOculusXRUInt64 Space;

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	FOculusXRUUID UUID;

	UPROPERTY(BlueprintReadWrite, Category = "OculusXR|SpatialAnchor")
	EOculusXRSpaceStorageLocation Location;
};

USTRUCT(BlueprintType)
struct OCULUSXRANCHORS_API FOculusXRSpaceQueryFilterValues
{
	GENERATED_BODY()
public:
	TArray<FOculusXRUUID> Uuids; // used if filtering by UUIDs
	TArray<EOculusXRSpaceComponentType> ComponentTypes; // used if filtering by component types
};