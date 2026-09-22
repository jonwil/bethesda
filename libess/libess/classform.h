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
struct ClassAttributes
{
	long primary[2];
	ulong specalization;
	long major[7];
	ulong flags;
	ulong services;
	byte trainSkill;
	ubyte trainLevel;
	ushort pad;
};
struct ClassAttributes2
{
	long primary[2];
	ulong specalization;
	long major[7];
	ulong flags;
	ulong services;
};
class ClassForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *description;
	char *icon;
	ClassAttributes attributes;
	ClassAttributes2 attributes2;
	bool smallattributes;
public:
	ClassForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), description(0), icon(0), smallattributes(false)
	{
	}
	virtual ~ClassForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (description)
		{
			delete[] description;
		}
		if (icon)
		{
			delete[] icon;
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
			case 'DESC':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				if (h.size == 0x34)
				{
					attributes = f->read<ClassAttributes>();
					readSize += sizeof(ClassAttributes);
				}
				else
				{
					smallattributes = true;
					attributes2 = f->read<ClassAttributes2>();
					readSize += sizeof(ClassAttributes2);
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
		WriteZStringSubrecord('FULL',fullName,f);
		WriteZStringSubrecord('DESC',description,f);
		WriteZStringSubrecord('ICON',icon,f);
		if (!smallattributes)
		{
			WriteSubrecord('DATA',sizeof(ClassAttributes),f);
			f->write<ClassAttributes>(attributes);
		}
		else
		{
			WriteSubrecord('DATA',sizeof(ClassAttributes2),f);
			f->write<ClassAttributes2>(attributes2);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(description);
		size += ZStringSubrecordSize(icon);
		if (!smallattributes)
		{
			size += ComputeSubrecordSize(sizeof(ClassAttributes));
		}
		else
		{
			size += ComputeSubrecordSize(sizeof(ClassAttributes2));
		}
		return size;
	}
};
