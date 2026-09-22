/*	libfos
	Copyright 2015 Jonathan Wilson

	This file is part of libfos
	libfos is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "boundobjectform.h"
#pragma pack(push,1)
struct WeaponData
{
	long value;
	long health;
	float weight;
	ushort baseDamage;
	ubyte clipSize;
};
#pragma pack(pop)
struct WeaponStatsData
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 ulong unk;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponActorValue;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPoints;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float animShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long weaponSkill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
	 ulong sightUsage;
	 float semiAutoFireDelayMin;
	 float semiAutoFireDelayMax;
};
struct WeaponStatsDataSmall
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 ulong unk;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponActorValue;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPoints;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float animShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long weaponSkill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
	 long resistType;
};
struct WeaponStatsDataTiny
{
	 ubyte weaponAnimType;
	 float animMult;
	 float reach;
	 ubyte flags1;
	 ubyte handGrip;
	 ubyte ammoUse;
	 ubyte reloadAnim;
	 float minSpread;
	 float spread;
	 ulong unk;
	 float sightFOV;
	 ubyte conditionLevel;
	 formid projectile;
	 ubyte baseVATSChance;
	 ubyte attackAnim;
	 ubyte numProjectiles;
	 ubyte embedWeaponActorValue;
	 float minRange;
	 float maxRange;
	 ulong onHit;
	 ulong flags2;
	 float animAttackMult;
	 float fireRate;
	 float actionPoints;
	 float rumbleLeftMotor;
	 float rumbleRightMotor;
	 float rumbleDuration;
	 float damageToWeaponMult;
	 float animShotsPerSec;
	 float reloadTime;
	 float jamTime;
	 float aimArc;
	 long weaponSkill;
	 ulong rumblePattern;
	 float rumbleWaveLength;
	 float limbDamageMult;
};
struct WeaponCritData
{
	ushort critDamage;
	float critPercentage;
	ubyte critEffectOnDeath;
	formid critEffect;
};
class WeaponForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public ModelFaceGenFlags, public Texture, public Scriptable, public Enchantable, public Ammo, public DestructibleObject, public RepairItem, public EquipType, public MessageTexture, public BipedModelList, public PickupPutdownSounds
{
protected:
	Model shellCasingModel;
	Model scopeTargetModel;
	formid scopeEffect;
	Model worldModel;
	char *enbeddedWeaponNode;
	formid impactDataSet;
	formid firstPersonModel;
	formid soundAttack;
	formid soundAttack2D;
	formid soundAttackLooping;
	formid soundAttackFail;
	formid soundBlock;
	formid soundIdle;
	formid soundEquip;
	formid soundUnequip;
	WeaponData data;
	WeaponStatsData statsData;
	WeaponStatsDataSmall statsDataSmall;
	WeaponStatsDataTiny statsDataTiny;
	WeaponCritData critData;
	ulong soundLevel;
	bool hasSmallStats;
	bool hasTinyStats;
public:
	WeaponForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), scopeEffect(0), enbeddedWeaponNode(0), impactDataSet(0), firstPersonModel(0), soundAttack(0), soundAttack2D(0), soundAttackLooping(0), soundAttackFail(0), soundBlock(0), soundIdle(0), soundEquip(0), soundUnequip(0), hasSmallStats(false), hasTinyStats(false)
	{
	}
	virtual ~WeaponForm()
	{
		if (enbeddedWeaponNode)
		{
			delete[] enbeddedWeaponNode;
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			BoundObjectFormLoad();
			FullNameLoad();
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			ModelFaceGenFlagsLoad(this,'MODD');
			TextureLoad(this,'ICON');
			MessageTextureLoad(this,'MICO');
			ScriptableLoad();
			EnchantableLoad();
			AmmoLoad();
			DestructibleObjectLoad();
			RepairItemLoad();
			EquipTypeLoad();
			BipedModelListLoad();
			PickupPutdownSoundsLoad();
			ModelBRLoad((&shellCasingModel),'MOD2','MO2B','MO2T');
			ModelBRLoad((&scopeTargetModel),'MOD3','MO3B','MO3T');
			case 'EFSD':
				scopeEffect = f->read<formid>();
				readSize += 4;
				break;
			ModelBRLoad((&worldModel),'MOD4','MO4B','MO4T');
			case 'NNAM':
				enbeddedWeaponNode = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'INAM':
				impactDataSet = f->read<formid>();
				readSize += 4;
				break;
			case 'WNAM':
				firstPersonModel = f->read<formid>();
				readSize += 4;
				break;
			case 'SNAM':
				soundAttack = f->read<formid>();
				readSize += 4;
				break;
			case 'XNAM':
				soundAttack2D = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM7':
				soundAttackLooping = f->read<formid>();
				readSize += 4;
				break;
			case 'TNAM':
				soundAttackFail = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM6':
				soundBlock = f->read<formid>();
				readSize += 4;
				break;
			case 'UNAM':
				soundIdle = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM9':
				soundEquip = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM8':
				soundUnequip = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
				data = f->read<WeaponData>();
				readSize += sizeof(WeaponData);
				break;
			case 'DNAM':
				if (h.size == sizeof(WeaponStatsData))
				{
					statsData = f->read<WeaponStatsData>();
					readSize += sizeof(WeaponStatsData);
				}
				else if (h.size == sizeof(WeaponStatsDataSmall))
				{
					hasSmallStats = true;
					statsDataSmall = f->read<WeaponStatsDataSmall>();
					readSize += sizeof(WeaponStatsDataSmall);
				} 
				else
				{
					hasTinyStats = true;
					statsDataTiny = f->read<WeaponStatsDataTiny>();
					readSize += sizeof(WeaponStatsDataTiny);
				}
				break;
			case 'CRDT':
				critData = f->read<WeaponCritData>();
				readSize += sizeof(WeaponCritData);
				break;
			case 'VNAM':
				soundLevel = f->read<ulong>();
				readSize += 4;
				break;
			default:
				printf("Unknown subrecord found");
				__debugbreak();
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		BoundObjectFormSave();
		FullNameSave();
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ModelFaceGenFlagsSave(this,'MODD');
		TextureSave(this,'ICON');
		MessageTextureSave(this,'MICO');
		ScriptableSave();
		EnchantableSave();
		AmmoSave();
		DestructibleObjectSave();
		RepairItemSave();
		EquipTypeSave();
		BipedModelListSave();
		PickupPutdownSoundsSave();
		ModelBRSave((&shellCasingModel),'MOD2','MO2B','MO2T');
		if (statsData.flags1 & 4)
		{
			ModelBRSave((&scopeTargetModel),'MOD3','MO3B','MO3T');
			if (scopeEffect)
			{
				WriteSubrecord('EFSD',4,f);
				f->write<formid>(scopeEffect);
			}
		}
		ModelBRSave((&worldModel),'MOD4','MO4B','MO4T');
		WriteZStringSubrecord('NNAM',enbeddedWeaponNode,f);
		if (impactDataSet)
		{
			WriteSubrecord('INAM',4,f);
			f->write<formid>(impactDataSet);
		}
		if (firstPersonModel)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(firstPersonModel);
		}
		if (soundAttack)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(soundAttack);
		}
		if (soundAttack2D)
		{
			WriteSubrecord('XNAM',4,f);
			f->write<formid>(soundAttack2D);
		}
		if (soundAttackLooping)
		{
			WriteSubrecord('NAM7',4,f);
			f->write<formid>(soundAttackLooping);
		}
		if (soundAttackFail)
		{
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(soundAttackFail);
		}
		if (soundBlock)
		{
			WriteSubrecord('NAM6',4,f);
			f->write<formid>(soundBlock);
		}
		if (soundIdle)
		{
			WriteSubrecord('UNAM',4,f);
			f->write<formid>(soundIdle);
		}
		if (soundEquip)
		{
			WriteSubrecord('NAM9',4,f);
			f->write<formid>(soundEquip);
		}
		if (soundUnequip)
		{
			WriteSubrecord('NAM8',4,f);
			f->write<formid>(soundUnequip);
		}
		WriteSubrecord('DATA',sizeof(WeaponData),f);
		f->write<WeaponData>(data);
		if (hasSmallStats)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsDataSmall),f);
			f->write<WeaponStatsDataSmall>(statsDataSmall);
		}
		else if (hasTinyStats)
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsDataTiny),f);
			f->write<WeaponStatsDataTiny>(statsDataTiny);
		}
		else
		{
			WriteSubrecord('DNAM',sizeof(WeaponStatsData),f);
			f->write<WeaponStatsData>(statsData);
		}
		WriteSubrecord('CRDT',sizeof(WeaponCritData),f);
		f->write<WeaponCritData>(critData);
		WriteSubrecord('VNAM',4,f);
		f->write<formid>(soundLevel);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ModelFaceGenFlagsGetSaveSize(this);
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		ScriptableGetSaveSize();
		EnchantableGetSaveSize();
		AmmoGetSaveSize();
		DestructibleObjectGetSaveSize();
		RepairItemGetSaveSize();
		EquipTypeGetSaveSize();
		BipedModelListGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		ModelBRGetSaveSize((&shellCasingModel));
		if (statsData.flags1 & 4)
		{
			ModelBRGetSaveSize((&scopeTargetModel));
			if (scopeEffect)
			{
				size += ComputeSubrecordSize(4);
			}
		}
		ModelBRGetSaveSize((&worldModel));
		size += ZStringSubrecordSize(enbeddedWeaponNode);
		if (impactDataSet)
		{
			size += ComputeSubrecordSize(4);
		}
		if (firstPersonModel)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttack)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttack2D)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttackLooping)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundAttackFail)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundBlock)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundIdle)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundEquip)
		{
			size += ComputeSubrecordSize(4);
		}
		if (soundUnequip)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(sizeof(WeaponData));
		if (hasSmallStats)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsDataSmall));
		}
		else if (hasTinyStats)
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsDataTiny));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(WeaponStatsData));
		}
		size += ComputeSubrecordSize(sizeof(WeaponCritData));
		size += ComputeSubrecordSize(4);
		return size;
	}
};
