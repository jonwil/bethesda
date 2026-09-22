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
struct LeveledItem
{
	ulong level;
	formid item;
	ulong count;
	bool smallRecord;
	LeveledItem() : level(0), item(0), count(0), smallRecord(false)
	{
	}
};
class LeveledItemForm : public Form
{
protected:
	char *editorID;
	ubyte chanceNone;
	ubyte flags;
	bool hasLVLF;
	SimpleDynVecClass<LeveledItem> leveledItems;
	ubyte data;
	bool hasData;
public:
	LeveledItemForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), chanceNone(0), flags(0), hasLVLF(false), leveledItems(0), data(0), hasData(0)
	{
	}
	virtual ~LeveledItemForm()
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
					LeveledItem l;
					l.level = f->read<ulong>();
					readSize += 4;
					l.item = f->read<ulong>();
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
					leveledItems.Add(l);
				}
				break;
			case 'DATA':
				hasData = true;
				data = f->read<ubyte>();
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
		WriteSubrecord('LVLD',1,f);
		f->write<ubyte>(chanceNone);
		if (hasLVLF)
		{
			WriteSubrecord('LVLF',1,f);
			f->write<ubyte>(flags);
		}
		for (int i = 0;i < leveledItems.Count();i++)
		{
			if (leveledItems[i].smallRecord)
			{
				WriteSubrecord('LVLO',8,f);
				f->write<ulong>(leveledItems[i].level);
				f->write<ulong>(leveledItems[i].item);
			}
			else
			{
				WriteSubrecord('LVLO',12,f);
				f->write<ulong>(leveledItems[i].level);
				f->write<ulong>(leveledItems[i].item);
				f->write<ulong>(leveledItems[i].count);
			}
		}
		if (hasData)
		{
			WriteSubrecord('DATA',1,f);
			f->write<ubyte>(data);
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
		for (int i = 0;i < leveledItems.Count();i++)
		{
			if (leveledItems[i].smallRecord)
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
		return size;
	}
};
