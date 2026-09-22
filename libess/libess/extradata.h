/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "changerecord.h"
#include "extradataform.h"
#include "spellform.h"
#include "alchemyform.h"
#include "enchantmentform.h"
#pragma warning(disable: 4100)
class ExtraData
{
protected:
	ulong type;
public:
	ExtraData() : type(0)
	{
	}
	virtual ~ExtraData()
	{
	}
	virtual void Load(FileRead *f,ESSFile *parent) = 0;
	virtual void Save(FileWrite *f,ESSFile *parent) = 0;
};
class ExtraCountData : public ExtraData
{
protected:
	short count;
public:
	ExtraCountData()
	{
		type = ExtraCount;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		count = f->read<short>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<short>(count);
	}
};
class ExtraHealthData : public ExtraData
{
protected:
	float health;
public:
	ExtraHealthData()
	{
		type = ExtraHealth;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		health = f->read<float>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<float>(health);
	}
};
class ExtraUsesData : public ExtraData
{
protected:
	ubyte uses;
public:
	ExtraUsesData()
	{
		type = ExtraUses;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		uses = f->read<ubyte>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ubyte>(uses);
	}
};
class ExtraTimeLeftData : public ExtraData
{
protected:
	float timeLeft;
public:
	ExtraTimeLeftData()
	{
		type = ExtraTimeLeft;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		timeLeft = f->read<float>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<float>(timeLeft);
	}
};
class ExtraChargeData : public ExtraData
{
protected:
	float charge;
public:
	ExtraChargeData()
	{
		type = ExtraCharge;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		charge = f->read<float>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<float>(charge);
	}
};
class ExtraSoulData : public ExtraData
{
protected:
	ubyte soul;
public:
	ExtraSoulData()
	{
		type = ExtraSoul;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		soul = f->read<ubyte>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ubyte>(soul);
	}
};
class ExtraLockData : public ExtraData
{
protected:
	ubyte lockLevel;
	formid lockKey;
	ubyte lockFlags;
public:
	ExtraLockData()
	{
		type = ExtraLock;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		lockLevel = f->read<ubyte>();
		lockKey = parent->GetFormID(f->read<iref>());
		lockFlags = f->read<ubyte>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ubyte>(lockLevel);
		f->write<iref>(parent->GetFormiRef(lockKey));
		f->write<ubyte>(lockFlags);
	}
};
class ExtraScaleData : public ExtraData
{
protected:
	float scale;
public:
	ExtraScaleData()
	{
		type = ExtraScale;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		scale = f->read<float>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<float>(scale);
	}
};
class ExtraInvestmentGoldData : public ExtraData
{
protected:
	ulong investmentGold;
public:
	ExtraInvestmentGoldData()
	{
		type = ExtraInvestmentGold;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		investmentGold = f->read<ulong>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ulong>(investmentGold);
	}
};
class ExtraCrimeGoldData : public ExtraData
{
protected:
	float crimeGold;
public:
	ExtraCrimeGoldData()
	{
		type = ExtraCrimeGold;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		crimeGold = f->read<float>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<float>(crimeGold);
	}
};
class ExtraOwnershipData : public ExtraData
{
protected:
	formid ownership;
public:
	ExtraOwnershipData()
	{
		type = ExtraOwnership;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		ownership = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(ownership));
	}
};
class ExtraGlobalData : public ExtraData
{
protected:
	formid global;
public:
	ExtraGlobalData()
	{
		type = ExtraGlobal;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		global = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(global));
	}
};
class ExtraRankData : public ExtraData
{
protected:
	long rank;
public:
	ExtraRankData()
	{
		type = ExtraRank;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		rank = f->read<long>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<long>(rank);
	}
};
class ExtraWornData : public ExtraData
{
public:
	ExtraWornData()
	{
		type = ExtraWorn;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
	}
};
class ExtraWornLeftData : public ExtraData
{
public:
	ExtraWornLeftData()
	{
		type = ExtraWornLeft;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
	}
};
class ExtraCannotWearData : public ExtraData
{
public:
	ExtraCannotWearData()
	{
		type = ExtraCannotWear;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
	}
};
class ExtraBoundArmorData : public ExtraData
{
public:
	ExtraBoundArmorData()
	{
		type = ExtraBoundArmor;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
	}
};
class ExtraGhostData : public ExtraData
{
public:
	ExtraGhostData()
	{
		type = ExtraGhost;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
	}
};
struct ScriptVariable
{
	ushort varIndex;
	ushort type;
	formid refvar;
	double locvar;
};
class ExtraScriptData : public ExtraData
{
protected:
	formid script;
	ushort varNum;
	SimpleDynVecClass<ScriptVariable> variables;
	ubyte scriptInfoPresent;
	ubyte scriptEffectInfoStartBlock;
	ubyte scriptEffectInfoFinishBlock;
	ushort scriptEffectInfoUnk;
	float scriptEffectInfoElapsedSeconds;
public:
	ExtraScriptData()
	{
		type = ExtraScript;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		script = parent->GetFormID(f->read<iref>());
		varNum = f->read<ushort>();
		for (ushort i = 0;i < varNum;i++)
		{
			ScriptVariable v;
			v.varIndex = f->read<ushort>();
			v.type = f->read<ushort>();
			if (v.type == 0)
			{
				v.locvar = f->read<double>();
			}
			else
			{
				v.refvar = parent->GetFormID(f->read<iref>());
			}
			variables.Add(v);
		}
		scriptInfoPresent = f->read<ubyte>();
		if (scriptInfoPresent)
		{
			scriptEffectInfoStartBlock = f->read<ubyte>();
			scriptEffectInfoFinishBlock = f->read<ubyte>();
			scriptEffectInfoUnk = f->read<ushort>();
			scriptEffectInfoElapsedSeconds = f->read<float>();
		}
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(script));
		f->write<ushort>(varNum);
		for (ushort i = 0;i < varNum;i++)
		{
			f->write<ushort>(variables[i].varIndex);
			f->write<ushort>(variables[i].type);
			if (type == 0)
			{
				f->write<double>(variables[i].locvar);
			}
			else
			{
				f->write<iref>(parent->GetFormiRef(variables[i].refvar));
			}
		}
		f->write<ubyte>(scriptInfoPresent);
		if (scriptInfoPresent)
		{
			f->write<ubyte>(scriptEffectInfoStartBlock);
			f->write<ubyte>(scriptEffectInfoFinishBlock);
			f->write<ushort>(scriptEffectInfoUnk);
			f->write<float>(scriptEffectInfoElapsedSeconds);
		}
	}
};
class ExtraLeveledItemData : public ExtraData
{
protected:
	ulong leveledItemUnk1;
	ubyte leveledItemUnk2;
public:
	ExtraLeveledItemData()
	{
		type = ExtraLeveledItem;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		leveledItemUnk1 = f->read<ulong>();
		leveledItemUnk2 = f->read<ubyte>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ulong>(leveledItemUnk1);
		f->write<ubyte>(leveledItemUnk2);
	}
};
class ExtraPackageData : public ExtraData
{
protected:
	formid packageID;
	ulong packageFlags;
	formid packageUnk1;
	ushort packageUnk2;
public:
	ExtraPackageData()
	{
		type = ExtraPackage;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		packageID = parent->GetFormID(f->read<iref>());
		packageFlags = f->read<ulong>();
		packageUnk1 = parent->GetFormID(f->read<iref>());
		packageUnk2 = f->read<ushort>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(packageID));
		f->write<ulong>(packageFlags);
		f->write<iref>(parent->GetFormiRef(packageUnk1));
		f->write<ushort>(packageUnk2);
	}
};
class ExtraTressPassPackageData : public ExtraData
{
protected:
	formid tresspassID;
	float tresspassUnk1;
	ulong tresspassUnk2;
	ulong tresspassUnk4;
	ulong tresspassUnk5;
	formid tresspassFaction;
	formid tresspassCell;
public:
	ExtraTressPassPackageData()
	{
		type = ExtraTressPassPackage;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		tresspassID = parent->GetFormID(f->read<iref>());
		tresspassUnk1 = f->read<float>();
		tresspassUnk2 = f->read<ulong>();
		tresspassUnk4 = f->read<ulong>();
		tresspassUnk5 = f->read<ulong>();
		tresspassFaction = parent->GetFormID(f->read<iref>());
		tresspassCell = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(tresspassID));
		f->write<float>(tresspassUnk1);
		f->write<ulong>(tresspassUnk2);
		f->write<ulong>(tresspassUnk4);
		f->write<ulong>(tresspassUnk5);
		f->write<iref>(parent->GetFormiRef(tresspassFaction));
		f->write<iref>(parent->GetFormiRef(tresspassCell));
	}
};
class ExtraUsedMarkersData : public ExtraData
{
protected:
	ulong usedMarkers;
public:
	ExtraUsedMarkersData()
	{
		type = ExtraUsedMarkers;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		usedMarkers = f->read<ulong>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ulong>(usedMarkers);
	}
};
class ExtraReferencePointerData : public ExtraData
{
protected:
	formid referencePointer;
public:
	ExtraReferencePointerData()
	{
		type = ExtraReferencePointer;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		referencePointer = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(referencePointer));
	}
};
class ExtraLeveledCreatureData : public ExtraData
{
public:
	ExtraLeveledCreatureData()
	{
		type = ExtraLeveledCreature;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
	}
};
#pragma pack(push,1)
struct RunOncePack
{
	formid packageID;
	ubyte unk;
};
#pragma pack(pop)
class ExtraRunOncePacksData : public ExtraData
{
protected:
	ushort packCount;
	RunOncePack *runOncePacks;
public:
	ExtraRunOncePacksData() : runOncePacks(0), packCount(0)
	{
		type = ExtraRunOncePacks;
	}
	~ExtraRunOncePacksData()
	{
		if (runOncePacks)
		{
			delete[] runOncePacks;
		}
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		packCount = f->read<ushort>();
		runOncePacks = f->readarray<RunOncePack>(packCount);
		for (ushort i = 0;i < packCount;i++)
		{
			runOncePacks[i].packageID = parent->GetFormID(runOncePacks[i].packageID);
		}
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ushort>(packCount);
		for (ushort i = 0;i < packCount;i++)
		{
			f->write<iref>(parent->GetFormiRef(runOncePacks[i].packageID));
			f->write<ubyte>(runOncePacks[i].unk);
		}
	}
};
class ExtraPackageStartLocationData : public ExtraData
{
protected:
	formid startLocationID;
	NiPoint3 position;
	float zRotation;
public:
	ExtraPackageStartLocationData()
	{
		type = ExtraPackageStartLocation;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		startLocationID = parent->GetFormID(f->read<iref>());
		position = f->read<NiPoint3>();
		zRotation = f->read<float>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(startLocationID));
		f->write<NiPoint3>(position);
		f->write<float>(zRotation);
	}
};
class ExtraFollowerData : public ExtraData
{
protected:
	ushort followerCount;
	formid *followers;
public:
	ExtraFollowerData() : followers(0), followerCount(0)
	{
		type = ExtraFollower;
	}
	~ExtraFollowerData()
	{
		if (followers)
		{
			delete[] followers;
		}
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		followerCount = f->read<ushort>();
		followers = f->readarray<iref>(followerCount);
		for (ushort i = 0;i < followerCount;i++)
		{
			followers[i] = parent->GetFormID(followers[i]);
		}
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ushort>(followerCount);
		for (ushort i = 0;i < followerCount;i++)
		{
			f->write<iref>(parent->GetFormiRef(followers[i]));
		}
	}
};
class ExtraNonActorMagicCasterData : public ExtraData
{
protected:
	formid magicItem;
	formid magicTarget;
	formid magicCaster;
public:
	ExtraNonActorMagicCasterData()
	{
		type = ExtraNonActorMagicCaster;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		magicItem = parent->GetFormID(f->read<iref>());
		magicTarget = parent->GetFormID(f->read<iref>());
		magicCaster = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(magicItem));
		f->write<iref>(parent->GetFormiRef(magicTarget));
		f->write<iref>(parent->GetFormiRef(magicCaster));
	}
};
class ActiveEffect;
struct EffectItemData
{
	ushort size;
	formid magicItem;
	ubyte effectIndex;
	ActiveEffect *effect;
};
class ExtraNonActorMagicTargetData : public ExtraData
{
protected:
	formid magicTarget;
	ushort effectCount;
	SimpleDynVecClass<EffectItemData> effectItems;
public:
	ExtraNonActorMagicTargetData()
	{
		type = ExtraNonActorMagicTarget;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		magicTarget = parent->GetFormID(f->read<iref>());
		effectCount = f->read<ushort>();
		for (ushort i = 0;i < effectCount;i++)
		{
			EffectItemData d;
			d.size = f->read<ushort>();
			d.magicItem = parent->GetFormID(f->read<iref>());
			d.effectIndex = f->read<ubyte>();
			effectItems.Add(d);
			Form *f = FindForm(d.magicItem);
			ulong effectID = 0;
			EnchantmentForm *e = dynamic_cast<EnchantmentForm *>(f);
			if (e)
			{
				effectID = e->GetEffectItems()[d.effectIndex].effectID;
			}
			SpellForm *s = dynamic_cast<SpellForm *>(f);
			if (s)
			{
				effectID = e->GetEffectItems()[d.effectIndex].effectID;
			}
			AlchemyForm *a = dynamic_cast<AlchemyForm *>(f);
			if (a)
			{
				effectID = e->GetEffectItems()[d.effectIndex].effectID;
			}
			printf("Unknown ActiveEffect found");
			__debugbreak();
		}
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(magicTarget));
	}
};
class ExtraTeleportData : public ExtraData
{
protected:
	NiPoint3 position;
	NiPoint3 rotation;
	formid door;
public:
	ExtraTeleportData()
	{
		type = ExtraTeleport;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		position = f->read<NiPoint3>();
		rotation = f->read<NiPoint3>();
		door = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<NiPoint3>(position);
		f->write<NiPoint3>(rotation);
		f->write<iref>(parent->GetFormiRef(door));
	}
};
class ExtraOblivionEntryData : public ExtraData
{
protected:
	formid door;
	NiPoint3 position;
public:
	ExtraOblivionEntryData()
	{
		type = ExtraOblivionEntry;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		door = parent->GetFormID(f->read<iref>());
		position = f->read<NiPoint3>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(door));
		f->write<NiPoint3>(position);
	}
};
class ExtraPersuasionPercentData : public ExtraData
{
protected:
	float unk1;
	float unk2;
	ubyte unk3;
	ulong unk4;
public:
	ExtraPersuasionPercentData()
	{
		type = ExtraPersuasionPercent;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		unk1 = f->read<float>();
		unk2 = f->read<float>();
		unk3 = f->read<ubyte>();
		unk4 = f->read<ulong>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<float>(unk1);
		f->write<float>(unk2);
		f->write<ubyte>(unk3);
		f->write<ulong>(unk4);
	}
};
class ExtraPoisonData : public ExtraData
{
protected:
	formid poison;
public:
	ExtraPoisonData()
	{
		type = ExtraPoison;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		poison = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(poison));
	}
};
class ExtraLastFinishedSequenceData : public ExtraData
{
protected:
	char *sequence;
public:
	ExtraLastFinishedSequenceData() : sequence(0)
	{
		type = ExtraLastFinishedSequence;
	}
	~ExtraLastFinishedSequenceData()
	{
		if (sequence)
		{
			delete[] sequence;
		}
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		sequence = f->readbstring();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->writebstring(sequence);
	}
};
class ExtraMapMarkerData : public ExtraData
{
protected:
	ubyte marker;
public:
	ExtraMapMarkerData()
	{
		type = ExtraMapMarker;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		marker = f->read<ubyte>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ubyte>(marker);
	}
};
class ExtraPersistentCellData : public ExtraData
{
protected:
	formid cell;
public:
	ExtraPersistentCellData()
	{
		type = ExtraPersistentCell;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		cell = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(cell));
	}
};
class ExtraDroppedItemListData : public ExtraData
{
protected:
	ubyte itemCount;
	formid *items;
public:
	ExtraDroppedItemListData() : items(0), itemCount(0)
	{
		type = ExtraDroppedItemList;
	}
	~ExtraDroppedItemListData()
	{
		if (items)
		{
			delete[] items;
		}
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		itemCount = f->read<ubyte>();
		items = f->readarray<iref>(itemCount);
		for (ubyte i = 0;i < itemCount;i++)
		{
			items[i] = parent->GetFormID(items[i]);
		}
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ubyte>(itemCount);
		for (ushort i = 0;i < itemCount;i++)
		{
			f->write<iref>(parent->GetFormiRef(items[i]));
		}
	}
};
class ExtraItemDropperData : public ExtraData
{
protected:
	formid dropper;
public:
	ExtraItemDropperData()
	{
		type = ExtraItemDropper;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		dropper = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(dropper));
	}
};
class ExtraSavedMovementDataData : public ExtraData
{
protected:
	ushort savedAnimationCount;
	byte *savedAnimationData;
	ushort savedAttachedAnimationCount;
	byte *shavedAttachedAnimationData;
	ushort savedHavocDataCount;
	byte *savedHavocData;
public:
	ExtraSavedMovementDataData() : savedAnimationCount(0), savedAnimationData(0), savedAttachedAnimationCount(0), shavedAttachedAnimationData(0), savedHavocDataCount(0), savedHavocData(0)
	{
		type = ExtraSavedMovementData;
	}
	~ExtraSavedMovementDataData()
	{
		if (savedAnimationData)
		{
			delete[] savedAnimationData;
		}
		if (shavedAttachedAnimationData)
		{
			delete[] shavedAttachedAnimationData;
		}
		if (savedHavocData)
		{
			delete[] savedHavocData;
		}
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		savedAnimationCount = f->read<ushort>();
		savedAnimationData = f->readarray<byte>(savedAnimationCount);
		savedAttachedAnimationCount = f->read<ushort>();
		shavedAttachedAnimationData = f->readarray<byte>(savedAttachedAnimationCount);
		savedHavocDataCount = f->read<ushort>();
		savedHavocData = f->readarray<byte>(savedHavocDataCount);
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ushort>(savedAnimationCount);
		f->writearray<byte>(savedAnimationCount,savedAnimationData);
		f->write<ushort>(savedAttachedAnimationCount);
		f->writearray<byte>(savedAttachedAnimationCount,shavedAttachedAnimationData);
		f->write<ushort>(savedHavocDataCount);
		f->writearray<byte>(savedHavocDataCount,savedHavocData);
	}
};
class ExtraMagicLightData : public ExtraData
{
protected:
	formid light;
public:
	ExtraMagicLightData()
	{
		type = ExtraMagicLight;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		light = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(light));
	}
};
#pragma pack(push,1)
struct FriendHit
{
	formid item;
	ushort unk1;
	ushort unk2;
};
#pragma pack(pop)
class ExtraFriendHitListData : public ExtraData
{
protected:
	ushort listCount;
	FriendHit *hitList;
public:
	ExtraFriendHitListData() : hitList(0), listCount(0)
	{
		type = ExtraFriendHitList;
	}
	~ExtraFriendHitListData()
	{
		if (hitList)
		{
			delete[] hitList;
		}
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		listCount = f->read<ushort>();
		hitList = f->readarray<FriendHit>(listCount);
		for (ushort i = 0;i < listCount;i++)
		{
			hitList[i].item = parent->GetFormID(hitList[i].item);
		}
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ushort>(listCount);
		for (ushort i = 0;i < listCount;i++)
		{
			f->write<iref>(parent->GetFormiRef(hitList[i].item));
			f->write<ushort>(hitList[i].unk1);
			f->write<ushort>(hitList[i].unk2);
		}
	}
};
class ExtraHeadingTargetData : public ExtraData
{
protected:
	formid target;
public:
	ExtraHeadingTargetData()
	{
		type = ExtraHeadingTarget;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		target = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(target));
	}
};
class ExtraStartingWorldOrCellData : public ExtraData
{
protected:
	formid start;
public:
	ExtraStartingWorldOrCellData()
	{
		type = ExtraStartingWorldOrCell;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		start = parent->GetFormID(f->read<iref>());
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<iref>(parent->GetFormiRef(start));
	}
};
class ExtraUnknown54Data : public ExtraData
{
public:
	ExtraUnknown54Data()
	{
		type = ExtraUnknown54;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
	}
};
class ExtraQuickKeyData : public ExtraData
{
protected:
	ubyte key;
public:
	ExtraQuickKeyData()
	{
		type = ExtraQuickKey;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		key = f->read<ubyte>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ubyte>(key);
	}
};
#pragma pack(push,1)
struct Conversation
{
	ubyte index;
	formid quest;
	formid dialog;
	formid info;
};
#pragma pack(pop)
class ExtraInfoGeneralTopicData : public ExtraData
{
protected:
	char *convTopic;
	ushort convCount;
	Conversation *conversations;
public:
	ExtraInfoGeneralTopicData() : convTopic(0), conversations(0), convCount(0)
	{
		type = ExtraInfoGeneralTopic;
	}
	~ExtraInfoGeneralTopicData()
	{
		if (convTopic)
		{
			delete[] convTopic;
		}
		if (conversations)
		{
			delete[] conversations;
		}
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		convCount = f->read<ushort>();
		conversations = f->readarray<Conversation>(convCount);
		for (ushort i = 0;i < convCount;i++)
		{
			conversations[i].quest = parent->GetFormID(conversations[i].quest);
			conversations[i].dialog = parent->GetFormID(conversations[i].dialog);
			conversations[i].info = parent->GetFormID(conversations[i].info);
		}
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ushort>(convCount);
		for (ushort i = 0;i < convCount;i++)
		{
			f->write<ubyte>(conversations[i].index);
			f->write<iref>(parent->GetFormiRef(conversations[i].quest));
			f->write<iref>(parent->GetFormiRef(conversations[i].dialog));
			f->write<iref>(parent->GetFormiRef(conversations[i].info));
		}
		f->writearray<Conversation>(convCount,conversations);
	}
};
class ExtraHasNoRumorsData : public ExtraData
{
protected:
	ubyte rumors;
public:
	ExtraHasNoRumorsData()
	{
		type = ExtraHasNoRumors;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		rumors = f->read<ubyte>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<ubyte>(rumors);
	}
};
class ExtraHaggleAmountData : public ExtraData
{
protected:
	float haggle;
public:
	ExtraHaggleAmountData()
	{
		type = ExtraHaggleAmount;
	}
	virtual void Load(FileRead *f,ESSFile *parent)
	{
		haggle = f->read<float>();
	}
	virtual void Save(FileWrite *f,ESSFile *parent)
	{
		f->write<float>(haggle);
	}
};
class ExtraDataList
{
protected:
	SimpleDynVecClass<ExtraData *> properties;
public:
	ExtraDataList() : properties(0)
	{
	}
	~ExtraDataList()
	{
		for (int i = 0;i < properties.Count();i++)
		{
			delete properties[i];
		}
	}
	void Load(FileRead *f,ulong flags,ChangeRecord *cr,ESSFile *parent)
	{
		ushort propertyCount = f->read<ushort>();
		for (ushort i = 0;i < propertyCount;i++)
		{
			ubyte type = f->read<ubyte>();
			switch (type)
			{
			case ExtraCount:
				if (flags & AllExtra)
				{
					ExtraCountData *d = new ExtraCountData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraHealth:
				if (flags & AllExtra)
				{
					ExtraHealthData *d = new ExtraHealthData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraUses:
				if (flags & AllExtra)
				{
					ExtraUsesData *d = new ExtraUsesData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraTimeLeft:
				if (flags & AllExtra)
				{
					ExtraTimeLeftData *d = new ExtraTimeLeftData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraCharge:
				if (flags & AllExtra)
				{
					ExtraChargeData *d = new ExtraChargeData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraSoul:
				if (flags & AllExtra)
				{
					ExtraSoulData *d = new ExtraSoulData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraLock:
				if (flags & Lock)
				{
					ExtraLockData *d = new ExtraLockData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraScale:
				if (flags & AllExtra)
				{
					ExtraScaleData *d = new ExtraScaleData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraInvestmentGold:
				if (flags & InvestmentGold)
				{
					ExtraInvestmentGoldData *d = new ExtraInvestmentGoldData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraCrimeGold:
				if (flags & InvestmentGold)
				{
					ExtraCrimeGoldData *d = new ExtraCrimeGoldData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraOwnership:
				if ((flags & AllExtra) || (flags & RefrOwner))
				{
					ExtraOwnershipData *d = new ExtraOwnershipData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraGlobal:
				if ((flags & AllExtra) || (flags & Global))
				{
					ExtraGlobalData *d = new ExtraGlobalData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraRank:
				if ((flags & AllExtra) || (flags & Rank))
				{
					ExtraRankData *d = new ExtraRankData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraWorn:
				if (flags & AllExtra)
				{
					ExtraWornData *d = new ExtraWornData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraWornLeft:
				if (flags & AllExtra)
				{
					ExtraWornLeftData *d = new ExtraWornLeftData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraCannotWear:
				if (flags & AllExtra)
				{
					ExtraCannotWearData *d = new ExtraCannotWearData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraBoundArmor:
				if (flags & AllExtra)
				{
					ExtraBoundArmorData *d = new ExtraBoundArmorData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraGhost:
				{
					ExtraGhostData *d = new ExtraGhostData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraScript:
				if ((flags & AllExtra) || (flags & Script))
				{
					ExtraScriptData *d = new ExtraScriptData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraLeveledItem:
				if (flags & AllExtra)
				{
					ExtraLeveledItemData *d = new ExtraLeveledItemData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraPackage:
				{
					ExtraPackageData *d = new ExtraPackageData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraTressPassPackage:
				if (flags & Tresspass)
				{
					ExtraTressPassPackageData *d = new ExtraTressPassPackageData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraUsedMarkers:
				if (flags & FurnitureMarker)
				{
					ExtraUsedMarkersData *d = new ExtraUsedMarkersData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraReferencePointer:
				if (flags & AllExtra)
				{
					ExtraReferencePointerData *d = new ExtraReferencePointerData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraLeveledCreature:
				if (flags & LeveledCreature)
				{
					ExtraLeveledCreatureData *d = new ExtraLeveledCreatureData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraRunOncePacks:
				{
					ExtraRunOncePacksData *d = new ExtraRunOncePacksData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraPackageStartLocation:
				{
					ExtraPackageStartLocationData *d = new ExtraPackageStartLocationData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraFollower:
				{
					ExtraFollowerData *d = new ExtraFollowerData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraNonActorMagicCaster:
				if (flags & ExtraMagic)
				{
					ExtraNonActorMagicCasterData *d = new ExtraNonActorMagicCasterData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraNonActorMagicTarget:
				if (flags & ExtraMagic)
				{
					ExtraNonActorMagicTargetData *d = new ExtraNonActorMagicTargetData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraTeleport:
				if (flags & Teleport)
				{
					ExtraTeleportData *d = new ExtraTeleportData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraOblivionEntry:
				if (flags & OblivionEntry)
				{
					ExtraOblivionEntryData *d = new ExtraOblivionEntryData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraPersuasionPercent:
				if (flags & PersuasionPercent)
				{
					ExtraPersuasionPercentData *d = new ExtraPersuasionPercentData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraPoison:
				if (flags & AllExtra)
				{
					ExtraPoisonData *d = new ExtraPoisonData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraLastFinishedSequence:
				if (flags & Animation)
				{
					ExtraLastFinishedSequenceData *d = new ExtraLastFinishedSequenceData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraMapMarker:
				if (flags & MapMarkerFlags)
				{
					ExtraMapMarkerData *d = new ExtraMapMarkerData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraPersistentCell:
				if (cr && cr->IsActor())
				{
					ExtraPersistentCellData *d = new ExtraPersistentCellData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraDroppedItemList:
				{
					ExtraDroppedItemListData *d = new ExtraDroppedItemListData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraItemDropper:
				{
					ExtraItemDropperData *d = new ExtraItemDropperData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraSavedMovementData:
				if (flags & MovementExtra)
				{
					ExtraSavedMovementDataData *d = new ExtraSavedMovementDataData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraMagicLight:
				{
					ExtraMagicLightData *d = new ExtraMagicLightData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraFriendHitList:
				{
					ExtraFriendHitListData *d = new ExtraFriendHitListData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraHeadingTarget:
				{
					ExtraHeadingTargetData *d = new ExtraHeadingTargetData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraStartingWorldOrCell:
				{
					ExtraStartingWorldOrCellData *d = new ExtraStartingWorldOrCellData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraUnknown54:
				{
					ExtraUnknown54Data *d = new ExtraUnknown54Data();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraQuickKey:
				if (flags & AllExtra)
				{
					ExtraQuickKeyData *d = new ExtraQuickKeyData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraInfoGeneralTopic:
				{
					ExtraInfoGeneralTopicData *d = new ExtraInfoGeneralTopicData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraHasNoRumors:
				{
					ExtraHasNoRumorsData *d = new ExtraHasNoRumorsData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			case ExtraHaggleAmount:
				{
					ExtraHaggleAmountData *d = new ExtraHaggleAmountData();
					d->Load(f,parent);
					properties.Add(d);
				}
				break;
			default:
				printf("Unknown property found");
				__debugbreak();
				break;
			}
		}
	}
	void Save(FileWrite *f,ulong flags,ChangeRecord *cr,ESSFile *parent)
	{
	}
};