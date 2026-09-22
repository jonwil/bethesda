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
struct PathGridCellConnection
{
	long localNode;
	NiPoint3 foreignNode;
};
struct PathGridPointLink
{
	formid linkedObject;
	ulong nodeCount;
	ulong *nodes;
	PathGridPointLink() : linkedObject(0), nodeCount(0), nodes(0)
	{
	}
};
class PathGridForm : public Form
{
protected:
	ushort nodeCount;
	ulong pointCount;
	Point *points;
	ulong PGAGSize;
	ubyte *PGAGData;
	ulong nodeConnectionCount;
	ushort *nodeConnections;
	ulong nodeCellConnectionCount;
	PathGridCellConnection *nodeCellConnections;
	SimpleDynVecClass<PathGridPointLink> pointLinks;
public:
	PathGridForm(FormHeader h,ModFile *f) : Form(h,f), pointCount(0), points(0), PGAGSize(0), PGAGData(0), nodeConnectionCount(0), nodeConnections(0), nodeCellConnectionCount(0), nodeCellConnections(0), pointLinks(0), nodeCount(0)
	{
	}
	virtual ~PathGridForm()
	{
		if (points)
		{
			delete[] points;
		}
		if (PGAGData)
		{
			delete[] PGAGData;
		}
		if (nodeConnections)
		{
			delete[] nodeConnections;
		}
		if (nodeCellConnections)
		{
			delete[] nodeCellConnections;
		}
		for (int i = 0; i < pointLinks.Count();i++)
		{
			if (pointLinks[i].nodes)
			{
				delete[] pointLinks[i].nodes;
			}
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
			case 'DATA':
				nodeCount = f->read<ushort>();
				readSize += 2;
				break;
			case 'PGRP':
				pointCount = h.size / sizeof(Point);
				points = f->readarray<Point>(pointCount);
				readSize += h.size;
				break;
			case 'PGAG':
				PGAGSize = h.size;
				PGAGData = f->readarray<ubyte>(PGAGSize);
				readSize += h.size;
				break;
			case 'PGRR':
				nodeConnectionCount = h.size / 2;
				nodeConnections = f->readarray<ushort>(nodeConnectionCount);
				readSize += h.size;
				break;
			case 'PGRI':
				nodeCellConnectionCount = h.size / sizeof(PathGridCellConnection);
				nodeCellConnections = f->readarray<PathGridCellConnection>(nodeCellConnectionCount);
				readSize += h.size;
				break;
			case 'PGRL':
				{
					PathGridPointLink p;
					p.linkedObject = f->read<formid>();
					p.nodeCount = (h.size - 4) / 4;
					p.nodes = f->readarray<ulong>(p.nodeCount);
					pointLinks.Add(p);
					readSize += h.size;
				}
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
		WriteSubrecord('DATA',2,f);
		f->write<ushort>(nodeCount);
		if (points)
		{
			WriteSubrecord('PGRP',pointCount * sizeof(Point),f);
			f->writearray<Point>(pointCount,points);
		}
		if (PGAGData)
		{
			WriteSubrecord('PGAG',PGAGSize,f);
			f->writearray<ubyte>(PGAGSize,PGAGData);
		}
		if (nodeConnections)
		{
			WriteSubrecord('PGRR',nodeConnectionCount * 2,f);
			f->writearray<ushort>(nodeConnectionCount,nodeConnections);
		}
		if (nodeCellConnections)
		{
			WriteSubrecord('PGRI',nodeCellConnectionCount * sizeof(PathGridCellConnection),f);
			f->writearray<PathGridCellConnection>(nodeCellConnectionCount,nodeCellConnections);
		}
		for (int i = 0;i < pointLinks.Count();i++)
		{
			WriteSubrecord('PGRL',(pointLinks[i].nodeCount * 4) + 4,f);
			f->write<formid>(pointLinks[i].linkedObject);
			f->writearray(pointLinks[i].nodeCount,pointLinks[i].nodes);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ComputeSubrecordSize(2);
		if (points)
		{
			size += ComputeSubrecordSize(pointCount * sizeof(Point));
		}
		if (PGAGData)
		{
			size += ComputeSubrecordSize(PGAGSize);
		}
		if (nodeConnections)
		{
			size += ComputeSubrecordSize(nodeConnectionCount * 2);
		}
		if (nodeCellConnections)
		{
			size += ComputeSubrecordSize(nodeCellConnectionCount * sizeof(PathGridCellConnection));
		}
		for (int i = 0;i < pointLinks.Count();i++)
		{
			size += ComputeSubrecordSize((pointLinks[i].nodeCount * 4) + 4);
		}
		return size;
	}
};
