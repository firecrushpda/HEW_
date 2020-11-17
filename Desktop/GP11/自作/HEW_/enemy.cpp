//=============================================================================
//
// エネミーモデル処理 [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "enemy.h"
#include "shadow.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_ENEMY		"data/MODEL/miku_02.obj"		// 読み込むモデル名

#define	VALUE_MOVE		(5.0f)							// 移動量
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)				// 回転量

#define ENEMY_SHADOW_SIZE	(0.4f)						// 影の大きさ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
int count;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ENEMY			g_Enemy[MAX_ENEMY];				// エネミー

//=============================================================================
// 初期化処理
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

		g_Enemy[i].spd = 1.0f;		// 移動スピードクリア

		D3DXVECTOR3 pos = g_Enemy[i].pos;
		pos.y = 0.0f;
		g_Enemy[i].shadowIdx = CreateShadow(pos, ENEMY_SHADOW_SIZE, ENEMY_SHADOW_SIZE);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	// モデルの解放処理
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		UnloadModel(&g_Enemy[i].model);
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateEnemy(void)
{
	//エネミーを動かす時　シャドウを同時
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
// 描画処理
//=============================================================================
void DrawEnemy(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	for (int i = 0; i < MAX_ENEMY; i++)
	{	
		if (g_Enemy[i].use == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Enemy[i].mtxWorld);

			// スケールを反映
			D3DXMatrixScaling(&mtxScl, g_Enemy[i].scl.x, g_Enemy[i].scl.y, g_Enemy[i].scl.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxScl);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Enemy[i].rot.y, g_Enemy[i].rot.x, g_Enemy[i].rot.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, g_Enemy[i].pos.x, g_Enemy[i].pos.y, g_Enemy[i].pos.z);
			D3DXMatrixMultiply(&g_Enemy[i].mtxWorld, &g_Enemy[i].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			SetWorldMatrix(&g_Enemy[i].mtxWorld);

			// モデル描画
			DrawModel(&g_Enemy[i].model);
		}
		
	}

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);
}

//=============================================================================
// エネミーの取得
//=============================================================================
ENEMY *GetEnemy()
{
	return &(g_Enemy[0]);
}
