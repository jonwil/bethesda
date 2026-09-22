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
class QuestChangeRecord : public ChangeRecord
{
protected:
	ubyte questFlags;
	ubyte questStageCount;
	QuestStage *questStages;
	ushort scriptVarCount;
	ScriptVar *scriptVars;
	ubyte effectInfoPresent;
	ScriptEffectInfo effectInfo;
public:
	QuestChangeRecord(ChangeRecordHeader h,ESSFile *p) : ChangeRecord(h,p), questFlags(0), questStageCount(0), questStages(0), scriptVarCount(0), scriptVars(0)
	{
	}
	virtual ~QuestChangeRecord()
	{
		if (questStages)
		{
			for (ubyte i = 0;i < questStageCount;i++)
			{
				if (questStages[i].items)
				{
					delete[] questStages[i].items;
				}
			}
			delete[] questStages;
		}
		if (scriptVars)
		{
			delete[] scriptVars;
		}
	}
	virtual void Load(FileRead *f)
	{
		ChangeRecord::Load(f);
		if (header.flags & QuestFlags)
		{
			questFlags = f->read<ubyte>();
		}
		if (header.flags & QuestStages)
		{
			questStageCount = f->read<ubyte>();
			if (questStageCount)
			{
				questStages = new QuestStage[questStageCount];
				for (ubyte i = 0;i < questStageCount;i++)
				{
					questStages[i].index = f->read<ubyte>();
					questStages[i].flags = f->read<ubyte>();
					questStages[i].itemCount = f->read<ubyte>();
					questStages[i].items = 0;
					if (questStages[i].itemCount)
					{
						questStages[i].items = new QuestStageItem[questStages[i].itemCount];
						for (ubyte j = 0;j < questStages[i].itemCount;j++)
						{
							questStages[i].items[j].index = f->read<ubyte>();
							questStages[i].items[j].dayOfYear = f->read<ushort>();
							questStages[i].items[j].year = f->read<ushort>();
						}
					}
				}
			}
		}
		if (header.flags & QuestScript)
		{
			scriptVarCount = f->read<ushort>();
			if (scriptVarCount)
			{
				scriptVars = new ScriptVar[scriptVarCount];
				for (ushort i = 0;i < scriptVarCount;i++)
				{
					scriptVars[i].flags = f->read<ulong>();
					if (scriptVars[i].flags & 0xF0000000)
					{
						scriptVars[i].id = parent->GetFormID(f->read<iref>());
					}
					else
					{
						scriptVars[i].value = f->read<double>();
					}
				}
			}
			effectInfoPresent = f->read<ubyte>();
			if (effectInfoPresent)
			{
				effectInfo = f->read<ScriptEffectInfo>();
			}
		}
	}
	virtual void Save(FileWrite *f)
	{
		ChangeRecord::Save(f);
		if (header.flags & QuestFlags)
		{
			f->write<ubyte>(questFlags);
		}
		if (header.flags & QuestStages)
		{
			f->write<ubyte>(questStageCount);
			if (questStageCount)
			{
				for (ubyte i = 0;i < questStageCount;i++)
				{
					f->write<ubyte>(questStages[i].index);
					f->write<ubyte>(questStages[i].flags);
					f->write<ubyte>(questStages[i].itemCount);
					if (questStages[i].itemCount)
					{
						for (ubyte j = 0;j < questStages[i].itemCount;j++)
						{
							f->write<ubyte>(questStages[i].items[j].index);
							f->write<ushort>(questStages[i].items[j].dayOfYear);
							f->write<ushort>(questStages[i].items[j].year);
						}
					}
				}
			}
		}
		if (header.flags & QuestScript)
		{
			f->write<ushort>(scriptVarCount);
			if (scriptVarCount)
			{
				for (ushort i = 0;i < scriptVarCount;i++)
				{
					f->write<ulong>(scriptVars[i].flags);
					if (scriptVars[i].flags & 0xF0000000)
					{
						f->write<iref>(parent->GetFormiRef(scriptVars[i].id));
					}
					else
					{
						f->write<double>(scriptVars[i].value);
					}
				}
			}
			f->write<ubyte>(effectInfoPresent);
			if (effectInfoPresent)
			{
				f->write<ScriptEffectInfo>(effectInfo);
			}
		}
	}
};
