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
class RoadForm : public Form
{
protected:
	ulong pointCount;
	Point *points;
	ulong connectionCount;
	NiPoint3 *connections;
public:
	RoadForm(FormHeader h,ModFile *f) : Form(h,f), pointCount(0), points(0), connectionCount(0), connections(0)
	{
	}
	virtual ~RoadForm()
	{
		if (points)
		{
			delete[] points;
		}
		if (connections)
		{
			delete[] connections;
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
			case 'PGRP':
				pointCount = h.size / sizeof(Point);
				points = f->readarray<Point>(pointCount);
				readSize += h.size;
				break;
			case 'PGRR':
				connectionCount = h.size / sizeof(NiPoint3);
				connections = f->readarray<NiPoint3>(connectionCount);
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
		if (points)
		{
			WriteSubrecord('PGRP',pointCount * sizeof(Point),f);
			f->writearray<Point>(pointCount,points);
		}
		if (connections)
		{
			WriteSubrecord('PGRR',connectionCount * sizeof(NiPoint3),f);
			f->writearray<NiPoint3>(connectionCount,connections);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		if (points)
		{
			size += ComputeSubrecordSize(pointCount * sizeof(Point));
		}
		if (connections)
		{
			size += ComputeSubrecordSize(connectionCount * sizeof(NiPoint3));
		}
		return size;
	}
};
