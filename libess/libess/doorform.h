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
class DoorForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	formid script;
	formid openSound;
	formid closeSound;
	formid loopSound;
	ubyte flags;
	SimpleDynVecClass<formid> teleports;
public:
	DoorForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), script(0), openSound(0), closeSound(0), loopSound(0), flags(0), teleports(0)
	{
	}
	virtual ~DoorForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (model)
		{
			delete[] model;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
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
			case 'FULL':
				fullName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODL':
				model = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODB':
				boundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MODT':
				textureHashesCount = h.size / sizeof(TextureHash);
				textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'SCRI':
				script = f->read<formid>();
				readSize += 4;
				break;
			case 'SNAM':
				openSound = f->read<formid>();
				readSize += 4;
				break;
			case 'ANAM':
				closeSound = f->read<formid>();
				readSize += 4;
				break;
			case 'BNAM':
				loopSound = f->read<formid>();
				readSize += 4;
				break;
			case 'FNAM':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'TNAM':
				teleports.Add(f->read<formid>());
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
		WriteZStringSubrecord('FULL',fullName,f);
		WriteZStringSubrecord('MODL',model,f);
		if (model)
		{
			WriteSubrecord('MODB',4,f);
			f->write<float>(boundRadius);
		}
		if (textureHashes)
		{
			WriteSubrecord('MODT',textureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(textureHashesCount,textureHashes);
		}
		if (script)
		{
			WriteSubrecord('SCRI',4,f);
			f->write<formid>(script);
		}
		if (openSound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(openSound);
		}
		if (closeSound)
		{
			WriteSubrecord('ANAM',4,f);
			f->write<formid>(closeSound);
		}
		if (loopSound)
		{
			WriteSubrecord('BNAM',4,f);
			f->write<formid>(loopSound);
		}
		WriteSubrecord('FNAM',1,f);
		f->write<ubyte>(flags);
		for (int i = 0;i < teleports.Count();i++)
		{
			WriteSubrecord('TNAM',4,f);
			f->write<formid>(teleports[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(model);
		if (model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (textureHashes)
		{
			size += ComputeSubrecordSize(textureHashesCount * sizeof(TextureHash));
		}
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		if (openSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (closeSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (loopSound)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(1);
		for (int i = 0;i < teleports.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
