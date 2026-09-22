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
class BirthSignForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *icon;
	char *description;
	SimpleDynVecClass<formid> spells;
public:
	BirthSignForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), icon(0), description(0), spells(0)
	{
	}
	virtual ~BirthSignForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (icon)
		{
			delete[] icon;
		}
		if (description)
		{
			delete[] description;
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
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DESC':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SPLO':
				spells.Add(f->read<formid>());
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
		WriteZStringSubrecord('FULL',fullName,f);
		WriteZStringSubrecord('ICON',icon,f);
		WriteZStringSubrecord('DESC',description,f);
		for (int i = 0;i < spells.Count();i++)
		{
			WriteSubrecord('SPLO',4,f);
			f->write<formid>(spells[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(icon);
		size += ZStringSubrecordSize(description);
		for (int i = 0;i < spells.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
