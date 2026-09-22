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
struct LeveledSpell
{
	ulong level;
	formid spell;
	ulong count;
	bool smallRecord;
	LeveledSpell() : level(0), spell(0), count(0), smallRecord(false)
	{
	}
};
class LeveledSpellForm : public Form
{
protected:
	char *editorID;
	ubyte chanceNone;
	ubyte flags;
	bool hasLVLF;
	SimpleDynVecClass<LeveledSpell> leveledSpells;
public:
	LeveledSpellForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), chanceNone(0), flags(0), hasLVLF(false), leveledSpells(0)
	{
	}
	virtual ~LeveledSpellForm()
	{
		if (editorID)
		{
			delete[] editorID;
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
			case 'LVLD':
				chanceNone = f->read<ubyte>();
				readSize += 1;
				break;
			case 'LVLF':
				hasLVLF = true;
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'LVLO':
				{
					LeveledSpell l;
					l.level = f->read<ulong>();
					readSize += 4;
					l.spell = f->read<ulong>();
					readSize += 4;
					if (h.size == 8)
					{
						l.smallRecord = true;
					}
					else
					{
						l.count = f->read<ulong>();
						readSize += 4;
					}
					leveledSpells.Add(l);
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
		WriteSubrecord('LVLD',1,f);
		f->write<ubyte>(chanceNone);
		if (hasLVLF)
		{
			WriteSubrecord('LVLF',1,f);
			f->write<ubyte>(flags);
		}
		for (int i = 0;i < leveledSpells.Count();i++)
		{
			if (leveledSpells[i].smallRecord)
			{
				WriteSubrecord('LVLO',8,f);
				f->write<ulong>(leveledSpells[i].level);
				f->write<ulong>(leveledSpells[i].spell);
			}
			else
			{
				WriteSubrecord('LVLO',12,f);
				f->write<ulong>(leveledSpells[i].level);
				f->write<ulong>(leveledSpells[i].spell);
				f->write<ulong>(leveledSpells[i].count);
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ComputeSubrecordSize(1);
		if (hasLVLF)
		{
			size += ComputeSubrecordSize(1);
		}
		for (int i = 0;i < leveledSpells.Count();i++)
		{
			if (leveledSpells[i].smallRecord)
			{
				size += ComputeSubrecordSize(8);
			}
			else
			{
				size += ComputeSubrecordSize(12);
			}
		}
		return size;
	}
};
