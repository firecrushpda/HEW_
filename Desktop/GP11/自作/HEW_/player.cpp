//=============================================================================
//
// モデル処理 [player.cpp]
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
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/miku_01.obj"		// 読み込むモデル名

#define	VALUE_MOVE			(2.0f)							// 移動量
#define	VALUE_ROTATE		(D3DX_PI * 0.02f)				// 回転量

#define PLAYER_SHADOW_SIZE	(0.4f)							// 影の大きさ
#define segmentNum			(60)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float temprotY;
//static int count;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static PLAYER				g_Player;						// プレイヤー

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LoadModel(MODEL_PLAYER, &g_Player.model);

	g_Player.count = 0;

	g_Player.pos = D3DXVECTOR3(0.0f, 7.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Player.scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	g_Player.spd = 0.0f;		// 移動スピードクリア
	g_Player.jumpspd = 100.0f;
	g_Player.isUp = true;

	//ここでプレーヤー用
	D3DXVECTOR3 pos = g_Player.pos;
	pos.y = 0.0f;
	g_Player.shadowIdx = CreateShadow(pos, PLAYER_SHADOW_SIZE, PLAYER_SHADOW_SIZE);

	g_Player.curve = GetThreePowerBeizerList(D3DXVECTOR3(0.0f, 0.07f, 0.0f), D3DXVECTOR3(0, 0.7, 0), D3DXVECTOR3(0, 0.9, 0), D3DXVECTOR3(1, 1, 0), segmentNum);

	//g_Player.curve = GetCubicBeizerList(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 1, 0), D3DXVECTOR3(0, 1, 0), segmentNum);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	// モデルの解放処理
	UnloadModel(&g_Player.model);

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{
	CAMERA *cam = GetCamera();

	g_Player.spd *= 0.0f;

	// 移動処理
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
	
	

	// 影もプレイヤーの位置に合わせる
	D3DXVECTOR3 pos = g_Player.pos;
	pos.y = 0.0f;
	SetPositionShadow(g_Player.shadowIdx, pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// カリング無効
	SetCullingMode(CULL_MODE_NONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, g_Player.scl.x, g_Player.scl.y, g_Player.scl.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y + D3DX_PI, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&g_Player.mtxWorld);

	// モデル描画
	DrawModel(&g_Player.model);

	// カリング設定を戻す
	SetCullingMode(CULL_MODE_BACK);
}


//=============================================================================
// プレイヤー情報を取得
//=============================================================================
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

