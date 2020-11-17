//=============================================================================
//
// �G�l�~�[���f������ [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "enemy.h"
#include "shadow.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_ENEMY		"data/MODEL/miku_02.obj"		// �ǂݍ��ރ��f����

#define	VALUE_MOVE		(5.0f)							// �ړ���
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// ��]��

#define ENEMY_SHADOW_SIZE	(0.4f)						// �e�̑傫��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int count;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ENEMY			g_Enemy[MAX_ENEMY];				// �G�l�~�[

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	srand((unsigned)time(NULL));

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//InitShadow();
		LoadModel(MODEL_ENEMY, &g_Enemy[i].model);

		float randx = -1000 + rand() % 2000;
		//float randy = (rand() % (-100 - 100 + 1)) + 100;
		float randz = -1000 + rand() % 2000;

		g_Enemy[i].pos = D3DXVECTOR3(randx, 7.0f, randz);
		g_Enemy[i].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_Enemy[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		float dirnormal = sqrtf(randx * randx + randz + randz);
		g_Enemy[i].dir = D3DXVECTOR3(-randx / dirnormal, 0, -randz / dirnormal);

		g_Enemy[i].spd = 1.0f;		// �ړ��X�s�[�h�N���A

		D3DXVECTOR3 pos = g_Enemy[i].pos;
		pos.y = 0.0f;
		g_Enemy[i].shadowIdx = CreateShadow(pos, ENEMY_SHADOW_SIZE, ENEMY_SHADOW_SIZE);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	// ���f���̉������
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		UnloadModel(&g_Enemy[i].model);
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	//�G�l�~�[�𓮂������@�V���h�E�𓯎�
	count++;
	g_Enemy[(int)count / 30].use = true;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (g_Enemy[i].use)
		{
			g_Enemy[i].pos.x += g_Enemy[i].dir.x * g_Enemy[i].spd;
			g_Enemy[i].pos.z += g_Enemy[i].dir.z * g_Enemy[i].spd;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// �J�����O����
	SetCullingMode(CULL_MODE_NONE);

	for (int i = 0; i < MAX_ENEMY; i++)
	{	
		if (g_Enemy[i].use == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			SetWorldMatrix(&g_Enemy[i].mtxWorld);

			// ���f���`��
			DrawModel(&g_Enemy[i].model);
		}
		
	}

	// �J�����O�ݒ��߂�
	SetCullingMode(CULL_MODE_BACK);
}

//=============================================================================
// �G�l�~�[�̎擾
//=============================================================================
ENEMY *GetEnemy()
{
	return &(g_Enemy[0]);
}
