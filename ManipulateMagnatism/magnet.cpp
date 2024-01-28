//=========================================================
//
// 磁石ブロック処理 [magnet.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "main.h"
#include "magnet.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "xfile.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "bossBattle.h"
#include "tutorial.h"
#include "manager.h"
#include "debugproc.h"

//===============================================
// 定数定義
//===============================================
namespace
{
	const float LENTH_MAGNET = 100.0f;		// 磁石が反応する距離
}

//===============================================
// 静的メンバ変数
//===============================================
int CMagnet::m_aIdxXFile[MODEL_MAX] = {};	// 使用するXファイルの番号

//===============================================
// コンストラクタ
//===============================================
CMagnet::CMagnet() : CObjectX(3)
{
	// 値をクリアする
	m_state = STATE_NONE;
	m_mtxWorld;
	m_nIdxShadow = -1;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CMagnet::CMagnet(int nPriority) : CObjectX(nPriority)
{
	// 値をクリアする
	m_state = STATE_NONE;
	m_mtxWorld;
	m_nIdxShadow = -1;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//===============================================
// デストラクタ
//===============================================
CMagnet::~CMagnet()
{

}

//===============================================
// 生成処理
//===============================================
CMagnet *CMagnet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type, int nPriority)
{
	CMagnet *pObjX;

	// オブジェクトの生成
	pObjX = new CMagnet(nPriority);

	// 種類の設定
	if (type == MODEL_DAMAGE)
	{
		pObjX->SetType(TYPE_BOXDAMAGE);
	}
	else
	{
		pObjX->SetType(TYPE_BOXNORMAL);
	}

	// モデルの設定
	pObjX->SetModel(type);

	// 初期化処理
	pObjX->Init(pos);

	// 向き設定
	pObjX->SetRot(rot);

	return pObjX;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CMagnet::Init(D3DXVECTOR3 pos)
{
	//// 影を設定
	//m_nIdxShadow = SetShadow();

	// 位置を反映
	m_pos = pos;

	m_state = STATE_N;

	CObjectX::Init(m_pos);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CMagnet::Uninit(void)
{
	CObjectX::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CMagnet::Update(void)
{
	D3DXVECTOR3 playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// プレイヤーの位置
	D3DXVECTOR3 playerPosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// プレイヤーの前回の位置
	D3DXVECTOR3 playerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// プレイヤーの向き
	CObject *pObj = NULL;

	m_posOld = m_pos;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CObject *pObject = CObject::GetTop(nCntPriority);		// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{// 使用されている
			CObject *pObjectNext = pObject->GetNext();		// 次のオブジェクトを保存
			CObject::TYPE type = pObject->GetType();		// 種類を取得

			if (type == CObject::TYPE_PLAYER)
			{// プレイヤー
				playerPos = pObject->GetPos();			// 位置を取得
				playerPosOld = pObject->GetPosOld();	// 前回の位置を取得
				playerRot = pObject->GetRot();			// 向きを取得
				pObj = pObject;
			}

			pObject = pObjectNext;		// 次のオブジェクトを代入
		}
	}

	//CollisionModel(&playerPos, &playerPosOld, 0, pObj, true);

	// 当たり判定
	//CGame::GetPlayer()->CollisionObjX(&m_pos, &m_posOld, m_vtxMax, m_vtxMin);
	//CGame::GetEnemy()->CollisionObjX(&m_pos, &m_posOld, m_vtxMax, m_vtxMin);
}

//===============================================
// 描画処理
//===============================================
void CMagnet::Draw(void)
{
	CObjectX::Draw();
}

//===============================================
// 描画処理
//===============================================
void CMagnet::DrawXFile(int nIdx, CXFile::COL col)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;										// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// Xファイルの描画
	CManager::GetInstance()->GetXFile()->Draw(nIdx, col);
}

//===============================================
// プレイヤーとの当たり判定
//===============================================
bool CMagnet::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool bLand = false;
	float fLenth = 0.0f;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CObject *pObject = CObject::GetTop(nCntPriority);		// 先頭のオブジェクトを代入
		
		while (pObject != NULL)
		{// 使用されている
			CObject *pObjectNext = pObject->GetNext();		// 次のオブジェクトを保存
			CObject::TYPE type = pObject->GetType();		// 種類を取得
			D3DXVECTOR3 pos = pObject->GetPos();			// 位置
			D3DXVECTOR3 posOld = pObject->GetPosOld();		// 前回の位置
			D3DXVECTOR3 sizeMax = pObject->GetSize();		// 最大サイズ
			D3DXVECTOR3 sizeMin = pObject->GetSizeMin();	// 最小サイズ

			if (type == CObject::TYPE_BOXDAMAGE)
			{// プレイヤー
				if (pos.x + sizeMin.x - vtxMax.x <= pPos->x && pos.x + sizeMax.x - vtxMin.x >= pPos->x
					&& pos.z + sizeMin.z - LENTH_MAGNET <= pPos->z - vtxMin.z && pos.z + sizeMax.z + LENTH_MAGNET >= pPos->z + vtxMin.z
					&& pos.y + sizeMin.y - LENTH_MAGNET <= pPos->y + vtxMax.y && pos.y + sizeMax.y + LENTH_MAGNET >= pPos->y + vtxMin.y)
				{// 範囲内にある
					CPlayer::EState state = CPlayer::STATE_NONE;

					if (CManager::GetMode() == CScene::MODE_GAME)
					{
						state = CGame::GetPlayer()->GetState();
					}
					else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
					{
						state = CTutorial::GetPlayer()->GetState();
					}
					else
					{
						state = CBossBattle::GetPlayer()->GetState();
					}

					if (CManager::GetMode() == CScene::MODE_GAME)
					{
						// プレイヤーとブロックの距離や向きを計算し逆向きに飛ばす
						D3DXVECTOR3 vecDiff;
						vecDiff.z = pPos->z - pos.z;
						vecDiff.y = pPos->y - pos.y;

						D3DXVec3Normalize(&vecDiff, &vecDiff);
						//vecDiff *= 0.08f;

						// 向きを目標方向に補正
						float fAngleDist = atan2f(vecDiff.y, vecDiff.z);

						// プレイヤーまでの距離を計算
						D3DXVECTOR3 vecDiffDelete;
						vecDiffDelete.x = pPos->x - pos.x;
						vecDiffDelete.y = pPos->y - pos.y;
						vecDiffDelete.z = pPos->z - pos.z;
						fLenth = D3DXVec3Length(&vecDiffDelete);
						fLenth = 220.0f - fLenth;

						//CGame::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, posOld.y - vtxMin.y + sizeMax.y, pPos->z));
						if (CGame::GetPlayer()->GetMagnet() == true)
						{// 反発
							CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, sinf(D3DX_PI * ROT_UP + fAngleDist) * fLenth, cosf(D3DX_PI * ROT_UP + fAngleDist) * fLenth));
						}
						else
						{// 引き寄せ
							//CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, sinf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth, cosf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth));
						}
					}

					if (posOld.y + sizeMax.y + LENTH_MAGNET <= pPosOld->y + vtxMin.y
						&& pos.y + sizeMax.y + LENTH_MAGNET >= pPos->y + vtxMin.y)
					{// 上からめり込んだ
						// 上にのせる
						if (CManager::GetMode() == CScene::MODE_GAME)
						{
						}
						else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
						{
							//CTutorial::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, posOld.y - vtxMin.y + sizeMax.y, pPos->z));
							CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, 0.0f, CTutorial::GetPlayer()->GetMove().z));
						}

						//if (pObject->GetType() == CObject::TYPE_BOXNORMAL)
						//{
							if (CManager::GetMode() == CScene::MODE_GAME)
							{
								CGame::GetPlayer()->SetState(CPlayer::STATE_NORMAL);
							}
							else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
							{
								CTutorial::GetPlayer()->SetState(CPlayer::STATE_NORMAL);
							}
							else
							{
								CBossBattle::GetPlayer()->SetState(CPlayer::STATE_NORMAL);
							}
						//}
						//else
						//{
						//	if (CManager::GetMode() == CScene::MODE_GAME)
						//	{
						//		CGame::GetPlayer()->SetState(CPlayer::STATE_DAMAGE);
						//	}
						//	else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
						//	{
						//		CTutorial::GetPlayer()->SetState(CPlayer::STATE_DAMAGE);
						//	}
						//	else
						//	{
						//		CBossBattle::GetPlayer()->SetState(CPlayer::STATE_DAMAGE);
						//	}
						//}

						bLand = true;
					}
					else if (posOld.y + sizeMin.y >= pPosOld->y + vtxMax.y
						&& pos.y + sizeMin.y <= pPos->y + vtxMax.y)
					{// 下からめり込んだ
						// 下に戻す
						if (CManager::GetMode() == CScene::MODE_GAME)
						{
							CGame::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, posOld.y - vtxMax.y + sizeMin.y, pPos->z));
							CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, 0.0f, CGame::GetPlayer()->GetMove().z));
						}
						else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
						{
							CTutorial::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, posOld.y - vtxMax.y + sizeMin.y, pPos->z));
							CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, 0.0f, CTutorial::GetPlayer()->GetMove().z));
						}
						else
						{
							CBossBattle::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, posOld.y - vtxMax.y + sizeMin.y, pPos->z));
							CBossBattle::GetPlayer()->SetMove(D3DXVECTOR3(CBossBattle::GetPlayer()->GetMove().x, 0.0f, CBossBattle::GetPlayer()->GetMove().z));
						}
					}
					else if (posOld.z + sizeMin.z >= pPosOld->z - vtxMin.z
						&& pos.z + sizeMin.z <= pPos->z - vtxMin.z)
					{// 左から右にめり込んだ
						// 位置を戻す
						if (CManager::GetMode() == CScene::MODE_GAME)
						{
							CGame::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, pPos->y, posOld.z + vtxMin.z + sizeMin.z));
						}
						else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
						{
							CTutorial::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, pPos->y, posOld.z + vtxMin.z + sizeMin.z));
						}
						else
						{
							CBossBattle::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, pPos->y, posOld.z + vtxMin.z + sizeMin.z));
						}
					}
					else if (posOld.z + sizeMax.z <= pPosOld->z + vtxMin.z
						&& pos.z + sizeMax.z >= pPos->z + vtxMin.z)
					{// 右から左にめり込んだ
						// 位置を戻す
						if (CManager::GetMode() == CScene::MODE_GAME)
						{
							CGame::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, pPos->y, posOld.z - vtxMin.z + sizeMax.z));
						}
						else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
						{
							CTutorial::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, pPos->y, posOld.z - vtxMin.z + sizeMax.z));
						}
						else
						{
							CBossBattle::GetPlayer()->SetPos(D3DXVECTOR3(pPos->x, pPos->y, posOld.z - vtxMin.z + sizeMax.z));
						}
					}
				}
			}
			pObject = pObjectNext;		// 次のオブジェクトを代入
		}
	}
	CManager::GetInstance()->GetDebugProc()->Print(" プレイヤーの移動距離：%f\n", fLenth);

	return bLand;
}

