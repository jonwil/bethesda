/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "essfile.h"
enum ChangeRecordFlags
{
	FormFlags = 0x00000001,
	Created = 0x00000002,
	FactionFlags = 0x00000004,
	BookSkill = 0x00000004,
	BaseHealth = 0x00000004,
	QuestFlags = 0x00000004,
	Moved = 0x00000004,
	ItemValue = 0x00000008,
	FactionReactions = 0x00000008,
	BaseAttributes = 0x00000008,
	CellFlags = 0x00000008,
	HavokMoved = 0x00000008,
	BaseData = 0x00000010,
	CellName = 0x00000010,
	Scale = 0x00000010,
	SpellList = 0x00000020,
	CellOwnership = 0x00000020,
	AllExtra = 0x00000020,
	ActorFactions = 0x00000040,
	Lock = 0x00000040,
	ActorName = 0x00000080,
	RefrOwner = 0x00000080,
	CrimeGold = 0x00000080,
	AIData = 0x00000100,
	Global = 0x00000100,
	ActorSkill = 0x00000200,
	Rank = 0x00000200,
	CombatStyle = 0x00000400,
	MapMarkerFlags = 0x00000400,
	HadHavokMoveFlag = 0x00000800,
	PersuasionPercent = 0x00001000,
	InvestmentGold = 0x00002000,
	OblivionEntry = 0x00004000,
	EmptyFlag = 0x00010000,
	DroppedItemFlag = 0x00020000,
	DoorDefaultState = 0x00040000,
	Tresspass = 0x00040000,
	DoorState = 0x00080000,
	Teleport = 0x00100000,
	ExtraMagic = 0x00200000,
	FurnitureMarker = 0x00400000,
	OblivionFlag = 0x00800000,
	PathGrid = 0x01000000,
	MovementExtra = 0x01000000,
	WorldSpacePosition1 = 0x02000000,
	Animation = 0x02000000,
	WorldSpacePosition2 = 0x04000000,
	Script = 0x04000000,
	QuestScript = 0x08000000,
	DetatchTime = 0x08000000,
	Inventory = 0x08000000,
	QuestStages = 0x10000000,
	BaseModifiers = 0x10000000,
	SeenData = 0x10000000,
	LeveledCreature = 0x10000000,
	EnabledDisabled = 0x40000000,
	CellChanged = 0x80000000,
};
class ChangeRecord
{
protected:
	ChangeRecordHeader header;
	ulong formFlags;
	ESSFile *parent;
public:
	ChangeRecord(ChangeRecordHeader h,ESSFile *p) : header(h), formFlags(0), parent(p)
	{
	}
	virtual ~ChangeRecord()
	{
	}
	virtual void Load(FileRead *f)
	{
		if (header.flags & FormFlags)
		{
			formFlags = f->read<ulong>();
		}
	}
	virtual void Save(FileWrite *f)
	{
		if (header.flags & FormFlags)
		{
			f->write<ulong>(formFlags);
		}
	}
	virtual bool IsActor()
	{
		return false;
	}
	ulong GetFlags()
	{
		return header.flags;
	}
	friend class essfile;
};
ChangeRecord *CreateChangeRecord(ChangeRecordHeader header,ESSFile *p);
