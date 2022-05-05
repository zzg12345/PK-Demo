
// LiveDemoDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LiveDemo.h"
#include "LiveDemoDlg.h"
#include "afxdialogex.h"
#include "VideoFrameObserver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CLiveBroadcastingRtcEngineEventHandler::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
	if (m_hMsgHanlder) {
		::PostMessage(m_hMsgHanlder, WM_MSGID(EID_JOINCHANNEL_SUCCESS), (WPARAM)uid, (LPARAM)elapsed);
	}
}


void CLiveBroadcastingRtcEngineEventHandler::onUserJoined(uid_t uid, int elapsed) {
	if (m_hMsgHanlder) {
		::PostMessage(m_hMsgHanlder, WM_MSGID(EID_USER_JOINED), (WPARAM)uid, (LPARAM)elapsed);
	}
}


void CLiveBroadcastingRtcEngineEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
	if (m_hMsgHanlder) {
		::PostMessage(m_hMsgHanlder, WM_MSGID(EID_USER_OFFLINE), (WPARAM)uid, (LPARAM)reason);
	}
}


void CLiveBroadcastingRtcEngineEventHandler::onLeaveChannel(const RtcStats& stats)
{
	if (m_hMsgHanlder) {
		::PostMessage(m_hMsgHanlder, WM_MSGID(EID_LEAVE_CHANNEL), (WPARAM)&stats, 0);
	}
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLiveDemoDlg 对话框



CLiveDemoDlg::CLiveDemoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIVEDEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLiveDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ROLE, m_RoleCom);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_videoArea);
	DDX_Control(pDX, IDC_CHECK_ORIGINALVIDEO, m_originalvideoCheck);
	DDX_Control(pDX, IDC_COMBO_CAMEAR, m_camearCombo);
	DDX_Control(pDX, IDC_COMBO_VIDOE_TYPE, m_videoType);
	DDX_Control(pDX, IDC_SLIDER_AUDIO, m_sldVolume);
	DDX_Control(pDX, IDC_CHECK_PLAYLOCAL, m_localOnlyCheck);
	DDX_Control(pDX, IDC_CHECK_REPLACEMIC, m_replaceMicCheck);
}

BEGIN_MESSAGE_MAP(CLiveDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLiveDemoDlg::OnBnClickedOk)
	ON_MESSAGE(WM_MSGID(EID_JOINCHANNEL_SUCCESS), &CLiveDemoDlg::OnEIDJoinChannelSuccess)
	ON_MESSAGE(WM_MSGID(EID_LEAVE_CHANNEL), &CLiveDemoDlg::OnEIDLeaveChannel)
	ON_MESSAGE(WM_MSGID(EID_USER_JOINED), &CLiveDemoDlg::OnEIDUserJoined)
	ON_MESSAGE(WM_MSGID(EID_USER_OFFLINE), &CLiveDemoDlg::OnEIDUserOffline)
	ON_MESSAGE(WM_MSGID(EID_LOCAL_VIDEO_STATS), &CLiveDemoDlg::onEIDLocalVideoStats)
	ON_MESSAGE(WM_MSGID(EID_LOCAL_VIDEO_STATE_CHANGED), &CLiveDemoDlg::onEIDLocalVideoStateChanged)
	ON_MESSAGE(WM_MSGID(EID_REMOTE_VIDEO_STATS), &CLiveDemoDlg::onEIDRemoteVideoStats)
	ON_MESSAGE(WM_MSGID(EID_REMOTE_VIDEO_STATE_CHANGED), &CLiveDemoDlg::onEIDRemoteVideoStateChanged)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_ROLE, &CLiveDemoDlg::OnCbnSelchangeComboRole)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_SENDMSG, &CLiveDemoDlg::OnBnClickedBtnSendmsg)
	ON_BN_CLICKED(IDC_BTNPK, &CLiveDemoDlg::OnBnClickedBtnpk)
	ON_MESSAGE(WM_QueryUserStatusResult, onQueryUserStatusResult)
	ON_MESSAGE(WM_MessageSendError, onMessageSendError)
	ON_MESSAGE(WM_MessageSendSuccess, onMessageSendSuccess)
	ON_MESSAGE(WM_MessageInstantReceive, onMessageInstantReceive)
	ON_MESSAGE(WM_MessageChannelReceive, onMessageChannelReceive)
	ON_MESSAGE(WM_ChannelJoined, onChannelJoined)
	ON_MESSAGE(WM_ChannelJoinedFailed, onChannelJoinFailed)
	ON_MESSAGE(WM_ChannelLeaved, onChannelLeaved)
	ON_MESSAGE(WM_ChannelUserList, onChannelUserList)
	ON_MESSAGE(WM_ChannelQueryUserNumResult, onChannelQueryUserNumResult)
	ON_MESSAGE(WM_InviteReceived, onAcceptCurrentRemoteInvitation)
	ON_MESSAGE(WM_RTMJoinChannle, onJoinRTMChannel)
	ON_MESSAGE(WM_InviteAccepted, onRemoteInviteAccepted)
	ON_MESSAGE(WM_InviteAcceptedByPeer, onLocalInviteAcceptedByPeer)
	ON_BN_CLICKED(IDC_BTNPKEND, &CLiveDemoDlg::OnBnClickedBtnpkend)
	ON_BN_CLICKED(IDC_BTN_CAPTURETYPE, &CLiveDemoDlg::OnBnClickedBtnCapturetype)
	ON_CBN_SELCHANGE(IDC_COMBO_CAMEAR, &CLiveDemoDlg::OnCbnSelchangeComboCamear)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AUDIO, &CLiveDemoDlg::OnNMReleasedcaptureSliderAudio)
	ON_BN_CLICKED(IDC_BTN_AUDIOMIXING, &CLiveDemoDlg::OnBnClickedBtnAudiomixing)
	ON_BN_CLICKED(IDC_BTN_RETATE, &CLiveDemoDlg::OnBnClickedBtnRetate)
	ON_BN_CLICKED(IDC_BTN_MIRROR, &CLiveDemoDlg::OnBnClickedBtnMirror)
END_MESSAGE_MAP()


// CLiveDemoDlg 消息处理程序

BOOL CLiveDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_initialize = false;
	m_joinChannel = false;
	m_bPlayMixing = false;
	m_bTranscoder = false;
	InitCtrl();
	SetWindowText(to_wstring(GetCurrentProcessId()).c_str());
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLiveDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLiveDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLiveDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CLiveDemoDlg::OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam)
{
	//m_btnJoinChannel.EnableWindow(TRUE);

	m_joinChannel = true;
	CWnd *hWnd =  GetDlgItem(IDOK);
	hWnd->SetWindowText(L"离开频道");

	
	CString strInfo;
	CString strMsg;
	strMsg.Format(_T("%d:join success, uid=%u"), GetCurrentTime(), wParam);
	GetDlgItemText(IDC_EDIT_RCVMSG, strInfo);
	strInfo += L"\r\n";
	strInfo += strMsg;
	SetDlgItemText(IDC_EDIT_RCVMSG, strInfo);

	if (m_isBroadcaster)
	{
		m_videoWnds[0].SetUID(wParam);
		m_lstUids.push_back(wParam);
	}


	::PostMessage(m_hWnd, WM_RTMJoinChannle, 0, 0);
	return S_OK;
}

