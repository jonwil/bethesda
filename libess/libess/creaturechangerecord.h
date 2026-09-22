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
class CreatureChangeRecord : public ActorBaseChangeRecord
{
protected:
	ubyte combatSkill;
	ubyte magicSkill;
	ubyte stealthSkill;
	formid combatStyle;
public:
	CreatureChangeRecord(ChangeRecordHeader h,ESSFile *p) : ActorBaseChangeRecord(h,p), combatSkill(0), magicSkill(0), stealthSkill(0), combatStyle(0)
	{
	}
	virtual ~CreatureChangeRecord()
	{
	}
	virtual void Load(FileRead *f)
	{
		ActorBaseChangeRecord::Load(f);
		if (header.flags & ActorSkill)
		{
			combatSkill = f->read<ubyte>();
			magicSkill = f->read<ubyte>();
			stealthSkill = f->read<ubyte>();
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
			f->write<ubyte>(combatSkill);
			f->write<ubyte>(magicSkill);
			f->write<ubyte>(stealthSkill);
		}
		if (header.flags & CombatStyle)
		{
			f->write<iref>(parent->GetFormiRef(combatStyle));
		}
	}
};
