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
struct TreeData
{
	float curvature;
	float minAngle;
	float maxAngle;
	float branchDim;
	float leafDim;
	long shadowRadius;
	float rockSpeed;
	float rustleSpeed;
};
class TreeForm : public Form
{
protected:
	char *editorID;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	char *icon;
	ulong seedCount;
	ulong *seeds;
	TreeData data;
	float billboardWidth;
	float billboardHeight;
public:
	TreeForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), icon(0), seedCount(0), seeds(0)
	{
	}
	virtual ~TreeForm()
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
		if (icon)
		{
			delete[] icon;
		}
		if (seeds)
		{
			delete[] seeds;
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
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SNAM':
				seedCount = h.size / 4;
				seeds = f->readarray<ulong>(seedCount);
				readSize += h.size;
				break;
			case 'CNAM':
				data = f->read<TreeData>();
				readSize += sizeof(TreeData);
				break;
			case 'BNAM':
				billboardWidth = f->read<float>();
				billboardHeight = f->read<float>();
				readSize += 8;
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
		WriteZStringSubrecord('ICON',icon,f);
		if (seeds)
		{
			WriteSubrecord('SNAM',seedCount * 4,f);
			f->writearray<ulong>(seedCount,seeds);
		}
		WriteSubrecord('CNAM',sizeof(TreeData),f);
		f->write<TreeData>(data);
		WriteSubrecord('BNAM',8,f);
		f->write<float>(billboardWidth);
		f->write<float>(billboardHeight);
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
		size += ZStringSubrecordSize(icon);
		if (seeds)
		{
			size += ComputeSubrecordSize(seedCount * 4);
		}
		size += ComputeSubrecordSize(sizeof(TreeData));
		size += ComputeSubrecordSize(8);
		return size;
	}
};
