#include "stdafx.h"
#include "SoundManager.h"
#include "PathManager.h"

// ���� ����
bool g_bBGM = true;

SoundManager::SoundManager(void)
	: m_pSound(NULL)
	, m_pBGM(NULL)
	, m_lVolume(100)
	, m_bOffSound(false)
{
}

SoundManager::~SoundManager(void)
{
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.begin();
	for (iter; iter != m_mapSoundBuffer.end(); ++iter)
	{
		iter->second->Release();
	}
}

int SoundManager::init(void)
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pSound, NULL)))
	{
		MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	//���� ����̽� �������� ����.
	HWND hWnd = g_hWnd;
	if (FAILED(m_pSound->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	//BGM load;
	SoundManager::Manager()->LoadSound(L"BGM//Stage_00.wav", L"BGM_STAGE_00");
	SoundManager::Manager()->LoadSound(L"BGM//Stage_01.wav", L"BGM_STAGE_01");
	SoundManager::Manager()->LoadSound(L"BGM//Stage_Start.wav", L"BGM_STAGE_START");
	SoundManager::Manager()->LoadSound(L"BGM//Stage_Select.wav", L"BGM_STAGE_SELECT");
	SoundManager::Manager()->LoadSound(L"BGM//Stage_Final.wav", L"BGM_STAGE_FINAL");
	SoundManager::Manager()->LoadSound(L"BGM//Sound_Boss_Silver.wav", L"BGM_BOSS_SILVER");
	SoundManager::Manager()->LoadSound(L"BGM//SuperSonic.wav", L"BGM_SuperSonic");



	SoundManager::Manager()->LoadSound(L"Effect//Logo//Buttom.wav", L"Sound_Buttom_Move");
	SoundManager::Manager()->LoadSound(L"Effect//Logo//intro.wav", L"Sound_Intro");

	//EFECT Load
	SoundManager::Manager()->LoadSound(L"Effect//Jump.wav", L"Sound_Jump");
	SoundManager::Manager()->LoadSound(L"Effect//Ring.wav", L"Sound_Ring");
	SoundManager::Manager()->LoadSound(L"Effect//Bouncer.wav", L"Sound_Spring");
	SoundManager::Manager()->LoadSound(L"Effect//SpitRings.wav", L"Sound_SpitRing");
	SoundManager::Manager()->LoadSound(L"Effect//Itembreak.wav", L"Sound_Itembreak");
	SoundManager::Manager()->LoadSound(L"Effect//Skid.wav", L"Sound_Break");
	SoundManager::Manager()->LoadSound(L"Effect//Spin.wav", L"Sound_Spin");
	SoundManager::Manager()->LoadSound(L"Effect//Fire.wav", L"Sound_Fire");
	SoundManager::Manager()->LoadSound(L"Effect//Water.wav", L"Sound_Water");
	SoundManager::Manager()->LoadSound(L"Effect//BossDamage.wav", L"Sound_BossDamage");
	SoundManager::Manager()->LoadSound(L"Effect//BossDeath.wav", L"Sound_BossDeath");
	SoundManager::Manager()->LoadSound(L"Effect//BossRoll.wav", L"Sound_BossRoll");
	SoundManager::Manager()->LoadSound(L"Effect//BossDash.wav", L"Sound_BossDash");
	SoundManager::Manager()->LoadSound(L"Effect//GoalSound.wav", L"Sound_Goal");
	SoundManager::Manager()->LoadSound(L"Effect//Victory.wav", L"Sound_Victory");
	SoundManager::Manager()->LoadSound(L"Effect//CashRegister.wav", L"Sound_CashRegister");
	SoundManager::Manager()->LoadSound(L"Effect//StoneBreak.wav", L"Sound_StoneBreak");
	SoundManager::Manager()->LoadSound(L"Effect//Explosion.wav", L"Sound_Explosion");
	SoundManager::Manager()->LoadSound(L"Effect//Electricity.wav", L"Sound_Electricity");
	SoundManager::Manager()->LoadSound(L"Effect//Boss_01_Apear.wav", L"Sound_Boss_01_Apear");



	return true;
}

int SoundManager::update(void)
{
	if (!m_strCurBGM.empty())
	{
		if (!g_bBGM && !m_bOffSound)
		{
			StopSound(m_strCurBGM, false);
			m_bOffSound = true; // �Ҹ��� ����.
		}
		else if (g_bBGM && m_bOffSound)
		{
			PlayBGM(m_strCurBGM);
			m_bOffSound = false;
		}
	}
	return true;
}

int SoundManager::LoadWavSound(TCHAR *_pFileName, TCHAR *_pResourceKey)
{
	HMMIO	hFile; // File Handle

				   //CreateFile
	hFile = mmioOpen(_pFileName, NULL, MMIO_READ);//wave������ ����.

												  //Chunk ûũ ����ü, ���ڿ��� ������ �ν��ؼ� WaveFormat �� ���ۼ��������� �о�´�.
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	DSBUFFERDESC	BuffInfo;
	memset(&BuffInfo, 0, sizeof(DSBUFFERDESC));
	BuffInfo.dwBufferBytes = pChild.cksize;
	BuffInfo.dwSize = sizeof(DSBUFFERDESC);
	BuffInfo.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	BuffInfo.lpwfxFormat = &wft;

	LPDIRECTSOUNDBUFFER	pSoundBuff;

	if (FAILED(m_pSound->CreateSoundBuffer(&BuffInfo, &pSoundBuff, NULL)))
	{
		MessageBox(NULL, L"������ۻ�������", L"", MB_OK);
		return false;
	}

	void* pWrite1 = NULL;
	void* pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	pSoundBuff->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0L);

	if (pWrite1 > 0)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 > 0)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	pSoundBuff->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	// �ʿ� ���带 ��´�.
	m_mapSoundBuffer.insert(make_pair(_pResourceKey, pSoundBuff));

	return true;
}

