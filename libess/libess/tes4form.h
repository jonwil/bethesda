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
class TES4Form : public Form
{
protected:
	float version;
	ulong formCount;
	ulong nextFormId;
	ushort offsetSize;
	ubyte *offsetData;
	bool deleSeen;
	ulong dele1;
	ulong dele2;
	char *author;
	char *description;
	SimpleDynVecClass<char *> masters;
	SimpleDynVecClass<uint64> sizes;
public:
	TES4Form(FormHeader h,ModFile *f) : Form(h,f), version(0), formCount(0), nextFormId(0), offsetSize(0), offsetData(0), deleSeen(false), dele1(0), dele2(0), author(0), description(0), masters(0), sizes(0)
	{
	}
	virtual ~TES4Form()
	{
		if (offsetData)
		{
			delete[] offsetData;
		}
		if (author)
		{
			delete[] author;
		}
		if (description)
		{
			delete[] description;
		}
		for (int i = 0;i < masters.Count();i++)
		{
			delete[] masters[i];
		}
		masters.Delete_All();
		sizes.Delete_All();
	}
protected:
	virtual void Load(FileRead *f)
	{
		while (readSize < uncompsize)
		{
			SubrecordHeader h = ReadSubrecord(f);
			switch(h.type)
			{
			case 'HEDR':
				version = f->read<float>();
				formCount = f->read<ulong>();
				nextFormId = f->read<ulong>();
				readSize += 12;
				break;
			case 'OFST':
				offsetSize = (ushort)h.size;
				offsetData = f->readarray<ubyte>(h.size);
				readSize += h.size;
				break;
			case 'DELE':
				deleSeen = true;
				dele1 = f->read<ulong>();
				dele2 = f->read<ulong>();
				readSize += 8;
				break;
			case 'CNAM':
				author = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SNAM':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MAST':
				masters.Add(f->readzstring(h.size));
				readSize += h.size;
				break;
			case 'DATA':
				sizes.Add(f->read<uint64>());
				readSize += 8;
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
		WriteSubrecord('HEDR',12,f);
		f->write<float>(version);
		f->write<ulong>(formCount);
		f->write<ulong>(nextFormId);
		if (offsetData)
		{
			WriteSubrecord('OFST',offsetSize,f);
			f->writearray<ubyte>(offsetSize,offsetData);
		}
		if (deleSeen)
		{
			WriteSubrecord('DELE',8,f);
			f->write<ulong>(dele1);
			f->write<ulong>(dele2);
		}
		WriteZStringSubrecord('CNAM',author,f);
		WriteZStringSubrecord('SNAM',description,f);
		for (int i = 0;i < masters.Count();i++)
		{
			WriteZStringSubrecord('MAST',masters[i],f);
			WriteSubrecord('DATA',8,f);
			f->write<uint64>(sizes[i]);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ComputeSubrecordSize(12);
		if (offsetData)
		{
			size += ComputeSubrecordSize(offsetSize);
		}
		if (deleSeen)
		{
			size += ComputeSubrecordSize(8);
		}
		size += ZStringSubrecordSize(author);
		size += ZStringSubrecordSize(description);
		for (int i = 0;i < masters.Count();i++)
		{
			size += ZStringSubrecordSize(masters[i]);
			size += ComputeSubrecordSize(8);
		}
		return size;
	}
	friend class ModFile;
};
