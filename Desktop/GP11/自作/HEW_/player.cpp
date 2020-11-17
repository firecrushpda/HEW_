//=============================================================================
//
// ���f������ [player.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "shadow.h"
#include "renderer.h"
#include "MathUtil.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/miku_01.obj"		// �ǂݍ��ރ��f����

#define	VALUE_MOVE			(2.0f)							// �ړ���
#define	VALUE_ROTATE		(D3DX_PI * 0.02f)				// ��]��

#define PLAYER_SHADOW_SIZE	(0.4f)							// �e�̑傫��
#define segmentNum			(60)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
float temprotY;
//static int count;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static PLAYER				g_Player;						// �v���C���[

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LoadModel(MODEL_PLAYER, &g_Player.model);

	g_Player.count = 0;

	g_Player.pos = D3DXVECTOR3(0.0f, 7.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	g_Player.spd = 0.0f;		// �ړ��X�s�[�h�N���A
	g_Player.jumpspd = 100.0f;
	g_Player.isUp = true;

	//�����Ńv���[���[�p
	D3DXVECTOR3 pos = g_Player.pos;
	pos.y = 0.0f;
	g_Player.shadowIdx = CreateShadow(pos, PLAYER_SHADOW_SIZE, PLAYER_SHADOW_SIZE);

	g_Player.curve = GetThreePowerBeizerList(D3DXVECTOR3(0.0f, 0.07f, 0.0f), D3DXVECTOR3(0, 0.7, 0), D3DXVECTOR3(0, 0.9, 0), D3DXVECTOR3(1, 1, 0), segmentNum);

	//g_Player.curve = GetCubicBeizerList(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), segmentNum);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	// ���f���̉������
	UnloadModel(&g_Player.model);

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	CAMERA *cam = GetCamera();

	g_Player.spd *= 0.0f;

	// �ړ�����
	if (GetKeyboardPress(DIK_LEFT))
	{
		g_Player.spd = VALUE_MOVE;
		temprotY = D3DX_PI / 2;
		
	}
	if (GetKeyboardPress(DIK_RIGHT))
	{
		g_Player.spd = VALUE_MOVE;
		temprotY = -D3DX_PI / 2;
	}
	if (GetKeyboardPress(DIK_UP))
	{
		g_Player.spd = VALUE_MOVE;
		temprotY = D3DX_PI;
	}
	if (GetKeyboardPress(DIK_DOWN))
	{
		g_Player.spd = VALUE_MOVE;
		temprotY = 0.0f;
	}

	if (GetKeyboardPress(DIK_SPACE))
	{
		g_Player.pos.z = g_Player.pos.x = 0.0f;
		g_Player.spd = 0.0f;
	}

	cam->at = g_Player.pos;

	g_Player.rot.y = cam->rot.y + temprotY;

	cam->pos.x = cam->at.x - sinf(cam->rot.y) * cam->len;
	cam->pos.z = cam->at.z - cosf(cam->rot.y) * cam->len;

	g_Player.pos.x -=  sinf(g_Player.rot.y) * g_Player.spd;
	g_Player.pos.z -=  cosf(g_Player.rot.y) * g_Player.spd;
	//g_Player.rot

	
	if (g_Player.isUp)
	{
		g_Player.pos.y = g_Player.curve[g_Player.count].y * g_Player.jumpspd;
	}
	else
	{
		g_Player.pos.y = g_Player.jumpspd - g_Player.curve[g_Player.count].y * g_Player.jumpspd;
	}
	g_Player.count += 1;

	if (g_Player.pos.y >= g_Player.jumpspd)
	{
		g_Player.isUp = false;
		g_Player.count = 0;
	}
	if (g_Player.pos.y <= 0)
	{
		g_Player.isUp = true;
		g_Player.count = 0;
	}
	
	

	// �e���v���C���[�̈ʒu�ɍ��킹��
	D3DXVECTOR3 pos = g_Player.pos;
	pos.y = 0.0f;
	SetPositionShadow(g_Player.shadowIdx, pos);
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y + D3DX_PI, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&g_Player.mtxWorld);

	// ���f���`��
	DrawModel(&g_Player.model);

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// �v���C���[�����擾
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

