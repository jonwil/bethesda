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
class FactionChangeRecord : public ChangeRecord
{
protected:
	ushort reactionCount;
	ReactionInfo *reactions;
	ubyte flags;
public:
	FactionChangeRecord(ChangeRecordHeader h,ESSFile *p) : ChangeRecord(h,p), reactionCount(0), reactions(0), flags(0)
	{
	}
	virtual ~FactionChangeRecord()
	{
		if (reactions)
		{
			delete[] reactions;
		}
	}
	virtual void Load(FileRead *f)
	{
		ChangeRecord::Load(f);
		if (header.flags & FactionReactions)
		{
			reactionCount = f->read<ushort>();
			reactions = new ReactionInfo[reactionCount];
			for (ushort i = 0;i < reactionCount;i++)
			{
				reactions[i].target = parent->GetFormID(f->read<iref>());
				reactions[i].reaction = f->read<ulong>();
			}
		}
		if (header.flags & FactionFlags)
		{
			flags = f->read<ubyte>();
		}
	}
	virtual void Save(FileWrite *f)
	{
		ChangeRecord::Save(f);
		if (header.flags & FactionReactions)
		{
			f->write<ushort>(reactionCount);
			for (ushort i = 0;i < reactionCount;i++)
			{
				f->write<iref>(parent->GetFormiRef(reactions[i].target));
				f->write<ulong>(reactions[i].reaction);
			}
		}
		if (header.flags & FactionFlags)
		{
			f->write<ubyte>(flags);
		}
	}
};
