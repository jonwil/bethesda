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
class SpellForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *fullNameOverride;
	ulong spellType;
	ulong spellCost;
	ulong spellLevel;
	ulong flags;
	SimpleDynVecClass<EffectItem> effectItems;
	bool hasOBMEData;
	ubyte obmeVersion;
	ubyte beta;
	ubyte minor;
	ubyte major;
	ubyte obmeReserved[0x1C];
	bool hasEFXX;
	bool hasDATXData;
	ubyte datxReserved[0x20];
public:
	SimpleDynVecClass<EffectItem> &GetEffectItems()
	{
		return effectItems;
	}
	SpellForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), fullNameOverride(0), spellType(0), spellCost(0), spellLevel(0), flags(0), effectItems(0), hasOBMEData(false), obmeVersion(0), beta(0), minor(0), major(0), hasEFXX(false), hasDATXData(false)
	{
	}
	virtual ~SpellForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (fullNameOverride)
		{
			delete[] fullNameOverride;
		}
		for (int i = 0;i < effectItems.Count();i++)
		{
			if (effectItems[i].scriptName)
			{
				delete[] effectItems[i].scriptName;
			}
			if (effectItems[i].icon)
			{
				delete[] effectItems[i].icon;
			}
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		bool OBME = false;
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			case 'EDID':
				editorID = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'OBME':
				hasOBMEData = true;
				obmeVersion = f->read<ubyte>();
				readSize += 1;
				beta = f->read<ubyte>();
				readSize += 1;
				minor = f->read<ubyte>();
				readSize += 1;
				major = f->read<ubyte>();
				readSize += 1;
				for (int i = 0;i < 0x1C;i++)
				{
					obmeReserved[i] = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'FULL':
				if (!effectItems.Count())
				{
					fullName = f->readzstring(h.size);
				}
				else
				{
					if (!hasEFXX)
					{
						effectItems[effectItems.Count() - 1].scriptName = f->readzstring(h.size);
					}
					else
					{
						fullNameOverride = f->readzstring(h.size);
					}
				}
				readSize += h.size;
				break;
			case 'SPIT':
				spellType = f->read<ulong>();
				readSize += 4;
				spellCost = f->read<ulong>();
				readSize += 4;
				spellLevel = f->read<ulong>();
				readSize += 4;
				flags = f->read<ulong>();
				readSize += 4;
				break;
			case 'EFME':
				{
					OBME = true;
					EffectItem i;
					i.hasEFMEData = true;
					i.version = f->read<ubyte>();
					readSize += 1;
					i.beta = f->read<ubyte>();
					readSize += 1;
					i.minor = f->read<ubyte>();
					readSize += 1;
					i.major = f->read<ubyte>();
					readSize += 1;
					i.efitParam = f->read<ubyte>();
					readSize += 1;
					i.efixParam = f->read<ubyte>();
					readSize += 1;
					for (int x = 0;x < 0xA;x++)
					{
						i.efmeReserved[x] = f->read<ubyte>();
						readSize += 1;
					}
					effectItems.Add(i);
				}
				break;
			case 'EFID':
				{
					if (!OBME)
					{
						EffectItem i;
						i.effectID = f->read<ulong>();
						readSize += 4;
						effectItems.Add(i);
					}
					else
					{
						effectItems[effectItems.Count() - 1].effectID = f->read<ulong>();
						readSize += 4;
					}
					OBME = false;
				}
				break;
			case 'EFIT':
				effectItems[effectItems.Count() - 1].effectID2 = f->read<ulong>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].magnitude = f->read<ulong>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].area = f->read<ulong>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].duration = f->read<ulong>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].type = f->read<ulong>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].actorValueIndex = f->read<ulong>();
				readSize += 4;
				break;
			case 'SCIT':
				effectItems[effectItems.Count() - 1].scriptSize = h.size;
				effectItems[effectItems.Count() - 1].scriptEffect = f->read<formid>();
				readSize += 4;
				if (h.size >= 8)
				{
					effectItems[effectItems.Count() - 1].scriptMagicSchool = f->read<ulong>();
					readSize += 4;
					if (h.size >= 0xC)
					{
						effectItems[effectItems.Count() - 1].scriptVisualEffect = f->read<ulong>();
						readSize += 4;
						if (h.size >= 0x10)
						{
							effectItems[effectItems.Count() - 1].scriptFlags = f->read<ulong>();
							readSize += 4;
						}
					}
				}
				break;
			case 'EFII':
				effectItems[effectItems.Count() - 1].icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'EFIX':
				effectItems[effectItems.Count() - 1].hasEFIXData = true;
				effectItems[effectItems.Count() - 1].efixOverrides = f->read<ulong>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].efixFlags = f->read<ulong>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].efixBaseCost = f->read<float>();
				readSize += 4;
				effectItems[effectItems.Count() - 1].efixResistAV = f->read<ulong>();
				readSize += 4;
				for (int x = 0;x < 0x10;x++)
				{
					effectItems[effectItems.Count() - 1].efixReserved[x] = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'EFXX':
				hasEFXX = true;
				break;
			case 'DATX':
				hasDATXData = true;
				for (int i = 0;i < 0x20;i++)
				{
					obmeReserved[i] = f->read<ubyte>();
					readSize += 1;
				}
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
		if (hasOBMEData)
		{
			WriteSubrecord('OBME',0x20,f);
			f->write<ubyte>(obmeVersion);
			f->write<ubyte>(beta);
			f->write<ubyte>(minor);
			f->write<ubyte>(major);
			for (int i = 0;i < 0x1C;i++)
			{
				f->write<ubyte>(obmeReserved[i]);
			}
		}
		WriteZStringSubrecord('FULL',fullName,f);
		WriteSubrecord('SPIT',16,f);
		f->write<ulong>(spellType);
		f->write<ulong>(spellCost);
		f->write<ulong>(spellLevel);
		f->write<ulong>(flags);
		for (int i = 0;i < effectItems.Count();i++)
		{
			if (effectItems[i].hasEFMEData)
			{
				WriteSubrecord('EFME',0x10,f);
				f->write<ubyte>(effectItems[i].version);
				f->write<ubyte>(effectItems[i].beta);
				f->write<ubyte>(effectItems[i].minor);
				f->write<ubyte>(effectItems[i].major);
				f->write<ubyte>(effectItems[i].efitParam);
				f->write<ubyte>(effectItems[i].efixParam);
				for (int x = 0;x < 0xA;x++)
				{
					f->write<ubyte>(effectItems[i].efmeReserved[x]);
				}
			}
			WriteSubrecord('EFID',4,f);
			f->write<ulong>(effectItems[i].effectID);
			WriteSubrecord('EFIT',24,f);
			f->write<ulong>(effectItems[i].effectID2);
			f->write<ulong>(effectItems[i].magnitude);
			f->write<ulong>(effectItems[i].area);
			f->write<ulong>(effectItems[i].duration);
			f->write<ulong>(effectItems[i].type);
			f->write<ulong>(effectItems[i].actorValueIndex);
			if (effectItems[i].scriptSize)
			{
				WriteSubrecord('SCIT',effectItems[i].scriptSize,f);
				f->write<formid>(effectItems[i].scriptEffect);
				if (effectItems[i].scriptSize >= 8)
				{
					f->write<ulong>(effectItems[i].scriptMagicSchool);
					readSize += 4;
					if (effectItems[i].scriptSize >= 0xC)
					{
						f->write<ulong>(effectItems[i].scriptVisualEffect);
						readSize += 4;
						if (effectItems[i].scriptSize >= 0x10)
						{
							f->write<ulong>(effectItems[i].scriptFlags);
							readSize += 4;
						}
					}
				}
			}
			WriteZStringSubrecord('FULL',effectItems[i].scriptName,f);
			WriteZStringSubrecord('EFII',effectItems[i].icon,f);
			if (effectItems[i].hasEFIXData)
			{
				WriteSubrecord('EFIX',0x20,f);
				f->write<ulong>(effectItems[i].efixOverrides);
				f->write<ulong>(effectItems[i].efixFlags);
				f->write<float>(effectItems[i].efixBaseCost);
				f->write<ulong>(effectItems[i].efixResistAV);
				for (int x = 0;x < 0x10;x++)
				{
					f->write<ubyte>(effectItems[i].efixReserved[x]);
				}
			}
		}
		if (hasEFXX)
		{
			WriteSubrecord('EFXX',0,f);
		}
		if (hasDATXData)
		{
			WriteSubrecord('DATX',0x20,f);
			for (int i = 0;i < 0x20;i++)
			{
				f->write<ubyte>(obmeReserved[i]);
			}
		}
		WriteZStringSubrecord('FULL',fullNameOverride,f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		if (hasOBMEData)
		{
			size += ComputeSubrecordSize(0x20);
		}
		size += ZStringSubrecordSize(fullName);
		size += ComputeSubrecordSize(16);
		for (int i = 0;i < effectItems.Count();i++)
		{
			if (effectItems[i].hasEFMEData)
			{
				size += ComputeSubrecordSize(0x10);
			}
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(24);
			if (effectItems[i].scriptSize)
			{
				size += ComputeSubrecordSize(effectItems[i].scriptSize);
			}
			size += ZStringSubrecordSize(effectItems[i].scriptName);
			size += ZStringSubrecordSize(effectItems[i].icon);
			if (effectItems[i].hasEFIXData)
			{
				size += ComputeSubrecordSize(0x20);
			}
		}
		if (hasEFXX)
		{
			size += ComputeSubrecordSize(0);
		}
		if (hasDATXData)
		{
			size += ComputeSubrecordSize(0x20);
		}
		size += ZStringSubrecordSize(fullNameOverride);
		return size;
	}
};
