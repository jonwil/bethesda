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
class ContainerForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	formid script;
	SimpleDynVecClass<ContainerItem> containerItems;
	ubyte flags;
	float weight;
	formid openSound;
	formid closeSound;
public:
	ContainerForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), script(0), containerItems(0), flags(0), weight(0), openSound(0), closeSound(0)
	{
	}
	virtual ~ContainerForm()
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
			case 'CNTO':
				{
					ContainerItem i;
					i.item = f->read<formid>();
					readSize += 4;
					i.count = f->read<ulong>();
					readSize += 4;
					containerItems.Add(i);
				}
				break;
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
				weight = f->read<float>();
				readSize += 4;
				break;
			case 'SNAM':
				openSound = f->read<formid>();
				readSize += 4;
				break;
			case 'QNAM':
				closeSound = f->read<formid>();
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
		for (int i = 0;i < containerItems.Count();i++)
		{
			WriteSubrecord('CNTO',8,f);
			f->write<formid>(containerItems[i].item);
			f->write<ulong>(containerItems[i].count);
		}
		WriteSubrecord('DATA',5,f);
		f->write<ubyte>(flags);
		f->write<float>(weight);
		if (openSound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(openSound);
		}
		if (closeSound)
		{
			WriteSubrecord('QNAM',4,f);
			f->write<formid>(closeSound);
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
		for (int i = 0;i < containerItems.Count();i++)
		{
			size += ComputeSubrecordSize(8);
		}
		size += ComputeSubrecordSize(5);
		if (openSound)
		{
			size += ComputeSubrecordSize(4);
		}
		if (closeSound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