LRESULT CLiveDemoDlg::OnEIDLeaveChannel(WPARAM wParam, LPARAM lParam)
{
	RtcStats *stats = (RtcStats*)wParam;
	//m_btnJoinChannel.EnableWindow(TRUE);
	//m_joinChannel = false;
	////m_btnJoinChannel.SetWindowText(commonCtrlJoinChannel);
	//CWnd *hWnd = GetDlgItem(IDOK);
	//if (m_isPk)
	//{

	//}
	////hWnd->SetWindowText(L"加入频道");

	CString strInfo;
	CString strMsg;
	strMsg.Format(_T("%d:LeaveChannel success, userCount=%d"), GetCurrentTime(), stats->userCount);
	GetDlgItemText(IDC_EDIT_RCVMSG, strInfo);
	strInfo += L"\r\n";
	strInfo += strMsg;
	SetDlgItemText(IDC_EDIT_RCVMSG, strInfo);

	m_lstUids.clear();
	for (int i = 0; i < m_maxVideoCount; i++) 
	{
		m_videoWnds[i].SetUID(0);
	}

	OutputDebugStringW(L"OnEIDLeaveChannel---");
	//notify parent window
	//::PostMessage(GetParent()->GetSafeHwnd(), WM_MSGID(EID_JOINCHANNEL_SUCCESS), FALSE, 0);
	return 0;
}

LRESULT CLiveDemoDlg::OnEIDUserJoined(WPARAM wParam, LPARAM lParam)
{
	if (m_lstUids.size() == m_maxVideoCount)
		return 0;
	//CString strInfo;
	//strInfo.Format(_T("%u joined"), wParam);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	CString strInfo;
	CString strMsg;
	strMsg.Format(_T("%u:joined"), wParam);
	GetDlgItemText(IDC_EDIT_RCVMSG, strInfo);
	strInfo += L"\r\n";
	strInfo += strMsg;
	strInfo += L"\r\n";
	SetDlgItemText(IDC_EDIT_RCVMSG, strInfo);


	m_lstUids.push_back(wParam);
	for (int i = 0; i < m_maxVideoCount; i++) 
	{
		if (m_videoWnds[i].GetUID() == 0) 
		{
			VideoCanvas canvas;
			canvas.uid = wParam;
			canvas.view = m_videoWnds[i].GetSafeHwnd();
			canvas.renderMode = media::base::RENDER_MODE_FIT;
			//setup remote video in engine to the canvas.
			if (m_isPk && wParam%100 == 0)
			{
				m_rtcEngine->setupRemoteVideoEx(canvas, m_pkConnection);
			}
			else
			{
				m_rtcEngine->setupRemoteVideo(canvas);
			}

			m_videoWnds[i].SetUID(wParam);
			strMsg.Format(L"setupRemoteVideo uid %u  index =%d",  wParam, i);
			OutputDebugStringW(strMsg.GetBuffer());
			break;
		}
	}
	return 0;
}

LRESULT CLiveDemoDlg::OnEIDUserOffline(WPARAM wParam, LPARAM lParam)
{
	uid_t remoteUid = (uid_t)wParam;
	VideoCanvas canvas;
	canvas.uid = remoteUid;
	canvas.view = NULL;
	m_rtcEngine->setupRemoteVideo(canvas);
	//CString strInfo;
	//strInfo.Format(_T("%u offline, reason:%d"), remoteUid, lParam);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	CString strInfo;
	CString strMsg;
	strMsg.Format(_T("uid:%d offline, reason, =%d"), remoteUid, lParam);
	GetDlgItemText(IDC_EDIT_RCVMSG, strInfo);
	strInfo += L"\r\n";
	strInfo += strMsg;
	SetDlgItemText(IDC_EDIT_RCVMSG, strInfo);

	for (int i = 1; i < m_maxVideoCount; i++) 
	{
		if (m_videoWnds[i].GetUID() == remoteUid) 
		{
			m_videoWnds[i].SetUID(0);
			m_videoWnds[i].Invalidate();
			break;
		}
	}

	for (auto iter = m_lstUids.begin();
		iter != m_lstUids.end(); iter++) 
	{
		if (*iter == remoteUid) 
		{
			m_lstUids.erase(iter);
			break;
		}
	}
	return 0;
}

LRESULT CLiveDemoDlg::onEIDLocalVideoStats(WPARAM wParam, LPARAM lParam) {
	LocalVideoStats* stats = (LocalVideoStats*)wParam;
	//CString strInfo = _T("===onLocalVideoStats===");
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	//strInfo.Format(_T("uid:%u"), stats->uid);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("sentBitrate:%d"), stats->sentBitrate);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	//strInfo.Format(_T("sentFrameRate:%d"), stats->sentFrameRate);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("encoderOutputFrameRate:%d"), stats->encoderOutputFrameRate);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	//strInfo.Format(_T("rendererOutputFrameRate:%d"), stats->rendererOutputFrameRate);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("targetBitrate:%d"), stats->targetBitrate);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	//strInfo.Format(_T("qualityAdaptIndication:%d"), stats->qualityAdaptIndication);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("encodedBitrate:%d"), stats->encodedBitrate);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	//strInfo.Format(_T("encodedFrameWidth:%d"), stats->encodedFrameWidth);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("encodedFrameHeight:%d"), stats->encodedFrameHeight);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	//strInfo.Format(_T("encodedFrameCount:%d"), stats->encodedFrameCount);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("codecType:%d"), stats->codecType);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	if (stats) 
	{
		delete stats;
		stats = nullptr;
	}
	return 0;
}
LRESULT CLiveDemoDlg::onEIDLocalVideoStateChanged(WPARAM wParam, LPARAM lParam) 
{

	LOCAL_VIDEO_STREAM_STATE state = (LOCAL_VIDEO_STREAM_STATE)wParam;
	LOCAL_VIDEO_STREAM_ERROR error = (LOCAL_VIDEO_STREAM_ERROR)lParam;
	//CString strInfo = _T("===onLocalVideoStateChanged===");
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);

	//strInfo.Format(_T("state:%d"), state);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("error:%d"), error);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	return 0;
}
LRESULT CLiveDemoDlg::onEIDRemoteVideoStats(WPARAM wParam, LPARAM lParam) {
	RemoteVideoStats* stats = (RemoteVideoStats*)wParam;
	CString strInfo = _T("===onRemoteVideoStats===");
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//CString strMsg;
	//strMsg = strInfo;
	//strInfo.Format(_T("uid:%u "), stats->uid);
	//strMsg += strInfo;

	//strInfo.Format(_T("rendererOutputFrameRate:%d "), stats->rendererOutputFrameRate);
	//strMsg += strInfo;
	////m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	////strInfo.Format(_T("height:%d "), stats->height);
	////strInfo.Format(_T("height:%d "), stats->height);
	////strMsg += strInfo;

	//GetDlgItemText(IDC_EDIT_RCVMSG, strInfo);
	//strInfo += L"\r\n";
	//strInfo += strMsg;
	//strInfo += L"\r\n";
	//SetDlgItemText(IDC_EDIT_RCVMSG, strInfo);


	if (stats) 
	{
		delete stats;
		stats = nullptr;
	}
	return 0;
}
LRESULT CLiveDemoDlg::onEIDRemoteVideoStateChanged(WPARAM wParam, LPARAM lParam) 
{
	//CString strInfo = _T("===onRemoteVideoStateChanged===");
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	PRemoteVideoState state = (PRemoteVideoState)wParam;

	//strInfo.Format(_T("elapsed:%d"), state->elapsed);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("uid:%u"), state->uid);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("state:%d"), state->state);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	//strInfo.Format(_T("reason:%d"), state->reason);
	//m_lstInfo.InsertString(m_lstInfo.GetCount(), strInfo);
	return 0;
}

