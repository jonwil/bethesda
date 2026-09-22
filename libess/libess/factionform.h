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
struct FactionRelation
{
	formid faction;
	long mod;
};
struct FactionRank
{
	long rank;
	char *male;
	char *female;
	char *insignia;
	FactionRank() : rank(0), male(0), female(0), insignia(0)
	{
	}
};
class FactionForm : public Form
{
protected:
	char *editorID;
	char *name;
	SimpleDynVecClass<FactionRelation> relations;
	ubyte flags;
	float crimeGoldMultiplier;
	SimpleDynVecClass<FactionRank> ranks;
	bool cnam;
public:
	FactionForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), name(0), relations(0), flags(0), crimeGoldMultiplier(0), ranks(0), cnam(false)
	{
	}
	virtual ~FactionForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (name)
		{
			delete[] name;
		}
		for (int i = 0;i < ranks.Count();i++)
		{
			delete[] ranks[i].male;
			delete[] ranks[i].female;
			delete[] ranks[i].insignia;
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
			case 'FULL':
				name = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'XNAM':
				{
					FactionRelation r;
					r.faction = f->read<formid>();
					readSize += 4;
					r.mod = f->read<long>();
					readSize += 4;
					relations.Add(r);
				}
				break;
			case 'DATA':
				flags = f->read<ubyte>();
				readSize += 1;
				break;
			case 'CNAM':
				cnam = true;
				crimeGoldMultiplier = f->read<float>();
				readSize += 4;
				break;
			case 'RNAM':
				{
					FactionRank r;
					r.rank = f->read<long>();
					readSize += 4;
					ranks.Add(r);
				}
				break;
			case 'MNAM':
				{
					ranks[ranks.Count() - 1].male = f->readzstring(h.size);
					readSize += h.size;
				}
				break;
			case 'FNAM':
				{
					ranks[ranks.Count() - 1].female = f->readzstring(h.size);
					readSize += h.size;
				}
				break;
			case 'INAM':
				{
					ranks[ranks.Count() - 1].insignia = f->readzstring(h.size);
					readSize += h.size;
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
		WriteZStringSubrecord('FULL',name,f);
		for (int i = 0;i < relations.Count();i++)
		{
			WriteSubrecord('XNAM',8,f);
			f->write<formid>(relations[i].faction);
			f->write<long>(relations[i].mod);
		}
		WriteSubrecord('DATA',1,f);
		f->write<ubyte>(flags);
		if (cnam)
		{
			WriteSubrecord('CNAM',4,f);
			f->write<float>(crimeGoldMultiplier);
		}
		for (int i = 0;i < ranks.Count();i++)
		{
			WriteSubrecord('RNAM',4,f);
			f->write<long>(ranks[i].rank);
			WriteZStringSubrecord('MNAM',ranks[i].male,f);
			WriteZStringSubrecord('FNAM',ranks[i].female,f);
			WriteZStringSubrecord('INAM',ranks[i].insignia,f);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(name);
		for (int i = 0;i < relations.Count();i++)
		{
			size += ComputeSubrecordSize(8);
		}
		size += ComputeSubrecordSize(1);
		if (cnam)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < ranks.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ZStringSubrecordSize(ranks[i].male);
			size += ZStringSubrecordSize(ranks[i].female);
			size += ZStringSubrecordSize(ranks[i].insignia);
		}
		return size;
	}
};
