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
struct Sound
{
	formid sound;
	ubyte chance;
};
struct SoundType
{
	ulong type;
	SimpleDynVecClass<Sound> sounds;
	SoundType() : sounds(0)
	{
	};
};
class CreatureForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	SimpleDynVecClass<formid> spellList;
	SimpleDynVecClass<char *> modelList;
	SimpleDynVecClass<char *> animationList;
	ulong niftextureHashesCount;
	ubyte *niftextureHashes;
	ulong flags;
	ushort baseSpellPoints;
	ushort fatigue;
	ushort barterGold;
	short level;
	ushort calcMin;
	ushort calcMax;
	formid deathItem;
	ubyte creatureType;
	ubyte combatSkill;
	ubyte magicSkill;
	ubyte stealthSkill;
	ushort soul;
	ushort health;
	ushort pad;
	ushort attackDamage;
	ubyte strength;
	ubyte intellegence;
	ubyte willpower;
	ubyte agillity;
	ubyte speed;
	ubyte endurance;
	ubyte personality;
	ubyte luck;
	ubyte attackReach;
	formid combatStyle;
	float turningSpeed;
	float baseScale;
	float footWeight;
	char *bloodSpray;
	char *bloodDecal;
	formid inheritsSoundsFrom;
	SimpleDynVecClass<SoundType *> sounds;
	SimpleDynVecClass<ContainerItem> containerItems;
	SimpleDynVecClass<FactionRef> factions;
	ubyte agression;
	ubyte confidence;
	ubyte energyLevel;
	ubyte responsibility;
	ulong aiFlags;
	ubyte trainSkill;
	ubyte trainLevel;
	ushort aiPad;
	SimpleDynVecClass<formid> aiPackages;
	formid script;
	SimpleDynVecClass<ulong> properties;
