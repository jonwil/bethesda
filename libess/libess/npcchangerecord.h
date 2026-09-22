/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "actorbasechangerecord.h"
class NPCChangeRecord : public ActorBaseChangeRecord
{
protected:
	ubyte *skillLevels;
	formid combatStyle;
public:
	NPCChangeRecord(ChangeRecordHeader h,ESSFile *p) : ActorBaseChangeRecord(h,p), skillLevels(0), combatStyle(0)
	{
	}
	virtual ~NPCChangeRecord()
	{
		if (skillLevels)
		{
			delete[] skillLevels;
		}
	}
	virtual void Load(FileRead *f)
	{
		ActorBaseChangeRecord::Load(f);
		if (header.flags & ActorSkill)
		{
			skillLevels = f->readarray<ubyte>(21);
		}
		if (header.flags & CombatStyle)
		{
			combatStyle = parent->GetFormID(f->read<iref>());
		}
	}
	virtual void Save(FileWrite *f)
	{
		ActorBaseChangeRecord::Save(f);
		if (header.flags & ActorSkill)
		{
			f->writearray<ubyte>(21,skillLevels);
		}
		if (header.flags & CombatStyle)
		{
			f->write<iref>(parent->GetFormiRef(combatStyle));
		}
	}
};
