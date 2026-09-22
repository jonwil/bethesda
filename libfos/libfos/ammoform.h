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
#pragma pack(push,1)
struct AmmoData
{
	float speed;
	ubyte flags;
	ubyte pad[3];
	long value;
	ubyte clipRounds;
};
#pragma pack(pop)
class AmmoForm : public BoundObjectForm, public FullName, public ModelTextureSwap, public Texture, public MessageTexture, public DestructibleObject, public PickupPutdownSounds
{
protected:
	AmmoData data;
	char *shortName;
public:
	AmmoForm(FormHeader h,ModFile *f) : BoundObjectForm(h,f), shortName(0)
	{
	}
	virtual ~AmmoForm()
	{
		if (shortName)
		{
			delete[] shortName;
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
			BoundObjectFormLoad();
			FullNameLoad();
			ModelTextureSwapBRLoad(this,'MODL','MODB','MODT','MODS');
			TextureLoad(this,'ICON');
			MessageTextureLoad(this,'MICO');
			DestructibleObjectLoad();
			PickupPutdownSoundsLoad();
			case 'DATA':
				data = f->read<AmmoData>();
				readSize += sizeof(AmmoData);
				break;
			case 'ONAM':
				shortName = f->readzstring(h.size);
				readSize += h.size;
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
		TextureSave(this,'ICON');
		MessageTextureSave(this,'MICO');
		DestructibleObjectSave();
		PickupPutdownSoundsSave();
		WriteSubrecord('DATA',sizeof(AmmoData),f);
		f->write<AmmoData>(data);
		WriteZStringSubrecord('ONAM',shortName,f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		BoundObjectFormGetSaveSize();
		FullNameGetSaveSize();
		ModelTextureSwapBRGetSaveSize(this);
		TextureGetSaveSize(this);
		MessageTextureGetSaveSize(this);
		DestructibleObjectGetSaveSize();
		PickupPutdownSoundsGetSaveSize();
		size += ComputeSubrecordSize(sizeof(AmmoData));
		size += ZStringSubrecordSize(shortName);
		return size;
	}
};
