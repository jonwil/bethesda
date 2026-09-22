/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "changerecord.h"
class UnparsedChangeRecord : public ChangeRecord
{
protected:
	ubyte *data;
public:
	UnparsedChangeRecord(ChangeRecordHeader h,ESSFile *p) : ChangeRecord(h,p), data(0)
	{
	}
	virtual ~UnparsedChangeRecord()
	{
		if (data)
		{
			delete[] data;
		}
	}
	virtual void Load(FileRead *f)
	{
		data = f->readarray<ubyte>(header.dataSize);
	}
	virtual void Save(FileWrite *f)
	{
		f->writearray<ubyte>(header.dataSize,data);
	}
};
