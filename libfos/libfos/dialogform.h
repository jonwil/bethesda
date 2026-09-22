/*	libfos
	Copyright 2015 Jonathan Wilson

	This file is part of libfos
	libfos is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "form.h"
#pragma pack(push,1)
struct DialogData
{
	ubyte type;
	ubyte flags;
};
struct DialogDataOld
{
	ubyte type;
};
#pragma pack(pop)
struct DialogQuest
{
	formid quest;
	ulong type;
};
class DialogForm : public Form, public FullName
{
protected:
	DialogData data;
	DialogDataOld oldData;
	bool hasOldData;
	SimpleDynVecClass<DialogQuest> quests;
	float priority;
	bool hasPriority;
public:
	DialogForm(FormHeader h,ModFile *f) : Form(h,f), hasOldData(false), hasPriority(false)
	{
	}
protected:
	virtual void Load(FileRead *f)
	{
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			FormLoad();
			case 'QSTI':
			case 'QSTR':
				{
					DialogQuest q;
					q.quest = f->read<formid>();
					readSize += 4;
					q.type = h.type;
					quests.Add(q);
				}
				break;
			FullNameLoad();
			case 'PNAM':
				hasPriority = true;
				priority = f->read<float>();
				readSize += 4;
				break;
			case 'DATA':
				if (h.size == sizeof(DialogData))
				{
					data = f->read<DialogData>();
					readSize += sizeof(DialogData);
				}
				else
				{
					hasOldData = true;
					oldData = f->read<DialogDataOld>();
					readSize += sizeof(DialogDataOld);
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
		FormSave();
		for (int i = 0;i < quests.Count();i++)
		{
			WriteSubrecord(quests[i].type,4,f);
			f->write<formid>(quests[i].quest);
		}
		FullNameSave();
		if (hasPriority)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<float>(priority);
		}
		if (hasOldData)
		{
			WriteSubrecord('DATA',sizeof(DialogDataOld),f);
			f->write<DialogDataOld>(oldData);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(DialogData),f);
			f->write<DialogData>(data);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		for (int i = 0;i < quests.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		FullNameGetSaveSize();
		if (hasPriority)
		{
			size += ComputeSubrecordSize(4);
		}
		if (hasOldData)
		{
			size += ComputeSubrecordSize(sizeof(DialogDataOld));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(DialogData));
		}
		return size;
	}
};
