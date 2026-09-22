/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "exteriorsubblockgroup.h"
class ExteriorBlockGroup
{
protected:
	ExteriorCellHeader header;
	SimpleDynVecClass<ExteriorCellHeader> groupHeaders;
	SimpleDynVecClass<ExteriorSubBlockGroup *> groups;
	ModFile *file;
public:
	ExteriorBlockGroup(ExteriorCellHeader h,ModFile *f) : header(h), file(f), groupHeaders(0), groups(0)
	{
	}
	~ExteriorBlockGroup()
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
		while (size > 0)
		{
			ExteriorCellHeader h = f->read<ExteriorCellHeader>();
			ExteriorSubBlockGroup *gr = new ExteriorSubBlockGroup(h,file);
			gr->Load(f);
			groupHeaders.Add(h);
			groups.Add(gr);
			size -= h.groupSize;
		}
	}
	void Save(FileWrite *f)
	{
		for (int i = 0;i < groups.Count();i++)
		{
			f->write<ExteriorCellHeader>(groupHeaders[i]);
			groups[i]->Save(f);
		}
	}
};
