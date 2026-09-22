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
class CellForm : public ExtraDataForm
{
protected:
	char *editorID;
	char *fullName;
	ubyte flags;
public:
	CellForm(FormHeader h,ModFile *f) : ExtraDataForm(h,f), editorID(0), fullName(0), flags(0)
	{
	}
	virtual ~CellForm()
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
	ubyte GetFlags()
	{
		return flags;
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
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
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
		WriteZStringSubrecord('FULL',fullName,f);
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(flags);
		SaveSubrecords(f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		size += ComputeSubrecordSize(1);
		size += GetSubrecordSize();
		return size;
	}
};
