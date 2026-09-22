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
class SoundForm : public Form
{
protected:
	char *editorID;
	char *soundFilename;
	bool snddSeen;
	ulong sndd1;
	ulong sndd2;
	ubyte minDistance;
	ubyte maxDistance;
	byte freqAdjustment;
	ubyte unk;
	ulong flags;
	short staticAtten;
	ubyte stopTime;
	ubyte startTime;
	bool sndx;
public:
	SoundForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), soundFilename(0), snddSeen(0), sndd1(0), sndd2(0), minDistance(0), maxDistance(0), freqAdjustment(0), unk(0), flags(0), staticAtten(0), stopTime(0), startTime(0), sndx(false)
	{
	}
	virtual ~SoundForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (soundFilename)
		{
			delete[] soundFilename;
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
			case 'FNAM':
				soundFilename = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SNDD':
				snddSeen = true;
				sndd1 = f->read<ulong>();
				readSize += 4;
				sndd2 = f->read<ulong>();
				readSize += 4;
				break;
			case 'SNDX':
				sndx = true;
				minDistance = f->read<ubyte>();
				readSize += 1;
				maxDistance = f->read<ubyte>();
				readSize += 1;
				freqAdjustment = f->read<byte>();
				readSize += 1;
				unk = f->read<ubyte>();
				readSize += 1;
				flags = f->read<ulong>();
				readSize += 4;
				staticAtten = f->read<short>();
				readSize += 2;
				stopTime = f->read<ubyte>();
				readSize += 1;
				startTime = f->read<ubyte>();
				readSize += 1;
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
		WriteZStringSubrecord('FNAM',soundFilename,f);
		if (snddSeen)
		{
			WriteSubrecord('SNDD',8,f);
			f->write<ulong>(sndd1);
			f->write<ulong>(sndd2);
		}
		if (sndx)
		{
			WriteSubrecord('SNDX',12,f);
			f->write<ubyte>(minDistance);
			f->write<ubyte>(maxDistance);
			f->write<byte>(freqAdjustment);
			f->write<ubyte>(unk);
			f->write<ulong>(flags);
			f->write<short>(staticAtten);
			f->write<ubyte>(stopTime);
			f->write<ubyte>(startTime);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(soundFilename);
		if (snddSeen)
		{
			size += ComputeSubrecordSize(8);
		}
		if (sndx)
		{
			size += ComputeSubrecordSize(12);
		}
		return size;
	}
};