void CLiveDemoDlg::InitCtrl()
{
	m_RoleCom.InsertString(0, L"Broadcaster");
	m_RoleCom.InsertString(1, L"Audience");
	m_RoleCom.SetCurSel(0);

	//
	m_buffer = new BYTE[1920 * 1280 * 4 * 4];
	m_imgBuffer = new BYTE[1920 * 1280 * 4 * 4];
	InitCamear();
	//
	CreateAllVideoWnds();
	ResumeStatus();
	InitAgora();
	//
	
}

bool CLiveDemoDlg::InitAgora()
{
	bool bRet = false;
	m_rtcEngine = (IRtcEngineEx*)createAgoraRtcEngine();
	if (m_rtcEngine == nullptr)
	{
		OutputDebugString(L"createAgoraRtcEngine failed!!");
		return bRet;
	}
	m_rtcEventHandle.SetMsgReceiver(m_hWnd);
	RtcEngineContext context;
	USES_CONVERSION;
	string strAppId = W2A(CConfig::GetInstance()->GetAPP_ID().GetBuffer());
	context.appId = strAppId.c_str();
	context.eventHandler = &m_rtcEventHandle;
	context.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	int ret = m_rtcEngine->initialize(context);
	if (ret)
	{
		OutputDebugString(L"initialize failed!!");
		return bRet;
	}
	m_rtcEngine->enableVideo();
	m_rtcEngine->setClientRole(CLIENT_ROLE_TYPE(m_RoleCom.GetCurSel() + 1));

	m_initialize = true;
	return true;
}
//UnInitialize the Agora SDK
void CLiveDemoDlg::UnInitAgora()
{
	if (m_rtcEngine)
	{
		if (m_joinChannel)
		{
			m_rtcEngine->leaveChannel();

		}
		m_rtcEngine->disableVideo();
		m_rtcEngine->release();
		m_rtcEngine = nullptr;
	}
	UnInitRTM();
}

void CLiveDemoDlg::CreateAllVideoWnds()
{
	for (int i = 0; i < VIDEO_COUNT; ++i) 
	{
		m_videoWnds[i].Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CRect(0, 0, 1, 1), this, IDC_BASEWND_VIDEO + i);
		//set window background color.
		m_videoWnds[i].SetFaceColor(RGB(0x58, 0x58, 0x58));
	}
}

void CLiveDemoDlg::ShowVideoWnds()
{
	m_videoArea.ShowWindow(SW_HIDE);
	int row = 2;
	int col = 2;
	m_maxVideoCount = 4;
	//switch (m_cmbPersons.GetCurSel())
	//{
	//case PEOPLE_IN_CHANNEL_2:
	//{
	//	row = 1;
	//	col = 2;
	//	m_maxVideoCount = 2;
	//}
	//break;
	//case PEOPLE_IN_CHANNEL_4:
	//{
	//	int row = 2;
	//	int col = 2;
	//	m_maxVideoCount = 4;
	//}
	//break;
	//case PEOPLE_IN_CHANNEL_9:
	//{
	//	row = 3;
	//	col = 3;
	//	m_maxVideoCount = 9;
	//}
	//break;
	//case PEOPLE_IN_CHANNEL_16:
	//{
	//	row = 4;
	//	col = 4;
	//	m_maxVideoCount = 16;
	//}
	//break;
	//}


	RECT rcArea;
	m_videoArea.GetClientRect(&rcArea);
	int space = 1;

	int w = (rcArea.right - rcArea.left - space * (col - 1)) / col;
	int h = (rcArea.bottom - rcArea.top - space * (row - 1)) / row;

	for (int r = 0; r < row; r++) 
	{
		for (int c = 0; c < col; c++) 
		{
			int x = rcArea.left + (w + space) * c;
			int y = rcArea.top + (h + space) * r;
			int nIndex = r * col + c;
			m_videoWnds[nIndex].MoveWindow(x, y, w, h, TRUE);
			m_videoWnds[nIndex].ShowWindow(SW_SHOW);
			m_videoWnds[nIndex].SetParent(this);

			if (!m_videoWnds[nIndex].IsWindowVisible()) 
			{
				m_videoWnds[nIndex].ShowWindow(SW_SHOW);
			}
		}
	}

	for (int i = m_maxVideoCount; i < VIDEO_COUNT; i++) 
	{
		m_videoWnds[i].ShowWindow(0);
		if (m_videoWnds[i].GetUID() != 0) 
		{
			VideoCanvas canvas;
			canvas.uid = m_videoWnds[i].GetUID();
			canvas.view = m_videoWnds[i].GetSafeHwnd();
			m_rtcEngine->setupRemoteVideo(canvas);
		}
	}
}

void CLiveDemoDlg::RenderLocalVideo()
{
	if (m_rtcEngine) 
	{
		//一定要在startPreview 前设置
		if (m_originalvideoCheck.GetCheck())
		{
			RegisterVideoFrameObserver(true, &m_garyVideoFrameObserver);
			m_garyVideoFrameObserver.InitFileObjet();
		}
		//start preview in the engine.
		m_rtcEngine->startPreview();
		VideoCanvas canvas;
		canvas.renderMode = media::base::RENDER_MODE_FIT;
		canvas.uid = 0;
		canvas.view = m_videoWnds[0].GetSafeHwnd();
		//setup local video in the engine to the canvas. 
		if (m_bTranscoder)
		{
			canvas.sourceType = VIDEO_SOURCE_TRANSCODED;
		}
		
		m_rtcEngine->setupLocalVideo(canvas);
		//m_rtcEngine->setLocalRenderMode()
		//m_rtcEngine->setLocalRenderMode(media::base::RENDER_MODE_FIT, VIDEO_MIRROR_MODE_ENABLED);
			//m_rtcEngine->setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_ENABLED);
		//m_lstInfo.InsertString(m_lstInfo.GetCount(), _T("render local video"));
	}
}

void CLiveDemoDlg::ResumeStatus()
{
	//m_lstInfo.ResetContent();
	m_RoleCom.SetCurSel(0);
	//m_cmbPersons.SetCurSel(0);
	//m_cmbVideoEncoder.SetCurSel(1);
	ShowVideoWnds();
	//InitCtrlText();

	//m_btnJoinChannel.EnableWindow(TRUE);
	//m_RoleCom.EnableWindow(TRUE);
	//m_edtChannelName.SetWindowText(_T(""));
	m_joinChannel = false;
	m_initialize = false;
}

void CLiveDemoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CString channle;
	int role=0;
	GetDlgItemText(IDC_EDIT_CHANNEL, channle);
	int uid = GetDlgItemInt(IDC_EDIT_UID);
	role = m_RoleCom.GetCurSel() + 1;
	CString strErr;
	if (m_rtcEngine == nullptr || !m_initialize)
	{
		return;
	}
	
	if (!m_joinChannel)
	{
		CString strChannel;
		GetDlgItemText(IDC_EDIT_CHANNEL, strChannel);
		if (strChannel.IsEmpty())
		{
			AfxMessageBox(_T("Fill channel name first"));
			return;
		}
		m_isBroadcaster = m_RoleCom.GetCurSel() == 0 ? true : false;
		if (m_isBroadcaster && !m_extenalCaptureVideo)
		{
			RenderLocalVideo();
		}
		
		if (!m_extenalCaptureVideo)
		{
			VideoEncoderConfiguration config;
			config.codecType = VIDEO_CODEC_VP8;
			
			m_rtcEngine->setVideoEncoderConfiguration(config);
		}
		
		
		USES_CONVERSION;
		string szChannel(W2A(strChannel.GetBuffer()));
		ChannelMediaOptions options;
		options.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
		options.clientRoleType = (CLIENT_ROLE_TYPE)(m_RoleCom.GetCurSel() + 1);
		//options.autoSubscribeAudio = true;
		//options.autoSubscribeVideo = true;
		if (m_bTranscoder)
		{
			options.publishTrancodedVideoTrack = true;
			options.publishCameraTrack = false;
		}
		
		//false不发布摄像头流
		if (m_extenalCaptureVideo)
		{
			//自采集一定要设置才发流
			options.publishCameraTrack = true;
		}
		
		//join
		m_rtcConnection.channelId = szChannel.c_str();
		m_rtcConnection.localUid = uid;
		//int nRet = m_rtcEngine->joinChannelEx(APP_TOKEN, m_rtcConnection, options, &m_rtcEventHandle);
		int nRet = m_rtcEngine->joinChannel(APP_TOKEN, szChannel.c_str(), uid, options);

		//options.publishCameraTrack = true;
		//m_rtcEngine->updateChannelMediaOptions(options);
		if (nRet)
		{
			strErr.Format(L"joinChannel error ret = %d", nRet);
			OutputDebugStringW(strErr.GetBuffer());
		}
		else
		{
			strErr.Format(L"joinChannel OK ");
			OutputDebugStringW(strErr.GetBuffer());
			m_originalvideoCheck.EnableWindow(false);
		}

		LoginRTM();
	}
	else
	{
		//离开频道前publishCameraTrack = false; 可以不停止摄像头
		ChannelMediaOptions options;
		options.publishAudioTrack = false;
		options.publishCameraTrack = false;
		m_rtcEngine->updateChannelMediaOptions(options);
		int nRet = m_rtcEngine->leaveChannel();
		UnInitRTM();
		if (nRet)
		{
			strErr.Format(L"leaveChannel error ret = %d", nRet);
			OutputDebugStringW(strErr.GetBuffer());
		}
		else
		{
			m_originalvideoCheck.EnableWindow(true);
			if (m_originalvideoCheck.GetCheck())
			{
				RegisterVideoFrameObserver(false);
				m_garyVideoFrameObserver.CloseFileObjet();
			}
			//m_rtcEngine->startPreview();
			//VideoCanvas canvas;
			//canvas.renderMode = media::base::RENDER_MODE_FIT;
			//canvas.uid = 0;
			//canvas.view = m_videoWnds[0].GetSafeHwnd();
			//setup local video in the engine to the canvas. 
			//m_rtcEngine->setupLocalVideo(canvas);

			//ShowVideoWnds();

			m_joinChannel = false;
			//m_btnJoinChannel.SetWindowText(commonCtrlJoinChannel);
			CWnd *hWnd = GetDlgItem(IDOK);
			hWnd->SetWindowText(L"加入频道");
			strErr.Format(L"leaveChannel OK ");
			OutputDebugStringW(strErr.GetBuffer());

		}
	}
}


void CLiveDemoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);
	if (bShow) 
	{
		//RenderLocalVideo();
	}
	else
	{
		ResumeStatus();
	}
	// TODO: 在此处添加消息处理程序代码
}


void CLiveDemoDlg::OnCbnSelchangeComboRole()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_rtcEngine != nullptr)
	{
		m_isBroadcaster = m_RoleCom.GetCurSel() == 0 ? true : false;
		m_rtcEngine->setClientRole(CLIENT_ROLE_TYPE(m_RoleCom.GetCurSel() + 1));
	}
}

bool CLiveDemoDlg::InitRTMService()
{
	bool ret = false;
	if (!m_pRTMInstance->IsInitCallManage())
	{
		ret = m_pRTMInstance->InitInvitationCall(m_hWnd);
	}

	
	return ret;
}

bool CLiveDemoDlg::JoinRtmChannel()
{
	CString strChannld;
	GetDlgItemText(IDC_EDIT_CHANNEL, strChannld);
	USES_CONVERSION;
	m_strChannel = W2A(strChannld.GetBuffer());
	bool ret = false;
	if (!m_pRTMInstance->IsInChannel() && !m_strChannel.empty())
	{
		ret = m_pRTMInstance->JoinChannel(m_strChannel);
		m_bInRtmChannle = true;
	}
	return ret;
}

bool CLiveDemoDlg::LoginRTM()
{
	USES_CONVERSION;
	string strAppId = W2A(CConfig::GetInstance()->GetAPP_ID().GetBuffer());
	string appCertificateID = "";
	m_pRTMCallBack = new CRTMCallBack(m_hWnd);
	m_pRTMInstance = CAgoraRTMInstance::getSignalInstance(strAppId, m_pRTMCallBack);
	m_pRTMInstance->setAppCertificateId(appCertificateID);

	m_pRTMInstance->setLoginWnd(m_hWnd);
	m_pRTMInstance->getAgoraAPI()->addEventHandler(m_pRTMCallBack);

	CString strUid;
	GetDlgItemText(IDC_EDIT_UID, strUid);
	string uid = W2A(strUid.GetBuffer());
	bool ret = m_pRTMInstance->Login(uid, strAppId);
	if (!ret)
	{
		AfxMessageBox(L"getSignalInstance()->Login error");
	}
	ret = InitRTMService();
	if (!ret)
	{
		AfxMessageBox(L"InitCallManage() error");
	}
	return ret;
}

void CLiveDemoDlg::UnInitRTM()
{
	if (m_pRTMInstance)
	{
		if (m_bInRtmChannle)
		{
			m_pRTMInstance->LeaveChannel();
			
			m_bInRtmChannle = false;
		}
		m_pRTMInstance->LogOut();
		m_pRTMInstance = nullptr;
	}
}

LRESULT CLiveDemoDlg::onJoinRTMChannel(WPARAM wParam, LPARAM lParam)
{
	Sleep(1000);
	//rtm 的 channel 不能加入过快，否则过报 102 的错误
	OutputDebugStringW(L"onJoinRTMChannel-------");
	JoinRtmChannel();
	return 1;
}

LRESULT CLiveDemoDlg::onQueryUserStatusResult(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_QUERYUSERSTATUSRESULT lpData = (PAG_SIGNAL_QUERYUSERSTATUSRESULT)wParam;

	if ("1" == lpData->status)
	{

		GetDlgItem(IDC_EDIT_RCVMSG)->SetWindowTextW(s2cs(lpData->name + std::string(" (Online)")));
	}
	else
	{

		GetDlgItem(IDC_EDIT_RCVMSG)->SetWindowTextW(s2cs(lpData->name + std::string(" (Offline)")));
	}


	delete lpData;
	lpData = nullptr;
	return TRUE;
}


LRESULT CLiveDemoDlg::onMessageSendSuccess(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGESENDSUCCESS lpData = (PAG_SIGNAL_MESSAGESENDSUCCESS)wParam;

	string strMsg;
	strMsg = "onMessageSendResult: "+ to_string(lpData->state) + "  messageID:"+lpData->messageID + "\r\n";
	CString msg;
	GetDlgItemText(IDC_EDIT_RCVMSG, msg);
	USES_CONVERSION;
	msg += L"\r\n";
	msg += A2W(strMsg.c_str());
	OutputDebugStringW(msg.GetBuffer());
	SetDlgItemText(IDC_EDIT_RCVMSG, msg);
	delete lpData;
	lpData = nullptr;

	return TRUE;
}

LRESULT CLiveDemoDlg::onMessageSendError(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGESENDERROR lpData = (PAG_SIGNAL_MESSAGESENDERROR)wParam;

	string strMsg;
	strMsg = lpData->message + "\r\n";
	CString msg(strMsg.c_str());
	SetDlgItemText(IDC_EDIT_RCVMSG, msg);
	delete lpData; lpData = nullptr;

	return TRUE;
}