//===============================================
// 敵との当たり判定
//===============================================
bool CMagnet::CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pRot, D3DXVECTOR3 *pMove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool bLand = false;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CObject *pObject = CObject::GetTop(nCntPriority);		// 先頭のオブジェクトを代入

		while (pObject != NULL)
		{// 使用されている
			CObject *pObjectNext = pObject->GetNext();		// 次のオブジェクトを保存
			CObject::TYPE type = pObject->GetType();		// 種類を取得
			D3DXVECTOR3 pos = pObject->GetPos();			// 位置
			D3DXVECTOR3 posOld = pObject->GetPosOld();		// 前回の位置
			D3DXVECTOR3 sizeMax = pObject->GetSize();		// 最大サイズ
			D3DXVECTOR3 sizeMin = pObject->GetSizeMin();	// 最小サイズ

			if (type == CObject::TYPE_BOXNORMAL || type == CObject::TYPE_BOXDAMAGE)
			{// プレイヤー
				if (pos.x + sizeMin.x - vtxMax.x <= pPos->x && pos.x + sizeMax.x - vtxMin.x >= pPos->x
					&& pos.z + sizeMin.z <= pPos->z - vtxMin.z && pos.z + sizeMax.z >= pPos->z + vtxMin.z
					&& pos.y + sizeMin.y <= pPos->y + vtxMax.y && pos.y + sizeMax.y >= pPos->y + vtxMin.y)
				{// 範囲内にある
					if (posOld.y + sizeMax.y <= pPosOld->y + vtxMin.y
						&& pos.y + sizeMax.y >= pPos->y + vtxMin.y)
					{// 上からめり込んだ
						// 上にのせる
						pPos->y = posOld.y - vtxMin.y + sizeMax.y;
						pMove->y = 0.0f;

						bLand = true;
					}
					else if (posOld.y + sizeMin.y >= pPosOld->y + vtxMax.y
						&& pos.y + sizeMin.y <= pPos->y + vtxMax.y)
					{// 下からめり込んだ
						// 下に戻す
						pPos->y = posOld.y - vtxMax.y + sizeMin.y;
						//CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, 0.0f, CGame::GetPlayer()->GetMove().z));
					}
					else if (posOld.z + sizeMin.z >= pPosOld->z - vtxMin.z
						&& pos.z + sizeMin.z <= pPos->z - vtxMin.z)
					{// 左から右にめり込んだ
						// 位置を戻す
						pPos->z = posOld.z + vtxMin.z + sizeMin.z;
						pRot->y = D3DX_PI * ROT_RIGHT + (ROT_CAMERA * CManager::GetInstance()->GetCamera()->GetRot().y);
					}
					else if (posOld.z + sizeMax.z <= pPosOld->z + vtxMin.z
						&& pos.z + sizeMax.z >= pPos->z + vtxMin.z)
					{// 右から左にめり込んだ
						// 位置を戻す
						pPos->z = posOld.z - vtxMin.z + sizeMax.z;
						pRot->y = D3DX_PI * ROT_LEFT + (ROT_CAMERA * CManager::GetInstance()->GetCamera()->GetRot().y);
					}
				}
			}
			pObject = pObjectNext;		// 次のオブジェクトを代入
		}
	}

	return bLand;
}