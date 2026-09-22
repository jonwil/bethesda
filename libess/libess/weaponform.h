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
class WeaponForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	char *icon;
	formid enchantment;
	ushort enchantmentPoints;
	formid script;
	ulong type;
	float speed;
	float reach;
	ulong flags;
	ulong value;
	ulong health;
	float weight;
	ushort damage;
public:
	WeaponForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), icon(0), enchantment(0), enchantmentPoints(0), script(0), type(0), speed(0), reach(0), flags(0), value(0), health(0), weight(0), damage(0)
	{
	}
	virtual ~WeaponForm()
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
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SCRI':
				script = f->read<formid>();
				readSize += 4;
				break;
			case 'ENAM':
				enchantment = f->read<formid>();
				readSize += 4;
				break;
			case 'ANAM':
				enchantmentPoints = f->read<ushort>();
				readSize += 2;
				break;
			case 'DATA':
				type = f->read<ulong>();
				readSize += 4;
				speed = f->read<float>();
				readSize += 4;
				reach = f->read<float>();
				readSize += 4;
				flags = f->read<ulong>();
				readSize += 4;
				value = f->read<ulong>();
				readSize += 4;
				health = f->read<ulong>();
				readSize += 4;
				weight = f->read<float>();
				readSize += 4;
				damage = f->read<ushort>();
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
		WriteZStringSubrecord('ICON',icon,f);
		if (script)
		{
			WriteSubrecord('SCRI',4,f);
			f->write<formid>(script);
		}
		if (enchantment)
		{
			WriteSubrecord('ENAM',4,f);
			f->write<formid>(enchantment);
		}
		if (enchantmentPoints)
		{
			WriteSubrecord('ANAM',2,f);
			f->write<ushort>(enchantmentPoints);
		}
		WriteSubrecord('DATA',30,f);
		f->write<ulong>(type);
		f->write<float>(speed);
		f->write<float>(reach);
		f->write<ulong>(flags);
		f->write<ulong>(value);
		f->write<ulong>(health);
		f->write<float>(weight);
		f->write<ushort>(damage);
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
		size += ZStringSubrecordSize(icon);
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		if (enchantment)
		{
			size += ComputeSubrecordSize(4);
		}
		if (enchantmentPoints)
		{
			size += ComputeSubrecordSize(2);
		}
		size += ComputeSubrecordSize(30);
		return size;
	}
};
