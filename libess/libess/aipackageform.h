/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "form.h"
struct AIPackageCondition
{
	ulong flags;
	float comparison;
	ulong functionIndex;
	ulong firstParameter;
	ulong secondParameter;
	ulong pad;
};
struct AIPackageConditionOld
{
	ulong flags;
	float comparison;
	ulong functionIndex;
	ulong firstParameter;
	ulong secondParameter;
};
class AIPackageForm : public Form
{
protected:
	char *editorID;
	ulong packageFlags;
	ulong packageType;
	bool locationSeen;
	ulong locationType;
	ulong locationValue;
	ulong locationRadius;
	ubyte month;
	ubyte day;
	ubyte date;
	ubyte time;
	long duration;
	bool targetSeen;
	ulong targetType;
	ulong targetValue;
	ulong targetCount;
	SimpleDynVecClass<AIPackageCondition> conditions;
	SimpleDynVecClass<AIPackageConditionOld> oldconditions;
	bool haspkdt;
	bool haspsdt;
	bool smallpkdt;
public:
	AIPackageForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), packageFlags(0), packageType(0), locationSeen(0), locationType(0), locationValue(0), locationRadius(0), month(0), day(0), date(0), time(0), duration(0), targetSeen(0), targetType(0), targetValue(0), targetCount(0), conditions(0), haspkdt(false), haspsdt(false), oldconditions(0), smallpkdt(false)
	{
	}
	virtual ~AIPackageForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
	}
protected:
	virtual void Load(FileRead *f)
	{
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			case 'EDID':
				editorID = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'PKDT':
				haspkdt = true;
				packageFlags = f->read<ulong>();
				readSize += 4;
				if (h.size == 4)
				{
					smallpkdt = true;
				}
				else
				{
					packageType = f->read<ulong>();
					readSize += 4;
				}
				break;
			case 'PLDT':
				locationSeen = true;
				locationType = f->read<ulong>();
				readSize += 4;
				locationValue = f->read<ulong>();
				readSize += 4;
				locationRadius = f->read<ulong>();
				readSize += 4;
				break;
			case 'PSDT':
				haspsdt = true;
				month = f->read<ubyte>();
				readSize += 1;
				day = f->read<ubyte>();
				readSize += 1;
				date = f->read<ubyte>();
				readSize += 1;
				time = f->read<ubyte>();
				readSize += 1;
				duration = f->read<ulong>();
				readSize += 4;
				break;
			case 'PTDT':
				targetSeen = true;
				targetType = f->read<ulong>();
				readSize += 4;
				targetValue = f->read<ulong>();
				readSize += 4;
				targetCount = f->read<ulong>();
				readSize += 4;
				break;
			case 'CTDA':
				conditions.Add(f->read<AIPackageCondition>());
				readSize += sizeof(AIPackageCondition);
				break;
			case 'CTDT':
				oldconditions.Add(f->read<AIPackageConditionOld>());
				readSize += sizeof(AIPackageConditionOld);
				break;
			default:
				printf("Unknown subrecord found");
				__debugbreak();
				break;
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		WriteZStringSubrecord('EDID',editorID,f);
		if (haspkdt)
		{
			if (smallpkdt)
			{
				WriteSubrecord('PKDT',4,f);
				f->write<ulong>(packageFlags);			
			}
			else
			{
				WriteSubrecord('PKDT',8,f);
				f->write<ulong>(packageFlags);
				f->write<ulong>(packageType);
			}
		}
		if (locationSeen)
		{
			WriteSubrecord('PLDT',12,f);
			f->write<ulong>(locationType);
			f->write<ulong>(locationValue);
			f->write<ulong>(locationRadius);
		}
		if (haspsdt)
		{
			WriteSubrecord('PSDT',8,f);
			f->write<ubyte>(month);
			f->write<ubyte>(day);
			f->write<ubyte>(date);
			f->write<ubyte>(time);
			f->write<ulong>(duration);
		}
		if (targetSeen)
		{
			WriteSubrecord('PTDT',12,f);
			f->write<ulong>(targetType);
			f->write<ulong>(targetValue);
			f->write<ulong>(targetCount);
		}
		for (int i = 0;i < conditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(AIPackageCondition),f);
			f->write<AIPackageCondition>(conditions[i]);
		}
		for (int i = 0;i < oldconditions.Count();i++)
		{
			WriteSubrecord('CTDT',sizeof(AIPackageConditionOld),f);
			f->write<AIPackageConditionOld>(oldconditions[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		if (haspkdt)
		{
			if (smallpkdt)
			{
				size += ComputeSubrecordSize(4);
			}
			else
			{
				size += ComputeSubrecordSize(8);
			}
		}
		if (locationSeen)
		{
			size += ComputeSubrecordSize(12);
		}
		if (haspsdt)
		{
			size += ComputeSubrecordSize(8);
		}
		if (targetSeen)
		{
			size += ComputeSubrecordSize(12);
		}
		for (int i = 0;i < conditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(AIPackageCondition));
		}
		for (int i = 0;i < oldconditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(AIPackageConditionOld));
		}
		return size;
	}
};
