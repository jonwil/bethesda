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
class ActorBaseChangeRecord : public ChangeRecord
{
protected:
	ubyte *attributes;
	ulong flags;
	ushort baseMagicka;
	ushort baseFatigue;
	ushort barterGold;
	short level;
	ushort levelCalcMin;
	ushort levelCalcMax;
	ushort factionCount;
	NPCFaction *factions;
	ushort spellCount;
	iref *spells;
	ubyte aidata1;
	ubyte aidata2;
	ubyte aidata3;
	ubyte aidata4;
	ulong baseHealth;
	ushort modifierCount;
	Modifier *modifiers;
	char *fullName;
public:
	ActorBaseChangeRecord(ChangeRecordHeader h,ESSFile *p) : ChangeRecord(h,p), attributes(0), flags(0), baseMagicka(0), baseFatigue(0), barterGold(0),
		level(0), levelCalcMin(0), levelCalcMax(0), factionCount(0), factions(0), spellCount(0), spells(0), aidata1(0), aidata2(0), aidata3(0),
		aidata4(0), baseHealth(0), modifierCount(0), modifiers(0), fullName(0)
	{
	}
	virtual ~ActorBaseChangeRecord()
	{
		if (attributes)
		{
			delete[] attributes;
		}
		if (factions)
		{
			delete[] factions;
		}
		if (spells)
		{
			delete[] spells;
		}
		if (modifiers)
		{
			delete[] modifiers;
		}
		if (fullName)
		{
			delete[] fullName;
		}
	}
	virtual void Load(FileRead *f)
	{
		ChangeRecord::Load(f);
		if (header.flags & BaseAttributes)
		{
			attributes = f->readarray<ubyte>(8);
		}
		if (header.flags & BaseData)
		{
			flags = f->read<ulong>();
			baseMagicka = f->read<ushort>();
			baseFatigue = f->read<ushort>();
			barterGold = f->read<ushort>();
			level = f->read<short>();
			levelCalcMin = f->read<ushort>();
			levelCalcMax = f->read<ushort>();
		}
		if (header.flags & ActorFactions)
		{
			factionCount = f->read<ushort>();
			factions = new NPCFaction[factionCount];
			for (ushort i = 0;i < factionCount;i++)
			{
				factions[i].faction = parent->GetFormID(f->read<iref>());
				factions[i].rank = f->read<ubyte>();
			}
		}
		if (header.flags & SpellList)
		{
			spellCount = f->read<ushort>();
			spells = new formid[spellCount];
			for (ushort i = 0;i < spellCount;i++)
			{
				spells[i] = parent->GetFormID(f->read<iref>());
			}
		}
		if (header.flags & AIData)
		{
			aidata1 = f->read<ubyte>();
			aidata2 = f->read<ubyte>();
			aidata3 = f->read<ubyte>();
			aidata4 = f->read<ubyte>();
		}
		if (header.flags & BaseHealth)
		{
			baseHealth = f->read<ulong>();
		}
		if (header.flags & BaseModifiers)
		{
			modifierCount = f->read<ushort>();
			modifiers = new Modifier[modifierCount];
			for (ushort i = 0;i < modifierCount;i++)
			{
				modifiers[i].valueIndex = f->read<ubyte>();
				modifiers[i].modValue = f->read<float>();
			}
		}
		if (header.flags & ActorName)
		{
			fullName = f->readbstring();
		}
	}
	virtual void Save(FileWrite *f)
	{
		ChangeRecord::Save(f);
		if (header.flags & BaseAttributes)
		{
			f->writearray<ubyte>(8,attributes);
		}
		if (header.flags & BaseData)
		{
			f->write<ulong>(flags);
			f->write<ushort>(baseMagicka);
			f->write<ushort>(baseFatigue);
			f->write<ushort>(barterGold);
			f->write<short>(level);
			f->write<ushort>(levelCalcMin);
			f->write<ushort>(levelCalcMax);
		}
		if (header.flags & ActorFactions)
		{
			f->write<ushort>(factionCount);
			for (ushort i = 0;i < factionCount;i++)
			{
				f->write<iref>(parent->GetFormiRef(factions[i].faction));
				f->write<ubyte>(factions[i].rank);
			}
		}
		if (header.flags & SpellList)
		{
			f->write<ushort>(spellCount);
			for (ushort i = 0;i < spellCount;i++)
			{
				f->write<iref>(parent->GetFormiRef(spells[i]));
			}
		}
		if (header.flags & AIData)
		{
			f->write<ubyte>(aidata1);
			f->write<ubyte>(aidata2);
			f->write<ubyte>(aidata3);
			f->write<ubyte>(aidata4);
		}
		if (header.flags & BaseHealth)
		{
			f->write<ulong>(baseHealth);
		}
		if (header.flags & BaseModifiers)
		{
			f->write<ushort>(modifierCount);
			for (ushort i = 0;i < modifierCount;i++)
			{
				f->write<ubyte>(modifiers[i].valueIndex);
				f->write<float>(modifiers[i].modValue);
			}
		}
		if (header.flags & ActorName)
		{
			f->writebstring(fullName);
		}
	}
};