LRESULT CLiveDemoDlg::onMessageInstantReceive(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGEINSTANCERECEIVE lpData = (PAG_SIGNAL_MESSAGEINSTANCERECEIVE)wParam;

	string strMsg;
	strMsg = lpData->account + ": " + lpData->msg + "\r\n";
	CString msg;
	GetDlgItemText(IDC_EDIT_RCVMSG, msg);
	USES_CONVERSION;
	msg += A2W(strMsg.c_str());
	SetDlgItemText(IDC_EDIT_RCVMSG, msg);
	if (lpData->account == m_pkUid && lpData->msg == "Stop PK")
	{
		CWnd *wnd = GetDlgItem(IDC_BTNPK);
		wnd->EnableWindow(TRUE);
		StopPK();
	}

	delete lpData; 
	lpData = nullptr;

	return TRUE;
}

LRESULT CLiveDemoDlg::onMessageChannelReceive(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_MESSAGECHANNELRECEIVE lpData = (PAG_SIGNAL_MESSAGECHANNELRECEIVE)wParam;

	string strMsg;
	strMsg = lpData->account + ": " + lpData->msg + "\r\n";
	if (lpData->msg == "PK Start")
	{
		StartPK();
	}
	else if (lpData->msg == "Stop PK")
	{
		StopPK();
	}
	else
	{
		CString msg;
		GetDlgItemText(IDC_EDIT_RCVMSG, msg);
		USES_CONVERSION;
		msg += A2W(strMsg.c_str());
		SetDlgItemText(IDC_EDIT_RCVMSG, msg);
	}



	delete lpData; 
	lpData = nullptr;
	return TRUE;
}

LRESULT CLiveDemoDlg::onChannelJoined(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOIN lpData = (PAG_SIGNAL_CHANNELJOIN)wParam;



	string strMsg = lpData->channelID + "\r\n";
	CString msg(strMsg.c_str());
	CString strInfo;
	GetDlgItemText(IDC_EDIT_RCVMSG, strInfo);
	strInfo += L"\r\n";
	strInfo += msg;
	SetDlgItemText(IDC_EDIT_RCVMSG, strInfo);

	delete lpData; 
	lpData = nullptr;
	return TRUE;
}

LRESULT CLiveDemoDlg::onChannelJoinFailed(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELJOINFAILED lpData = (PAG_SIGNAL_CHANNELJOINFAILED)wParam;

	CString strChannel = s2cs(lpData->channelID) + "\r\n";
	//AfxMessageBox(_T("join channel failed.."));
	//strChannel.ReleaseBuffer();
	SetDlgItemText(IDC_EDIT_RCVMSG, strChannel);

	delete lpData; 
	lpData = nullptr;
	return TRUE;
}

LRESULT CLiveDemoDlg::onChannelLeaved(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELLEAVE lpData = (PAG_SIGNAL_CHANNELLEAVE)wParam;

	delete lpData; 
	lpData = nullptr;
	return TRUE;
}

LRESULT CLiveDemoDlg::onChannelUserList(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELUSERLIST lpData = (PAG_SIGNAL_CHANNELUSERLIST)wParam;
	delete lpData; lpData = nullptr;

	return TRUE;
}

LRESULT CLiveDemoDlg::onChannelQueryUserNumResult(WPARAM wParam, LPARAM lParam)
{
	PAG_SIGNAL_CHANNELQUERYUSERNUMRESULT lpData = (PAG_SIGNAL_CHANNELQUERYUSERNUMRESULT)wParam;
	//char logDesc[MAXPATHLEN] = { '\0' };
	//sprintf_s(logDesc, "onChannelQueryUserNumResult(%s,%u,%d,%d)", lpData->channelID.data(), lpData->channelID.size(), lpData->ecode, lpData->num);
	//LOG_MSG(logDesc, LogType_CallBack);

	//std::map<std::string, CChatDlg*>::iterator it = m_mapChatChannel.find(lpData->channelID);
	//if (m_mapChatChannel.end() != it) {
	//	CString strParam;
	//	strParam.Format(_T("%s (numbers of channel: %d)"), s2cs(lpData->channelID), lpData->num);
	//	GetDlgItem(IDC_STATIC_CURCHATID)->SetWindowTextW(strParam);
	//}

	delete lpData; 
	lpData = nullptr;
	return TRUE;
}

LRESULT CLiveDemoDlg::onAcceptCurrentRemoteInvitation(WPARAM wParam, LPARAM lParam)
{
	IRemoteCallInvitation *lpData = (IRemoteCallInvitation*)wParam;
	if ((IRemoteCallInvitation*)wParam == nullptr)
	{
		return false;
	}
	string strCallerId = lpData->getCallerId();
	string strRes = lpData->getContent();
	string msg = strCallerId + ":" + strRes;
	int ret = MessageBoxA(m_hWnd, msg.c_str(), "提示", MB_YESNO);
	if (ret == IDYES)
	{
		ret = m_pRTMInstance->AcceptRemoteInvitation((IRemoteCallInvitation*)wParam);
		if (ret)
		{
			m_pkUid = strCallerId;
		}
	}
	else
	{
		ret = m_pRTMInstance->RefuseInvitation((IRemoteCallInvitation*)wParam);
	}
	return ret == 0 ? true : false;
}

//发起邀请PK者处理
LRESULT CLiveDemoDlg::onLocalInviteAcceptedByPeer(WPARAM wParam, LPARAM lParam)
{
	CWnd *wnd = GetDlgItem(IDC_BTNPK);
	wnd->EnableWindow(FALSE);
	StartPK();
	if (m_pRTMInstance != nullptr)
	{
		m_pRTMInstance->sendChannelMsg(m_strChannel, "PK Start", true);
	}
	//::EnableWindow((HWND)GetDlgItem(IDC_BTNPK), FALSE);
	return 1;
}

//被邀请PK者处理
LRESULT CLiveDemoDlg::onRemoteInviteAccepted(WPARAM wParam, LPARAM lParam)
{
	CWnd *wnd = GetDlgItem(IDC_BTNPK);
	wnd->EnableWindow(FALSE);
	StartPK();
	if (m_pRTMInstance != nullptr)
	{
		m_pRTMInstance->sendChannelMsg(m_strChannel, "PK Start", true);
	}
	//::EnableWindow((HWND)GetDlgItem(IDC_BTNPK), FALSE);
	return 1;
}

void CLiveDemoDlg::OnBnClickedBtnSendmsg()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strMsg;
	GetDlgItemText(IDC_EDIT_TEXT, strMsg);
	if (strMsg.IsEmpty() || m_pRTMInstance == nullptr)
	{
		return;
	}

	if (_T("") != strMsg)
	{
		m_pRTMInstance->sendChannelMsg(m_strChannel, cs2s(strMsg), false);
	}

	GetDlgItem(IDC_EDIT_TEXT)->SetWindowTextW(_T(""));
}


void CLiveDemoDlg::OnBnClickedBtnpk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUid;
	GetDlgItemText(IDC_EDIT_PKUID, strUid);

	if (strUid.IsEmpty())
	{
		return;
	}
	USES_CONVERSION;
	m_pkUid = W2A(strUid.GetBuffer());

	bool ret = m_pRTMInstance->SendInvitation(m_pkUid);
	if (!ret)
	{
		AfxMessageBox(L"SendInvitation failed!!");
	}
}


