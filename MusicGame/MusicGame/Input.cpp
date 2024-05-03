//=======================================================================================
//
//	  CInput�N���X [Input.cpp]
//
//=======================================================================================
#include "Input.h"
#include "WindowManager.h"
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
namespace {
	const int	g_nMouseBtn[] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2 };
};

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
WORD		CInput::m_wKeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̉�����Ԃ�ێ����郏�[�N
WORD		CInput::m_wKeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K��Ԃ�ێ����郏�[�N
WORD		CInput::m_wKeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��Ԃ�ێ����郏�[�N
WORD		CInput::m_wKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��Ԃ�ێ����郏�[�N
int			CInput::m_nKeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

DWORD		CInput::m_dwJoyCount;
JOYINFOEX	CInput::m_joyState[NUM_JOY_MAX];
DWORD		CInput::m_dwJoyButtonTrigger[NUM_JOY_MAX];
DWORD		CInput::m_dwJoyButtonRelease[NUM_JOY_MAX];

POINT		CInput::m_ptMouse;

//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT CInput::Init()
{
	HRESULT hr = S_OK;

	// �L�[�{�[�h�̏�����
	hr = InitKeyboard();

	// �Q�[���p�b�h�̏�����
	if (SUCCEEDED(hr)) {
		hr = InitJoystick();
	}

	// �}�E�X�̏�����
	if (SUCCEEDED(hr)) {
		hr = InitMouse();
	}

	return hr;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void CInput::Fin()
{
	// �}�E�X�̏I������
	UninitMouse();

	// �Q�[���p�b�h�̏I������
	UninitJoystick();

	// �L�[�{�[�h�̏I������
	UninitKeyboard();
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void CInput::Update()
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();

	// �Q�[���p�b�h�̍X�V
	UpdateJoystick();

	// �}�E�X�̍X�V
	UpdateMouse();
}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT CInput::InitKeyboard()
{
	HRESULT hr = S_OK;

	return hr;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInput::UninitKeyboard(void)
{
	// (�������Ȃ�)
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
HRESULT CInput::UpdateKeyboard(void)
{
	HRESULT hr = S_OK;
	WORD wKeyState;

	// �L�[�{�[�h�̏�Ԃ��擾
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++) {
		wKeyState = GetAsyncKeyState(nCntKey);

		m_wKeyStateTrigger[nCntKey] = (m_wKeyState[nCntKey] ^ wKeyState) & wKeyState;
		m_wKeyStateRelease[nCntKey] = (m_wKeyState[nCntKey] ^ wKeyState) & ~wKeyState;
		m_wKeyStateRepeat[nCntKey] = m_wKeyStateTrigger[nCntKey];

		if (wKeyState & 0x8000) {
			m_nKeyStateRepeatCnt[nCntKey]++;
			if (m_nKeyStateRepeatCnt[nCntKey] >= 20) {
				m_wKeyStateRepeat[nCntKey] = wKeyState;
			}
		} else {
			m_nKeyStateRepeatCnt[nCntKey] = 0;
			m_wKeyStateRepeat[nCntKey] = 0;
		}

		m_wKeyState[nCntKey] = wKeyState;
	}

	return hr;
}

//=============================================================================
// �Q�[���p�b�h�̏���������
//=============================================================================
HRESULT CInput::InitJoystick()
{
	GetJoyCount();

	return S_OK;
}

//=============================================================================
// �Q�[���p�b�h�̏I������
//=============================================================================
void CInput::UninitJoystick()
{
	// (�������Ȃ�)
}

//=============================================================================
// �Q�[���p�b�h�̍X�V����
//=============================================================================
HRESULT CInput::UpdateJoystick()
{
	HRESULT hr = S_OK;

	for (DWORD i = 0; i < m_dwJoyCount; ++i) {
		JOYINFOEX& ji = m_joyState[i];
		DWORD dwButtons = ji.dwButtons;
		ZeroMemory(&ji, sizeof(ji));
		ji.dwSize = sizeof(ji);
		ji.dwFlags = JOY_RETURNALL;
		if (joyGetPosEx(i, &ji) != JOYERR_NOERROR) {
			hr = E_FAIL;
			break;
		}
		m_dwJoyButtonTrigger[i] = (m_joyState[i].dwButtons ^ dwButtons) & dwButtons;
		m_dwJoyButtonRelease[i] = (m_joyState[i].dwButtons ^ dwButtons) & ~dwButtons;
	}
	return hr;
}

//=============================================================================
// �}�E�X�̏���������
//=============================================================================
HRESULT CInput::InitMouse()
{
	return S_OK;
}

//=============================================================================
// �}�E�X�̏I������
//=============================================================================
void CInput::UninitMouse()
{
	// (�������Ȃ�)
}

//=============================================================================
// �}�E�X�̍X�V����
//=============================================================================
HRESULT CInput::UpdateMouse()
{
	CWindowManager *window = WindowManager;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(window->GetWindowHandle(), &pt);
	m_ptMouse = pt;
	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool CInput::GetKeyPress(int nKey)
{
	return (m_wKeyState[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K��Ԃ��擾
//=============================================================================
bool CInput::GetKeyTrigger(int nKey)
{
	return (m_wKeyStateTrigger[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool CInput::GetKeyRepeat(int nKey)
{
	return (m_wKeyStateRepeat[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool CInput::GetKeyRelease(int nKey)
{
	return (m_wKeyStateRelease[nKey] & 0x8000) ? true : false;
}

//=============================================================================
// �Q�[���p�b�h�ڑ����擾
//=============================================================================
DWORD CInput::GetJoyCount()
{
	JOYINFO	ji;
	DWORD dwCount = joyGetNumDevs();
	if (dwCount > NUM_JOY_MAX)
		dwCount = NUM_JOY_MAX;
	for (m_dwJoyCount = 0; m_dwJoyCount < dwCount; ++m_dwJoyCount) {
		if (joyGetPos(m_dwJoyCount, &ji) != JOYERR_NOERROR)
			break;
	}
	return m_dwJoyCount;
}

//=============================================================================
// �Q�[���p�b�h���擾
//=============================================================================
JOYINFOEX* CInput::GetJoyState(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return nullptr;
	return &m_joyState[dwJoy];
}

//=============================================================================
// �Q�[���p�b�hX���擾
//=============================================================================
LONG CInput::GetJoyX(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)m_joyState[dwJoy].dwXpos - 0x08000;
}

//=============================================================================
// �Q�[���p�b�hY���擾
//=============================================================================
LONG CInput::GetJoyY(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)m_joyState[dwJoy].dwYpos - 0x08000;
}

//=============================================================================
// �Q�[���p�b�hZ���擾
//=============================================================================
LONG CInput::GetJoyZ(DWORD dwJoy)
{
	if (dwJoy >= NUM_JOY_MAX) return 0L;
	return (LONG)m_joyState[dwJoy].dwZpos - 0x08000;
}

//=============================================================================
// �Q�[���p�b�h �{�^�����擾
//=============================================================================
bool CInput::GetJoyButton(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (m_joyState[dwJoy].dwButtons & (1 << dwBtn)) ? true : false;
}

//=============================================================================
// �Q�[���p�b�h �g���K���擾
//=============================================================================
bool CInput::GetJoyTrigger(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (m_dwJoyButtonTrigger[dwJoy] & (1 << dwBtn)) ? true : false;
}

//=============================================================================
// �Q�[���p�b�h �����[�X���擾
//=============================================================================
bool CInput::GetJoyRelease(DWORD dwJoy, DWORD dwBtn)
{
	if (dwJoy >= NUM_JOY_MAX) return false;
	return (m_dwJoyButtonRelease[dwJoy] & (1 << dwBtn)) ? true : false;
}

//=============================================================================
// �}�E�X���W�擾
//=============================================================================
POINT* CInput::GetMousePosition()
{
	return &m_ptMouse;
}

//=============================================================================
// �}�E�X �{�^�����擾
//=============================================================================
bool CInput::GetMouseButton(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyPress(g_nMouseBtn[dwBtn]);
}

//=============================================================================
// �}�E�X �g���K���擾
//=============================================================================
bool CInput::GetMouseTrigger(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyTrigger(g_nMouseBtn[dwBtn]);
}

//=============================================================================
// �}�E�X �����[�X���擾
//=============================================================================
bool CInput::GetMouseRelease(DWORD dwBtn)
{
	if (dwBtn >= _countof(g_nMouseBtn)) return false;
	return GetKeyRelease(g_nMouseBtn[dwBtn]);
}

//=======================================================================================
//	End of File
//=======================================================================================
