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
class BookForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	char *icon;
	formid script;
	formid enchantment;
	ushort enchantmentPoints; 
	bool scriptBeforeDescription;
	char *description;
	ubyte flags;
	ubyte skill;
	ulong value;
	float weight;
public:
	BookForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), icon(0), script(0), enchantment(0), enchantmentPoints(0), description(0), flags(0), skill(0xFF), value(0), weight(0), scriptBeforeDescription(true)
	{
	}
	virtual ~BookForm()
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
		if (description)
		{
			delete[] description;
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
				if (description)
				{
					scriptBeforeDescription = false;
				}
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
			case 'DESC':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				flags = f->read<ubyte>();
				skill = f->read<ubyte>();
				value = f->read<ulong>();
				weight = f->read<float>();
				readSize += 10;
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
		if (script && scriptBeforeDescription)
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
		WriteZStringSubrecord('DESC',description,f);
		if (script && !scriptBeforeDescription)
		{
			WriteSubrecord('SCRI',4,f);
			f->write<formid>(script);
		}
		WriteSubrecord('DATA',10,f);
		f->write<ubyte>(flags);
		f->write<ubyte>(skill);
		f->write<ulong>(value);
		f->write<float>(weight);
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
		size += ZStringSubrecordSize(description);
		size += ComputeSubrecordSize(10);
		return size;
	}
};
