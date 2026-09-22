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
#include "armorform.h"
class ArmorAddonForm : public BoundObjectForm, public FullName, public BipedModel, public EquipType
{
protected:
	ArmorData data;
	ArmorData2 data2;
public:
	ArmorAddonForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f)
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
			FullNameLoad();
			BipedModelLoad();
			EquipTypeLoad();
			case 'DATA':
				data = f->read<ArmorData>();
				readSize += sizeof(ArmorData);
				break;
			case 'DNAM':
				data2 = f->read<ArmorData2>();
				readSize += sizeof(ArmorData2);
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
		FullNameSave();
		BipedModelSave();
		EquipTypeSave();
		WriteSubrecord('DATA',sizeof(ArmorData),f);
		f->write<ArmorData>(data);
		WriteSubrecord('DNAM',sizeof(ArmorData2),f);
		f->write<ArmorData2>(data2);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		BipedModelGetSaveSize();
		EquipTypeGetSaveSize();
		size += ComputeSubrecordSize(sizeof(ArmorData));
		size += ComputeSubrecordSize(sizeof(ArmorData2));
		return size;
	}
};
