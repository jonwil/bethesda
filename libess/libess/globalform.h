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
class GlobalForm : public Form
{
protected:
	char *editorID;
	ubyte type;
	float value;
public:
	GlobalForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), type(0), value(0)
	{
	}
	virtual ~GlobalForm()
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
			case 'FNAM':
				type = f->read<ubyte>();
				readSize += 1;
				break;
			case 'FLTV':
				value = f->read<float>();
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
		WriteSubrecord('FNAM',1,f);
		f->write<ubyte>(type);
		WriteSubrecord('FLTV',4,f);
		f->write<float>(value);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(4);
		return size;
	}
};