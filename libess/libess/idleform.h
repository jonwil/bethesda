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
struct IdleCondition
{
	ulong flags;
	float comparison;
	ulong functionIndex;
	ulong firstParameter;
	ulong secondParameter;
	ulong pad;
};
struct IdleConditionOld
{
	ulong flags;
	float comparison;
	ulong functionIndex;
	ulong firstParameter;
	ulong secondParameter;
};
class IdleForm : public Form
{
protected:
	char *editorID;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	SimpleDynVecClass<IdleCondition> conditions;
	SimpleDynVecClass<IdleConditionOld> oldconditions;
	ubyte flags;
	formid parent;
	formid prev;
public:
	IdleForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), conditions(0), flags(0), parent(0), prev(0), oldconditions(0)
	{
	}
	virtual ~IdleForm()
	{
		if (editorID)
		{
			delete[] editorID;
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
			case 'CTDA':
				conditions.Add(f->read<IdleCondition>());
				readSize += sizeof(IdleCondition);
				break;
			case 'CTDT':
				oldconditions.Add(f->read<IdleConditionOld>());
				readSize += sizeof(IdleConditionOld);
				break;
			case 'ANAM':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'DATA':
				parent = f->read<formid>();
				readSize += 4;
				prev = f->read<formid>();
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
		for (int i = 0;i < conditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(IdleCondition),f);
			f->write<IdleCondition>(conditions[i]);
		}
		for (int i = 0;i < oldconditions.Count();i++)
		{
			WriteSubrecord('CTDT',sizeof(IdleConditionOld),f);
			f->write<IdleConditionOld>(oldconditions[i]);
		}
		WriteSubrecord('ANAM',1,f);
		f->write<ubyte>(flags);
		WriteSubrecord('DATA',8,f);
		f->write<formid>(parent);
		f->write<formid>(prev);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(model);
		if (model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (textureHashes)
		{
			size += ComputeSubrecordSize(textureHashesCount * sizeof(TextureHash));
		}
		for (int i = 0;i < conditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(IdleCondition));
		}
		for (int i = 0;i < oldconditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(IdleConditionOld));
		}
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(8);
		return size;
	}
};
