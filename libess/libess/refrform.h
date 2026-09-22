/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "extradataform.h"
class RefrForm : public ExtraDataForm
{
protected:
	char *editorID;
	formid parentObject;
	bool openByDefault;
	bool dataPresent;
	NiPoint3 position;
	NiPoint3 rotation;
public:
	RefrForm(FormHeader h,ModFile *f) : ExtraDataForm(h,f), editorID(0), parentObject(0), openByDefault(false), dataPresent(false)
	{
	}
	virtual ~RefrForm()
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
			case 'NAME':
				parentObject = f->read<formid>();
				readSize += 4;
				break;
			case 'ONAM':
				openByDefault = true;
				break;
			case 'DATA':
				dataPresent = true;
				position = f->read<NiPoint3>();
				rotation = f->read<NiPoint3>();
				readSize += 24;
				break;
			default:
				LoadSubrecord(h,f);
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		WriteZStringSubrecord('EDID',editorID,f);
		if (parentObject)
		{
			WriteSubrecord('NAME',4,f);
			f->write<formid>(parentObject);
		}
		SaveSubrecords(f);
		if (openByDefault)
		{
			WriteSubrecord('ONAM',0,f);
		}
		if (dataPresent)
		{
			WriteSubrecord('DATA',24,f);
			f->write<NiPoint3>(position);
			f->write<NiPoint3>(rotation);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		if (parentObject)
		{
			size += ComputeSubrecordSize(4);
		}
		size += GetSubrecordSize();
		if (openByDefault)
		{
			size += ComputeSubrecordSize(0);
		}
		if (dataPresent)
		{
			size += ComputeSubrecordSize(24);
		}
		return size;
	}
};
