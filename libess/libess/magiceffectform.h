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
class MagicEffectForm : public Form
{
protected:
	char *editorID;
	ulong editorIDSize;
	char *fullName;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	char *icon;
	char *description;
	bool obmePresent;
	ubyte obmeVersion;
	ubyte obmeBeta;
	ubyte obmeMinor;
	ubyte obmeMajor;
	ubyte obmeParamAType;
	ubyte obmeParamBType;
	ushort obmeReserved;
	ulong obmeEffectHandler;
	ulong obmeFlags;
	ulong obmeParamB;
	ubyte obmePad[0x1C];
	char *editorIDOBME;
	ulong dataFlags;
	ulong baseCost;
	ulong mgefParam;
	ulong school;
	ulong avCode;
	ushort counterCount;
	ushort pad;
	formid light;
	float speed;
	formid effectShader;
	formid enchantShader;
	formid castSound;
	formid boltSound;
	formid hitSound;
	formid areaSound;
	float enchantFactor;
	float barterFactor;
	bool extraDATAData;
	bool extraDATAData2;
	ulong dataEffectHandler;
	ulong dataOBMEFlags;
	ulong dataMgefParamB;
	ubyte dataPad[0x14];
	bool datxPresent;
	ulong datxEffectHandler;
	ulong datxOBMEFlags;
	ulong datxMgefParamB;
	ubyte datxPad[0x14];
	ulong counterSize;
	ulong *counters;
public:
	MagicEffectForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), model(0), boundRadius(0), textureHashesCount(0), textureHashes(0), icon(0), description(0), obmePresent(0), obmeVersion(0), obmeBeta(0), obmeMinor(0), obmeMajor(0), obmeParamAType(0), obmeParamBType(0), obmeReserved(0), obmeEffectHandler(0), obmeFlags(0), obmeParamB(0), editorIDOBME(0), dataFlags(0), baseCost(0), mgefParam(0), school(0), avCode(0), counterCount(0), pad(0), light(0), speed(0), effectShader(0), enchantShader(0), castSound(0), boltSound(0), hitSound(0), areaSound(0), enchantFactor(0), barterFactor(0), extraDATAData(0), dataEffectHandler(0), dataOBMEFlags(0), dataMgefParamB(0), datxPresent(0), datxEffectHandler(0), datxOBMEFlags(0), datxMgefParamB(0), counters(0), counterSize(0), extraDATAData2(false)
	{
	}
	virtual ~MagicEffectForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (model)
		{
			delete[] model;
		}
		if (textureHashes)
		{
			delete[] textureHashes;
		}
		if (icon)
		{
			delete[] icon;
		}
		if (description)
		{
			delete[] description;
		}
		if (editorIDOBME)
		{
			delete[] editorIDOBME;
		}
		if (counters)
		{
			delete[] counters;
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
				editorID = f->readarray<char>(h.size);
				readSize += h.size;
				editorIDSize = h.size;
				break;
			case 'OBME':
				obmePresent = true;
				obmeVersion = f->read<ubyte>();
				readSize += 1;
				obmeBeta = f->read<ubyte>();
				readSize += 1;
				obmeMinor = f->read<ubyte>();
				readSize += 1;
				obmeMajor = f->read<ubyte>();
				readSize += 1;
				obmeParamAType = f->read<ubyte>();
				readSize += 1;
				obmeParamBType = f->read<ubyte>();
				readSize += 1;
				obmeReserved = f->read<ushort>();
				readSize += 2;
				obmeEffectHandler = f->read<ulong>();
				readSize += 4;
				obmeFlags = f->read<ulong>();
				readSize += 4;
				obmeParamB = f->read<ulong>();
				readSize += 4;
				for (int i = 0;i < 0x1C;i++)
				{
					obmePad[i] = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'EDDX':
				editorIDOBME = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'FULL':
				fullName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DESC':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODL':
				model = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODB':
				boundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MODT':
				textureHashesCount = h.size / sizeof(TextureHash);
				textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'ICON':
				icon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				dataFlags = f->read<ulong>();
				readSize += 4;
				baseCost = f->read<ulong>();
				readSize += 4;
				mgefParam = f->read<ulong>();
				readSize += 4;
				school = f->read<ulong>();
				readSize += 4;
				avCode = f->read<ulong>();
				readSize += 4;
				counterCount = f->read<ushort>();
				readSize += 2;
				pad = f->read<ushort>();
				readSize += 2;
				light = f->read<formid>();
				readSize += 4;
				speed = f->read<float>();
				readSize += 4;
				effectShader = f->read<formid>();
				readSize += 4;
				if (h.size >= 0x40)
				{
					extraDATAData2 = true;
					enchantShader = f->read<formid>();
					readSize += 4;
					castSound = f->read<formid>();
					readSize += 4;
					boltSound = f->read<formid>();
					readSize += 4;
					hitSound = f->read<formid>();
					readSize += 4;
					areaSound = f->read<formid>();
					readSize += 4;
					enchantFactor = f->read<float>();
					readSize += 4;
					barterFactor = f->read<float>();
					readSize += 4;
					if (h.size == 0x60)
					{
						extraDATAData = true;
						dataEffectHandler = f->read<ulong>();
						readSize += 4;
						dataOBMEFlags = f->read<ulong>();
						readSize += 4;
						dataMgefParamB = f->read<ulong>();
						readSize += 4;
						for (int i = 0;i < 0x14;i++)
						{
							dataPad[i] = f->read<ubyte>();
							readSize += 1;
						}
					}
				}
				break;
			case 'DATX':
				datxPresent = true;
				datxEffectHandler = f->read<ulong>();
				readSize += 4;
				datxOBMEFlags = f->read<ulong>();
				readSize += 4;
				datxMgefParamB = f->read<ulong>();
				readSize += 4;
				for (int i = 0;i < 0x14;i++)
				{
					datxPad[i] = f->read<ubyte>();
					readSize += 1;
				}
				break;
			case 'ESCE':
				counterSize = h.size / 4;
				counters = f->readarray<ulong>(counterSize);
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
		if (editorID)
		{
			WriteSubrecord('EDID',editorIDSize,f);
			f->writearray<char>(editorIDSize,editorID);
		}
		if (obmePresent)
		{
			WriteSubrecord('OBME',0x30,f);
			f->write<ubyte>(obmeVersion);
			f->write<ubyte>(obmeBeta);
			f->write<ubyte>(obmeMinor);
			f->write<ubyte>(obmeMajor);
			f->write<ubyte>(obmeParamAType);
			f->write<ubyte>(obmeParamBType);
			f->write<ushort>(obmeReserved);
			f->write<ulong>(obmeEffectHandler);
			f->write<ulong>(obmeFlags);
			f->write<ulong>(obmeParamB);
			for (int i = 0;i < 0x1C;i++)
			{
				f->write<ubyte>(obmePad[i]);
			}
		}
		WriteZStringSubrecord('EDDX',editorIDOBME,f);
		WriteZStringSubrecord('FULL',fullName,f);
		WriteZStringSubrecord('DESC',description,f);
		WriteZStringSubrecord('ICON',icon,f);
		WriteZStringSubrecord('MODL',model,f);
		if (model)
		{
			WriteSubrecord('MODB',4,f);
			f->write<float>(boundRadius);
		}
		if (textureHashes)
		{
			WriteSubrecord('MODT',textureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(textureHashesCount,textureHashes);
		}
		if (extraDATAData2)
		{
			if (extraDATAData)
			{
				WriteSubrecord('DATA',0x60,f);
			}
			else
			{
				WriteSubrecord('DATA',0x40,f);
			}
		}
		else
		{
			WriteSubrecord('DATA',0x24,f);
		}
		f->write<ulong>(dataFlags);
		f->write<ulong>(baseCost);
		f->write<ulong>(mgefParam);
		f->write<ulong>(school);
		f->write<ulong>(avCode);
		f->write<ushort>(counterCount);
		f->write<ushort>(pad);
		f->write<formid>(light);
		f->write<float>(speed);
		f->write<formid>(effectShader);
		if (extraDATAData2)
		{
			f->write<formid>(enchantShader);
			f->write<formid>(castSound);
			f->write<formid>(boltSound);
			f->write<formid>(hitSound);
			f->write<formid>(areaSound);
			f->write<float>(enchantFactor);
			f->write<float>(barterFactor);
			if (extraDATAData)
			{
				f->write<ulong>(dataEffectHandler);
				f->write<ulong>(dataOBMEFlags);
				f->write<ulong>(dataMgefParamB);
				for (int i = 0;i < 0x14;i++)
				{
					f->write<ubyte>(dataPad[i]);
				}
			}
		}
		if (datxPresent)
		{
			WriteSubrecord('DATX',0x20,f);
			f->write<ulong>(datxEffectHandler);
			f->write<ulong>(datxOBMEFlags);
			f->write<ulong>(datxMgefParamB);
			for (int i = 0;i < 0x14;i++)
			{
				f->write<ubyte>(datxPad[i]);
			}
		}
		if (counters)
		{
			WriteSubrecord('ESCE',counterSize * 4,f);
			f->writearray<ulong>(counterSize,counters);
		}
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		if (editorID)
		{
			size += ComputeSubrecordSize(editorIDSize);
		}
		if (obmePresent)
		{
			size += ComputeSubrecordSize(0x30);
		}
		size += ZStringSubrecordSize(editorIDOBME);
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(description);
		size += ZStringSubrecordSize(model);
		if (model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (textureHashes)
		{
			size += ComputeSubrecordSize(textureHashesCount * sizeof(TextureHash));
		}
		size += ZStringSubrecordSize(icon);
		if (extraDATAData2)
		{
			if (extraDATAData)
			{
				size += ComputeSubrecordSize(0x60);
			}
			else
			{
				size += ComputeSubrecordSize(0x40);
			}
		}
		else
		{
			size += ComputeSubrecordSize(0x24);
		}
		if (datxPresent)
		{
			size += ComputeSubrecordSize(0x20);
		}
		if (counters)
		{
			size += ComputeSubrecordSize(counterSize * 4);
		}
		return size;
	}
};