void CLiveDemoDlg::OnBnClickedBtnpkend()
{
	// TODO: 在此添加控件通知处理程序代码
	//::EnableWindow((HWND)GetDlgItem(IDC_BTNPK), TRUE);
	CWnd *wnd = GetDlgItem(IDC_BTNPK);
	wnd->EnableWindow(TRUE);

	if (m_pkUid.empty())
	{
		return;
	}

	bool ret = m_pRTMInstance->sendInstantMsg(m_pkUid, "Stop PK", false);
	if (!ret)
	{
		OutputDebugStringW(L"sendInstantMsg  Stop PK error");
	}
	else
	{
		ret = m_pRTMInstance->sendChannelMsg(m_strChannel, "Stop PK", true);
		StopPK();
	}
}

bool CLiveDemoDlg::StartPK()
{
	bool bRet = false;
	if (m_isBroadcaster)
	{
		bRet = StartPKAsBroadcaster();
	}
	else
	{
		bRet = StartPKAsAudience();
	}
	return bRet;
}

bool CLiveDemoDlg::StartPKAsAudience()
{
	//old channel
	ChannelMediaOptions option;
	option.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	option.clientRoleType = CLIENT_ROLE_AUDIENCE;
	option.autoSubscribeAudio = true;
	option.autoSubscribeVideo = true;
	option.publishAudioTrack = false;
	option.publishCameraTrack = false;
	m_rtcEngine->updateChannelMediaOptions(option);

	//entry new channel
	ChannelMediaOptions optionNew;
	optionNew.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	optionNew.clientRoleType = CLIENT_ROLE_AUDIENCE;
	optionNew.autoSubscribeAudio = true;
	optionNew.autoSubscribeVideo = true;
	optionNew.publishAudioTrack = false;
	optionNew.publishCameraTrack = false;
	m_rtc2EventHandler.SetMsgReceiver(m_hWnd);
	m_pkConnection.localUid = GetDlgItemInt(IDC_EDIT_UID) * 10;
	m_pkConnection.channelId = PK_CHANNLE;
	int ret = m_rtcEngine->joinChannelEx(APP_TOKEN, m_pkConnection, optionNew, &m_rtc2EventHandler);
	if (ret != 0)
	{
		string msg = "PK joinChannelEx error : " + to_string(ret);
		OutputDebugStringA(msg.c_str());
		return false;
	}

	m_isPk = true;
	return true;
}

bool CLiveDemoDlg::StartPKAsBroadcaster()
{
	//old channel
	ChannelMediaOptions option;
	option.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	option.clientRoleType = CLIENT_ROLE_BROADCASTER;
	option.autoSubscribeAudio = true;
	option.autoSubscribeVideo = true;
	option.publishAudioTrack = false;
	option.publishCameraTrack = false;
	m_rtcEngine->updateChannelMediaOptions(option);

	//entry new channel
	ChannelMediaOptions optionNew;
	optionNew.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	optionNew.clientRoleType = CLIENT_ROLE_BROADCASTER;
	optionNew.autoSubscribeAudio = true;
	optionNew.autoSubscribeVideo = true;
	optionNew.publishAudioTrack = false;//todo
	optionNew.publishCameraTrack = true;
	m_rtc2EventHandler.SetMsgReceiver(m_hWnd);
	m_pkConnection.localUid = GetDlgItemInt(IDC_EDIT_UID) * 100;
	m_pkConnection.channelId = PK_CHANNLE;
	int ret = m_rtcEngine->joinChannelEx(APP_TOKEN, m_pkConnection, optionNew, &m_rtc2EventHandler);
	if (ret != 0)
	{
		string msg = "PK joinChannelEx error : " + to_string(ret);
		OutputDebugStringA(msg.c_str());
		return false;
	}
	//updateChannelMediaOptionsEx 不能显示远端view
	//m_rtcEngine->updateChannelMediaOptionsEx(optionNew, m_pkConnection);
	//m_rtcEngine->setLiveTranscoding(,);


	m_isPk = true;
	//ShowVideoWnds();
	return true;
}

void CLiveDemoDlg::StopPK()
{
	ChannelMediaOptions option;
	option.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	if (m_isBroadcaster)
	{
		option.clientRoleType = CLIENT_ROLE_BROADCASTER;
		option.publishAudioTrack = true;
		option.publishCameraTrack = true;
	}
	else
	{
		option.clientRoleType = CLIENT_ROLE_AUDIENCE;
		option.publishAudioTrack = false;
		option.publishCameraTrack = false;
	}
	option.autoSubscribeAudio = true;
	option.autoSubscribeVideo = true;
	m_rtcEngine->updateChannelMediaOptions(option);

	//不能updateChannelMediaOptionsEx 否则 channel 1 不能推流
	//ChannelMediaOptions option1;
	//option1.channelProfile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	//option1.clientRoleType = CLIENT_ROLE_BROADCASTER;
	//option1.autoSubscribeAudio = false;
	//option1.autoSubscribeVideo = false;
	//option1.publishAudioTrack = false;
	//option1.publishCameraTrack = false;
	//m_rtcEngine->updateChannelMediaOptionsEx(option, m_pkConnection);

	if (m_isPk)
	{
		m_rtcEngine->leaveChannelEx(m_pkConnection);
		m_isPk = false;
	}

	if (m_isBroadcaster)
	{
		m_rtcEngine->enableVideo();
		RenderLocalVideo();
	}

	
}

bool CLiveDemoDlg::RegisterVideoFrameObserver(BOOL bEnable, IVideoFrameObserver * videoFrameObserver)
{
	agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
	mediaEngine.queryInterface(m_rtcEngine, AGORA_IID_MEDIA_ENGINE);
	int nRet = 0;
	agora::base::AParameter apm(*m_rtcEngine);
	if (mediaEngine.get()==nullptr)
	{
		return false;
	}
	if (bEnable)
	{
		nRet = mediaEngine->registerVideoFrameObserver(videoFrameObserver);
	}
	else
	{
		nRet = mediaEngine->registerVideoFrameObserver(nullptr);
	}
	return true;
}

bool CLiveDemoDlg::EnableExtendVideoCapture(BOOL bEnable)
{
	agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
	//query interface agora::AGORA_IID_MEDIA_ENGINE in the engine.
	mediaEngine.queryInterface(m_rtcEngine, agora::rtc::AGORA_IID_MEDIA_ENGINE);
	int nRet = 0;
	agora::base::AParameter apm(m_rtcEngine);
	if (mediaEngine.get() == NULL)
		return FALSE;
	if (bEnable) 
	{
		//mediaEngine->setExternalVideoSource(false, false);
		//set local video camera index.
		//nRet = apm->setParameters("{\"che.video.local.camera_index\":1024}");
		//register agora video frame observer.
		//(*lpDeviceManager)->setDevice("1024");
		nRet = mediaEngine->setExternalVideoSource(true, false);
		//nRet = mediaEngine->registerVideoFrameObserver(&m_extVideoFrameObserver);
	}
	else 
	{

		//nRet = apm->setParameters("{\"che.video.local.camera_index\":0}");
		nRet = mediaEngine->setExternalVideoSource(false, false);
		//unregister agora video frame observer.
		//nRet = mediaEngine->registerVideoFrameObserver(NULL);
	}
	return nRet == 0 ? true : false;
}

void CLiveDemoDlg::InitCamear()
{
	AGORA_DEVICE_INFO	agDeviceInfo;
	m_camearCombo.ResetContent();
	//enum video capture device.
	CoInitialize(nullptr);
	m_agVideoCaptureDevice.Create();

	m_agVideoCaptureDevice.EnumDeviceList();
	for (int nIndex = 0; nIndex < m_agVideoCaptureDevice.GetDeviceCount(); nIndex++) 
	{
		m_agVideoCaptureDevice.GetDeviceInfo(nIndex, &agDeviceInfo);
		m_camearCombo.InsertString(nIndex, agDeviceInfo.szDeviceName);
	}
	m_camearCombo.SetCurSel(0);

	OnCbnSelchangeComboCamear();
}

