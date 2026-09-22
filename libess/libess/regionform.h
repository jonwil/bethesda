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
struct RegionArea
{
	ulong edgeFallOff;
	ulong pointCount;
	NiPoint2 *points;
	RegionArea() : edgeFallOff(0), pointCount(0), points(0)
	{
	}
};
struct RegionObject
{
	formid object;
	ulong parentIndex;
	float density;
	ubyte clustering;
	ubyte minSlope;
	ubyte maxSlope;
	ubyte flags;
	ushort radiusParent;
	ushort radius;
	ulong unk;
	float maxHeight;
	float sink;
	float sinkVar;
	float sizeVar;
	ushort angleVarX;
	ushort angleVarY;
	ushort angleVarZ;
	ushort unk2;
	ulong unk3;
};
struct RegionGrass
{
	formid grass;
	ulong unk;
};
struct RegionSound
{
	formid sound;
	ulong flags;
	ulong chance;
};
struct RegionWeather
{
	formid weather;
	ulong chance;
};
struct RegionDataEntry
{
	ulong entryType;
	ubyte flags;
	ubyte priority;
	ushort pad;
	ulong objectCount;
	RegionObject *objects;
	char *mapName;
	char *icon;
	ulong grassCount;
	RegionGrass *grasses;
	ulong musicType;
	ulong soundCount;
	RegionSound *sounds;
	ulong weatherCount;
	RegionWeather *weatherTypes;
	RegionDataEntry() : entryType(0), flags(0), priority(0), pad(0), objectCount(0), objects(0), mapName(0), icon(0), grassCount(0), grasses(0), musicType(0), soundCount(0), sounds(0), weatherCount(0), weatherTypes(0)
	{
	}
};
class RegionForm : public Form
{
protected:
	char *editorID;
	char *icon;
	Color mapColor;
	formid worldspace;
	SimpleDynVecClass<RegionArea> areas;
	SimpleDynVecClass<RegionDataEntry> dataEntries;
public:
	RegionForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), icon(0), worldspace(0), areas(0), dataEntries(0)
	{
	}
	virtual ~RegionForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (icon)
		{
			delete[] icon;
		}
		for (int i = 0;i < areas.Count();i++)
		{
			delete[] areas[i].points;
		}
		for (int i = 0;i < dataEntries.Count();i++)
		{
			delete[] dataEntries[i].objects;
			delete[] dataEntries[i].mapName;
			delete[] dataEntries[i].icon;
			delete[] dataEntries[i].grasses;
			delete[] dataEntries[i].sounds;
			delete[] dataEntries[i].weatherTypes;
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
				if (!dataEntries.Count())
				{
					icon = f->readzstring(h.size);
					readSize += h.size;
				}
				else
				{
					dataEntries[dataEntries.Count() - 1].icon = f->readzstring(h.size);
					readSize += h.size;
				}
				break;
			case 'RCLR':
				mapColor = f->read<Color>();
				readSize += 4;
				break;
			case 'WNAM':
				worldspace = f->read<formid>();
				readSize += 4;
				break;
			case 'RPLI':
				{
					RegionArea a;
					a.edgeFallOff = f->read<ulong>();
					readSize += 4;
					areas.Add(a);
				}
				break;
			case 'RPLD':
				areas[areas.Count() - 1].pointCount = h.size / 8;
				areas[areas.Count() - 1].points = f->readarray<NiPoint2>(h.size / 8);
				readSize += h.size;
				break;
			case 'RDAT':
				{
					RegionDataEntry r;
					r.entryType = f->read<ulong>();
					readSize += 4;
					r.flags = f->read<ubyte>();
					readSize += 1;
					r.priority = f->read<ubyte>();
					readSize += 1;
					r.pad = f->read<ushort>();
					readSize += 2;
					dataEntries.Add(r);
				}
				break;
			case 'RDOT':
				dataEntries[dataEntries.Count() - 1].objectCount = h.size / sizeof(RegionObject);
				dataEntries[dataEntries.Count() - 1].objects = f->readarray<RegionObject>(h.size / sizeof(RegionObject));
				readSize += h.size;
				break;
			case 'RDMP':
				dataEntries[dataEntries.Count() - 1].mapName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'RDGS':
				dataEntries[dataEntries.Count() - 1].grassCount = h.size / sizeof(RegionGrass);
				dataEntries[dataEntries.Count() - 1].grasses = f->readarray<RegionGrass>(h.size / sizeof(RegionGrass));
				readSize += h.size;
				break;
			case 'RDMD':
				dataEntries[dataEntries.Count() - 1].musicType = f->read<ulong>();
				readSize += 4;
				break;
			case 'RDSD':
				dataEntries[dataEntries.Count() - 1].soundCount = h.size / sizeof(RegionSound);
				dataEntries[dataEntries.Count() - 1].sounds = f->readarray<RegionSound>(h.size / sizeof(RegionSound));
				readSize += h.size;
				break;
			case 'RDWT':
				dataEntries[dataEntries.Count() - 1].weatherCount = h.size / sizeof(RegionWeather);
				dataEntries[dataEntries.Count() - 1].weatherTypes = f->readarray<RegionWeather>(h.size / sizeof(RegionWeather));
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
		WriteZStringSubrecord('EDID',editorID,f);
		WriteZStringSubrecord('ICON',icon,f);
		WriteSubrecord('RCLR',4,f);
		f->write<Color>(mapColor);
		if (worldspace)
		{
			WriteSubrecord('WNAM',4,f);
			f->write<formid>(worldspace);
		}
		for (int i = 0;i < areas.Count();i++)
		{
			WriteSubrecord('RPLI',4,f);
			f->write<ulong>(areas[i].edgeFallOff);
			WriteSubrecord('RPLD',areas[i].pointCount * 8,f);
			f->writearray<NiPoint2>(areas[i].pointCount,areas[i].points);
		}
		for (int i = 0;i < dataEntries.Count();i++)
		{
			WriteSubrecord('RDAT',8,f);
			f->write<ulong>(dataEntries[i].entryType);
			f->write<ubyte>(dataEntries[i].flags);
			f->write<ubyte>(dataEntries[i].priority);
			f->write<ushort>(dataEntries[i].pad);
			switch (dataEntries[i].entryType)
			{
			case 2:
				WriteSubrecord('RDOT',dataEntries[i].objectCount * sizeof(RegionObject),f);
				f->writearray<RegionObject>(dataEntries[i].objectCount,dataEntries[i].objects);
				break;
			case 3:
				if (dataEntries[i].weatherCount)
				{
					WriteSubrecord('RDWT',dataEntries[i].weatherCount * sizeof(RegionWeather),f);
					f->writearray<RegionWeather>(dataEntries[i].weatherCount,dataEntries[i].weatherTypes);
				}
				break;
			case 4:
				WriteZStringSubrecord('RDMP',dataEntries[i].mapName,f);
				break;
			case 5:
				WriteZStringSubrecord('ICON',dataEntries[i].icon,f);
				break;
			case 6:
				WriteSubrecord('RDGS',dataEntries[i].grassCount * sizeof(RegionGrass),f);
				f->writearray<RegionGrass>(dataEntries[i].grassCount,dataEntries[i].grasses);
				break;
			case 7:
				WriteSubrecord('RDMD',4,f);
				f->write<ulong>(dataEntries[i].musicType);
				WriteSubrecord('RDSD',dataEntries[i].soundCount * sizeof(RegionSound),f);
				f->writearray<RegionSound>(dataEntries[i].soundCount,dataEntries[i].sounds);
				break;
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(icon);
		size += ComputeSubrecordSize(4);
		if (worldspace)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < areas.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ComputeSubrecordSize(areas[i].pointCount * 8);
		}
		for (int i = 0;i < dataEntries.Count();i++)
		{
			size += ComputeSubrecordSize(8);
			switch (dataEntries[i].entryType)
			{
			case 2:
				size += ComputeSubrecordSize(dataEntries[i].objectCount * sizeof(RegionObject));
				break;
			case 3:
				if (dataEntries[i].weatherCount)
				{
					size += ComputeSubrecordSize(dataEntries[i].weatherCount * sizeof(RegionWeather));
				}
				break;
			case 4:
				size += ZStringSubrecordSize(dataEntries[i].mapName);
				break;
			case 5:
				size += ZStringSubrecordSize(dataEntries[i].icon);
				break;
			case 6:
				size += ComputeSubrecordSize(dataEntries[i].grassCount * sizeof(RegionGrass));
				break;
			case 7:
				size += ComputeSubrecordSize(4);
				size += ComputeSubrecordSize(dataEntries[i].soundCount * sizeof(RegionSound));
				break;
			}
		}
		return size;
	}
};
