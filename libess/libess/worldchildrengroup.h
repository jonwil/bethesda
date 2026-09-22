/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "exteriorblockgroup.h"
class WorldChildrenGroup
{
protected:
	ParentGroupHeader header;
	FormHeader roadHeader;
	Form *road;
	FormHeader cellHeader;
	Form *cell;
	ParentGroupHeader cellGroupHeader;
	CellChildGroup *cellGroup;
	SimpleDynVecClass<ExteriorCellHeader> groupHeaders;
	SimpleDynVecClass<ExteriorBlockGroup *> groups;
	ModFile *file;
public:
	WorldChildrenGroup(ParentGroupHeader h,ModFile *f) : header(h), file(f), groupHeaders(0), groups(0), road(0), cell(0), cellGroup(0)
	{
	}
	~WorldChildrenGroup()
	{
		for (int i = 0;i < groups.Count();i++)
		{
			delete groups[i];
		}
		groups.Delete_All();
	}
	void Load(FileRead *f)
	{
		int size = header.groupSize - 0x14;
		FormHeader h = f->read<FormHeader>();
		if (SwapBytes(h.type) == 'ROAD')
		{
			roadHeader = h;
			road = CreateForm(h,file);
			road->LoadCompressed(f);
			size -= sizeof(FormHeader);
			size -= h.dataSize;
		}
		else
		{
			f->unread(sizeof(FormHeader));
		}
		FormHeader h2 = f->read<FormHeader>();
		if (SwapBytes(h2.type) == 'CELL')
		{
			cellHeader = h2;
			cell = CreateForm(h2,file);
			cell->LoadCompressed(f);
			size -= sizeof(FormHeader);
			size -= h.dataSize;
			cellGroupHeader = f->read<ParentGroupHeader>();
			if (cellGroupHeader.groupType == 6)
			{
				cellGroup = new CellChildGroup(cellGroupHeader,file);
				cellGroup->Load(f);
				size -= cellGroupHeader.groupSize;
			}
			else
			{
				f->unread(sizeof(ParentGroupHeader));
			}
		}
		else
		{
			f->unread(sizeof(FormHeader));
		}
		while (size > 0)
		{
			ExteriorCellHeader h = f->read<ExteriorCellHeader>();
			ExteriorBlockGroup *gr = new ExteriorBlockGroup(h,file);
			gr->Load(f);
			groupHeaders.Add(h);
			groups.Add(gr);
			size -= h.groupSize;
		}
	}
	void Save(FileWrite *f)
	{
		if (road)
		{
			road->SaveCompressed(f);
		}
		if (cell)
		{
			cell->SaveCompressed(f);
			if (cellGroup)
			{
				f->write<ParentGroupHeader>(cellGroupHeader);
				cellGroup->Save(f);
			}
		}
		for (int i = 0;i < groups.Count();i++)
		{
			f->write<ExteriorCellHeader>(groupHeaders[i]);
			groups[i]->Save(f);
		}
	}
};