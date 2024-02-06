//=========================================================
//
// ���΃u���b�N���� [magnet.cpp]
// Author = �����đ�Y
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
// �萔��`
//===============================================
namespace
{
	const float LENTH_MAGNET = 100.0f;		// ���΂��������鋗��
}

//===============================================
// �ÓI�����o�ϐ�
//===============================================
int CMagnet::m_aIdxXFile[MODEL_MAX] = {};	// �g�p����X�t�@�C���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CMagnet::CMagnet() : CObjectX(3)
{
	// �l���N���A����
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
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CMagnet::CMagnet(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A����
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
// �f�X�g���N�^
//===============================================
CMagnet::~CMagnet()
{

}

//===============================================
// ��������
//===============================================
CMagnet *CMagnet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL type, int nPriority)
{
	CMagnet *pObjX;

	// �I�u�W�F�N�g�̐���
	pObjX = new CMagnet(nPriority);

	// ��ނ̐ݒ�
	if (type == MODEL_DAMAGE)
	{
		pObjX->SetType(TYPE_BOXDAMAGE);
	}
	else
	{
		pObjX->SetType(TYPE_BOXNORMAL);
	}

	// ���f���̐ݒ�
	pObjX->SetModel(type);

	// ����������
	pObjX->Init(pos);

	// �����ݒ�
	pObjX->SetRot(rot);

	return pObjX;
}

//===============================================
// ����������
//===============================================
HRESULT CMagnet::Init(D3DXVECTOR3 pos)
{
	//// �e��ݒ�
	//m_nIdxShadow = SetShadow();

	// �ʒu�𔽉f
	m_pos = pos;

	m_state = STATE_N;

	CObjectX::Init(m_pos);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CMagnet::Uninit(void)
{
	CObjectX::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CMagnet::Update(void)
{
	D3DXVECTOR3 playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �v���C���[�̈ʒu
	D3DXVECTOR3 playerPosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �v���C���[�̑O��̈ʒu
	D3DXVECTOR3 playerRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �v���C���[�̌���
	CObject *pObj = NULL;

	m_posOld = m_pos;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CObject *pObject = CObject::GetTop(nCntPriority);		// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{// �g�p����Ă���
			CObject *pObjectNext = pObject->GetNext();		// ���̃I�u�W�F�N�g��ۑ�
			CObject::TYPE type = pObject->GetType();		// ��ނ��擾

			if (type == CObject::TYPE_PLAYER)
			{// �v���C���[
				playerPos = pObject->GetPos();			// �ʒu���擾
				playerPosOld = pObject->GetPosOld();	// �O��̈ʒu���擾
				playerRot = pObject->GetRot();			// �������擾
				pObj = pObject;
			}

			pObject = pObjectNext;		// ���̃I�u�W�F�N�g����
		}
	}

	//CollisionModel(&playerPos, &playerPosOld, 0, pObj, true);

	// �����蔻��
	//pPlayer->CollisionObjX(&m_pos, &m_posOld, m_vtxMax, m_vtxMin);
	//CGame::GetEnemy()->CollisionObjX(&m_pos, &m_posOld, m_vtxMax, m_vtxMin);
}

//===============================================
// �`�揈��
//===============================================
void CMagnet::Draw(void)
{
	CObjectX::Draw();
}

//===============================================
// �`�揈��
//===============================================
void CMagnet::DrawXFile(int nIdx, CXFile::COL col)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;										// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// X�t�@�C���̕`��
	CManager::GetInstance()->GetXFile()->Draw(nIdx, col);
}

//===============================================
// �v���C���[�Ƃ̓����蔻��
//===============================================
bool CMagnet::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool bLand = false;
	float fLenth = 0.0f;
	float fAngleDist = 0.0f;
	D3DXVECTOR3 vecDiff = {};

	CPlayer* pPlayer = nullptr;

	//pPlayer = CPlayer::GetInstance();

	//if (pPlayer != nullptr)
	//{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			CObject* pObject = CObject::GetTop(nCntPriority);		// �擪�̃I�u�W�F�N�g����

			while (pObject != NULL)
			{// �g�p����Ă���
				CObject* pObjectNext = pObject->GetNext();		// ���̃I�u�W�F�N�g��ۑ�
				CObject::TYPE type = pObject->GetType();		// ��ނ��擾
				D3DXVECTOR3 pos = pObject->GetPos();			// �ʒu
				D3DXVECTOR3 posOld = pObject->GetPosOld();		// �O��̈ʒu
				D3DXVECTOR3 sizeMax = pObject->GetSize();		// �ő�T�C�Y
				D3DXVECTOR3 sizeMin = pObject->GetSizeMin();	// �ŏ��T�C�Y

				if (type == CObject::TYPE_BOXDAMAGE)
				{// �v���C���[
					if (pos.x + sizeMin.x - vtxMax.x <= pPos->x && pos.x + sizeMax.x - vtxMin.x >= pPos->x
						&& pos.z + sizeMin.z - LENTH_MAGNET <= pPos->z - vtxMin.z && pos.z + sizeMax.z + LENTH_MAGNET >= pPos->z + vtxMin.z
						&& pos.y + sizeMin.y - LENTH_MAGNET <= pPos->y + vtxMax.y && pos.y + sizeMax.y + LENTH_MAGNET >= pPos->y + vtxMin.y)
					{// �͈͓��ɂ���
						CPlayer::EState state = CPlayer::STATE_NONE;
						if (CManager::GetMode() == CScene::MODE_GAME)
						{
							state = CGame::GetPlayer()->GetState();
						}
						else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
						{
							state = CTutorial::GetPlayer()->GetState();
						}

						// �v���C���[�ƃu���b�N�̋�����������v�Z���t�����ɔ�΂�
						vecDiff.z = pPos->z - pos.z;
						vecDiff.y = pPos->y - pos.y;

						D3DXVec3Normalize(&vecDiff, &vecDiff);
						//vecDiff *= 0.08f;

						// ������ڕW�����ɕ␳
						fAngleDist = atan2f(vecDiff.y, vecDiff.z);

						// �v���C���[�܂ł̋������v�Z
						vecDiff.x = pPos->x - pos.x;
						vecDiff.y = pPos->y - pos.y;
						vecDiff.z = pPos->z - pos.z;
						fLenth = D3DXVec3Length(&vecDiff);
						//fLenth = 200.0f - fLenth;

						if ((CManager::GetMode() == CScene::MODE_GAME && CGame::GetPlayer()->GetMagnet() == true)
							|| (CManager::GetMode() == CScene::MODE_TUTORIAL && CTutorial::GetPlayer()->GetMagnet() == true))
						{// ����
							//pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, sinf(D3DX_PI * ROT_UP + fAngleDist) * fLenth, cosf(D3DX_PI * ROT_UP + fAngleDist) * fLenth));
						}

						if ((CManager::GetMode() == CScene::MODE_GAME && CGame::GetPlayer()->GetMagnet() == true)
							|| (CManager::GetMode() == CScene::MODE_TUTORIAL && CTutorial::GetPlayer()->GetMagnet() == true))
						{// ����
							if (pos.z + sizeMin.z <= pPos->z
								&& pos.z + sizeMax.z >= pPos->z)
							{// �㉺����
								if (CManager::GetMode() == CScene::MODE_GAME)
								{
									CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, CGame::GetPlayer()->GetMove().y + (vecDiff.y * 0.02f), CGame::GetPlayer()->GetMove().z));
								}
								else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
								{
									CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, CTutorial::GetPlayer()->GetMove().y + (vecDiff.y * 0.02f), CTutorial::GetPlayer()->GetMove().z));
								}
							}
							else if (pos.z + sizeMax.z >= pPos->z)
							{// �E����
								if (CManager::GetMode() == CScene::MODE_GAME)
								{
									CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, CGame::GetPlayer()->GetMove().y + vecDiff.y * 0.04f, CGame::GetPlayer()->GetMove().z + vecDiff.z * 0.04f));
								}
								else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
								{
									CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, CTutorial::GetPlayer()->GetMove().y + vecDiff.y * 0.04f, CTutorial::GetPlayer()->GetMove().z + vecDiff.z * 0.04f));
								}
							}
							else if (pos.z + sizeMin.z <= pPos->z)
							{// ������
								if (CManager::GetMode() == CScene::MODE_GAME)
								{
									CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, CGame::GetPlayer()->GetMove().y + vecDiff.y * 0.04f, CGame::GetPlayer()->GetMove().z + vecDiff.z * 0.04f));
								}
								else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
								{
									CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, CTutorial::GetPlayer()->GetMove().y + vecDiff.y * 0.04f, CTutorial::GetPlayer()->GetMove().z + vecDiff.z * 0.04f));
								}
							}

							//if (pPlayer->GetMagnet() == true)
							//{
							//	if (pos.y + sizeMax.y + LENTH_MAGNET >= pPos->y + vtxMin.y
							//		&& posOld.y + sizeMax.y + LENTH_MAGNET <= pPosOld->y + vtxMin.y)
							//	{
							//		pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, 1.0f, pPlayer->GetMove().z));
							//	}
							//	else if (pPlayer->GetMagnet() == true && pPlayer->GetMagnetOld() == false)
							//	{
							//		if (pos.y + sizeMax.y <= pPos->y + vtxMin.y
							//			&& pos.z + sizeMin.z <= pPos->z
							//			&& pos.z + sizeMax.z >= pPos->z)
							//		{// �^�ォ��
							//			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y + fLenth * 0.3f, pPlayer->GetMove().z));
							//		}
							//		else if (posOld.y + sizeMax.y <= pPosOld->y + vtxMin.y
							//			&& pos.z + sizeMax.z >= pPos->z)
							//		{// �E�΂߂���
							//			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y + vecDiff.y * 0.04f, pPlayer->GetMove().z + vecDiff.z * 0.04f));
							//		}
							//		else if (posOld.y + sizeMax.y <= pPosOld->y + vtxMin.y
							//			&& pos.z + sizeMin.z <= pPos->z)
							//		{// ���΂߂���
							//			pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, pPlayer->GetMove().y + vecDiff.y * 0.04f, pPlayer->GetMove().z + vecDiff.z * 0.04f));
							//		}
							//	}
							//}
						}
						else if ((CManager::GetMode() == CScene::MODE_GAME && CGame::GetPlayer()->GetMagnet() == false)
						|| (CManager::GetMode() == CScene::MODE_TUTORIAL && CTutorial::GetPlayer()->GetMagnet() == false))
						{// ������
							if (pos.z + sizeMin.z <= pPos->z
								&& pos.z + sizeMax.z >= pPos->z)
							{// �㉺����
								if (CManager::GetMode() == CScene::MODE_GAME)
								{
									CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, sinf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth * 0.1f, cosf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth * 0.1f));
								}
								else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
								{
									CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, CTutorial::GetPlayer()->GetMove().y - (vecDiff.y * 0.02f), CTutorial::GetPlayer()->GetMove().z));
								}
							}
							else if (pos.z + sizeMax.z >= pPos->z)
							{// �E����
								if (CManager::GetMode() == CScene::MODE_GAME)
								{
									CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, sinf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth * 0.1f, cosf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth * 0.1f));
								}
								else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
								{
									CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, CTutorial::GetPlayer()->GetMove().y - vecDiff.y * 0.04f, CTutorial::GetPlayer()->GetMove().z - vecDiff.z * 0.04f));
								}
							}
							else if (pos.z + sizeMin.z <= pPos->z)
							{// ������
								if (CManager::GetMode() == CScene::MODE_GAME)
								{
									CGame::GetPlayer()->SetMove(D3DXVECTOR3(CGame::GetPlayer()->GetMove().x, sinf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth * 0.1f, cosf(D3DX_PI * ROT_DOWN + fAngleDist) * fLenth * 0.1f));
								}
								else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
								{
									CTutorial::GetPlayer()->SetMove(D3DXVECTOR3(CTutorial::GetPlayer()->GetMove().x, CTutorial::GetPlayer()->GetMove().y - vecDiff.y * 0.04f, CTutorial::GetPlayer()->GetMove().z - vecDiff.z * 0.04f));
								}
							}
						}
						D3DXVECTOR3 move = {};

						if (CManager::GetMode() == CScene::MODE_GAME)
						{
							move = CGame::GetPlayer()->GetMove();

							if (move.y >= 25.0f)
							{
								move.y = 25.0f;
								CGame::GetPlayer()->SetMove(move);
							}
							if (move.z >= 25.0f)
							{
								move.z = 25.0f;
								CGame::GetPlayer()->SetMove(move);
							}
						}
						else if (CManager::GetMode() == CScene::MODE_TUTORIAL)
						{
							move = CTutorial::GetPlayer()->GetMove();

							if (move.y >= 25.0f)
							{
								move.y = 25.0f;
								CTutorial::GetPlayer()->SetMove(move);
							}
							if (move.z >= 25.0f)
							{
								move.z = 25.0f;
								CTutorial::GetPlayer()->SetMove(move);
							}
						}
					}
				}
				pObject = pObjectNext;		// ���̃I�u�W�F�N�g����
			}
		}
	//}
	CManager::GetInstance()->GetDebugProc()->Print(" �v���C���[�̈ړ������F%f\n", fLenth);

	return bLand;
}