int SoundManager::LoadSound(TCHAR *_pFileName, TCHAR *_pResourceKey)
{
	if (!m_pSound)
		return false; // ���� ��ü �������� ����

	if (m_mapSoundBuffer.find(_pFileName) != m_mapSoundBuffer.end())// �̹� ������ �ε�Ǿ��ִ�.
		return false;

	// ���ϸ��� ���ҽ� ��ο� ��ģ��.
	if (_pFileName == NULL)
		return true;

	TCHAR	szPath[255] = { 0 };
	wchar_t* pPath = PathManager::GetResPath();
	wcscpy_s(szPath, 255, pPath);

	wcscat_s(szPath, 255, L"\\Sound\\");
	wcscat_s(szPath, 255, _pFileName);

	// Ȯ���� �̸� �����ϱ�
	TCHAR _pExtension[10] = { 0 };

	int iSize = (int)_tcslen(_pFileName);
	int iStart = 0;

	for (int i = 0; i < iSize; ++i)
	{
		if (_pFileName[i] == '.')
		{
			iStart = i + 1;
			break;
		}
	}

	for (int i = iStart, j = 0; i < iSize; ++i, ++j)
	{
		_pExtension[j] = _pFileName[i];
	}

	if (!_tcscmp(_pExtension, _T("wav"))) // WAV ���� �ε�
	{
		if (false == LoadWavSound(szPath, _pResourceKey))
			return false;
	}
	//else if( !_tcscmp( _pExtension, _T("ogg") ) ) // OGG ���� �ε�
	//{
	//	if(RET_FAILED == LoadOggSound(szPath,_pResourceKey))
	//		return RET_FAILED;
	//}

	return true;
}

// Sound Play //
int SoundManager::PlaySound(const wstring& _strSoundKey, const bool& _bLoop)
{
	// SoundMgr �� �ش� Ű�� ��ϵ� ���尡 ���ٸ�
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.find(_strSoundKey);
	if (iter == m_mapSoundBuffer.end())
	{
		MessageBox(NULL, L"���� ��� ����", L"���� ���� ����", MB_OK);
		return false;
	}

	// Play �Լ��� 1��° 2��° ���ڴ� 0 ���� �̹� ����Ǿ��ִ�.
	// 3��° ������ ���带 �ݺ���� �� ������ �ƴ����� �����Ѵ�.
	if (_bLoop)
		iter->second->Play(0, 0, DSBPLAY_LOOPING);
	else
		iter->second->Play(0, 0, 0);

	return true;
}

int SoundManager::PlayBGM(const wstring& _strSoundKey, const bool& _bLoop)
{
	// SoundMgr �� �ش� Ű�� ��ϵ� ���尡 ���ٸ�
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.find(_strSoundKey);
	if (iter == m_mapSoundBuffer.end())
	{
		MessageBox(NULL, L"���� ��� ����", L"���� ���� ����", MB_OK);
		return false;
	}

	m_strCurBGM = _strSoundKey;

	// BGM �� 1���� �����Ѵ�.
	//SUCCEEDED(m_pBGM->GetStatus((LPDWORD)DSBSTATUS_PLAYING))
	if (m_pBGM)
	{
		// BGM �� �ְ�, BGM �� ������̶�� Stop
		m_pBGM->Stop();
		m_pBGM->SetCurrentPosition(0);
	}

	// ���ο� BGM ���� �ٲ۴�.
	m_pBGM = iter->second;
	m_pBGM->SetVolume(m_lVolume);

	if (_bLoop)
		m_pBGM->Play(0, 0, DSBPLAY_LOOPING);
	else
		m_pBGM->Play(0, 0, 0);

	return true;
}

void SoundManager::StopSound(const wstring& _strSoundKey, const bool& _bReset)
{
	map<wstring, LPDIRECTSOUNDBUFFER>::iterator iter = m_mapSoundBuffer.find(_strSoundKey);
	if (iter != m_mapSoundBuffer.end())
	{
		iter->second->Stop();

		if (m_pBGM == iter->second)
			m_pBGM = NULL;

		if (_bReset)
			iter->second->SetCurrentPosition(0);
	}
}

void SoundManager::SetBGMVolume(const double& _dVolume)
{
	double dVolume = _dVolume;
	if (dVolume > 100.0)
		dVolume = 100.0;
	else if (dVolume <= 0.0)
		dVolume = 0.00001;

	// 1 ~ 100 ���̰��� ���ú� ������ ����
	m_lVolume = (LONG)(-2000.0 * log10(100.0 / dVolume));
	if (m_lVolume < -10000)
		m_lVolume = -10000;

	if (m_pBGM)
		m_pBGM->SetVolume(m_lVolume);
}

const long& SoundManager::GetBGMVolume(void)
{
	return m_lVolume;
}