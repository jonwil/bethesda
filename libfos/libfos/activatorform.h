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
class ActivatorForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Scriptable, public DestructibleObject
{
protected:
	formid loopSound;
	formid activationSound;
	formid waterType;
	formid radioStation;
public:
	ActivatorForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), loopSound(0), activationSound(0), waterType(0), radioStation(0)
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
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			ScriptableLoad();
			DestructibleObjectLoad();
			case 'SNAM':
				loopSound = f->read<formid>();
				readSize += 4;
				break;
			case 'VNAM':
				activationSound = f->read<formid>();
				readSize += 4;
				break;
			case 'WNAM':
				waterType = f->read<formid>();
				readSize += 4;
				break;
			case 'RNAM':
				radioStation = f->read<formid>();
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
		FullNameSave();
		ModelTextureSwapBRSave(this,'MODL','MODB','MODT','MODS');
		ScriptableSave();
		DestructibleObjectSave();
		if (loopSound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(loopSound);
		}
		if (activationSound)
		{
			WriteSubrecord('VNAM',4,f);
			f->write<formid>(activationSound);
		}
		if (waterType)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(waterType);
		}
		if (radioStation)
		{
			WriteSubrecord('RNAM',4,f);
			f->write<formid>(radioStation);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		ScriptableGetSaveSize();
		DestructibleObjectGetSaveSize();
		if (loopSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (activationSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (waterType)
		{
			size += ComputeSubrecordSize(4);
		}
		if (radioStation)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
