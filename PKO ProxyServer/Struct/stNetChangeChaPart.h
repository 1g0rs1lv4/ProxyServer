#pragma once

const long	ITEMATTR_MAX_NUM = 58;

class CItemAttr
{
public:
	short	m_sAttr[ITEMATTR_MAX_NUM];
	bool	m_bInitFlag;

};

enum EItemDBParam
{
	enumITEMDBP_FORGE,
	enumITEMDBP_INST_ID,

	enumITEMDBP_MAXNUM,
};

#define defITEM_INSTANCE_ATTR_NUM			5

#pragma pack(push,1)
struct SItemGrid
{
public:
	short   sID;
	short   sNum;
	short   sEndure[2];
	short   sEnergy[2];
	char    chForgeLv;
	unsigned char unk;
	long    lDBParam[enumITEMDBP_MAXNUM];
	short   sInstAttr[defITEM_INSTANCE_ATTR_NUM][2];
	CItemAttr   CAttr;

	bool    bValid;
	bool    bChange;

};
#pragma pack(pop)

enum EEquipLinkPos
{
	enumEQUIP_HEAD = 0,
	enumEQUIP_FACE = 1,
	enumEQUIP_BODY = 2,
	enumEQUIP_GLOVE = 3,
	enumEQUIP_SHOES = 4,

	enumEQUIP_NECK = 5,
	enumEQUIP_LHAND = 6,
	enumEQUIP_HAND1 = 7,
	enumEQUIP_HAND2 = 8,
	enumEQUIP_RHAND = 9,

	enumEQUIP_PART_NUM = 5,
	enumEQUIP_NUM = 10,
	enumEQUIP_BOTH_HAND = 9999,
	enumEQUIP_TOTEM = 9998,
};

typedef
struct stNetChangeChaPart
{
	stNetChangeChaPart() { sVer = 0; sTypeID = 0; }

	short   sVer;
	short   sTypeID;
	SItemGrid   SLink[enumEQUIP_NUM];
	short       sHairID;
} LOOK;