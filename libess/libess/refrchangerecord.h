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
#include "extradata.h"
struct InventoryItem
{
	formid item;
	ulong stackedItemsNum;
	SimpleDynVecClass<ExtraDataList *> changedEntries;
	InventoryItem() : changedEntries(0)
	{
	}
};
class RefrChangeRecord : public ChangeRecord
{
protected:
	ubyte *data;
	CreatedData created;
	MovedData moved;
	ChangedData changed;
	formid oblivionFlag;
	SimpleDynVecClass<InventoryItem *> inventory;
	ExtraDataList *properties;
	ushort animationSize;
	byte *animationData;
	ushort havocSize;
	byte *havocData;
	float scale;
	bool hasProcess;
	ubyte processType;
public:
	RefrChangeRecord(ChangeRecordHeader h,ESSFile *p) : ChangeRecord(h,p), data(0), inventory(0), animationSize(0), animationData(0), hasProcess(false), processType(0xFF)
	{
		created.flags = 3;
	}
	virtual ~RefrChangeRecord()
	{
		if (data)
		{
			delete[] data;
		}
		for (int i = 0;i < inventory.Count();i++)
		{
			for (int j = 0;j < inventory[i]->changedEntries.Count();j++)
			{
				delete inventory[i]->changedEntries[j];
			}
			delete inventory[i];
		}
		if (properties)
		{
			delete properties;
		}
		if (animationData)
		{
			delete[] animationData;
		}
		if (havocData)
		{
			delete[] havocData;
		}
	}
	virtual void PreLoadData(FileRead *f)
	{
		if (header.flags & Created)
		{
			created = f->read<CreatedData>();
			if (created.flags != 2)
			{
				created.baseItem = parent->GetFormID(created.baseItem);
			}
			created.data.cell = parent->GetFormID(created.data.cell);
		}
		else if ((header.flags & Moved) || (header.flags & HavokMoved))
		{
			if (header.flags & CellChanged)
			{
				changed = f->read<ChangedData>();
				changed.cell = parent->GetFormID(changed.cell);
				changed.data.cell = parent->GetFormID(changed.data.cell);
			}
			else
			{
				moved = f->read<MovedData>();
				moved.cell = parent->GetFormID(moved.cell);
			}
		}
		else
		{
			if (header.flags & OblivionFlag)
			{
				oblivionFlag = parent->GetFormID(f->read<iref>());
			}
		}
		LoadData(f);
	}
	virtual void LoadData(FileRead *f)
	{
		switch (created.flags)
		{
		case 1:
		case 2:
			hasProcess = true;
			processType = f->read<ubyte>();
			break;
		case 3:
		case 0:
			break;
		default:
			printf("Unknown refr tyype found");
			__debugbreak();
			break;
		}
		ChangeRecord::Load(f);
		if (header.flags & Inventory)
		{
			ushort itemNum = f->read<ushort>();
			for (ushort i = 0;i < itemNum;i++)
			{
				InventoryItem *item = new InventoryItem();
				item->item = parent->GetFormID(f->read<iref>());
				item->stackedItemsNum = f->read<ulong>();
				ulong changedEntriesNum = f->read<ulong>();
				for (ulong j = 0;j < changedEntriesNum;j++)
				{
					ExtraDataList *d = new ExtraDataList();
					d->Load(f,32,0,parent);
					item->changedEntries.Add(d);
				}
				inventory.Add(item);
			}
		}
		if ((header.flags & 0x177577E0) || (IsActor()))
		{
			properties = new ExtraDataList();
			properties->Load(f,header.flags,this,parent);
		}
		if ((header.flags & Animation) && !IsActor())
		{
			animationSize = f->read<ushort>();
			animationData = f->readarray<byte>(animationSize);
		}
		if ((header.flags & HavokMoved) || (header.flags & HadHavokMoveFlag))
		{
			havocSize = f->read<ushort>();
			havocData = f->readarray<byte>(havocSize);
		}
		if (header.flags & Scale)
		{
			scale = f->read<float>();
		}
		if (hasProcess)
		{
			switch (processType)
			{
			case 0:
				//read HighProcess data
				break;
			case 1:
				//read MediumHighProcess data;
				break;
			case 2:
				//read MediumLowProcess data;
				break;
			case 3:
				//read LowProcess data;
				break;
			case 0xFF:
				break;
			default:
				printf("Unknown process tyype found");
				__debugbreak();
				break;
			}
		}
		switch (created.flags)
		{
		case 1:
			//read ArrowProjectile data
			break;
		case 2:
			switch (created.baseItem)
			{
			case 0:
				//read MagicBallProjectile data
				break;
			case 1:
				//read MagicBoltProjectile data
				break;
			case 3:
				//read MagicFogProjectile data
				break;
			default:
				printf("Unknown projectile tyype found");
				__debugbreak();
				break;
			}
			break;
		}
	}
	virtual void Load(FileRead *f)
	{
		if (header.dataSize)
		{
			data = f->readarray<ubyte>(header.dataSize);
			f->SetCompressed(data);
		}
		//PreLoadData(f);
		if (header.dataSize)
		{
			f->ClearCompressed();
		}
	}
	virtual void Save(FileWrite *f)
	{
		if (header.dataSize)
		{
			f->writearray<ubyte>(header.dataSize,data);
		}
	}
};