void CLiveDemoDlg::InitVideoType()
{

}

void CLiveDemoDlg::OnBnClickedBtnCapturetype()
{
	// TODO: 在此添加控件通知处理程序代码
	m_isBroadcaster = m_RoleCom.GetCurSel() == 0 ? true : false;
	if (!m_isBroadcaster)
	{
		return;
	}
	m_extenalCaptureVideo = !m_extenalCaptureVideo;
	if (m_extenalCaptureVideo)
	{
		if (m_videoType.GetCurSel() == -1)
		{
			//m_lstInfo.InsertString(m_lstInfo.GetCount(), _T("can not set vitrual video capture"));
			return;
		}
		EnableExtendVideoCapture(TRUE);
		//register agora video frame observer.
		EnableCaputre(TRUE);

		((CWnd*)GetDlgItem(IDC_BTN_CAPTURETYPE))->SetWindowText(L"取消自采集");
		//m_lstInfo.InsertString(m_lstInfo.GetCount(), _T("use extenal video frame observer sucess!"));

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRun, this, 0, NULL);
	}
	else 
	{
		EnableCaputre(FALSE);
		//unregister agora frame observer.
		EnableExtendVideoCapture(FALSE);
		((CWnd*)GetDlgItem(IDC_BTN_CAPTURETYPE))->SetWindowText(L"设置自采集");
		//m_lstInfo.InsertString(m_lstInfo.GetCount(), _T("restore video frame observer sucess!"));
	}
}

void CLiveDemoDlg::EnableCaputre(BOOL bEnable)
{
	if (bEnable == (BOOL)!m_extenalCaptureVideo)
		return;

	int nIndex = m_videoType.GetCurSel();
	if (bEnable)
	{
		//select video capture type.
		m_agVideoCaptureDevice.SelectMediaCap(nIndex == -1 ? 0 : nIndex);
		VIDEOINFOHEADER videoInfo;
		VideoEncoderConfiguration config;
		//create video capture filter.
		m_agVideoCaptureDevice.CreateCaptureFilter();
		m_agVideoCaptureDevice.GetCurrentVideoCap(&videoInfo);
		config.dimensions.width = videoInfo.bmiHeader.biWidth;
		config.dimensions.height = videoInfo.bmiHeader.biHeight;
		m_videoFrame.stride = videoInfo.bmiHeader.biWidth;
		m_videoFrame.height = videoInfo.bmiHeader.biHeight;
		m_videoFrame.rotation = 0;
		m_videoFrame.cropBottom = 0;
		m_videoFrame.cropLeft = 0;
		m_videoFrame.cropRight = 0;
		m_videoFrame.cropTop = 0;
		m_videoFrame.format = agora::media::base::VIDEO_PIXEL_I420;
		m_videoFrame.type = agora::media::base::ExternalVideoFrame::VIDEO_BUFFER_TYPE::VIDEO_BUFFER_RAW_DATA;
		//set video encoder configuration.
		m_rtcEngine->setVideoEncoderConfiguration(config);
		//set render hwnd,image width,image height,identify yuv.
		m_d3dRender.Init(m_videoWnds[0].GetSafeHwnd(), videoInfo.bmiHeader.biWidth, videoInfo.bmiHeader.biHeight, true);
		//start video capture.
		m_agVideoCaptureDevice.Start();
		//enable video in the engine.
		m_rtcEngine->enableVideo();
		//start preview in the engine.
		m_rtcEngine->startPreview();

		//VideoCanvas canvas;
		//canvas.renderMode = media::base::RENDER_MODE_FIT;
		//canvas.uid = 0;
		//canvas.view = m_videoWnds[0].GetSafeHwnd();
		////setup local video in the engine to the canvas. 

		//m_rtcEngine->setupLocalVideo(canvas);
	}
	else {
		//video capture stop.
		m_agVideoCaptureDevice.Stop();
		//remove video capture filter.
		m_agVideoCaptureDevice.RemoveCaptureFilter();
		if (m_rtcEngine)
		{
			//disable video in the engine.
			m_rtcEngine->disableVideo();
			//stop preview in the engine.
			m_rtcEngine->stopPreview();

			m_d3dRender.Close();
		}
	}
}

void CLiveDemoDlg::ThreadRun(CLiveDemoDlg * self)
{
	agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
	//query interface agora::AGORA_IID_MEDIA_ENGINE in the engine.
	mediaEngine.queryInterface(self->m_rtcEngine, agora::rtc::AGORA_IID_MEDIA_ENGINE);
	while (self->m_extenalCaptureVideo)
	{
		if (self->m_videoFrame.format == 24)
		{
			return;
		}
		else if (self->m_videoFrame.format == agora::media::base::VIDEO_PIXEL_I420) 
		{
			int bufSize = self->m_videoFrame.stride * self->m_videoFrame.height * 3 / 2;
			int timestamp = GetTickCount();
			if (CAgVideoBuffer::GetInstance()->readBuffer(self->m_buffer, bufSize, timestamp)) 
			{
				memcpy_s(self->m_imgBuffer, bufSize, self->m_buffer, bufSize);
				self->m_videoFrame.timestamp = timestamp;
			}
			else
			{
				Sleep(1);
				continue;
			}
			self->m_videoFrame.buffer = self->m_imgBuffer;
			//render image buffer to hwnd.
			self->m_d3dRender.Render((char*)self->m_buffer);

			mediaEngine->pushVideoFrame(&self->m_videoFrame);
			Sleep(1);
		}
	}
}

void CLiveDemoDlg::OnCbnSelchangeComboCamear()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR	szDevicePath[MAX_PATH] = { 0 };
	SIZE_T	nPathLen = MAX_PATH;
	int		nSel = m_camearCombo.GetCurSel();

	VIDEOINFOHEADER		vidInfoHeader;
	CString				strInfo;
	CString				strCompress;
	//get current device name.
	m_videoType.ResetContent();

	BOOL bSuccess = m_agVideoCaptureDevice.GetCurrentDevice(szDevicePath, &nPathLen);
	if (bSuccess)
		m_agVideoCaptureDevice.CloseDevice();

	if (nSel != -1) 
	{
		//open device.
		if (!m_agVideoCaptureDevice.OpenDevice(nSel))
			return;
	}
	//enumerate video capture device type. 
	int count = m_agVideoCaptureDevice.GetMediaCapCount();
	for (int nIndex = 0; nIndex < count; nIndex++) 
	{
		m_agVideoCaptureDevice.GetVideoCap(nIndex, &vidInfoHeader);
		if (vidInfoHeader.bmiHeader.biCompression == 0)continue;
		switch (vidInfoHeader.bmiHeader.biCompression)
		{
		case MAKEFOURCC('I', '4', '2', '0'):
			strInfo.Format(_T("%d*%d %dfps(YUV420)"), vidInfoHeader.bmiHeader.biWidth, vidInfoHeader.bmiHeader.biHeight, 10000000 / vidInfoHeader.AvgTimePerFrame);
			break;
		case 0x00000000:
			strInfo.Format(_T("%d*%d %dfps(RGB24)"), vidInfoHeader.bmiHeader.biWidth, vidInfoHeader.bmiHeader.biHeight, 10000000 / vidInfoHeader.AvgTimePerFrame);
			break;
		case MAKEFOURCC('Y', 'U', 'Y', '2'):
			strInfo.Format(_T("%d*%d %dfps(YUY2)"), vidInfoHeader.bmiHeader.biWidth, vidInfoHeader.bmiHeader.biHeight, 10000000 / vidInfoHeader.AvgTimePerFrame);
			break;
		case MAKEFOURCC('M', 'J', 'P', 'G'):
			strInfo.Format(_T("%d*%d %dfps(MJPEG)"), vidInfoHeader.bmiHeader.biWidth, vidInfoHeader.bmiHeader.biHeight, 10000000 / vidInfoHeader.AvgTimePerFrame);
			break;
		case MAKEFOURCC('U', 'Y', 'V', 'Y'):
			strInfo.Format(_T("%d*%d %dfps(UYVY)"), vidInfoHeader.bmiHeader.biWidth, vidInfoHeader.bmiHeader.biHeight, 10000000 / vidInfoHeader.AvgTimePerFrame);
			break;
		}
		m_videoType.InsertString(nIndex, strInfo);
	}
	m_videoType.SetCurSel(0);
}

