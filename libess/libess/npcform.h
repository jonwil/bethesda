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
class NPCForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	ulong flags;
	ushort baseSpellPoints;
	ushort fatigue;
	ushort barterGold;
	short level;
	ushort calcMin;
	ushort calcMax;
	SimpleDynVecClass<FactionRef> factions;
	formid deathItem;
	formid race;
	SimpleDynVecClass<formid> spellList;
	formid script;
	SimpleDynVecClass<ContainerItem> containerItems;
	ubyte agression;
	ubyte confidence;
	ubyte energyLevel;
	ubyte responsibility;
	ulong aiFlags;
	ubyte trainSkill;
	ubyte trainLevel;
	ushort aiPad;
	SimpleDynVecClass<formid> aiPackages;
	SimpleDynVecClass<char *> animationList;
	formid classType;
	ubyte skills[21];
	ulong health;
	ubyte attributes[8];
	formid hair;
	float hairLength;
	formid eyes;
	Color hairColor;
	formid combatStyle;
	ulong fggsSize;
	byte *fggs;
	ulong fggaSize;
	byte *fgga;
	ulong fgtsSize;
	byte *fgts;
	ushort faceRace;
	SimpleDynVecClass<ulong> properties;
	bool fnamseen;
	bool lnamseen;
public:
	NPCForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), flags(0), baseSpellPoints(0), fatigue(0), barterGold(0), level(0), calcMin(0), calcMax(0), factions(0), deathItem(0), race(0), spellList(0), script(0), containerItems(0), agression(0), confidence(0), energyLevel(0), responsibility(0), aiFlags(0), trainSkill(0), trainLevel(0), aiPad(0), aiPackages(0), animationList(0), classType(0), health(0), hair(0), hairLength(0), eyes(0), combatStyle(0), fggsSize(0), fggs(0), fggaSize(0), fgga(0), fgtsSize(0), fgts(0), faceRace(0), fnamseen(false), lnamseen(false), properties(0)
	{
	}
	virtual ~NPCForm()
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
		for (int i = 0;i < animationList.Count();i++)
		{
			delete[] animationList[i];
		}
		if (fggs)
		{
			delete[] fggs;
		}
		if (fgga)
		{
			delete[] fgga;
		}
		if (fgts)
		{
			delete[] fgts;
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
			case 'INAM':
				properties.Add('INAM');
				deathItem = f->read<formid>();
				readSize += 4;
				break;
			case 'RNAM':
				properties.Add('RNAM');
				race = f->read<formid>();
				readSize += 4;
				break;
			case 'SPLO':
				if (!properties.Count() || properties[properties.Count() - 1] != 'SPLO')
				{
					properties.Add('SPLO');
				}
				spellList.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'SCRI':
				properties.Add('SCRI');
				script = f->read<formid>();
				readSize += 4;
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
			case 'CNAM':
				properties.Add('CNAM');
				classType = f->read<formid>();
				readSize += 4;
				break;
			case 'DATA':
				properties.Add('DATA');
				for (int i = 0;i < 21;i++)
				{
					skills[i] = f->read<ubyte>();
					readSize += 1;
				}
				health = f->read<ulong>();
				readSize += 4;
				for (int i = 0;i < 8;i++)
				{
					attributes[i] = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'HNAM':
				properties.Add('HNAM');
				hair = f->read<formid>();
				readSize += 4;
				break;
			case 'LNAM':
				lnamseen = true;
				properties.Add('LNAM');
				hairLength = f->read<float>();
				readSize += 4;
				break;
			case 'ENAM':
				properties.Add('ENAM');
				eyes = f->read<formid>();
				readSize += 4;
				break;
			case 'HCLR':
				properties.Add('HCLR');
				hairColor = f->read<Color>();
				readSize += 4;
				break;
			case 'ZNAM':
				properties.Add('ZNAM');
				combatStyle = f->read<formid>();
				readSize += 4;
				break;
			case 'FGGS':
				properties.Add('FGGS');
				fggsSize = h.size;
				fggs = f->readarray<byte>(fggsSize);
				readSize += h.size;
				break;
			case 'FGGA':
				properties.Add('FGGA');
				fggaSize = h.size;
				fgga = f->readarray<byte>(fggaSize);
				readSize += h.size;
				break;
			case 'FGTS':
				properties.Add('FGTS');
				fgtsSize = h.size;
				fgts = f->readarray<byte>(fgtsSize);
				readSize += h.size;
				break;
			case 'FNAM':
				fnamseen = true;
				properties.Add('FNAM');
				faceRace = f->read<ushort>();
				readSize += 2;
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
			switch(properties[i])
			{
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
			case 'RNAM':
				if (race)
				{
					WriteSubrecord('RNAM',4,f);
					f->write<formid>(race);
				}
				break;
			case 'SPLO':
				for (int i = 0;i < spellList.Count();i++)
				{
					WriteSubrecord('SPLO',4,f);
					f->write<formid>(spellList[i]);
				}
				break;
			case 'CNTO':
				for (int i = 0;i < containerItems.Count();i++)
				{
					WriteSubrecord('CNTO',8,f);
					f->write<formid>(containerItems[i].item);
					f->write<ulong>(containerItems[i].count);
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
			case 'CNAM':
				if (classType)
				{
					WriteSubrecord('CNAM',4,f);
					f->write<formid>(classType);
				}
				break;
			case 'DATA':
				WriteSubrecord('DATA',33,f);
				for (int i = 0;i < 21;i++)
				{
					f->write<ubyte>(skills[i]);
				}
				f->write<ulong>(health);
				for (int i = 0;i < 8;i++)
				{
					f->write<ubyte>(attributes[i]);
				}
				break;
			case 'HNAM':
				if (hair)
				{
					WriteSubrecord('HNAM',4,f);
					f->write<formid>(hair);
				}
				break;
			case 'LNAM':
				WriteSubrecord('LNAM',4,f);
				f->write<float>(hairLength);
				break;
			case 'ENAM':
				if (eyes)
				{
					WriteSubrecord('ENAM',4,f);
					f->write<formid>(eyes);
				}
				break;
			case 'HCLR':
				WriteSubrecord('HCLR',4,f);
				f->write<Color>(hairColor);
				break;
			case 'ZNAM':
				if (combatStyle)
				{
					WriteSubrecord('ZNAM',4,f);
					f->write<formid>(combatStyle);
				}
				break;
			case 'FGGS':
				if (fggsSize)
				{
					WriteSubrecord('FGGS',fggsSize,f);
					f->writearray<byte>(fggsSize,fggs);
				}
				break;
			case 'FGGA':
				if (fggaSize)
				{
					WriteSubrecord('FGGA',fggaSize,f);
					f->writearray<byte>(fggaSize,fgga);
				}
				break;
			case 'FGTS':
				if (fgtsSize)
				{
					WriteSubrecord('FGTS',fgtsSize,f);
					f->writearray<byte>(fgtsSize,fgts);
				}
				break;
			case 'FNAM':
				WriteSubrecord('FNAM',2,f);
				f->write<ushort>(faceRace);
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
		size += ComputeSubrecordSize(16);
		for (int i = 0;i < factions.Count();i++)
		{
			size += ComputeSubrecordSize(8);
		}
		if (deathItem)
		{
			size += ComputeSubrecordSize(4);
		}
		if (race)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < spellList.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < containerItems.Count();i++)
		{
			size += ComputeSubrecordSize(8);
		}
		size += ComputeSubrecordSize(12);
		for (int i = 0;i < aiPackages.Count();i++)
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
		if (classType)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(33);
		if (hair)
		{
			size += ComputeSubrecordSize(4);
		}
		if (lnamseen)
		{
			size += ComputeSubrecordSize(4);
		}
		if (eyes)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		if (combatStyle)
		{
			size += ComputeSubrecordSize(4);
		}
		if (fggsSize)
		{
			size += ComputeSubrecordSize(fggsSize);
		}
		if (fggaSize)
		{
			size += ComputeSubrecordSize(fggaSize);
		}
		if (fgtsSize)
		{
			size += ComputeSubrecordSize(fgtsSize);
		}
		if (fnamseen)
		{
			size += ComputeSubrecordSize(2);
		}
		return size;
	}
};
