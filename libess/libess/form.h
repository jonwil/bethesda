/*	libess
	Copyright 2013 Jonathan Wilson

	This file is part of libess
	libess is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#pragma once
#include "essfile.h"
#include "modfile.h"
class Form
{
protected:
	FormHeader header;
	ulong readSize;
	ModFile *file;
	ulong uncompsize;
public:
	Form(FormHeader h,ModFile *f) : header(h), file(f), readSize(0), uncompsize(h.dataSize)
	{
		AddForm(this);
	}
	virtual ~Form()
	{
		RemoveForm(this);
	}
	void LoadCompressed(FileRead *f);
	void SaveCompressed(FileWrite *f);
	FormHeader Get_Header()
	{
		return header;
	}
	formid RemapFormID(formid id)
	{
		if (!id)
		{
			return 0;
		}
		if (file)
		{
			return id |= (file->GetLoadID((ubyte)(id >> 24)) << 24);
		}
		else
		{
			return id;
		}
	}
protected:
	virtual void Load(FileRead *f) = 0;
	virtual void Save(FileWrite *f) = 0;
	virtual int GetSaveSize() = 0;
	SubrecordHeader ReadSubrecord(FileRead *f)
	{
		SubrecordHeader h;
		h.type = SwapBytes(f->read<ulong>());
		readSize += 4;
		h.size = f->read<ushort>();
		readSize += 2;
		if (h.type == 'XXXX')
		{
			h.size = f->read<ulong>();
			readSize += 4;
			h.type = SwapBytes(f->read<ulong>());
			readSize += 4;
			f->read<ushort>();
			readSize += 2;
		}
		return h;
	}
	void WriteSubrecord(ulong type, ulong size, FileWrite *f)
	{
		if (size > 0xFFFF)
		{
			WriteSubrecord('XXXX',4,f);
			f->write<ulong>(size);
			size = 0;
		}
		f->write<ulong>(SwapBytes(type));
		f->write<ushort>((ushort)size);
	}
	int ComputeSubrecordSize(ulong size)
	{
		int sz = 6;
		if (size > 0xFFFF)
		{
			sz += 6;
			sz += 4;
		}
		sz += size;
		return sz;
	}
	void WriteZStringSubrecord(ulong type,char *string,FileWrite *f)
	{
		if (string)
		{
			ulong size = strlen(string) + 1;
			WriteSubrecord(type,size,f);
			f->writezstring(size,string);
		}
	}
	int ZStringSubrecordSize(char *string)
	{
		if (string)
		{
			return ComputeSubrecordSize(strlen(string) + 1);
		}
		return 0;
	}
	friend class ESSFile;
};
Form *CreateForm(FormHeader header,ModFile *f);
