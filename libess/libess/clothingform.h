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
class ClothingForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	formid script;
	formid enchantment;
	ushort enchantmentPoints;
	ushort partMask;
	ushort flags;
	char *maleBipedModel;
	float maleBipedBoundRadius;
	ulong maleBipedtextureHashesCount;
	TextureHash *maleBipedtextureHashes;
	char *maleGroundModel;
	float maleGroundBoundRadius;
	ulong maleGroundtextureHashesCount;
	TextureHash *maleGroundtextureHashes;
	char *maleIcon;
	char *femaleBipedModel;
	float femaleBipedBoundRadius;
	ulong femaleBipedtextureHashesCount;
	TextureHash *femaleBipedtextureHashes;
	char *femaleGroundModel;
	float femaleGroundBoundRadius;
	ulong femaleGroundtextureHashesCount;
	TextureHash *femaleGroundtextureHashes;
	char *femaleIcon;
	ulong value;
	float weight;
public:
	ClothingForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), script(0), enchantment(0), enchantmentPoints(0), partMask(0), flags(0), maleBipedModel(0), maleBipedBoundRadius(0), maleBipedtextureHashesCount(0), maleBipedtextureHashes(0), maleGroundModel(0), maleGroundBoundRadius(0), maleGroundtextureHashesCount(0), maleGroundtextureHashes(0), maleIcon(0), femaleBipedModel(0), femaleBipedBoundRadius(0), femaleBipedtextureHashesCount(0), femaleBipedtextureHashes(0), femaleGroundModel(0), femaleGroundBoundRadius(0), femaleGroundtextureHashesCount(0), femaleGroundtextureHashes(0), femaleIcon(0), value(0), weight(0)
	{
	}
	virtual ~ClothingForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (maleBipedModel)
		{
			delete[] maleBipedModel;
		}
		if (maleBipedtextureHashes)
		{
			delete[] maleBipedtextureHashes;
		}
		if (maleGroundModel)
		{
			delete[] maleGroundModel;
		}
		if (maleGroundtextureHashes)
		{
			delete[] maleGroundtextureHashes;
		}
		if (maleIcon)
		{
			delete[] maleIcon;
		}
		if (femaleBipedModel)
		{
			delete[] femaleBipedModel;
		}
		if (femaleBipedtextureHashes)
		{
			delete[] femaleBipedtextureHashes;
		}
		if (femaleGroundModel)
		{
			delete[] femaleGroundModel;
		}
		if (femaleGroundtextureHashes)
		{
			delete[] femaleGroundtextureHashes;
		}
		if (femaleIcon)
		{
			delete[] femaleIcon;
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
				fullName = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SCRI':
				script = f->read<formid>();
				readSize += 4;
				break;
			case 'ENAM':
				enchantment = f->read<formid>();
				readSize += 4;
				break;
			case 'ANAM':
				enchantmentPoints = f->read<ushort>();
				readSize += 2;
				break;
			case 'BMDT':
				partMask = f->read<ushort>();
				readSize += 2;
				flags = f->read<ushort>();
				readSize += 2;
				break;
			case 'MODL':
				maleBipedModel = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MODB':
				maleBipedBoundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MODT':
				maleBipedtextureHashesCount = h.size / sizeof(TextureHash);
				maleBipedtextureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'MOD2':
				maleGroundModel = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MO2B':
				maleGroundBoundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MO2T':
				maleGroundtextureHashesCount = h.size / sizeof(TextureHash);
				maleGroundtextureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'ICON':
				maleIcon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MOD3':
				femaleBipedModel = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MO3B':
				femaleBipedBoundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MO3T':
				femaleBipedtextureHashesCount = h.size / sizeof(TextureHash);
				femaleBipedtextureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'MOD4':
				femaleGroundModel = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'MO4B':
				femaleGroundBoundRadius = f->read<float>();
				readSize += 4;
				break;
			case 'MO4T':
				femaleGroundtextureHashesCount = h.size / sizeof(TextureHash);
				femaleGroundtextureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
				readSize += h.size;
				break;
			case 'ICO2':
				femaleIcon = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'DATA':
				value = f->read<ulong>();
				weight = f->read<float>();
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
		WriteZStringSubrecord('EDID',editorID,f);
		WriteZStringSubrecord('FULL',fullName,f);
		if (script)
		{
			WriteSubrecord('SCRI',4,f);
			f->write<formid>(script);
		}
		if (enchantment)
		{
			WriteSubrecord('ENAM',4,f);
			f->write<formid>(enchantment);
		}
		if (enchantmentPoints)
		{
			WriteSubrecord('ANAM',2,f);
			f->write<ushort>(enchantmentPoints);
		}
		WriteSubrecord('BMDT',4,f);
		f->write<ushort>(partMask);
		f->write<ushort>(flags);
		WriteZStringSubrecord('MODL',maleBipedModel,f);
		if (maleBipedModel)
		{
			WriteSubrecord('MODB',4,f);
			f->write<float>(maleBipedBoundRadius);
		}
		if (maleBipedtextureHashes)
		{
			WriteSubrecord('MODT',maleBipedtextureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(maleBipedtextureHashesCount,maleBipedtextureHashes);
		}
		WriteZStringSubrecord('MOD2',maleGroundModel,f);
		if (maleGroundModel)
		{
			WriteSubrecord('MO2B',4,f);
			f->write<float>(maleGroundBoundRadius);
		}
		if (maleGroundtextureHashes)
		{
			WriteSubrecord('MO2T',maleGroundtextureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(maleGroundtextureHashesCount,maleGroundtextureHashes);
		}
		WriteZStringSubrecord('ICON',maleIcon,f);
		WriteZStringSubrecord('MOD3',femaleBipedModel,f);
		if (femaleBipedModel)
		{
			WriteSubrecord('MO3B',4,f);
			f->write<float>(femaleBipedBoundRadius);
		}
		if (femaleBipedtextureHashes)
		{
			WriteSubrecord('MO3T',femaleBipedtextureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(femaleBipedtextureHashesCount,femaleBipedtextureHashes);
		}
		WriteZStringSubrecord('MOD4',femaleGroundModel,f);
		if (femaleGroundModel)
		{
			WriteSubrecord('MO4B',4,f);
			f->write<float>(femaleGroundBoundRadius);
		}
		if (femaleGroundtextureHashes)
		{
			WriteSubrecord('MO4T',femaleGroundtextureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(femaleGroundtextureHashesCount,femaleGroundtextureHashes);
		}
		WriteZStringSubrecord('ICO2',femaleIcon,f);
		WriteSubrecord('DATA',8,f);
		f->write<ulong>(value);
		f->write<float>(weight);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		if (script)
		{
			size += ComputeSubrecordSize(4);
		}
		if (enchantment)
		{
			size += ComputeSubrecordSize(4);
		}
		if (enchantmentPoints)
		{
			size += ComputeSubrecordSize(2);
		}
		size += ComputeSubrecordSize(4);
		size += ZStringSubrecordSize(maleBipedModel);
		if (maleBipedModel)
		{
			size += ComputeSubrecordSize(4);
		}
		if (maleBipedtextureHashes)
		{
			size += ComputeSubrecordSize(maleBipedtextureHashesCount * sizeof(TextureHash));
		}
		size += ZStringSubrecordSize(maleGroundModel);
		if (maleGroundModel)
		{
			size += ComputeSubrecordSize(4);
		}
		if (maleGroundtextureHashes)
		{
			size += ComputeSubrecordSize(maleGroundtextureHashesCount * sizeof(TextureHash));
		}
		size += ZStringSubrecordSize(maleIcon);
		size += ZStringSubrecordSize(femaleBipedModel);
		if (femaleBipedModel)
		{
			size += ComputeSubrecordSize(4);
		}
		if (femaleBipedtextureHashes)
		{
			size += ComputeSubrecordSize(femaleBipedtextureHashesCount * sizeof(TextureHash));
		}
		size += ZStringSubrecordSize(femaleGroundModel);
		if (femaleGroundModel)
		{
			size += ComputeSubrecordSize(4);
		}
		if (femaleGroundtextureHashes)
		{
			size += ComputeSubrecordSize(femaleGroundtextureHashesCount * sizeof(TextureHash));
		}
		size += ZStringSubrecordSize(femaleIcon);
		size += ComputeSubrecordSize(8);
		return size;
	}
};
