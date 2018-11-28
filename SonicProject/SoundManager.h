#pragma once
class SoundManager
{

public:
	static SoundManager* Manager() { static SoundManager mgr; return &mgr; }

private:
	LPDIRECTSOUND8		m_pSound; // ����ī�� ��ǥ ��ü

								  // Sound Buffer Container //
	map<wstring, LPDIRECTSOUNDBUFFER> m_mapSoundBuffer; // Key ������ ����	

private:
	LPDIRECTSOUNDBUFFER				  m_pBGM;	// ����� ����
	LONG							  m_lVolume;// ����� ����(���� ���ú�) -10000 ~ 0 ������ ��
	wstring							  m_strCurBGM; // ���� ������� BGM
	bool							  m_bOffSound;

public:
	int init(void);
	int update(void);
	int LoadSound(TCHAR* _pFileName, TCHAR* _pResourceKey);

public: // Playe Sound //
	int PlaySound(const wstring& _strSoundKey, const bool& _bLoop);
	int PlayBGM(const wstring& _strSoundKey, const bool& _bLoop = true);

public: // Stop Sound //
		// bReset == true Stop �Ǵ� ���尡 ó����ġ�� ���µ��� �ƴ���
	void StopSound(const wstring& _strSoundKey, const bool& _bReset = true);

private:
	int  LoadWavSound(TCHAR* _pFileName, TCHAR* _pResourceKey);

	// Set //
public:
	void SetBGMVolume(const  double& _dVolume); // 1 ~ 100 ���̰�

public:
	// Get //
	const long& GetBGMVolume(void);

public:
	SoundManager(void);
	~SoundManager(void);

};