void CLiveDemoDlg::OnNMReleasedcaptureSliderAudio(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int pos = m_sldVolume.GetPos();
	m_rtcEngine->adjustAudioMixingPlayoutVolume(pos);
	m_rtcEngine->adjustAudioMixingPublishVolume(pos);
}

void CLiveDemoDlg::OnBnClickedBtnAudiomixing()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_rtcEngine == nullptr)
	{
		return;
	}
	m_bPlayMixing = !m_bPlayMixing;
	if (m_bPlayMixing)
	{
		int pos = m_sldVolume.GetPos();
		bool bLocalOnly = m_localOnlyCheck.GetCheck();
		bool bReplaceMic = m_replaceMicCheck.GetCheck();
		int loopCount = GetDlgItemInt(IDC_EDIT_PLAYCOUNT);
		if (loopCount < 1)
		{
			loopCount = 1;
		}
		CString filePath;
		GetDlgItemText(IDC_EDIT_AUDIOPATH, filePath);
		if (filePath.IsEmpty())
		{
			return;
		}
		USES_CONVERSION;
		string path(W2A(filePath.GetBuffer()));
		int ret = m_rtcEngine->startAudioMixing(path.c_str(), bLocalOnly, bReplaceMic, loopCount);
		m_rtcEngine->adjustAudioMixingPlayoutVolume(pos);
		if (ret >0 )
		{
			OutputDebugStringW(L"startAudioMixing error");
		}
		m_localOnlyCheck.EnableWindow(false);
		m_replaceMicCheck.EnableWindow(false);
	}
	else
	{
		m_rtcEngine->stopAudioMixing();
		m_localOnlyCheck.EnableWindow(true);
		m_replaceMicCheck.EnableWindow(true);
	}
}


void CLiveDemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CoUninitialize();
	UnInitAgora();
	delete []m_buffer;
	delete []m_imgBuffer;
	CDialogEx::OnClose();
}





void CLiveDemoDlg::OnBnClickedBtnRetate()
{
	// TODO: 在此添加控件通知处理程序代码
	static int nCount = 0;
	nCount++;
	nCount = nCount % 4;
	VIDEO_ORIENTATION rotate = (VIDEO_ORIENTATION)(VIDEO_ORIENTATION_0 + nCount * VIDEO_ORIENTATION_90);
	m_rtcEngine->setCameraDeviceOrientation(VIDEO_SOURCE_CAMERA_PRIMARY, rotate);
	
}


void CLiveDemoDlg::OnBnClickedBtnMirror()
{
	// TODO: 在此添加控件通知处理程序代码
	//char *id = new char(521);
	static bool enable = false;
	enable = !enable;
	VIDEO_MIRROR_MODE_TYPE mode = enable ? VIDEO_MIRROR_MODE_ENABLED : VIDEO_MIRROR_MODE_DISABLED;

	//LocalTranscoderConfiguration config;
	//TranscodingVideoStream inStream;
	//VideoEncoderConfiguration encoderConfig;

	CameraCapturerConfiguration config;
	config.format.width = 640;
	config.format.height = 360;
	config.format.fps = 15;

	AVideoDeviceManager* videoDeviceManager = new AVideoDeviceManager(m_rtcEngine);
	if (videoDeviceManager == nullptr)
	{
		return;
	}
	IVideoDeviceCollection* collections = (*videoDeviceManager)->enumerateVideoDevices();
	USES_CONVERSION;

	for (int i = 0; i < collections->getCount(); ++i) {
		char deviceId[512] = { 0 };
		char deviceName[512] = { 0 };
		// Get camera information
		collections->getDevice(i, deviceName, deviceId);
		CString strName;
		m_camearCombo.GetWindowText(strName);
		string strDevice(W2A(strName.GetBuffer()));
		if (strDevice == deviceName)
		{
			strcpy_s(config.deviceId, 512, deviceId);
			break;
		}
	}
	int ret = 0;
	//start primary camera capture
	ret = m_rtcEngine->startPrimaryCameraCapture(config);

	agora::rtc::TranscodingVideoStream stream_infos[2];    //指定视频源在合图中的布局
	stream_infos[0].sourceType = agora::media::PRIMARY_CAMERA_SOURCE;  //指定视频源的类型为camera

	stream_infos[0].x = 0;
	stream_infos[0].y = 0;
	stream_infos[0].width = 640;
	stream_infos[0].height = 320;
	stream_infos[0].zOrder = 3;    //越大表示图层越靠上
	stream_infos[0].mirror = enable;
	stream_infos[0].alpha = 0.5;

	stream_infos[1].sourceType = agora::media::RTC_IMAGE_PNG_SOURCE;     //指定视频源的类型为PNG图片

	stream_infos[1].x = 0;
	stream_infos[1].y = 0;
	stream_infos[1].width = 640;
	stream_infos[1].height = 320;
	stream_infos[1].zOrder = 1;
	stream_infos[1].imageUrl = "C:\\Users\\ZhongZhigang\\Pictures\\64861961789.png";
	//stream_infos[1].mirror = enable;

	agora::rtc::VideoEncoderConfiguration encoder_config;
	encoder_config.codecType = agora::rtc::VIDEO_CODEC_H264;
	//输出的视图大小
	encoder_config.dimensions = { 640, 320 };
	encoder_config.bitrate = 2000;
	encoder_config.frameRate = 15;

	agora::rtc::LocalTranscoderConfiguration transcoder_config;
	transcoder_config.streamCount = sizeof(stream_infos) / sizeof(stream_infos[0]);
	transcoder_config.VideoInputStreams = stream_infos;
	transcoder_config.videoOutputConfiguration = encoder_config;

	static bool bStart = false;
	if (!bStart)
	{
		int ret = m_rtcEngine->startLocalVideoTranscoder(transcoder_config);
		bStart = true;
		if (ret != 0)
		{
			OutputDebugStringW(L"updateLocalTranscoderConfiguration error");
		}
		//m_rtcEngine->updateLocalTranscoderConfiguration(transcoder_config);
		m_bTranscoder = true;
		GetDlgItem(IDC_BTN_MIRROR)->SetWindowText(L"水平翻转");
		return;
	}
	
	transcoder_config.VideoInputStreams[0].mirror = enable;
	ret = m_rtcEngine->updateLocalTranscoderConfiguration(transcoder_config);
	if (ret != 0)
	{
		OutputDebugStringW(L"updateLocalTranscoderConfiguration error");
	}
	
	//m_rtcEngine->setLocalVideoMirrorMode(mode);
	//m_rtcEngine->setLocalRenderMode(media::base::RENDER_MODE_FIT, mode);
	//m_rtcEngine->updateLocalTranscoderConfiguration(config);
}
