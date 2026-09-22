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
class LightForm : public Form
{
protected:
	char *editorID;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	formid script;
	char *fullName;
	char *icon;
	long time;
	ulong radius;
	Color color;
	ulong flags;
	float falloffExponent;
	float FOV;
	ulong value;
	float weight;
	bool hasFade;
	float fade;
	formid sound;
	bool smallerData;
public:
	LightForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), script(0), fullName(0), icon(0), time(0), radius(0), flags(0), falloffExponent(1.0), FOV(90), value(0), weight(0), fade(0), sound(0), smallerData(false), hasFade(false)
	{
	}
	virtual ~LightForm()
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
		if (icon)
		{
			delete[] icon;
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
			case 'SCRI':
				script = f->read<formid>();
				readSize += 4;
				break;
			case 'FULL':
				fullName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				time = f->read<long>();
				readSize += 4;
				radius = f->read<ulong>();
				readSize += 4;
				color = f->read<Color>();
				readSize += 4;
				flags = f->read<ulong>();
				readSize += 4;
				if (h.size == 32)
				{
					falloffExponent = f->read<float>();
					readSize += 4;
					FOV = f->read<float>();
					readSize += 4;
				}
				else
				{
					smallerData = true;
				}
				value = f->read<ulong>();
				readSize += 4;
				weight = f->read<float>();
				readSize += 4;
				break;
			case 'FNAM':
				hasFade = true;
				fade = f->read<float>();
				readSize += 4;
				break;
			case 'SNAM':
				sound = f->read<formid>();
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
		if (script)
		{
			WriteSubrecord('SCRI',4,f);
			f->write<formid>(script);
		}
		WriteZStringSubrecord('FULL',fullName,f);
		WriteZStringSubrecord('ICON',icon,f);
		if (smallerData)
		{
			WriteSubrecord('DATA',24,f);
		}
		else
		{
			WriteSubrecord('DATA',32,f);
		}
		f->write<long>(time);
		f->write<ulong>(radius);
		f->write<Color>(color);
		f->write<ulong>(flags);
		if (!smallerData)
		{
			f->write<float>(falloffExponent);
			f->write<float>(FOV);
		}
		f->write<ulong>(value);
		f->write<float>(weight);
		if (hasFade)
		{
			WriteSubrecord('FNAM',4,f);
			f->write<float>(fade);
		}
		if (sound)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<formid>(sound);
		}
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
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(icon);
		if (smallerData)
		{
			size += ComputeSubrecordSize(24);
		}
		else
		{
			size += ComputeSubrecordSize(32);
		}
		if (hasFade)
		{
			size += ComputeSubrecordSize(4);
		}
		if (sound)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
