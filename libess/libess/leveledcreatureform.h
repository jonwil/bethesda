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
struct LeveledCreature
{
	ulong level;
	formid creature;
	ulong count;
	bool smallRecord;
	LeveledCreature() : level(0), creature(0), count(0), smallRecord(false)
	{
	}
};
class LeveledCreatureForm : public Form
{
protected:
	char *editorID;
	ubyte chanceNone;
	ubyte flags;
	bool hasLVLF;
	SimpleDynVecClass<LeveledCreature> leveledCreatures;
	ubyte data;
	bool hasData;
	formid script;
	formid templateCreature;
public:
	LeveledCreatureForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), chanceNone(0), flags(0), hasLVLF(false), leveledCreatures(0), data(0), hasData(0), script(0), templateCreature(0)
	{
	}
	virtual ~LeveledCreatureForm()
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
					LeveledCreature l;
					l.level = f->read<ulong>();
					readSize += 4;
					l.creature = f->read<ulong>();
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
					leveledCreatures.Add(l);
				}
				break;
			case 'DATA':
				hasData = true;
				data = f->read<ubyte>();
				readSize += 1;
				break;
			case 'SCRI':
				script = f->read<formid>();
				readSize += 4;
				break;
			case 'TNAM':
				templateCreature = f->read<formid>();
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
		WriteZStringSubrecord('EDID',editorID,f);
		WriteSubrecord('LVLD',1,f);
		f->write<ubyte>(chanceNone);
		if (hasLVLF)
		{
			WriteSubrecord('LVLF',1,f);
			f->write<ubyte>(flags);
		}
		for (int i = 0;i < leveledCreatures.Count();i++)
		{
			if (leveledCreatures[i].smallRecord)
			{
				WriteSubrecord('LVLO',8,f);
				f->write<ulong>(leveledCreatures[i].level);
				f->write<ulong>(leveledCreatures[i].creature);
			}
			else
			{
				WriteSubrecord('LVLO',12,f);
				f->write<ulong>(leveledCreatures[i].level);
				f->write<ulong>(leveledCreatures[i].creature);
				f->write<ulong>(leveledCreatures[i].count);
			}
		}
		if (hasData)
		{
			WriteSubrecord('DATA',1,f);
			f->write<ubyte>(data);
		}
		if (script)
		{
			WriteSubrecord('SCRI',4,f);
			f->write<formid>(script);
		}
		if (templateCreature)
		{
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(templateCreature);
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
		for (int i = 0;i < leveledCreatures.Count();i++)
		{
			if (leveledCreatures[i].smallRecord)
			{
				size += ComputeSubrecordSize(8);
			}
			else
			{
				size += ComputeSubrecordSize(12);
			}
		}
		if (hasData)
		{
			size += ComputeSubrecordSize(1);
		}
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		if (templateCreature)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
