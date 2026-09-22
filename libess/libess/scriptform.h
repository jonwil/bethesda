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
struct VariableRef
{
	ulong index;
	ulong unk1;
	ulong unk2;
	ulong unk3;
	ulong type;
	ulong unk4;
	char *name;
};
struct ScriptRef
{
	ulong type;
	ulong item;
};
class ScriptForm : public Form
{
protected:
	char *editorID;
	ulong schrUnk;
	ulong refCount;
	ulong compiledSize;
	ulong variableCount;
	ulong type;
	ulong compiledScriptSize;
	byte *compiledScript;
	ulong scriptTextSize;
	char *scriptText;
	SimpleDynVecClass<VariableRef> variables;
	SimpleDynVecClass<ScriptRef> references;
public:
	ScriptForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), schrUnk(0), refCount(0), compiledSize(0), variableCount(0), type(0), compiledScriptSize(0), compiledScript(0), scriptTextSize(0), scriptText(0), variables(0), references(0)
	{
	}
	virtual ~ScriptForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (compiledScript)
		{
			delete[] compiledScript;
		}
		if (scriptText)
		{
			delete[] scriptText;
		}
		for (int i = 0;i < variables.Count();i++)
		{
			delete[] variables[i].name;
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
			case 'SCHR':
				schrUnk = f->read<ulong>();
				readSize += 4;
				refCount = f->read<ulong>();
				readSize += 4;
				compiledSize = f->read<ulong>();
				readSize += 4;
				variableCount = f->read<ulong>();
				readSize += 4;
				type = f->read<ulong>();
				readSize += 4;
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
			case 'SLSD':
				{
					VariableRef r;
					r.index = f->read<ulong>();
					readSize += 4;
					r.unk1 = f->read<ulong>();
					readSize += 4;
					r.unk2 = f->read<ulong>();
					readSize += 4;
					r.unk3 = f->read<ulong>();
					readSize += 4;
					r.type = f->read<ulong>();
					readSize += 4;
					r.unk4 = f->read<ulong>();
					readSize += 4;
					variables.Add(r);
				}
				break;
			case 'SCVR':
				variables[variables.Count() - 1].name = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SCRV':
			case 'SCRO':
				{
					ScriptRef r;
					r.type = h.type;
					r.item = f->read<ulong>();
					references.Add(r);
					readSize += 4;
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
		WriteSubrecord('SCHR',20,f);
		f->write<ulong>(schrUnk);
		f->write<ulong>(refCount);
		f->write<ulong>(compiledSize);
		f->write<ulong>(variableCount);
		f->write<ulong>(type);
		WriteSubrecord('SCDA',compiledScriptSize,f);
		f->writearray<byte>(compiledScriptSize,compiledScript);
		WriteSubrecord('SCTX',scriptTextSize,f);
		f->writearray<char>(scriptTextSize,scriptText);
		for (int i = 0;i < variables.Count();i++)
		{
			WriteSubrecord('SLSD',24,f);
			f->write<ulong>(variables[i].index);
			f->write<ulong>(variables[i].unk1);
			f->write<ulong>(variables[i].unk2);
			f->write<ulong>(variables[i].unk3);
			f->write<ulong>(variables[i].type);
			f->write<ulong>(variables[i].unk4);
			WriteZStringSubrecord('SCVR',variables[i].name,f);
		}
		for (int i = 0;i < references.Count();i++)
		{
			WriteSubrecord(references[i].type,4,f);
			f->write<ulong>(references[i].item);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ComputeSubrecordSize(20);
		size += ComputeSubrecordSize(compiledScriptSize);
		size += ComputeSubrecordSize(scriptTextSize);
		for (int i = 0;i < variables.Count();i++)
		{
			size += ComputeSubrecordSize(24);
			size += ZStringSubrecordSize(variables[i].name);
		}
		for (int i = 0;i < references.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		return size;
	}
};
