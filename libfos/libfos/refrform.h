/*	libfos
	Copyright 2015 Jonathan Wilson

	This file is part of libfos
	libfos is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "extradataform.h"
class RefrForm : public ExtraDataForm
{
protected:
	bool openByDefault;
	NiPoint3 position;
	NiPoint3 rotation;
	float scale;
public:
	RefrForm(FormHeader h,ModFile *f) : ExtraDataForm(h,f), openByDefault(false), scale(1)
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
			case 'XSCL':
				scale = f->read<float>();
				readSize += 4;
				break;
			case 'ONAM':
				openByDefault = true;
				break;
			case 'DATA':
				position = f->read<NiPoint3>();
				rotation = f->read<NiPoint3>();
				readSize += 24;
				break;
			default:
				LoadExtraData(f,h);
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		FormSave();
		if (!(header.flags & 0x20))
		{
			SaveExtraData(f);
			if (scale != 1)
			{
				WriteSubrecord('XSCL',4,f);
				f->write<float>(scale);
			}
			if (openByDefault)
			{
				WriteSubrecord('ONAM',0,f);
			}
			WriteSubrecord('DATA',24,f);
			f->write<NiPoint3>(position);
			f->write<NiPoint3>(rotation);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		FormGetSaveSize();
		if (!(header.flags & 0x20))
		{
			size += GetExtraDataSaveSize();
			if (scale != 1)
			{
				size += ComputeSubrecordSize(4);
			}
			if (openByDefault)
			{
				size += ComputeSubrecordSize(0);
			}
			size += ComputeSubrecordSize(24);
		}
		return size;
	}
};
