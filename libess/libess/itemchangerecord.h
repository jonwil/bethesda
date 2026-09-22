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
class ItemChangeRecord : public ChangeRecord
{
protected:
	float value;
public:
	ItemChangeRecord(ChangeRecordHeader h,ESSFile *p) : ChangeRecord(h,p), value(0)
	{
	}
	virtual ~ItemChangeRecord()
	{
	}
	virtual void Load(FileRead *f)
	{
		ChangeRecord::Load(f);
		if (header.flags & ItemValue)
		{
			value = f->read<float>();
		}
	}
	virtual void Save(FileWrite *f)
	{
		ChangeRecord::Save(f);
		if (header.flags & ItemValue)
		{
			f->write<float>(value);
		}
	}
};
