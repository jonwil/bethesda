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
class SubSpaceForm : public Form
{
protected:
	char *editorID;
	NiPoint3 dimentions;
public:
	SubSpaceForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0)
	{
	}
	virtual ~SubSpaceForm()
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
			case 'DNAM':
				dimentions = f->read<NiPoint3>();
				readSize += 12;
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
		WriteSubrecord('DNAM',12,f);
		f->write<NiPoint3>(dimentions);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ComputeSubrecordSize(12);
		return size;
	}
};
