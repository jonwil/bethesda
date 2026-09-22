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
struct LoadScreenLocation
{
	formid direct;
	formid indirect;
	short x;
	short y;
};
class LoadScreenForm : public Form
{
protected:
	char *editorID;
	char *icon;
	char *description;
	SimpleDynVecClass<LoadScreenLocation> locations;
public:
	LoadScreenForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), icon(0), description(0), locations(0)
	{
	}
	virtual ~LoadScreenForm()
	{
		if (editorID)
		{
			delete[] editorID;
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
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DESC':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'LNAM':
				locations.Add(f->read<LoadScreenLocation>());
				readSize += sizeof(LoadScreenLocation);
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
		WriteZStringSubrecord('ICON',icon,f);
		WriteZStringSubrecord('DESC',description,f);
		for (int i = 0;i < locations.Count();i++)
		{
			WriteSubrecord('LNAM',sizeof(LoadScreenLocation),f);
			f->write<LoadScreenLocation>(locations[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(icon);
		size += ZStringSubrecordSize(description);
		for (int i = 0;i < locations.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(LoadScreenLocation));
		}
		return size;
	}
};