//===============================================
// �G�Ƃ̓����蔻��
//===============================================
bool CMagnet::CollisionEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pRot, D3DXVECTOR3 *pMove, D3DXVECTOR3 vtxMax, D3DXVECTOR3 vtxMin)
{
	bool bLand = false;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CObject *pObject = CObject::GetTop(nCntPriority);		// �擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{// �g�p����Ă���
			CObject *pObjectNext = pObject->GetNext();		// ���̃I�u�W�F�N�g��ۑ�
			CObject::TYPE type = pObject->GetType();		// ��ނ��擾
			D3DXVECTOR3 pos = pObject->GetPos();			// �ʒu
			D3DXVECTOR3 posOld = pObject->GetPosOld();		// �O��̈ʒu
			D3DXVECTOR3 sizeMax = pObject->GetSize();		// �ő�T�C�Y
			D3DXVECTOR3 sizeMin = pObject->GetSizeMin();	// �ŏ��T�C�Y

			if (type == CObject::TYPE_BOXNORMAL || type == CObject::TYPE_BOXDAMAGE)
			{// �v���C���[
				if (pos.x + sizeMin.x - vtxMax.x <= pPos->x && pos.x + sizeMax.x - vtxMin.x >= pPos->x
					&& pos.z + sizeMin.z <= pPos->z - vtxMin.z && pos.z + sizeMax.z >= pPos->z + vtxMin.z
					&& pos.y + sizeMin.y <= pPos->y + vtxMax.y && pos.y + sizeMax.y >= pPos->y + vtxMin.y)
				{// �͈͓��ɂ���
					if (posOld.y + sizeMax.y <= pPosOld->y + vtxMin.y
						&& pos.y + sizeMax.y >= pPos->y + vtxMin.y)
					{// �ォ��߂荞��
						// ��ɂ̂���
						pPos->y = posOld.y - vtxMin.y + sizeMax.y;
						pMove->y = 0.0f;

						bLand = true;
					}
					else if (posOld.y + sizeMin.y >= pPosOld->y + vtxMax.y
						&& pos.y + sizeMin.y <= pPos->y + vtxMax.y)
					{// ������߂荞��
						// ���ɖ߂�
						pPos->y = posOld.y - vtxMax.y + sizeMin.y;
						//pPlayer->SetMove(D3DXVECTOR3(pPlayer->GetMove().x, 0.0f, pPlayer->GetMove().z));
					}
					else if (posOld.z + sizeMin.z >= pPosOld->z - vtxMin.z
						&& pos.z + sizeMin.z <= pPos->z - vtxMin.z)
					{// ������E�ɂ߂荞��
						// �ʒu��߂�
						pPos->z = posOld.z + vtxMin.z + sizeMin.z;
						pRot->y = D3DX_PI * ROT_RIGHT + (ROT_CAMERA * CManager::GetInstance()->GetCamera()->GetRot().y);
					}
					else if (posOld.z + sizeMax.z <= pPosOld->z + vtxMin.z
						&& pos.z + sizeMax.z >= pPos->z + vtxMin.z)
					{// �E���獶�ɂ߂荞��
						// �ʒu��߂�
						pPos->z = posOld.z - vtxMin.z + sizeMax.z;
						pRot->y = D3DX_PI * ROT_LEFT + (ROT_CAMERA * CManager::GetInstance()->GetCamera()->GetRot().y);
					}
				}
			}
			pObject = pObjectNext;		// ���̃I�u�W�F�N�g����
		}
	}

	return bLand;
}