public:
	CreatureForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), spellList(0), modelList(0), animationList(0), flags(0), baseSpellPoints(0), fatigue(0), barterGold(0), level(0), calcMin(0), calcMax(0), deathItem(0), creatureType(0), combatSkill(0), magicSkill(0), stealthSkill(0), soul(0), health(0), pad(0), attackDamage(0), strength(0), intellegence(0), willpower(0), agillity(0), speed(0), endurance(0), personality(0), luck(0), attackReach(0), combatStyle(0), turningSpeed(0), baseScale(0), footWeight(0), bloodSpray(0), bloodDecal(0), inheritsSoundsFrom(0), sounds(0), niftextureHashesCount(0), niftextureHashes(0), containerItems(0), factions(0), agression(0), confidence(0), energyLevel(0), responsibility(0), aiFlags(0), trainSkill(0), trainLevel(0), aiPad(0), aiPackages(0), script(0), properties(0)
	{
	}
	virtual ~CreatureForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (model)
		{
			delete[] model;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
		}
		for (int i = 0;i < modelList.Count();i++)
		{
			delete[] modelList[i];
		}
		for (int i = 0;i < animationList.Count();i++)
		{
			delete[] animationList[i];
		}
		if (bloodSpray)
		{
			delete[] bloodSpray;
		}
		if (bloodDecal)
		{
			delete[] bloodDecal;
		}
		if (niftextureHashes)
		{
			delete[] niftextureHashes;
		}
		for (int i = 0;i < sounds.Count();i++)
		{
			delete sounds[i];
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
			case 'EDID':
				editorID = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'FULL':
				fullName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODL':
				model = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODB':
				boundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MODT':
				textureHashesCount = h.size / sizeof(TextureHash);
				textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'CNTO':
				{
					if (!properties.Count() || properties[properties.Count() - 1] != 'CNTO')
					{
						properties.Add('CNTO');
					}
					ContainerItem i;
					i.item = f->read<formid>();
					readSize += 4;
					i.count = f->read<ulong>();
					readSize += 4;
					containerItems.Add(i);
				}
				break;
			case 'SPLO':
				if (!properties.Count() || properties[properties.Count() - 1] != 'SPLO')
				{
					properties.Add('SPLO');
				}
				spellList.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'NIFZ':
				{
					properties.Add('NIFZ');
					char *strarray = f->readarray<char>(h.size);
					char *array2 = strarray;
					while(strlen(array2))
					{
						char *str = new char[strlen(array2)+1];
						memcpy(str,array2,strlen(array2)+1);
						array2 += strlen(array2);
						array2++;
						modelList.Add(str);
					}
					delete[] strarray;
					readSize += h.size;
				}
				break;
			case 'NIFT':
				properties.Add('NIFT');
				niftextureHashesCount = h.size;
				niftextureHashes = f->readarray<ubyte>(h.size);
				readSize += h.size;
				break;
			case 'ACBS':
				properties.Add('ACBS');
				flags = f->read<ulong>();
				readSize += 4;
				baseSpellPoints = f->read<ushort>();
				readSize += 2;
				fatigue = f->read<ushort>();
				readSize += 2;
				barterGold = f->read<ushort>();
				readSize += 2;
				level = f->read<short>();
				readSize += 2;
				calcMin = f->read<ushort>();
				readSize += 2;
				calcMax = f->read<ushort>();
				readSize += 2;
				break;
			case 'SNAM':
				{
					if (!properties.Count() || properties[properties.Count() - 1] != 'SNAM')
					{
						properties.Add('SNAM');
					}
					FactionRef r;
					r.faction = f->read<formid>();
					r.rank = f->read<ulong>();
					factions.Add(r);
					readSize += 8;
				}
				break;
			case 'SCRI':
				properties.Add('SCRI');
				script = f->read<formid>();
				readSize += 4;
				break;
			case 'AIDT':
				properties.Add('AIDT');
				agression = f->read<ubyte>();
				readSize += 1;
				confidence = f->read<ubyte>();
				readSize += 1;
				energyLevel = f->read<ubyte>();
				readSize += 1;
				responsibility = f->read<ubyte>();
				readSize += 1;
				aiFlags = f->read<ulong>();
				readSize += 4;
				trainSkill = f->read<ubyte>();
				readSize += 1;
				trainLevel = f->read<ubyte>();
				readSize += 1;
				aiPad = f->read<ushort>();
				readSize += 2;
				break;
			case 'PKID':
				if (!properties.Count() || properties[properties.Count() - 1] != 'PKID')
				{
					properties.Add('PKID');
				}
				aiPackages.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'INAM':
				properties.Add('INAM');
				deathItem = f->read<formid>();
				readSize += 4;
				break;
			case 'KFFZ':
				{
					properties.Add('KFFZ');
					char *strarray = f->readarray<char>(h.size);
					char *array2 = strarray;
					while(strlen(array2))
					{
						char *str = new char[strlen(array2)+1];
						memcpy(str,array2,strlen(array2)+1);
						array2 += strlen(array2);
						array2++;
						animationList.Add(str);
					}
					delete[] strarray;
					readSize += h.size;
				}
				break;
			case 'DATA':
				properties.Add('DATA');
				creatureType = f->read<ubyte>();
				readSize += 1;
				combatSkill = f->read<ubyte>();
				readSize += 1;
				magicSkill = f->read<ubyte>();
				readSize += 1;
				stealthSkill = f->read<ubyte>();
				readSize += 1;
				soul = f->read<ushort>();
				readSize += 2;
				health = f->read<ushort>();
				readSize += 2;
				pad = f->read<ushort>();
				readSize += 2;
				attackDamage = f->read<ushort>();
				readSize += 2;
				strength = f->read<ubyte>();
				readSize += 1;
				intellegence = f->read<ubyte>();
				readSize += 1;
				willpower = f->read<ubyte>();
				readSize += 1;
				agillity = f->read<ubyte>();
				readSize += 1;
				speed = f->read<ubyte>();
				readSize += 1;
				endurance = f->read<ubyte>();
				readSize += 1;
				personality = f->read<ubyte>();
				readSize += 1;
				luck = f->read<ubyte>();
				readSize += 1;
				break;
			case 'RNAM':
				properties.Add('RNAM');
				attackReach = f->read<ubyte>();
				readSize += 1;
				break;
			case 'ZNAM':
				properties.Add('ZNAM');
				combatStyle = f->read<formid>();
				readSize += 4;
				break;
			case 'TNAM':
				properties.Add('TNAM');
				turningSpeed = f->read<float>();
				readSize += 4;
				break;
			case 'BNAM':
				properties.Add('BNAM');
				baseScale = f->read<float>();
				readSize += 4;
				break;
			case 'WNAM':
				properties.Add('WNAM');
				footWeight = f->read<float>();
				readSize += 4;
				break;
			case 'NAM0':
				properties.Add('NAM0');
				bloodSpray = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM1':
				properties.Add('NAM1');
				bloodDecal = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'CSCR':
				properties.Add('CSCR');
				inheritsSoundsFrom = f->read<formid>();
				readSize += 4;
				break;
			case 'CSDT':
				{
					if (!properties.Count() || (properties[properties.Count() - 1] != 'CSDI' && properties[properties.Count() - 1] != 'CSDC' && properties[properties.Count() - 1] != 'CSDT'))
					{
						properties.Add('CSDT');
					}
					SoundType *t = new SoundType;
					t->type = f->read<ulong>();
					readSize += 4;
					sounds.Add(t);
				}
				break;
			case 'CSDI':
				{
					Sound s;
					s.sound = f->read<formid>();
					readSize += 4;
					sounds[sounds.Count() - 1]->sounds.Add(s);
				}
				break;
			case 'CSDC':
				sounds[sounds.Count() - 1]->sounds[sounds[sounds.Count() - 1]->sounds.Count() - 1].chance = f->read<ubyte>();
				readSize += 1;
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
		WriteZStringSubrecord('EDID',editorID,f);
		WriteZStringSubrecord('FULL',fullName,f);
		WriteZStringSubrecord('MODL',model,f);
		if (model)
		{
			WriteSubrecord('MODB',4,f);
			f->write<float>(boundRadius);
		}
		if (textureHashes)
		{
			WriteSubrecord('MODT',textureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(textureHashesCount,textureHashes);
		}
		for (int i = 0;i < properties.Count();i++)
		{
			switch (properties[i])
			{
			case 'CNTO':
				for (int i = 0;i < containerItems.Count();i++)
				{
					WriteSubrecord('CNTO',8,f);
					f->write<formid>(containerItems[i].item);
					f->write<ulong>(containerItems[i].count);
				}
				break;
			case 'SPLO':
				for (int i = 0;i < spellList.Count();i++)
				{
					WriteSubrecord('SPLO',4,f);
					f->write<formid>(spellList[i]);
				}
				break;
			case 'NIFZ':
				if (modelList.Count())
				{
					int mlsz = 1;
					for (int i = 0;i < modelList.Count();i++)
					{
						mlsz += strlen(modelList[i]);
						mlsz++;
					}
					char *mlbuf = new char[mlsz];
					memset(mlbuf,0,mlsz);
					char *mlbuf2 = mlbuf;
					for (int i = 0;i < modelList.Count();i++)
					{
						strcat(mlbuf2,modelList[i]);
						mlbuf2 += strlen(modelList[i]);
						mlbuf2++;
					}
					WriteSubrecord('NIFZ',mlsz,f);
					f->writearray<char>(mlsz,mlbuf);
					delete[] mlbuf;
				}
				break;
			case 'NIFT':
				if (niftextureHashesCount)
				{
					WriteSubrecord('NIFT',niftextureHashesCount,f);
					f->writearray<ubyte>(niftextureHashesCount,niftextureHashes);
				}
				break;
			case 'ACBS':
				WriteSubrecord('ACBS',16,f);
				f->write<ulong>(flags);
				f->write<ushort>(baseSpellPoints);
				f->write<ushort>(fatigue);
				f->write<ushort>(barterGold);
				f->write<short>(level);
				f->write<ushort>(calcMin);
				f->write<ushort>(calcMax);
				break;
			case 'SNAM':
				for (int i = 0;i < factions.Count();i++)
				{
					WriteSubrecord('SNAM',8,f);
					f->write<formid>(factions[i].faction);
					f->write<ulong>(factions[i].rank);
				}
				break;
			case 'INAM':
				if (deathItem)
				{
					WriteSubrecord('INAM',4,f);
					f->write<formid>(deathItem);
				}
				break;
			case 'SCRI':
				if (script)
				{
					WriteSubrecord('SCRI',4,f);
					f->write<formid>(script);
				}
				break;
			case 'AIDT':
				WriteSubrecord('AIDT',12,f);
				f->write<ubyte>(agression);
				f->write<ubyte>(confidence);
				f->write<ubyte>(energyLevel);
				f->write<ubyte>(responsibility);
				f->write<ulong>(aiFlags);
				f->write<ubyte>(trainSkill);
				f->write<ubyte>(trainLevel);
				f->write<ushort>(aiPad);
				break;
			case 'PKID':
				for (int i = 0;i < aiPackages.Count();i++)
				{
					WriteSubrecord('PKID',4,f);
					f->write<formid>(aiPackages[i]);
				}
				break;
			case 'KFFZ':
				if (animationList.Count())
				{
					int ansz = 1;
					for (int i = 0;i < animationList.Count();i++)
					{
						ansz += strlen(animationList[i]);
						ansz++;
					}
					char *anbuf = new char[ansz];
					memset(anbuf,0,ansz);
					char *anbuf2 = anbuf;
					for (int i = 0;i < animationList.Count();i++)
					{
						strcat(anbuf2,animationList[i]);
						anbuf2 += strlen(animationList[i]);
						anbuf2++;
					}
					WriteSubrecord('KFFZ',ansz,f);
					f->writearray<char>(ansz,anbuf);
					delete[] anbuf;
				}
				break;
			case 'DATA':
				WriteSubrecord('DATA',20,f);
				f->write<ubyte>(creatureType);
				f->write<ubyte>(combatSkill);
				f->write<ubyte>(magicSkill);
				f->write<ubyte>(stealthSkill);
				f->write<ushort>(soul);
				f->write<ushort>(health);
				f->write<ushort>(pad);
				f->write<ushort>(attackDamage);
				f->write<ubyte>(strength);
				f->write<ubyte>(intellegence);
				f->write<ubyte>(willpower);
				f->write<ubyte>(agillity);
				f->write<ubyte>(speed);
				f->write<ubyte>(endurance);
				f->write<ubyte>(personality);
				f->write<ubyte>(luck);
				break;
			case 'RNAM':
				WriteSubrecord('RNAM',1,f);
				f->write<ubyte>(attackReach);
				break;
			case 'ZNAM':
				if (combatStyle)
				{
					WriteSubrecord('ZNAM',4,f);
					f->write<formid>(combatStyle);
				}
				break;
			case 'TNAM':
				WriteSubrecord('TNAM',4,f);
				f->write<float>(turningSpeed);
				break;
			case 'BNAM':
				WriteSubrecord('BNAM',4,f);
				f->write<float>(baseScale);
				break;
			case 'WNAM':
				WriteSubrecord('WNAM',4,f);
				f->write<float>(footWeight);
				break;
			case 'CSCR':
				if (inheritsSoundsFrom)
				{
					WriteSubrecord('CSCR',4,f);
					f->write<formid>(inheritsSoundsFrom);
				}
				break;
			case 'NAM0':
				WriteZStringSubrecord('NAM0',bloodSpray,f);
				break;
			case 'NAM1':
				WriteZStringSubrecord('NAM1',bloodDecal,f);
				break;
			case 'CSDT':
				for (int i = 0;i < sounds.Count();i++)
				{
					WriteSubrecord('CSDT',4,f);
					f->write<ulong>(sounds[i]->type);
					for (int j = 0;j < sounds[i]->sounds.Count();j++)
					{
						WriteSubrecord('CSDI',4,f);
						f->write<formid>(sounds[i]->sounds[j].sound);
						WriteSubrecord('CSDC',1,f);
						f->write<ubyte>(sounds[i]->sounds[j].chance);
					}
				}
				break;
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(model);
		if (model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (textureHashes)
		{
			size += ComputeSubrecordSize(textureHashesCount * sizeof(TextureHash));
		}
		for (int i = 0;i < containerItems.Count();i++)
		{
			size += ComputeSubrecordSize(8);
		}
		for (int i = 0;i < spellList.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		if (modelList.Count())
		{
			int mlsz = 1;
			for (int i = 0;i < modelList.Count();i++)
			{
				mlsz += strlen(modelList[i]);
				mlsz++;
			}
			size += ComputeSubrecordSize(mlsz);
		}
		if (niftextureHashesCount)
		{
			size += ComputeSubrecordSize(niftextureHashesCount);
		}
		size += ComputeSubrecordSize(16);
		for (int i = 0;i < factions.Count();i++)
		{
			size += ComputeSubrecordSize(8);
		}
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(12);
		for (int i = 0;i < aiPackages.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		if (deathItem)
		{
			size += ComputeSubrecordSize(4);
		}
		if (animationList.Count())
		{
			int ansz = 1;
			for (int i = 0;i < animationList.Count();i++)
			{
				ansz += strlen(animationList[i]);
				ansz++;
			}
			size += ComputeSubrecordSize(ansz);
		}
		size += ComputeSubrecordSize(20);
		size += ComputeSubrecordSize(1);
		if (combatStyle)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ComputeSubrecordSize(4);
		size += ZStringSubrecordSize(bloodSpray);
		size += ZStringSubrecordSize(bloodDecal);
		if (inheritsSoundsFrom)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < sounds.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			for (int j = 0;j < sounds[i]->sounds.Count();j++)
			{
				size += ComputeSubrecordSize(4);
				size += ComputeSubrecordSize(1);
			}
		}
		return size;
	}
};
