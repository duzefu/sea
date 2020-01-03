/*
**	NetGE_Misc.h 
**	misc functions header.
**
**	Jack, 2003.1.7
*/
#pragma once


//
// DEFINES //////////////////////////////////////////////////////////////////////////////////////////////////
//
#define BOAT_SPEED_RESISTANCE_RATE			0.8		//��t�שM���O�����Y�ʤ���
#define MAX_BOAT_DIR						360     //��঳���̦h��V
#define MAX_WIND_DIR						8       //���঳���̦h��V
#define BOAT_SPEED_ACCURACY					10		//���0.1

//
// VARIABLE ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern  FLOAT   g_32dir_vector[32][3];      //�O�s����p��n��...32��V�����q
extern  FLOAT   g_32dir_rotation[32][3];      //�O�s����p��n��...32��V�����઺
//
// FUNCTIONS ////////////////////////////////////////////////////////////////////////////////////////////////
//
extern	void	DebugLogShipMath(void);
extern  void    ShipDegreeDirToVector(SLONG degree_dir, FLOAT dir[3]);
extern  void    WindDirToVector(SLONG degree_dir,FLOAT dir[3]);
extern  void    ShipWindDirToForceVector(SLONG boat_dir,SLONG wind_dir,FLOAT dir[3] );
extern	void    ComputeSeaCharacterSailForce(float wind[3], float boat_dir[3], float wind_use_rate,
											 float boat_force[3], float sail_dir[3]) ;
extern	void    ComputeSeaCharacterSailResistance(float boat_weight, float speedx, float speedy,
												  float boat_dir[3], float resist[3]);
//
extern	void    VectorSub(float in1[3] , float in2[3] , float out[3] );
extern	void    VectorAdd(float in1[3] , float in2[3] , float out[3] );
extern	float   VectorDotProduct(float in1[3] , float in2[3] );
extern	void    VectorCrossProduct(float in1[3],float in2[3],float out[3]);
extern	float   VectorAbsolute ( float in1[3]  );
extern	float   VectorNormal( float normal[3] );
extern	void    CreateUnitMatrix( float out[4][4] );
extern	void    CreateZeroMatrix( float out[4][4] );
extern	void    VectorZCross(float in[3],float out1[3],float out2[3] );
extern	void	Vertex3DRoateZ(FLOAT in[3],FLOAT out[3],FLOAT radians);

//��V���ǬO�q12�I�}�l�����ɰw��V
extern	SLONG   Vertex2Dir8(SLONG  in_of_pos[3]);
extern	SLONG   Vertex2Dir16(SLONG  in_of_pos[3]);
extern	SLONG   Vertex2Dir32(SLONG  in_of_pos[3]);
//  ���P��V�зǤ������ഫ
extern  SLONG   DirChange(SLONG lScDir, SLONG lScDirMax, SLONG lTagDirMax);
//  ��}�l��
//---
extern	void    IniMiscMath(void);
//  ����B��
extern	SLONG	Involution(SLONG x, SLONG y);

