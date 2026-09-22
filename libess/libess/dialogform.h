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
class DialogForm : public Form
{
protected:
	char *editorID;
	SimpleDynVecClass<formid> addedQuests;
	SimpleDynVecClass<formid> removedQuests;
	char *fullName;
	ubyte dialType;
public:
	DialogForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), addedQuests(0), removedQuests(0), dialType(0)
	{
	}
	virtual ~DialogForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
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
			case 'QSTI':
				addedQuests.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'QSTR':
				removedQuests.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'FULL':
				fullName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				dialType = f->read<ubyte>();
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
		for (int i = 0;i < addedQuests.Count();i++)
		{
			WriteSubrecord('QSTI',4,f);
			f->write<formid>(addedQuests[i]);
		}
		for (int i = 0;i < removedQuests.Count();i++)
		{
			WriteSubrecord('QSTR',4,f);
			f->write<formid>(removedQuests[i]);
		}
		WriteZStringSubrecord('FULL',fullName,f);
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(dialType);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		for (int i = 0;i < addedQuests.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < removedQuests.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(1);
		return size;
	}
};
