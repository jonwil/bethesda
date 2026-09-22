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
struct QuestCondition
{
	ulong flags;
	float comparison;
	ulong functionIndex;
	ulong firstParameter;
	ulong secondParameter;
	ulong pad;
};
struct QuestEntry
{
	ubyte flags;
	SimpleDynVecClass<QuestCondition> stageConditions;
	char *logEntry;
	ulong schrUnk;
	ulong refCount;
	ulong compiledSize;
	ulong variableCount;
	ulong type;
	ulong compiledScriptSize;
	byte *compiledScript;
	ulong scriptTextSize;
	char *scriptText;
	SimpleDynVecClass<formid> globals;
	QuestEntry() : flags(0), stageConditions(0), logEntry(0), schrUnk(0), refCount(0), compiledSize(0), variableCount(0), type(0), compiledScriptSize(0), compiledScript(0), scriptTextSize(0), scriptText(0), globals(0)
	{
	}
};
struct QuestStageEntry
{
	ushort index;
	SimpleDynVecClass<QuestEntry *> questEntries;
	QuestStageEntry() : index(0), questEntries(0)
	{
	}
};
struct QuestTarget
{
	formid target;
	ulong flags;
	SimpleDynVecClass<QuestCondition> targetConditions;
};
class QuestForm : public Form
{
protected:
	char *editorID;
	formid script;
	char *fullName;
	char *icon;
	ubyte flags;
	ubyte priority;
	SimpleDynVecClass<QuestCondition> questConditions;
	SimpleDynVecClass<QuestStageEntry *> questStages;
	SimpleDynVecClass<QuestTarget *> questTargets;
	bool indexSeen;
	bool targetSeen;
public:
	QuestForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), icon(0), script(0), questConditions(0), indexSeen(false), targetSeen(false), questStages(0), questTargets(0)
	{
	}
	virtual ~QuestForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (icon)
		{
			delete[] icon;
		}
		for (int i = 0;i < questStages.Count();i++)
		{
			for (int j = 0;j < questStages[i]->questEntries.Count();j++)
			{
				delete questStages[i]->questEntries[j];
			}
			delete questStages[i];
		}
		for (int i = 0;i < questTargets.Count();i++)
		{
			delete questTargets[i];
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
			case 'SCRI':
				script = f->read<formid>();
				readSize += 4;
				break;
			case 'FULL':
				fullName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				flags = f->read<ubyte>();
				priority = f->read<ubyte>();
				readSize += 2;
				break;
			case 'CTDA':
				if (!indexSeen)
				{
					questConditions.Add(f->read<QuestCondition>());
				}
				else if (!targetSeen)
				{
					questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->stageConditions.Add(f->read<QuestCondition>());
				}
				else
				{
					questTargets[questTargets.Count() - 1]->targetConditions.Add(f->read<QuestCondition>());
				}
				readSize += sizeof(QuestCondition);
				break;
			case 'CTDT':
				if (!indexSeen)
				{
					questConditions.Add(f->read<QuestCondition>());
				}
				else if (!targetSeen)
				{
					questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->stageConditions.Add(f->read<QuestCondition>());
				}
				else
				{
					questTargets[questTargets.Count() - 1]->targetConditions.Add(f->read<QuestCondition>());
				}
				readSize += sizeof(QuestCondition);
				break;
			case 'INDX':
				{
					indexSeen = true;
					QuestStageEntry *s = new QuestStageEntry;
					s->index = f->read<ushort>();
					questStages.Add(s);
					readSize += 2;
				}
				break;
			case 'QSDT':
				{
					QuestEntry *q = new QuestEntry;
					q->flags = f->read<ubyte>();
					questStages[questStages.Count() - 1]->questEntries.Add(q);
					readSize += 1;
				}
				break;
			case 'CNAM':
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->logEntry = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SCHR':
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->schrUnk = f->read<ulong>();
				readSize += 4;
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->refCount = f->read<ulong>();
				readSize += 4;
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->compiledSize = f->read<ulong>();
				readSize += 4;
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->variableCount = f->read<ulong>();
				readSize += 4;
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->type = f->read<ulong>();
				readSize += 4;
				break;
			case 'SCDA':
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->compiledScriptSize = h.size;
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->compiledScript = f->readarray<byte>(h.size);
				readSize += h.size;
				break;
			case 'SCTX':
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->scriptTextSize = h.size;
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->scriptText = f->readarray<char>(h.size);
				readSize += h.size;
				break;
			case 'SCRO':
				questStages[questStages.Count() - 1]->questEntries[questStages[questStages.Count() - 1]->questEntries.Count() - 1]->globals.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'QSTA':
				{
					targetSeen = true;
					QuestTarget *t = new QuestTarget;
					t->target = f->read<formid>();
					readSize += 4;
					t->flags = f->read<ulong>();
					readSize += 4;
					questTargets.Add(t);
				}
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
		if (script)
		{
			WriteSubrecord('SCRI',4,f);
			f->write<formid>(script);
		}
		WriteZStringSubrecord('FULL',fullName,f);
		WriteZStringSubrecord('ICON',icon,f);
		WriteSubrecord('DATA',2,f);
		f->write<ubyte>(flags);
		f->write<ubyte>(priority);
		for (int i = 0;i < questConditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(QuestCondition),f);
			f->write<QuestCondition>(questConditions[i]);
		}
		for (int i = 0;i < questStages.Count();i++)
		{
			WriteSubrecord('INDX',2,f);
			f->write<ushort>(questStages[i]->index);
			for (int j = 0;j < questStages[i]->questEntries.Count();j++)
			{
				WriteSubrecord('QSDT',1,f);
				f->write<ubyte>(questStages[i]->questEntries[j]->flags);
				for (int k = 0;k < questStages[i]->questEntries[j]->stageConditions.Count();k++)
				{
					WriteSubrecord('CTDA',sizeof(QuestCondition),f);
					f->write<QuestCondition>(questStages[i]->questEntries[j]->stageConditions[k]);
				}
				WriteZStringSubrecord('CNAM',questStages[i]->questEntries[j]->logEntry,f);
				WriteSubrecord('SCHR',20,f);
				f->write<ulong>(questStages[i]->questEntries[j]->schrUnk);
				f->write<ulong>(questStages[i]->questEntries[j]->refCount);
				f->write<ulong>(questStages[i]->questEntries[j]->compiledSize);
				f->write<ulong>(questStages[i]->questEntries[j]->variableCount);
				f->write<ulong>(questStages[i]->questEntries[j]->type);
				if (questStages[i]->questEntries[j]->compiledScriptSize)
				{
					WriteSubrecord('SCDA',questStages[i]->questEntries[j]->compiledScriptSize,f);
					f->writearray<byte>(questStages[i]->questEntries[j]->compiledScriptSize,questStages[i]->questEntries[j]->compiledScript);
				}
				if (questStages[i]->questEntries[j]->scriptTextSize)
				{
					WriteSubrecord('SCTX',questStages[i]->questEntries[j]->scriptTextSize,f);
					f->writearray<char>(questStages[i]->questEntries[j]->scriptTextSize,questStages[i]->questEntries[j]->scriptText);
				}
				for (int k = 0;k < questStages[i]->questEntries[j]->globals.Count();k++)
				{
					WriteSubrecord('SCRO',4,f);
					f->write<formid>(questStages[i]->questEntries[j]->globals[k]);
				}
			}
		}
		for (int i = 0;i < questTargets.Count();i++)
		{
			WriteSubrecord('QSTA',8,f);
			f->write<formid>(questTargets[i]->target);
			f->write<ulong>(questTargets[i]->flags);
			for (int j = 0;j < questTargets[i]->targetConditions.Count();j++)
			{
				WriteSubrecord('CTDA',sizeof(QuestCondition),f);
				f->write<QuestCondition>(questTargets[i]->targetConditions[j]);
			}
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(icon);
		size += ComputeSubrecordSize(2);
		for (int i = 0;i < questConditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(QuestCondition));
		}
		for (int i = 0;i < questStages.Count();i++)
		{
			size += ComputeSubrecordSize(2);
			for (int j = 0;j < questStages[i]->questEntries.Count();j++)
			{
				size += ComputeSubrecordSize(1);
				for (int k = 0;k < questStages[i]->questEntries[j]->stageConditions.Count();k++)
				{
					size += ComputeSubrecordSize(sizeof(QuestCondition));
				}
				size += ZStringSubrecordSize(questStages[i]->questEntries[j]->logEntry);
				size += ComputeSubrecordSize(20);
				if (questStages[i]->questEntries[j]->compiledScriptSize)
				{
					size += ComputeSubrecordSize(questStages[i]->questEntries[j]->compiledScriptSize);
				}
				if (questStages[i]->questEntries[j]->scriptTextSize)
				{
					size += ComputeSubrecordSize(questStages[i]->questEntries[j]->scriptTextSize);
				}
				for (int k = 0;k < questStages[i]->questEntries[j]->globals.Count();k++)
				{
					size += ComputeSubrecordSize(4);
				}
			}
		}
		for (int i = 0;i < questTargets.Count();i++)
		{
			size += ComputeSubrecordSize(8);
			for (int j = 0;j < questTargets[i]->targetConditions.Count();j++)
			{
				size += ComputeSubrecordSize(sizeof(QuestCondition));
			}
		}
		return size;
	}
};
