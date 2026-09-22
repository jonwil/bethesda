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
struct MapData
{
	long xSize;
	long ySize;
	short nwCellX;
	short nwCellY;
	short seCellX;
	short seCellY;
};
class WorldspaceForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	formid parent;
	formid climate;
	formid water;
	char *icon;
	bool mapDataPresent;
	MapData mapData;
	ubyte flags;
	NiPoint2 minBounds;
	NiPoint2 maxBounds;
	ulong musicType;
	ulong offsetSize;
	ubyte *offsetData;
public:
	WorldspaceForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), parent(0), climate(0), water(0), icon(0), flags(0), musicType(0), offsetSize(0), offsetData(0), mapDataPresent(false)
	{
	}
	virtual ~WorldspaceForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (icon)
		{
			delete[] icon;
		}
		if (offsetData)
		{
			delete[] offsetData;
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
			case 'WNAM':
				parent = f->read<formid>();
				readSize += 4;
				break;
			case 'CNAM':
				climate = f->read<formid>();
				readSize += 4;
				break;
			case 'NAM2':
				water = f->read<formid>();
				readSize += 4;
				break;
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MNAM':
				mapDataPresent = true;
				mapData = f->read<MapData>();
				readSize += sizeof(mapData);
				break;
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'NAM0':
				minBounds = f->read<NiPoint2>();
				readSize += sizeof(NiPoint2);
				break;
			case 'NAM9':
				maxBounds = f->read<NiPoint2>();
				readSize += sizeof(NiPoint2);
				break;
			case 'SNAM':
				musicType = f->read<ulong>();
				readSize += 4;
				break;
			case 'OFST':
				offsetSize = h.size;
				offsetData = f->readarray<ubyte>(offsetSize);
				readSize += offsetSize;
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
		if (parent)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(parent);
		}
		if (climate)
		{
			WriteSubrecord('CNAM',4,f);
			f->write<formid>(climate);
		}
		if (water)
		{
			WriteSubrecord('NAM2',4,f);
			f->write<formid>(water);
		}
		WriteZStringSubrecord('ICON',icon,f);
		if (mapDataPresent)
		{
			WriteSubrecord('MNAM',sizeof(MapData),f);
			f->write<MapData>(mapData);
		}
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(flags);
		WriteSubrecord('NAM0',sizeof(NiPoint2),f);
		f->write<NiPoint2>(minBounds);
		WriteSubrecord('NAM9',sizeof(NiPoint2),f);
		f->write<NiPoint2>(maxBounds);
		if (musicType)
		{
			WriteSubrecord('SNAM',4,f);
			f->write<ulong>(musicType);
		}
		if (offsetData)
		{
			WriteSubrecord('OFST',offsetSize,f);
			f->writearray<ubyte>(offsetSize,offsetData);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		if (parent)
		{
			size += ComputeSubrecordSize(4);
		}
		if (climate)
		{
			size += ComputeSubrecordSize(4);
		}
		if (water)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ZStringSubrecordSize(icon);
		if (mapDataPresent)
		{
			size += ComputeSubrecordSize(sizeof(MapData));
		}
		size += ComputeSubrecordSize(1);
		size += ComputeSubrecordSize(sizeof(NiPoint2));
		size += ComputeSubrecordSize(sizeof(NiPoint2));
		if (musicType)
		{
			size += ComputeSubrecordSize(4);
		}
		if (offsetData)
		{
			size += ComputeSubrecordSize(offsetSize);
		}
		return size;
	}
};
