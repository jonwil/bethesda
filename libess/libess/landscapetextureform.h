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
class LandscapeTextureForm : public Form
{
protected:
	char *editorID;
	char *icon;
	bool hashnam;
	ubyte materialType;
	ubyte friction;
	ubyte restitution;
	bool hassnam;
	ubyte textureSpecularExponent;
	SimpleDynVecClass<formid> grassTypes;
public:
	LandscapeTextureForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), icon(0), hashnam(false), materialType(0), friction(0), restitution(0), hassnam(0), textureSpecularExponent(0), grassTypes(0)
	{
	}
	virtual ~LandscapeTextureForm()
	{
		if (editorID)
		{
			delete[] editorID;
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
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'HNAM':
				hashnam = true;
				materialType = f->read<ubyte>();
				readSize += 1;
				friction = f->read<ubyte>();
				readSize += 1;
				restitution = f->read<ubyte>();
				readSize += 1;
				break;
			case 'SNAM':
				hassnam = true;
				textureSpecularExponent = f->read<ubyte>();
				readSize += 1;
				break;
			case 'GNAM':
				grassTypes.Add(f->read<formid>());
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
		WriteZStringSubrecord('ICON',icon,f);
		if (hashnam)
		{
			WriteSubrecord('HNAM',3,f);
			f->write<ubyte>(materialType);
			f->write<ubyte>(friction);
			f->write<ubyte>(restitution);
		}
		if (hassnam)
		{
			WriteSubrecord('SNAM',1,f);
			f->write<ubyte>(textureSpecularExponent);
		}
		for (int i = 0;i < grassTypes.Count();i++)
		{
			WriteSubrecord('GNAM',4,f);
			f->write<formid>(grassTypes[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(icon);
		if (hashnam)
		{
			size += ComputeSubrecordSize(3);
		}
		if (hassnam)
		{
			size += ComputeSubrecordSize(1);
		}
		for (int i = 0;i < grassTypes.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
