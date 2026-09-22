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
struct SkillData
{
	long action;
	long attribute;
	ulong specalization;
	float use0;
	float use1;
};
class SkillForm : public Form
{
protected:
	char *editorID;
	long skillIndex;
	char *description;
	char *icon;
	SkillData data;
	char *apprentice;
	char *journeyman;
	char *expert;
	char *master;
public:
	SkillForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), icon(0), description(0), apprentice(0), journeyman(0), expert(0), master(0)
	{
	}
	virtual ~SkillForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (apprentice)
		{
			delete[] apprentice;
		}
		if (journeyman)
		{
			delete[] journeyman;
		}
		if (expert)
		{
			delete[] expert;
		}
		if (master)
		{
			delete[] master;
		}
		if (icon)
		{
			delete[] icon;
		}
		if (description)
		{
			delete[] description;
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
			case 'INDX':
				skillIndex = f->read<long>();
				readSize += 4;
				break;
			case 'DESC':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				data = f->read<SkillData>();
				readSize += sizeof(SkillData);
				break;
			case 'ANAM':
				apprentice = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'JNAM':
				journeyman = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'ENAM':
				expert = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MNAM':
				master = f->readzstring(h.size);
				readSize += h.size;
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
		WriteSubrecord('INDX',4,f);
		f->write<long>(skillIndex);
		WriteZStringSubrecord('DESC',description,f);
		WriteZStringSubrecord('ICON',icon,f);
		WriteSubrecord('DATA',sizeof(SkillData),f);
		f->write<SkillData>(data);
		WriteZStringSubrecord('ANAM',apprentice,f);
		WriteZStringSubrecord('JNAM',journeyman,f);
		WriteZStringSubrecord('ENAM',expert,f);
		WriteZStringSubrecord('MNAM',master,f);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ComputeSubrecordSize(4);
		size += ZStringSubrecordSize(description);
		size += ZStringSubrecordSize(icon);
		size += ComputeSubrecordSize(sizeof(SkillData));
		size += ZStringSubrecordSize(apprentice);
		size += ZStringSubrecordSize(journeyman);
		size += ZStringSubrecordSize(expert);
		size += ZStringSubrecordSize(master);
		return size;
	}
};
