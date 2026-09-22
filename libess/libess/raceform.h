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
struct RaceAttributes
{
	ubyte maleStrength;
	ubyte maleIntellegence;
	ubyte maleWillpower;
	ubyte maleAgility;
	ubyte maleSpeed;
	ubyte maleEndurance;
	ubyte malePersonality;
	ubyte maleLuck;
	ubyte femaleStrength;
	ubyte femaleIntellegence;
	ubyte femaleWillpower;
	ubyte femaleAgility;
	ubyte femaleSpeed;
	ubyte femaleEndurance;
	ubyte femalePersonality;
	ubyte femaleLuck;
};
struct RaceRelation
{
	formid race;
	long mod;
};
struct RaceVoices
{
	formid male;
	formid female;
	RaceVoices() : male(0), female(0)
	{
	}
};
struct RaceHair
{
	formid male;
	formid female;
	RaceHair() : male(0), female(0)
	{
	}
};
struct RaceSkill
{
	ubyte value;
	ubyte boost;
};
struct RaceData
{
	RaceSkill skills[7];
	ushort unk1;
	float maleScale;
	float femaleScale;
	float maleWeight;
	float femaleWeight;
	ulong flags;
};
struct FaceData
{
	ulong index;
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	char *icon;
	FaceData() : model(0), textureHashes(0), textureHashesCount(0), icon(0)
	{
	}
};
struct BodyPart
{
	ulong index;
	char *icon;
	BodyPart() : icon(0)
	{
	}
};
struct BodyData
{
	char *model;
	float boundRadius;
	ulong textureHashesCount;
	TextureHash *textureHashes;
	SimpleDynVecClass<BodyPart> bodyParts;
	BodyData() : model(0), textureHashes(0), textureHashesCount(0), bodyParts(0)
	{
	}
};
class RaceForm : public Form
{
protected:
	char *editorID;
	char *fullName;
	char *description;
	SimpleDynVecClass<formid> spellList;
	SimpleDynVecClass<RaceRelation> relations;
	RaceData data;
	RaceVoices voices;
	RaceHair hair;
	ubyte hairColor;
	float mainClamp;
	float faceClamp;
	RaceAttributes attributes;
	bool face;
	SimpleDynVecClass<FaceData> faces;
	bool body;
	bool male;
	bool female;
	BodyData maleData;
	BodyData femaleData;
	ulong hairCount;
	formid *hairs;
	ulong eyeCount;
	formid *eyes;
	ulong fggsSize;
	byte *fggs;
	ulong fggaSize;
	byte *fgga;
	ulong fgtsSize;
	byte *fgts;
	ushort snam;
public:
	RaceForm(FormHeader h,ModFile *f) : Form(h,f), editorID(0), fullName(0), description(0), spellList(0), relations(0), hairColor(0), mainClamp(0), faceClamp(0), face(false), faces(0), body(false), male(false), female(false), hairCount(0), hairs(0), eyeCount(0), eyes(0), fggsSize(0), fggs(0), fggaSize(0), fgga(0), fgtsSize(0), fgts(0), snam(0)
	{
	}
	virtual ~RaceForm()
	{
		if (editorID)
		{
			delete[] editorID;
		}
		if (fullName)
		{
			delete[] fullName;
		}
		if (description)
		{
			delete[] description;
		}
		for (int i = 0;i < faces.Count();i++)
		{
			if (faces[i].model)
			{
				delete[] faces[i].model;
			}
			if (faces[i].textureHashes)
			{
				delete[] faces[i].textureHashes;
			}
			if (faces[i].icon)
			{
				delete[] faces[i].icon;
			}
		}
		if (maleData.model)
		{
			delete[] maleData.model;
		}
		if (maleData.textureHashes)
		{
			delete[] maleData.textureHashes;
		}
		for (int i = 0;i < maleData.bodyParts.Count();i++)
		{
			if (maleData.bodyParts[i].icon)
			{
				delete[] maleData.bodyParts[i].icon;
			}
		}
		if (femaleData.model)
		{
			delete[] femaleData.model;
		}
		if (femaleData.textureHashes)
		{
			delete[] femaleData.textureHashes;
		}
		for (int i = 0;i < femaleData.bodyParts.Count();i++)
		{
			if (femaleData.bodyParts[i].icon)
			{
				delete[] femaleData.bodyParts[i].icon;
			}
		}
		if (hairs)
		{
			delete[] hairs;
		}
		if (eyes)
		{
			delete[] eyes;
		}
		if (fggs)
		{
			delete[] fggs;
		}
		if (fgga)
		{
			delete[] fgga;
		}
		if (fgts)
		{
			delete[] fgts;
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
			case 'DESC':
				description = f->readzstring(h.size);
				readSize += h.size;
				break;
			case 'SPLO':
				spellList.Add(f->read<formid>());
				readSize += 4;
				break;
			case 'XNAM':
				{
					RaceRelation r;
					r.race = f->read<formid>();
					readSize += 4;
					r.mod = f->read<long>();
					readSize += 4;
					relations.Add(r);
				}
				break;
			case 'DATA':
				data = f->read<RaceData>();
				readSize += sizeof(RaceData);
				break;
			case 'VNAM':
				voices = f->read<RaceVoices>();
				readSize += sizeof(RaceVoices);
				break;
			case 'DNAM':
				hair = f->read<RaceHair>();
				readSize += sizeof(RaceHair);
				break;
			case 'CNAM':
				hairColor = f->read<ubyte>();
				readSize += 1;
				break;
			case 'PNAM':
				mainClamp = f->read<float>();
				readSize += 4;
				break;
			case 'UNAM':
				faceClamp = f->read<float>();
				readSize += 4;
				break;
			case 'ATTR':
				attributes = f->read<RaceAttributes>();
				readSize += sizeof(RaceAttributes);
				break;
			case 'NAM0':
				face = true;
				break;
			case 'INDX':
				if (face)
				{
					FaceData d;
					d.index = f->read<ulong>();
					readSize += 4;
					faces.Add(d);
				}
				else if (male)
				{
					BodyPart d;
					d.index = f->read<ulong>();
					readSize += 4;
					maleData.bodyParts.Add(d);
				}
				else if (female)
				{
					BodyPart d;
					d.index = f->read<ulong>();
					readSize += 4;
					femaleData.bodyParts.Add(d);
				}
				break;
			case 'MODL':
				if (face)
				{
					faces[faces.Count() - 1].model = f->readzstring(h.size);
					readSize += h.size;
				}
				else if (male)
				{
					maleData.model = f->readzstring(h.size);
					readSize += h.size;
				}
				else if (female)
				{
					femaleData.model = f->readzstring(h.size);
					readSize += h.size;
				}
				break;
			case 'MODB':
				if (face)
				{
					faces[faces.Count() - 1].boundRadius = f->read<float>();
					readSize += 4;
				}
				else if (male)
				{
					maleData.boundRadius = f->read<float>();
					readSize += 4;
				}
				else if (female)
				{
					femaleData.boundRadius = f->read<float>();
					readSize += 4;
				}
				break;
			case 'MODT':
				if (face)
				{
					faces[faces.Count() - 1].textureHashesCount = h.size / sizeof(TextureHash);
					faces[faces.Count() - 1].textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
					readSize += h.size;
				}
				else if (male)
				{
					maleData.textureHashesCount = h.size / sizeof(TextureHash);
					maleData.textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
					readSize += h.size;
				}
				else if (female)
				{
					femaleData.textureHashesCount = h.size / sizeof(TextureHash);
					femaleData.textureHashes = f->readarray<TextureHash>(h.size / sizeof(TextureHash));
					readSize += h.size;
				}
				break;
			case 'ICON':
				if (face)
				{
					faces[faces.Count() - 1].icon = f->readzstring(h.size);
					readSize += h.size;
				}
				else if (male)
				{
					maleData.bodyParts[maleData.bodyParts.Count() - 1].icon = f->readzstring(h.size);
					readSize += h.size;
				}
				else if (female)
				{
					femaleData.bodyParts[femaleData.bodyParts.Count() - 1].icon = f->readzstring(h.size);
					readSize += h.size;
				}
				break;
			case 'NAM1':
				body = true;
				face = false;
				break;
			case 'MNAM':
				male = true;
				break;
			case 'FNAM':
				male = false;
				female = true;
				break;
			case 'HNAM':
				hairCount = h.size / 4;
				hairs = f->readarray<formid>(hairCount);
				readSize += h.size;
				break;
			case 'ENAM':
				eyeCount = h.size / 4;
				eyes = f->readarray<formid>(eyeCount);
				readSize += h.size;
				break;
			case 'FGGS':
				fggsSize = h.size;
				fggs = f->readarray<byte>(fggsSize);
				readSize += h.size;
				break;
			case 'FGGA':
				fggaSize = h.size;
				fgga = f->readarray<byte>(fggaSize);
				readSize += h.size;
				break;
			case 'FGTS':
				fgtsSize = h.size;
				fgts = f->readarray<byte>(fgtsSize);
				readSize += h.size;
				break;
			case 'SNAM':
				snam = f->read<ushort>();
				readSize += 2;
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
		WriteZStringSubrecord('DESC',description,f);
		for (int i = 0;i < spellList.Count();i++)
		{
			WriteSubrecord('SPLO',4,f);
			f->write<formid>(spellList[i]);
		}
		for (int i = 0;i < relations.Count();i++)
		{
			WriteSubrecord('XNAM',8,f);
			f->write<formid>(relations[i].race);
			f->write<long>(relations[i].mod);
		}
		WriteSubrecord('DATA',sizeof(RaceData),f);
		f->write<RaceData>(data);
		if (voices.female || voices.male)
		{
			WriteSubrecord('VNAM',sizeof(RaceVoices),f);
			f->write<RaceVoices>(voices);
		}
		if (hair.female || hair.male)
		{
			WriteSubrecord('DNAM',sizeof(RaceHair),f);
			f->write<RaceHair>(hair);
		}
		WriteSubrecord('CNAM',1,f);
		f->write<ubyte>(hairColor);
		if (mainClamp)
		{
			WriteSubrecord('PNAM',4,f);
			f->write<float>(mainClamp);
		}
		if (faceClamp)
		{
			WriteSubrecord('UNAM',4,f);
			f->write<float>(faceClamp);
		}
		WriteSubrecord('ATTR',sizeof(RaceAttributes),f);
		f->write<RaceAttributes>(attributes);
		WriteSubrecord('NAM0',0,f);
		for (int i = 0;i < faces.Count();i++)
		{
			WriteSubrecord('INDX',4,f);
			f->write<ulong>(faces[i].index);
			WriteZStringSubrecord('MODL',faces[i].model,f);
			if (faces[i].model)
			{
				WriteSubrecord('MODB',4,f);
				f->write<float>(faces[i].boundRadius);
			}
			if (faces[i].textureHashes)
			{
				WriteSubrecord('MODT',faces[i].textureHashesCount * sizeof(TextureHash),f);
				f->writearray<TextureHash>(faces[i].textureHashesCount,faces[i].textureHashes);
			}
			WriteZStringSubrecord('ICON',faces[i].icon,f);
		}
		WriteSubrecord('NAM1',0,f);
		WriteSubrecord('MNAM',0,f);
		WriteZStringSubrecord('MODL',maleData.model,f);
		if (maleData.model)
		{
			WriteSubrecord('MODB',4,f);
			f->write<float>(maleData.boundRadius);
		}
		if (maleData.textureHashes)
		{
			WriteSubrecord('MODT',maleData.textureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(maleData.textureHashesCount,maleData.textureHashes);
		}
		for (int i = 0;i < maleData.bodyParts.Count();i++)
		{
			WriteSubrecord('INDX',4,f);
			f->write<ulong>(maleData.bodyParts[i].index);
			WriteZStringSubrecord('ICON',maleData.bodyParts[i].icon,f);
		}
		WriteSubrecord('FNAM',0,f);
		WriteZStringSubrecord('MODL',femaleData.model,f);
		if (femaleData.model)
		{
			WriteSubrecord('MODB',4,f);
			f->write<float>(femaleData.boundRadius);
		}
		if (femaleData.textureHashes)
		{
			WriteSubrecord('MODT',femaleData.textureHashesCount * sizeof(TextureHash),f);
			f->writearray<TextureHash>(femaleData.textureHashesCount,femaleData.textureHashes);
		}
		for (int i = 0;i < femaleData.bodyParts.Count();i++)
		{
			WriteSubrecord('INDX',4,f);
			f->write<ulong>(femaleData.bodyParts[i].index);
			WriteZStringSubrecord('ICON',femaleData.bodyParts[i].icon,f);
		}
		WriteSubrecord('HNAM',hairCount * 4,f);
		if (hairs)
		{
			f->writearray<formid>(hairCount,hairs);
		}
		WriteSubrecord('ENAM',eyeCount * 4,f);
		if (eyes)
		{
			f->writearray<formid>(eyeCount,eyes);
		}
		if (fggsSize)
		{
			WriteSubrecord('FGGS',fggsSize,f);
			f->writearray<byte>(fggsSize,fggs);
		}
		if (fggaSize)
		{
			WriteSubrecord('FGGA',fggaSize,f);
			f->writearray<byte>(fggaSize,fgga);
		}
		if (fgtsSize)
		{
			WriteSubrecord('FGTS',fgtsSize,f);
			f->writearray<byte>(fgtsSize,fgts);
		}
		WriteSubrecord('SNAM',2,f);
		f->write<ushort>(snam);
	}
	virtual int GetSaveSize()
	{
		int size = 0;
		size += ZStringSubrecordSize(editorID);
		size += ZStringSubrecordSize(fullName);
		size += ZStringSubrecordSize(description);
		for (int i = 0;i < spellList.Count();i++)
		{
			size += ComputeSubrecordSize(4);
		}
		for (int i = 0;i < relations.Count();i++)
		{
			size += ComputeSubrecordSize(8);
		}
		size += ComputeSubrecordSize(sizeof(RaceData));
		if (voices.female || voices.male)
		{
			size += ComputeSubrecordSize(sizeof(RaceVoices));
		}
		if (hair.female || hair.male)
		{
			size += ComputeSubrecordSize(sizeof(RaceHair));
		}
		size += ComputeSubrecordSize(1);
		if (mainClamp)
		{
			size += ComputeSubrecordSize(4);
		}
		if (faceClamp)
		{
			size += ComputeSubrecordSize(4);
		}
		size += ComputeSubrecordSize(sizeof(RaceAttributes));
		size += ComputeSubrecordSize(0);
		for (int i = 0;i < faces.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ZStringSubrecordSize(faces[i].model);
			if (faces[i].model)
			{
				size += ComputeSubrecordSize(4);
			}
			if (faces[i].textureHashes)
			{
				size += ComputeSubrecordSize(faces[i].textureHashesCount * sizeof(TextureHash));
			}
			size += ZStringSubrecordSize(faces[i].icon);
		}
		size += ComputeSubrecordSize(0);
		size += ComputeSubrecordSize(0);
		size += ZStringSubrecordSize(maleData.model);
		if (maleData.model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (maleData.textureHashes)
		{
			size += ComputeSubrecordSize(maleData.textureHashesCount * sizeof(TextureHash));
		}
		for (int i = 0;i < maleData.bodyParts.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ZStringSubrecordSize(maleData.bodyParts[i].icon);
		}
		size += ComputeSubrecordSize(0);
		size += ZStringSubrecordSize(femaleData.model);
		if (femaleData.model)
		{
			size += ComputeSubrecordSize(4);
		}
		if (femaleData.textureHashes)
		{
			size += ComputeSubrecordSize(femaleData.textureHashesCount * sizeof(TextureHash));
		}
		for (int i = 0;i < femaleData.bodyParts.Count();i++)
		{
			size += ComputeSubrecordSize(4);
			size += ZStringSubrecordSize(femaleData.bodyParts[i].icon);
		}
		size += ComputeSubrecordSize(hairCount * 4);
		size += ComputeSubrecordSize(eyeCount * 4);
		if (fggsSize)
		{
			size += ComputeSubrecordSize(fggsSize);
		}
		if (fggaSize)
		{
			size += ComputeSubrecordSize(fggaSize);
		}
		if (fgtsSize)
		{
			size += ComputeSubrecordSize(fgtsSize);
		}
		size += ComputeSubrecordSize(2);
		return size;
	}
};
