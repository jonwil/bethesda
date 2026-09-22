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
struct DialogCondition
{
	ulong flags;
	float comparison;
	ulong functionIndex;
	ulong firstParameter;
	ulong secondParameter;
	ulong pad;
};
struct DialogConditionOld
{
	ulong flags;
	float comparison;
	ulong functionIndex;
	ulong firstParameter;
	ulong secondParameter;
};
struct DialogResponse
{
	ulong emotionType;
	ulong emotionValue;
	ulong unk1;
	ulong responseNumber;
	char *responseText;
	char *scriptNotes;
	DialogResponse() : emotionType(0), emotionValue(0), unk1(0), responseNumber(0), responseText(0), scriptNotes(0)
	{
	}
};
class DialogResponseForm : public Form
{
protected:
	char *editorID;
	ushort type;
	ubyte flags;
	formid quest;
	formid topic;
	bool previousResponseSeen;
	formid previousResponse;
	SimpleDynVecClass<formid> newTopics;
	SimpleDynVecClass<DialogResponse> responses;
	SimpleDynVecClass<DialogCondition> conditions;
	SimpleDynVecClass<DialogConditionOld> oldconditions;
	SimpleDynVecClass<formid> choices;
	SimpleDynVecClass<formid> linkFrom;
	ulong schrUnk;
	ulong refCount;
	ulong compiledSize;
	ulong variableCount;
	ulong scriptType;
	ulong compiledScriptSize;
	ulong schdsize;
	ulong schd1;
	ulong schd2;
	byte *compiledScript;
	ulong scriptTextSize;
	char *scriptText;
	SimpleDynVecClass<formid> references;
	bool smalldata;
public:
	DialogResponseForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), type(0), flags(0), quest(0), topic(0), newTopics(0), responses(0), conditions(0), choices(0), linkFrom(0), schrUnk(0), refCount(0), compiledSize(0), variableCount(0), scriptType(0), compiledScriptSize(0), compiledScript(0), scriptTextSize(0), scriptText(0), references(0), previousResponseSeen(false), oldconditions(0), schdsize(0), schd1(0), schd2(0), smalldata(false)
	{
	}
	virtual ~DialogResponseForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		for (int i = 0;i < responses.Count();i++)
		{
			delete[] responses[i].responseText;
			delete[] responses[i].scriptNotes;
		}
		if (compiledScript)
		{
			delete[] compiledScript;
		}
		if (scriptText)
		{
			delete[] scriptText;
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
			case 'DATA':
				type = f->read<ushort>();
				readSize += 2;
				if (h.size == 2)
				{
					smalldata = true;
				}
				else
				{
					flags = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'QSTI':
				quest = f->read<formid>();
				readSize += 4;
				break;
			case 'TPIC':
				topic = f->read<formid>();
				readSize += 4;
				break;
			case 'PNAM':
				previousResponseSeen = true;
				previousResponse = f->read<formid>();
				readSize += 4;
				break;
			case 'NAME':
				newTopics.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'TRDT':
				{
					DialogResponse r;
					r.emotionType = f->read<ulong>();
					readSize += 4;
					r.emotionValue = f->read<ulong>();
					readSize += 4;
					r.unk1 = f->read<ulong>();
					readSize += 4;
					r.responseNumber = f->read<ulong>();
					readSize += 4;
					responses.Add(r);
				}
				break;
			case 'NAM1':
				responses[responses.Count() - 1].responseText = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'NAM2':
				responses[responses.Count() - 1].scriptNotes = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'CTDA':
				conditions.Add(f->read<DialogCondition>());
				readSize += sizeof(DialogCondition);
				break;
			case 'CTDT':
				oldconditions.Add(f->read<DialogConditionOld>());
				readSize += sizeof(DialogConditionOld);
				break;
			case 'TCLT':
				choices.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'TCLF':
				linkFrom.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'SCHR':
				schrUnk = f->read<ulong>();
				readSize += 4;
				refCount = f->read<ulong>();
				readSize += 4;
				compiledSize = f->read<ulong>();
				readSize += 4;
				variableCount = f->read<ulong>();
				readSize += 4;
				scriptType = f->read<ulong>();
				readSize += 4;
				break;
			case 'SCHD':
				schdsize = h.size;
				schrUnk = f->read<ulong>();
				readSize += 4;
				refCount = f->read<ulong>();
				readSize += 4;
				compiledSize = f->read<ulong>();
				readSize += 4;
				variableCount = f->read<ulong>();
				readSize += 4;
				scriptType = f->read<ulong>();
				readSize += 4;
				schd1 = f->read<ulong>();
				readSize += 4;
				if (schdsize >= 0x1C)
				{
					schd2 = f->read<ulong>();
					readSize += 4;
				}
				break;
			case 'SCDA':
				compiledScriptSize = h.size;
				compiledScript = f->readarray<byte>(compiledScriptSize);
				readSize += h.size;
				break;
			case 'SCTX':
				scriptTextSize = h.size;
				scriptText = f->readarray<char>(scriptTextSize);
				readSize += h.size;
				break;
			case 'SCRO':
				references.Add(f->read<formid>());
				readSize += 4;
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
		if (!smalldata)
		{
			WriteSubrecord('DATA',3,f);
			f->write<ushort>(type);
			f->write<ubyte>(flags);
		}
		else
		{
			WriteSubrecord('DATA',2,f);
			f->write<ushort>(type);
		}
		if (quest)
		{
			WriteSubrecord('QSTI',4,f);
			f->write<formid>(quest);
		}
		if (topic)
		{
			WriteSubrecord('TPIC',4,f);
			f->write<formid>(topic);
		}
		if (previousResponseSeen)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<formid>(previousResponse);
		}
		for (int i = 0;i < newTopics.Count();i++)
		{
			WriteSubrecord('NAME',4,f);
			f->write<formid>(newTopics[i]);
		}
		for (int i = 0;i < responses.Count();i++)
		{
			WriteSubrecord('TRDT',16,f);
			f->write<ulong>(responses[i].emotionType);
			f->write<ulong>(responses[i].emotionValue);
			f->write<ulong>(responses[i].unk1);
			f->write<ulong>(responses[i].responseNumber);
			WriteZStringSubrecord('NAM1',responses[i].responseText,f);
			WriteZStringSubrecord('NAM2',responses[i].scriptNotes,f);
		}
		for (int i = 0;i < conditions.Count();i++)
		{
			WriteSubrecord('CTDA',sizeof(DialogCondition),f);
			f->write<DialogCondition>(conditions[i]);
		}
		for (int i = 0;i < oldconditions.Count();i++)
		{
			WriteSubrecord('CTDT',sizeof(DialogConditionOld),f);
			f->write<DialogConditionOld>(oldconditions[i]);
		}
		for (int i = 0;i < choices.Count();i++)
		{
			WriteSubrecord('TCLT',4,f);
			f->write<formid>(choices[i]);
		}
		for (int i = 0;i < linkFrom.Count();i++)
		{
			WriteSubrecord('TCLF',4,f);
			f->write<formid>(linkFrom[i]);
		}
		if (!schdsize)
		{
			WriteSubrecord('SCHR',20,f);
			f->write<ulong>(schrUnk);
			f->write<ulong>(refCount);
			f->write<ulong>(compiledSize);
			f->write<ulong>(variableCount);
			f->write<ulong>(scriptType);
		}
		else if (schdsize >= 0x1C)
		{
			WriteSubrecord('SCHD',28,f);
			f->write<ulong>(schrUnk);
			f->write<ulong>(refCount);
			f->write<ulong>(compiledSize);
			f->write<ulong>(variableCount);
			f->write<ulong>(scriptType);
			f->write<ulong>(schd1);
			f->write<ulong>(schd2);
		}
		else
		{
			WriteSubrecord('SCHD',24,f);
			f->write<ulong>(schrUnk);
			f->write<ulong>(refCount);
			f->write<ulong>(compiledSize);
			f->write<ulong>(variableCount);
			f->write<ulong>(scriptType);
			f->write<ulong>(schd1);
		}
		if (compiledScriptSize)
		{
			WriteSubrecord('SCDA',compiledScriptSize,f);
			f->writearray<byte>(compiledScriptSize,compiledScript);
		}
		if (scriptTextSize)
		{
			WriteSubrecord('SCTX',scriptTextSize,f);
			f->writearray<char>(scriptTextSize,scriptText);
		}
		for (int i = 0;i < references.Count();i++)
		{
			WriteSubrecord('SCRO',4,f);
			f->write<formid>(references[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		if (!smalldata)
		{
			size += ComputeSubrecordSize(3);
		}
		else
		{
			size += ComputeSubrecordSize(2);
		}
		if (quest)
		{
			size += ComputeSubrecordSize(4);
		}
		if (topic)
		{
			size += ComputeSubrecordSize(4);
		}
		if (previousResponseSeen)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < newTopics.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < responses.Count();i++)
		{
			size += ComputeSubrecordSize(16);
			size += ZStringSubrecordSize(responses[i].responseText);
			size += ZStringSubrecordSize(responses[i].scriptNotes);
		}
		for (int i = 0;i < conditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(DialogCondition));
		}
		for (int i = 0;i < oldconditions.Count();i++)
		{
			size += ComputeSubrecordSize(sizeof(DialogConditionOld));
		}
		for (int i = 0;i < choices.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < linkFrom.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		if (!schdsize)
		{
			size += ComputeSubrecordSize(20);
		}
		else if (schdsize >= 0x1C)
		{
			size += ComputeSubrecordSize(28);
		}
		else
		{
			size += ComputeSubrecordSize(24);
		}
		if (compiledScriptSize)
		{
			size += ComputeSubrecordSize(compiledScriptSize);
		}
		if (scriptTextSize)
		{
			size += ComputeSubrecordSize(scriptTextSize);
		}
		for (int i = 0;i < references.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
