/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "form.h"
struct CellLighting
{
	Color ambient;
	Color directional;
	Color fog;
	float fogNear;
	float fogFar;
	long directionalXY;
	long directionalZ;
	float directionalFade;
	float fogClip;
};
enum ExtraDataProperties
{
	ExtraHavok = 0x2,
	ExtraCell3D = 0x3,
	ExtraCellWaterHeight = 0x4,
	ExtraCellWaterType = 0x5,
	ExtraRegionList = 0x8,
	ExtraSeenData = 0x9,
	ExtraEditorID = 0x0A,
	ExtraCellMusicType = 0x0B,
	ExtraCellClimate = 0x0C,
	ExtraProcessMiddleLow = 0x0D,
	ExtraCellCanopyShadowMask = 0x0F,
	ExtraDetatchTime = 0x10,
	ExtraPersistentCell = 0x11,
	ExtraScript = 0x12,
	ExtraAction = 0x13,
	ExtraStartingPosition = 0x14,
	ExtraAnim = 0x15,
	ExtraUsedMarkers = 0x17,
	ExtraDistantData = 0x18,
	ExtraRagDollData = 0x19,
	ExtraContainerChanges = 0x1A,
	ExtraWorn = 0x1B,
	ExtraWornLeft = 0x1C,
	ExtraPackageStartLocation = 0x1E,
	ExtraPackage = 0x1F,
	ExtraTressPassPackage = 0x20,
	ExtraRunOncePacks = 0x21,
	ExtraReferencePointer = 0x22,
	ExtraFollower = 0x23,
	ExtraLevCreaModifier = 0x24,
	ExtraGhost = 0x25,
	ExtraOriginalReference = 0x26,
	ExtraOwnership = 0x27,
	ExtraGlobal = 0x28,
	ExtraRank = 0x29,
	ExtraCount = 0x2A,
	ExtraHealth = 0x2B,
	ExtraUses = 0x2C,
	ExtraTimeLeft = 0x2D,
	ExtraCharge = 0x2E,
	ExtraSoul = 0x2F,
	ExtraLight = 0x30,
	ExtraLock = 0x31,
	ExtraTeleport = 0x32,
	ExtraMapMarker = 0x33,
	ExtraUnknown34 = 0x34,
	ExtraLeveledCreature = 0x35,
	ExtraLeveledItem = 0x36,
	ExtraScale = 0x37,
	ExtraSeed = 0x38,
	ExtraNonActorMagicCaster = 0x39,
	ExtraNonActorMagicTarget = 0x3A,
	ExtraInvestmentGoldUnused = 0x3C,
	ExtraCrimeGold = 0x3D,
	ExtraOblivionEntry = 0x3E,
	ExtraEnableStateParent = 0x3F,
	ExtraEnableStateChildren = 0x40,
	ExtraItemDropper = 0x41,
	ExtraDroppedItemList = 0x42,
	ExtraRandomTeleportMarker = 0x43,
	ExtraMerchantContainer = 0x44,
	ExtraMagicLight = 0x45,
	ExtraPersuasionPercent = 0x46,
	ExtraCannotWear = 0x47,
	ExtraPoison = 0x48,
	ExtraUnknown49 = 0x49,
	ExtraLastFinishedSequence = 0x4A,
	ExtraSavedMovementData = 0x4B,
	ExtraNorthRotation = 0x4C,
	ExtraXTarget = 0x4D,
	ExtraFriendHitList = 0x4E,
	ExtraHeadingTarget = 0x4F,
	ExtraBoundArmor = 0x50,
	ExtraRefracton = 0x51,
	ExtraInvestmentGold = 0x52,
	ExtraStartingWorldOrCell = 0x53,
	ExtraUnknown54 = 0x54,
	ExtraQuickKey = 0x55,
	ExtraEditorRefMoveData = 0x57,
	ExtraTravelHorse = 0x58,
	ExtraInfoGeneralTopic = 0x59,
	ExtraHasNoRumors = 0x5A,
	ExtraSound = 0x5B,
	ExtraHaggleAmount = 0x5C,
	ExtraXPCI = 0x5D, //custom added
	ExtraGrid = 0x5E //custom added
};
class ExtraDataForm : public Form
{
protected:
	formid CellWaterType;
	float WaterHeight;
	long Count;
	ulong Action;
	ulong Health;
	ubyte CellMusicType;
	formid TravelHorse;
	formid Ownership;
	formid EnableStateParentForm;
	ulong EnableStateParentFlags;
	ulong RegionListCount;
	formid *RegionList;
	formid Poison;
	long LevCreaModifier;
	float TimeLeft;
	formid RandomTeleportMarker;
	formid CellClimate;
	formid TeleportForm;
	NiPoint3 TeleportPosition;
	NiPoint3 TeleportRotation;
	ubyte Soul;
	formid PackageStartLocationForm;
	NiPoint3 PackageStartLocationPosition;
	float PackageStartLocationRotateZ;
	bool MapMarkerPresent;
	bool MapMarkerFlagsPresent;
	ubyte MapMarkerFlags;
	char *MapMarkerName;
	ushort MapMarkerType;
	formid XTarget;
	formid XPCIForm;
	char *XPCIName;
	long Rank;
	float Charge;
	ulong RagDollDataSize;
	ubyte *RagDollData;
	bool DistantDataPresent;
	float DistantData1;
	float DistantData2;
	float DistantData3;
	long Uses;
	ubyte SeedByte;
	ulong SeedLong;
	formid Global;
	bool LockPresent;
	long LockLevel;
	formid LockKey;
	bool LockSize16;
	ulong LockUnused;
	ulong LockFlags;
	formid MerchantContainer;
	int SeedSize;
	float Scale;
	CellLighting Lighting;
	long Gridx;
	long Gridy;
	SimpleDynVecClass<ExtraDataProperties> Properties;
public:
	ExtraDataForm(FormHeader h,ModFile *f) : Form(h,f), CellWaterType(0), WaterHeight(0), Count(1), Action(1), Health(0), CellMusicType(0), TravelHorse(0), Ownership(0), EnableStateParentForm(0), EnableStateParentFlags(0), RegionListCount(0), RegionList(0), Poison(0), LevCreaModifier(0), TimeLeft(0), RandomTeleportMarker(0), CellClimate(0), TeleportForm(0), Soul(0), PackageStartLocationForm(0), PackageStartLocationRotateZ(0), MapMarkerPresent(0), MapMarkerFlagsPresent(false), MapMarkerFlags(0), MapMarkerName(0), MapMarkerType(0), XTarget(0), XPCIForm(0), XPCIName(0), Rank(-1), Charge(0), RagDollDataSize(0), RagDollData(0), DistantDataPresent(false), DistantData1(0), DistantData2(0), DistantData3(0), Uses(0), SeedByte(0), SeedLong(0), Global(0), LockPresent(false), LockLevel(0), LockKey(0), LockSize16(false), LockUnused(0), LockFlags(0), MerchantContainer(0), SeedSize(0), Properties(0), Scale(1.0)
	{
	}
	~ExtraDataForm()
	{
		if (RegionList)
		{
			delete[] RegionList;
		}
		if (MapMarkerName)
		{
			delete[] MapMarkerName;
		}
		if (XPCIName)
		{
			delete[] XPCIName;
		}
		if (RagDollData)
		{
			delete[] RagDollData;
		}
	}
protected:
	void LoadSubrecord(SubrecordHeader h,FileRead *f)
	{
			switch(h.type)
			{
			case 'XCWT':
				Properties.Add(ExtraCellWaterType);
				CellWaterType = f->read<formid>();
				readSize += 4;
				break;
			case 'XCLW':
				Properties.Add(ExtraCellWaterHeight);
				WaterHeight = f->read<float>();
				readSize += 4;
				break;
			case 'XCNT':
				Properties.Add(ExtraCount);
				Count = f->read<long>();
				readSize += 4;
				break;
			case 'XACT':
				Properties.Add(ExtraAction);
				Action = f->read<ulong>();
				readSize += 4;
				break;
			case 'XHLT':
				Properties.Add(ExtraHealth);
				Health = f->read<ulong>();
				readSize += 4;
				break;
			case 'XCMT':
				Properties.Add(ExtraCellMusicType);
				CellMusicType = f->read<ubyte>();
				readSize += 1;
				break;
			case 'XHRS':
				Properties.Add(ExtraTravelHorse);
				TravelHorse = f->read<formid>();
				readSize += 4;
				break;
			case 'XOWN':
				Properties.Add(ExtraOwnership);
				Ownership = f->read<formid>();
				readSize += 4;
				break;
			case 'XESP':
				Properties.Add(ExtraEnableStateParent);
				EnableStateParentForm = f->read<formid>();
				readSize += 4;
				EnableStateParentFlags = f->read<ulong>();
				readSize += 4;
				break;
			case 'XCLR':
				Properties.Add(ExtraRegionList);
				RegionListCount = h.size / 4;
				RegionList = f->readarray<formid>(RegionListCount);
				readSize += h.size;
				break;
			case 'XPSN':
				Properties.Add(ExtraPoison);
				Poison = f->read<formid>();
				readSize += 4;
				break;
			case 'XLCM':
				Properties.Add(ExtraLevCreaModifier);
				LevCreaModifier = f->read<long>();
				readSize += 4;
				break;
			case 'XTIM':
				Properties.Add(ExtraTimeLeft);
				TimeLeft = f->read<float>();
				readSize += 4;
				break;
			case 'XRTM':
				Properties.Add(ExtraRandomTeleportMarker);
				RandomTeleportMarker = f->read<formid>();
				readSize += 4;
				break;
			case 'XCCM':
				Properties.Add(ExtraCellClimate);
				CellClimate = f->read<formid>();
				readSize += 4;
				break;
			case 'XTEL':
				Properties.Add(ExtraTeleport);
				TeleportForm = f->read<formid>();
				readSize += 4;
				TeleportPosition = f->read<NiPoint3>();
				readSize += 12;
				TeleportRotation = f->read<NiPoint3>();
				readSize += 12;
				break;
			case 'XSOL':
				if (h.size == 1)
				{
					Properties.Add(ExtraSoul);
					Soul = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'XPSL':
				Properties.Add(ExtraPackageStartLocation);
				PackageStartLocationForm = f->read<formid>();
				readSize += 4;
				PackageStartLocationPosition = f->read<NiPoint3>();
				readSize += 12;
				PackageStartLocationRotateZ = f->read<float>();
				readSize += 4;
				break;
			case 'XMRK':
				Properties.Add(ExtraMapMarker);
				MapMarkerPresent = true;
				break;
			case 'FNAM':
				MapMarkerFlagsPresent = true;
				MapMarkerFlags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'FULL':
				if (MapMarkerPresent && !MapMarkerName)
				{
					MapMarkerName = f->readzstring(h.size);
					readSize += h.size;
				}
				else
				{
					XPCIName = f->readzstring(h.size);
					readSize += h.size;
				}
				break;
			case 'TNAM':
				MapMarkerType = f->read<ushort>();
				readSize += 2;
				break;
			case 'XTRG':
				Properties.Add(ExtraXTarget);
				XTarget = f->read<formid>();
				readSize += 4;
				break;
			case 'XPCI':
				Properties.Add(ExtraXPCI);
				XPCIForm = f->read<formid>();
				readSize += 4;
				break;
			case 'XRNK':
				Properties.Add(ExtraRank);
				Rank = f->read<long>();
				readSize += 4;
				break;
			case 'XCHG':
				Properties.Add(ExtraCharge);
				Charge = f->read<float>();
				readSize += 4;
				break;
			case 'XRGD':
				Properties.Add(ExtraRagDollData);
				RagDollDataSize = h.size;
				RagDollData = f->readarray<ubyte>(h.size);
				readSize += h.size;
				break;
			case 'XLOD':
				Properties.Add(ExtraDistantData);
				DistantDataPresent = true;
				DistantData1 = f->read<float>();
				readSize += 4;
				DistantData2 = f->read<float>();
				readSize += 4;
				DistantData3 = f->read<float>();
				readSize += 4;
				break;
			case 'XUSE':
				Properties.Add(ExtraUses);
				Uses = f->read<long>();
				readSize += 4;
				break;
			case 'XSED':
				if (h.size == 1)
				{
					Properties.Add(ExtraSeed);
					SeedSize = 1;
					SeedByte = f->read<ubyte>();
					readSize += 1;
				}
				else if (h.size == 4)
				{
					Properties.Add(ExtraSeed);
					SeedSize = 4;
					SeedLong = f->read<ulong>();
					readSize += 4;
				}
				break;
			case 'XGLB':
				Properties.Add(ExtraGlobal);
				Global = f->read<formid>();
				readSize += 4;
				break;
			case 'XLOC':
				Properties.Add(ExtraLock);
				LockPresent = true;
				LockLevel = f->read<ulong>();
				readSize += 4;
				LockKey = f->read<formid>();
				readSize += 4;
				if (h.size == 16)
				{
					LockSize16 = true;
					LockUnused = f->read<ulong>();
					readSize += 4;
				}
				LockFlags = f->read<ulong>();
				readSize += 4;
				break;
			case 'XMRC':
				Properties.Add(ExtraMerchantContainer);
				MerchantContainer = f->read<formid>();
				readSize += 4;
				break;
			case 'XSCL':
				Properties.Add(ExtraScale);
				Scale = f->read<float>();
				readSize += 4;
				break;
			case 'XCLL':
				Properties.Add(ExtraLight);
				Lighting = f->read<CellLighting>();
				readSize += sizeof(CellLighting);
				break;
			case 'XCLC':
				Properties.Add(ExtraGrid);
				Gridx = f->read<long>();
				Gridy = f->read<long>();
				readSize += 8;
				break;
			default:
				printf("Unknown subrecord found");
				__debugbreak();
				break;
			}
	}
	void SaveSubrecords(FileWrite *f)
	{
		for (int i = 0;i < Properties.Count();i++)
		{
			ExtraDataProperties p = Properties[i];
			if (p == ExtraCellMusicType)
			{
				WriteSubrecord('XCMT',1,f);
				f->write<ubyte>(CellMusicType);
			}
			if (p == ExtraCellWaterType)
			{
				WriteSubrecord('XCWT',4,f);
				f->write<formid>(CellWaterType);
			}
			if (p == ExtraOwnership)
			{
				WriteSubrecord('XOWN',4,f);
				f->write<formid>(Ownership);
			}
			if (p == ExtraRank)
			{
				WriteSubrecord('XRNK',4,f);
				f->write<long>(Rank);
			}
			if (p == ExtraCellWaterHeight)
			{
				WriteSubrecord('XCLW',4,f);
				f->write<float>(WaterHeight);
			}
			if (p == ExtraCount)
			{
				WriteSubrecord('XCNT',4,f);
				f->write<long>(Count);
			}
			if (p == ExtraAction)
			{
				WriteSubrecord('XACT',4,f);
				f->write<ulong>(Action);
			}
			if (p == ExtraHealth)
			{
				WriteSubrecord('XHLT',4,f);
				f->write<ulong>(Health);
			}
			if (p == ExtraTravelHorse)
			{
				WriteSubrecord('XHRS',4,f);
				f->write<formid>(TravelHorse);
			}
			if (p == ExtraEnableStateParent)
			{
				WriteSubrecord('XESP',8,f);
				f->write<formid>(EnableStateParentForm);
				f->write<ulong>(EnableStateParentFlags);
			}
			if (p == ExtraRegionList)
			{
				WriteSubrecord('XCLR',RegionListCount * 4,f);
				f->writearray<formid>(RegionListCount,RegionList);
			}
			if (p == ExtraPoison)
			{
				WriteSubrecord('XPSN',4,f);
				f->write<formid>(Poison);
			}
			if (p == ExtraLevCreaModifier)
			{
				WriteSubrecord('XLCM',4,f);
				f->write<long>(LevCreaModifier);
			}
			if (p == ExtraTimeLeft)
			{
				WriteSubrecord('XTIM',4,f);
				f->write<float>(TimeLeft);
			}
			if (p == ExtraRandomTeleportMarker)
			{
				WriteSubrecord('XRTM',4,f);
				f->write<formid>(RandomTeleportMarker);
			}
			if (p == ExtraCellClimate)
			{
				WriteSubrecord('XCCM',4,f);
				f->write<formid>(CellClimate);
			}
			if (p == ExtraTeleport)
			{
				WriteSubrecord('XTEL',28,f);
				f->write<formid>(TeleportForm);
				f->write<NiPoint3>(TeleportPosition);
				f->write<NiPoint3>(TeleportRotation);
			}
			if (p == ExtraSoul)
			{
				WriteSubrecord('XSOL',1,f);
				f->write<ubyte>(Soul);
			}
			if (p == ExtraPackageStartLocation)
			{
				WriteSubrecord('XPSL',20,f);
				f->write<formid>(PackageStartLocationForm);
				f->write<NiPoint3>(PackageStartLocationPosition);
				f->write<float>(PackageStartLocationRotateZ);
			}
			if (p == ExtraMapMarker)
			{
				WriteSubrecord('XMRK',0,f);
				WriteSubrecord('FNAM',1,f);
				f->write<ubyte>(MapMarkerFlags);
				WriteZStringSubrecord('FULL',MapMarkerName,f);
				WriteSubrecord('TNAM',2,f);
				f->write<ushort>(MapMarkerType);
			}
			if (p == ExtraXTarget)
			{
				WriteSubrecord('XTRG',4,f);
				f->write<formid>(XTarget);
			}
			if (p == ExtraXPCI)
			{
				WriteSubrecord('XPCI',4,f);
				f->write<formid>(XPCIForm);
				WriteZStringSubrecord('FULL',XPCIName,f);
			}
			if (p == ExtraCharge)
			{
				WriteSubrecord('XCHG',4,f);
				f->write<float>(Charge);
			}
			if (p == ExtraRagDollData)
			{
				WriteSubrecord('XRGD',RagDollDataSize,f);
				f->writearray<ubyte>(RagDollDataSize,RagDollData);
			}
			if (p == ExtraDistantData)
			{
				WriteSubrecord('XLOD',12,f);
				f->write<float>(DistantData1);
				f->write<float>(DistantData2);
				f->write<float>(DistantData3);
			}
			if (p == ExtraUses)
			{
				WriteSubrecord('XUSE',4,f);
				f->write<long>(Uses);
			}
			if (p == ExtraSeed)
			{
				if (SeedSize == 1)
				{
					WriteSubrecord('XSED',1,f);
					f->write<ubyte>(SeedByte);
				}
				if (SeedSize == 4)
				{
					WriteSubrecord('XSED',4,f);
					f->write<ulong>(SeedLong);
				}
			}
			if (p == ExtraGlobal)
			{
				WriteSubrecord('XGLB',4,f);
				f->write<formid>(Global);
			}
			if (p == ExtraLock)
			{
				if (LockSize16)
				{
					WriteSubrecord('XLOC',16,f);
				}
				else
				{
					WriteSubrecord('XLOC',12,f);
				}
				f->write<ulong>(LockLevel);
				f->write<formid>(LockKey);
				if (LockSize16)
				{
					f->write<ulong>(LockUnused);
				}
				f->write<ulong>(LockFlags);
			}
			if (p == ExtraMerchantContainer)
			{
				WriteSubrecord('XMRC',4,f);
				f->write<formid>(MerchantContainer);
			}
			if (p == ExtraScale)
			{
				WriteSubrecord('XSCL',4,f);
				f->write<float>(Scale);
			}
			if (p == ExtraLight)
			{
				WriteSubrecord('XCLL',sizeof(CellLighting),f);
				f->write<CellLighting>(Lighting);
			}
			if (p == ExtraGrid)
			{
				WriteSubrecord('XCLC',8,f);
				f->write<long>(Gridx);
				f->write<long>(Gridy);
			}
		}
	}
	int GetSubrecordSize()
	{
		int size = 0;
		for (int i = 0;i < Properties.Count();i++)
		{
			ExtraDataProperties p = Properties[i];
			if (p == ExtraCellMusicType)
			{
				size += ComputeSubrecordSize(1);
			}
			if (p == ExtraCellWaterType)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraOwnership)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraRank)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraCellWaterHeight)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraCount)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraAction)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraHealth)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraTravelHorse)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraEnableStateParent)
			{
				size += ComputeSubrecordSize(8);
			}
			if (p == ExtraRegionList)
			{
				size += ComputeSubrecordSize(RegionListCount * 4);
			}
			if (p == ExtraPoison)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraLevCreaModifier)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraTimeLeft)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraRandomTeleportMarker)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraCellClimate)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraTeleport)
			{
				size += ComputeSubrecordSize(28);
			}
			if (p == ExtraSoul)
			{
				size += ComputeSubrecordSize(1);
			}
			if (p == ExtraPackageStartLocation)
			{
				size += ComputeSubrecordSize(20);
			}
			if (p == ExtraMapMarker)
			{
				size += ComputeSubrecordSize(0);
				size += ComputeSubrecordSize(1);
				size += ZStringSubrecordSize(MapMarkerName);
				size += ComputeSubrecordSize(2);
			}
			if (p == ExtraXTarget)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraXPCI)
			{
				size += ComputeSubrecordSize(4);
				size += ZStringSubrecordSize(XPCIName);
			}
			if (p == ExtraCharge)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraRagDollData)
			{
				size += ComputeSubrecordSize(RagDollDataSize);
			}
			if (p == ExtraDistantData)
			{
				size += ComputeSubrecordSize(12);
			}
			if (p == ExtraUses)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraSeed)
			{
				if (SeedSize == 1)
				{
					size += ComputeSubrecordSize(1);
				}
				if (SeedSize == 4)
				{
					size += ComputeSubrecordSize(4);
				}
			}
			if (p == ExtraGlobal)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraLock)
			{
				if (LockSize16)
				{
					size += ComputeSubrecordSize(16);
				}
				else
				{
					size += ComputeSubrecordSize(12);
				}
			}
			if (p == ExtraMerchantContainer)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraScale)
			{
				size += ComputeSubrecordSize(4);
			}
			if (p == ExtraLight)
			{
				size += ComputeSubrecordSize(sizeof(CellLighting));
			}
			if (p == ExtraGrid)
			{
				size += ComputeSubrecordSize(8);
			}
		}
		return size;
	}
};
