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
#include "cellform.h"
struct IntSeenData
{
	ubyte seenBits[32];
	byte cellGridX;
	byte cellGridY;
	IntSeenData *next;
	~IntSeenData()
	{
		if (next)
		{
			delete next;
		}
	}
};
class CellChangeRecord : public ChangeRecord
{
protected:
	ulong detatchTime;
	ubyte cellFlags;
	char *fullName;
	formid owner;
	ushort pathGridCount;
	ushort *pathGridPoints;
	formid worldSpace;
	short cellXCoord;
	short cellYCoord;
	ubyte extSeenBits[32];
	ushort index;
	IntSeenData *intdata;
public:
	CellChangeRecord(ChangeRecordHeader h,ESSFile *p) : ChangeRecord(h,p), detatchTime(0), cellFlags(0), fullName(0), owner(0), pathGridCount(0), pathGridPoints(0), worldSpace(0), cellXCoord(0), cellYCoord(0), intdata(0), index(0)
	{
	}
	virtual ~CellChangeRecord()
	{
		if (fullName)
		{
			delete[] fullName;
		}
		if (pathGridPoints)
		{
			delete[] pathGridPoints;
		}
		if (intdata)
		{
			delete[] intdata;
		}
	}
	virtual void Load(FileRead *f)
	{
		if (header.flags & WorldSpacePosition2)
		{
			worldSpace = parent->GetWorldSpaceFormID(f->read<ushort>());
			cellXCoord = f->read<byte>();
			cellYCoord = f->read<byte>();
		}
		else if (header.flags & WorldSpacePosition1)
		{
			worldSpace = parent->GetWorldSpaceFormID(f->read<ushort>());
			cellXCoord = f->read<short>();
			cellYCoord = f->read<short>();
		}
		if (header.flags & DetatchTime)
		{
			detatchTime = f->read<ulong>();
		}
		ChangeRecord::Load(f);
		if (header.flags & CellFlags)
		{
			cellFlags = f->read<ubyte>();
		}
		if (header.flags & SeenData)
		{
			bool interior = false;
			Form *fo = FindForm(header.id);
			if (fo && SwapBytes(fo->Get_Header().type) == 'CELL')
			{
				CellForm *c = (CellForm *)fo;
				if (c->GetFlags() & 1)
				{
					interior = true;
				}
			}
			else if (!worldSpace)
			{
				interior = true;
			}
			if (interior)
			{
				intdata = new IntSeenData;
				IntSeenData *d = intdata;
				for (int i = 0;i < 32;i++)
				{
					intdata->seenBits[i] = f->read<ubyte>();
				}
				index = f->read<ushort>();
				intdata->cellGridX = f->read<byte>();
				intdata->cellGridY = f->read<byte>();
				for (ushort i = 0;i < index - 1;i++)
				{
					d->next = new IntSeenData;
					d = d->next;
					for (int i = 0;i < 32;i++)
					{
						d->seenBits[i] = f->read<ubyte>();
					}
					d->cellGridX = f->read<byte>();
					d->cellGridY = f->read<byte>();
				}
			}
			else
			{
				for (int i = 0;i < 32;i++)
				{
					extSeenBits[i] = f->read<ubyte>();
				}
			}
		}
		if (header.flags & CellName)
		{
			fullName = f->readbstring();
		}
		if (header.flags & CellOwnership)
		{
			owner = parent->GetFormID(f->read<iref>());
		}
		if (header.flags & PathGrid)
		{
			pathGridCount = f->read<ushort>();
			if (pathGridCount)
			{
				pathGridPoints = f->readarray<ushort>(pathGridCount);
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		if (header.flags & WorldSpacePosition2)
		{
			f->write<ushort>(parent->GetWorldSpaceFormiRef(worldSpace));
			f->write<byte>((byte)cellXCoord);
			f->write<byte>((byte)cellYCoord);
		}
		else if (header.flags & WorldSpacePosition1)
		{
			f->write<ushort>(parent->GetWorldSpaceFormiRef(worldSpace));
			f->write<short>(cellXCoord);
			f->write<short>(cellYCoord);
		}
		if (header.flags & DetatchTime)
		{
			f->write<ulong>(detatchTime);
		}
		ChangeRecord::Save(f);
		if (header.flags & CellFlags)
		{
			f->write<ubyte>(cellFlags);
		}
		if (header.flags & SeenData)
		{
			bool interior = false;
			Form *fo = FindForm(header.id);
			if (fo && SwapBytes(fo->Get_Header().type) == 'CELL')
			{
				CellForm *c = (CellForm *)fo;
				if (c->GetFlags() & 1)
				{
					interior = true;
				}
			}
			else if (!worldSpace)
			{
				interior = true;
			}
			if (interior)
			{
				IntSeenData *d = intdata;
				for (int i = 0;i < 32;i++)
				{
					f->write<ubyte>(intdata->seenBits[i]);
				}
				f->write<ushort>(index);
				f->write<byte>(intdata->cellGridX);
				f->write<byte>(intdata->cellGridY);
				for (ushort i = 0;i < index - 1;i++)
				{
					d = d->next;
					for (int i = 0;i < 32;i++)
					{
						f->write<ubyte>(d->seenBits[i]);
					}
					f->write<byte>(d->cellGridX);
					f->write<byte>(d->cellGridY);
				}
			}
			else
			{
				for (int i = 0;i < 32;i++)
				{
					f->write<ubyte>(extSeenBits[i]);
				}
			}
		}
		if (header.flags & CellName)
		{
			f->writebstring(fullName);
		}
		if (header.flags & CellOwnership)
		{
			f->write<iref>(parent->GetFormiRef(owner));
		}
		if (header.flags & PathGrid)
		{
			f->write<ushort>(pathGridCount);
			if (pathGridCount)
			{
				f->writearray<ushort>(pathGridCount,pathGridPoints);
			}
		}
	}
};
