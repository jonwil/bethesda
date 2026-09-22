/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "fileread.h"
#include "filewrite.h"
class TypeGroup;
class TES4Form;
struct Master
{
	char *name;
	ubyte loadID;
};
class ModFile {
protected:
	FormHeader h;
	TES4Form *header;
	char *fname;
	SimpleDynVecClass<TypeGroupHeader> typeGroupHeaders;
	SimpleDynVecClass<TypeGroup *> typeGroups;
	SimpleDynVecClass<Master> masters;
public:
	ModFile();
	void Open(const char *path);
	void Save(const char *path);
	~ModFile();
	int GroupCount()
	{
		return typeGroups.Count();
	}
	TypeGroup *GetGroup(int pos)
	{
		return typeGroups[pos];
	}
	ubyte GetLoadID(ubyte index)
	{
		return masters[index].loadID;
	}
};
