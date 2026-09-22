/*	SSA Extractor
	Copyright 2005 Jonathan Wilson

	The SSA Extractor Program is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
	The files libdynamite.h and libdynamite.cpp are Copyright (c) 2003 David Eriksson <twogood@users.sourceforge.net>
*/

#include "stdafx.h"
#include "libdynamite.h"
#include <conio.h>
#include <shlobj.h>
#include <shlwapi.h>

struct SSAHeader
{
	unsigned long magic;
	unsigned long unk;
	unsigned long unk2;
	unsigned long fileheadersize;
};
struct SSAFileHeader
{
	unsigned long start;
	unsigned long end;
	unsigned long size;
};
struct SSACompressedDataHeader
{
	unsigned long magic;
	unsigned long size;
	unsigned long unknown;
};
typedef struct _Cookie
{
	char *input;
	size_t count;
	char *output;
} Cookie;

static size_t reader(void* buffer, size_t size, void* cookie)
{
	Cookie *c = (Cookie *)cookie;
	size_t count;
	if (c->count >= size)
	{
		memcpy(buffer,c->input,size);
		c->input += size;
		c->count -= size;
		count = size;
	}
	else
	{
		memcpy(buffer,c->input,c->count);
		count = c->count;
		c->input = 0;
		c->count = 0;
	}
	return count;
}

static size_t writer(void* buffer, size_t size, void* cookie)
{
	memcpy(((Cookie *)cookie)->output,buffer,size);
	((Cookie *)cookie)->output += size;
	return size;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Please select .ssa to extract.\n");
	printf("E.g. C:/Sierra/Empire Earth/data/data.ssa\n");
	char infile[MAX_PATH];
	char outdir[MAX_PATH];
	fgets(infile,MAX_PATH,stdin);
	infile[strlen(infile)-1] = 0;
	printf("Please select output directory.\n");
	fgets(outdir,MAX_PATH,stdin);
	outdir[strlen(outdir)-1] = 0;
	if (!PathFileExists(outdir))
	{
		SHCreateDirectoryEx(NULL,outdir,NULL);
	}
	FILE *f = fopen(infile,"rb");
	if (!f)
	{
		printf("Can't open %s\n",infile);
		getch();
		exit(1);
	}
	SSAHeader h;
	char *FileHeaders;
	fread(&h,sizeof(h),1,f);
	if (h.magic != 'ssar')
	{
		printf("Not a SSA file\n");
	}
	FileHeaders = new char[h.fileheadersize];
	fread(FileHeaders,h.fileheadersize,1,f);
	char *FileHeaderPos = FileHeaders;
	while (FileHeaderPos < FileHeaders + h.fileheadersize)
	{
		int FileNameLen = *(unsigned long *)FileHeaderPos;
		FileHeaderPos += 4;
		char *FileName = FileHeaderPos;
		FileHeaderPos += FileNameLen;
		SSAFileHeader *fh = (SSAFileHeader *)FileHeaderPos;
		FileHeaderPos += sizeof(SSAFileHeader);
		printf("Extracting %s\n",FileName);
		fseek(f,fh->start,SEEK_SET);
		char *Data = new char[fh->size];
		fread(Data,fh->size,1,f);
		SSACompressedDataHeader *ch = (SSACompressedDataHeader *)Data;
		char *OutData;
		unsigned long OutSize;
		if (ch->magic == '10KP')
		{
			OutData = new char[ch->size];
			OutSize = ch->size;
			Data += sizeof(SSACompressedDataHeader);
			Cookie cookie;
			cookie.input = Data;
			cookie.count = fh->size - sizeof(SSACompressedDataHeader);
			cookie.output = OutData;
			dynamite_explode(reader, writer, &cookie);
		}
		else
		{
			OutData = Data;
			OutSize = fh->size;
		}
		char *dir = strdup(FileName);
		strrchr(dir,'\\')[0] = 0;
		char location[MAX_PATH];
		char curdir[MAX_PATH];
		GetCurrentDirectory(MAX_PATH,curdir);
		sprintf(location,"%s\\%s",curdir,dir);
		if (!PathFileExists(location))
		{
			SHCreateDirectoryEx(NULL,location,NULL);
		}
		FILE *f2 = fopen(FileName,"wb");
		if (!f2)
		{
			printf("Can't open %s\n",FileName);
			getch();
			exit(1);
		}
		fwrite(OutData,OutSize,1,f2);
		fclose(f2);
	}
}

