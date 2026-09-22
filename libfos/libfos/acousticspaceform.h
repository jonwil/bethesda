/*	libfos
	Copyright 2015 Jonathan Wilson

	This file is part of libfos
	libfos is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 3, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "boundobjectform.h"
class AcousticSpaceForm : public BoundObjectForm
{
protected:
	formid sound;
	formid region;
	ulong environmentType;
public:
	AcousticSpaceForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), sound(0), region(0)
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
			BoundObjectFormLoad();
			case 'SNAM':
				sound = f->read<formid>();
				readSize += 4;
				break;
			case 'RDAT':
				region = f->read<formid>();
				readSize += 4;
				break;
			case 'ANAM':
				environmentType = f->read<ulong>();
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
		BoundObjectFormSave();
		if (sound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound);
		}
		if (region)
		{
			WriteSubrecord('RDAT',4,f);
			f->write<formid>(region);
		}
		WriteSubrecord('ANAM',4,f);
		f->write<ulong>(environmentType);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (region)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(4);
		return size;
	}
};
