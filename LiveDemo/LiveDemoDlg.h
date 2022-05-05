
// LiveDemoDlg.h: 头文件
//

#pragma once
#include <list>
#include "VideoFrameObserver.h"
#include "DirectShow/AgVideoBuffer.h"
#include "DirectShow/AGDShowVideoCapture.h"
#include "d3d/D3DRender.h"
#define VIDEO_COUNT                     36
#define IDC_BASEWND_VIDEO               113


class CLiveBroadcastingRtcEngineEventHandler
	: public IRtcEngineEventHandler
{
public:
	//set the message notify window handler
	void SetMsgReceiver(HWND hWnd) { m_hMsgHanlder = hWnd; }
	/*
	note:
		Join the channel callback.This callback method indicates that the client
		successfully joined the specified channel.Channel ids are assigned based
		on the channel name specified in the joinChannel. If IRtcEngine::joinChannel
		is called without a user ID specified. The server will automatically assign one
	parameters:
		channel:channel name.
		uid: user ID。If the UID is specified in the joinChannel, that ID is returned here;
		Otherwise, use the ID automatically assigned by the Agora server.
		elapsed: The Time from the joinChannel until this event occurred (ms).
	*/
	virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;
	/*
	note:
		In the live broadcast scene, each anchor can receive the callback
		of the new anchor joining the channel, and can obtain the uID of the anchor.
		Viewers also receive a callback when a new anchor joins the channel and
		get the anchor's UID.When the Web side joins the live channel, the SDK will
		default to the Web side as long as there is a push stream on the
		Web side and trigger the callback.
	parameters:
		uid: remote user/anchor ID for newly added channel.
		elapsed: The joinChannel is called from the local user to the delay triggered
		by the callback（ms).
	*/
	virtual void onUserJoined(uid_t uid, int elapsed) override;
	/*
	note:
		Remote user (communication scenario)/anchor (live scenario) is called back from
		the current channel.A remote user/anchor has left the channel (or dropped the line).
		There are two reasons for users to leave the channel, namely normal departure and
		time-out:When leaving normally, the remote user/anchor will send a message like
		"goodbye". After receiving this message, determine if the user left the channel.
		The basis of timeout dropout is that within a certain period of time
		(live broadcast scene has a slight delay), if the user does not receive any
		packet from the other side, it will be judged as the other side dropout.
		False positives are possible when the network is poor. We recommend using the
		Agora Real-time messaging SDK for reliable drop detection.
	parameters:
		uid: The user ID of an offline user or anchor.
		reason:Offline reason: USER_OFFLINE_REASON_TYPE.
	*/
	virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) override;
	/*
	note:
		When the App calls the leaveChannel method, the SDK indicates that the App
		has successfully left the channel. In this callback method, the App can get
		the total call time, the data traffic sent and received by THE SDK and other
		information. The App obtains the call duration and data statistics received
		or sent by the SDK through this callback.
	parametes:
		stats: Call statistics.
	*/
	virtual void onLeaveChannel(const RtcStats& stats) override;
	virtual void onNetworkQuality(uid_t uid, int txQuality, int rxQuality) override {
		if (m_hMsgHanlder&& report) {
			PNetworkQuality quality = new NetworkQuality;
			quality->uid = uid;
			quality->txQuality = txQuality;
			quality->txQuality = rxQuality;

			//::PostMessage(m_hMsgHanlder, WM_MSGID(EID_NETWORK_QUALITY), (WPARAM)quality, 0);

		}
	}
	virtual void onRtcStats(const RtcStats& stats) override {
		if (m_hMsgHanlder&& report) {
			RtcStats* s = new RtcStats;
			*s = stats;

			//::PostMessage(m_hMsgHanlder, WM_MSGID(EID_RTC_STATS), (WPARAM)s, 0);

		}
	}


	virtual void onLocalAudioStats(const LocalAudioStats& stats) override {
		if (m_hMsgHanlder&& report) {
			LocalAudioStats* s = new LocalAudioStats;
			*s = stats;
			//::PostMessage(m_hMsgHanlder, WM_MSGID(EID_LOCAL_AUDIO_STATS), (WPARAM)s, 0);

		}
	}

	virtual void onLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error) {
		if (m_hMsgHanlder&& report) {
			//::PostMessage(m_hMsgHanlder, WM_MSGID(EID_LOCAL_AUDIO_STATE_CHANED), (WPARAM)state, (LPARAM)error);
		}
	}

	virtual void onRemoteAudioStats(const RemoteAudioStats& stats) {
		if (m_hMsgHanlder&& report) {
			RemoteAudioStats* s = new RemoteAudioStats;
			*s = stats;
			//::PostMessage(m_hMsgHanlder, WM_MSGID(EID_REMOTE_AUDIO_STATS), (WPARAM)s, 0);

		}
	}

	virtual void onRemoteAudioStateChanged(uid_t uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, int elapsed) {
		if (m_hMsgHanlder&& report) {
			PRemoteAudioState s = new RemoteAudioState;
			s->elapsed = elapsed;
			s->uid = uid;
			s->state = state;
			s->reason = reason;
			//::PostMessage(m_hMsgHanlder, WM_MSGID(EID_REMOTE_AUDIO_STATE_CHANGED), (WPARAM)s, 0);

		}
	}
	virtual void onLocalVideoStats(const LocalVideoStats& stats) {
		if (m_hMsgHanlder&& report) {
			LocalVideoStats* s = new LocalVideoStats;
			*s = stats;
			::PostMessage(m_hMsgHanlder, WM_MSGID(EID_LOCAL_VIDEO_STATS), (WPARAM)s, 0);

		}
	}

	virtual void onLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error) 
	{
		if (m_hMsgHanlder&& report) 
		{
			::PostMessage(m_hMsgHanlder, WM_MSGID(EID_LOCAL_VIDEO_STATE_CHANGED), (WPARAM)state, (LPARAM)error);
		}
	}
	virtual void onRemoteVideoStats(const RemoteVideoStats& stats) 
	{
		if (m_hMsgHanlder/*&& report*/) 
		{
			RemoteVideoStats* s = new RemoteVideoStats;
			*s = stats;
			::PostMessage(m_hMsgHanlder, WM_MSGID(EID_REMOTE_VIDEO_STATS), (WPARAM)s, 0);

		}
	}

	virtual void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, int elapsed) {
		if (m_hMsgHanlder&& report) {
			PRemoteVideoState s = new RemoteVideoState;
			s->elapsed = elapsed;
			s->uid = uid;
			s->state = state;
			s->reason = reason;
			::PostMessage(m_hMsgHanlder, WM_MSGID(EID_REMOTE_VIDEO_STATE_CHANGED), (WPARAM)s, 0);

		}
	}

	virtual void onNetworkTypeChanged(NETWORK_TYPE type) 
	{
			(void)type;
			string strType = to_string(type);
			OutputDebugStringA(strType.c_str());
	}
	void SetReport(bool b) { report = b; }
private:
	HWND m_hMsgHanlder;
	bool report = false;
};


// CLiveDemoDlg 对话框
class CLiveDemoDlg : public CDialogEx
{
// 构造
public:
	CLiveDemoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIVEDEMO_DIALOG };
#endif
	void InitCtrl();

	//Initialize the Agora SDK
	bool InitAgora();
	//UnInitialize the Agora SDK
	void UnInitAgora();
	//init rtm
	bool InitRTMService();
	//
	bool LoginRTM();
	//
	void UnInitRTM();
	//
	bool JoinRtmChannel();

	//create all video window to save m_videoWnds.
	void CreateAllVideoWnds();
	//show all video window from m_videoWnds.
	void ShowVideoWnds();

	void RenderLocalVideo();
	//resume window status
	void ResumeStatus();
	//
	void StopPK();
	//
	bool StartPK();
	bool StartPKAsBroadcaster();
	bool StartPKAsAudience();


	//register or unregister agora video Frame Observer.
	bool RegisterVideoFrameObserver(BOOL bEnable, IVideoFrameObserver * videoFrameObserver = NULL);
	//set Extend video src
	bool EnableExtendVideoCapture(BOOL bEnable);

	void InitCamear();

	void InitVideoType();

	//
	void EnableCaputre(BOOL bEnable);

	static void ThreadRun(CLiveDemoDlg*self);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	CButton m_originalvideoCheck;
	CComboBox m_camearCombo;
	CComboBox m_videoType;
	CSliderCtrl m_sldVolume;
	CButton m_localOnlyCheck;
	CButton m_replaceMicCheck;
	//rtm
	CAgoraRTMInstance* m_pRTMInstance;
	CRTMCallBack* m_pRTMCallBack;
	//
	CLiveBroadcastingRtcEngineEventHandler m_rtcEventHandle;
	CLiveBroadcastingRtcEngineEventHandler m_rtc2EventHandler;
	RtcConnection m_pkConnection;
	RtcConnection m_rtcConnection;
	IRtcEngineEx* m_rtcEngine = nullptr;
	bool m_initialize;
	bool m_joinChannel;
	int m_maxVideoCount;
	list<uid_t> m_lstUids;
	CComboBox m_RoleCom;
	CStatic m_videoArea;
	bool m_bInRtmChannle;
	string m_strChannel;
	string m_pkUid;
	bool m_isPk;
	bool m_isBroadcaster;
	bool m_extenalCaptureVideo;
	CAGDShowVideoCapture m_agVideoCaptureDevice;
	D3DRender m_d3dRender;
	agora::media::base::ExternalVideoFrame m_videoFrame;
	BYTE * m_buffer;
	BYTE * m_imgBuffer;
	//
	CGrayVideoProcFrameObserver m_garyVideoFrameObserver;
	CAverageFilterVideoProcFrameObserver m_averageFilterVideoFrameObserver;

	//video wnd
	CAGVideoWnd m_videoWnds[VIDEO_COUNT];
	//音效
	bool m_bPlayMixing;

	bool m_bTranscoder;

public:
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//Agora Event handler
	afx_msg LRESULT OnEIDJoinChannelSuccess(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDLeaveChannel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserJoined(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEIDUserOffline(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onEIDLocalVideoStats(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onEIDLocalVideoStateChanged(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onEIDRemoteVideoStats(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onEIDRemoteVideoStateChanged(WPARAM wParam, LPARAM lParam);

	//rtm
	LRESULT onJoinRTMChannel(WPARAM wParam, LPARAM lParam);
	LRESULT onQueryUserStatusResult(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageSendSuccess(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageSendError(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageInstantReceive(WPARAM wParam, LPARAM lParam);
	LRESULT onMessageChannelReceive(WPARAM wParam, LPARAM lParam);

	LRESULT onChannelJoined(WPARAM wParam, LPARAM lParam);
	LRESULT onChannelJoinFailed(WPARAM wParam, LPARAM lParam);
	LRESULT onChannelLeaved(WPARAM wParam, LPARAM lParam);
	LRESULT onChannelUserList(WPARAM wParam, LPARAM lParam);
	LRESULT onChannelQueryUserNumResult(WPARAM wParam, LPARAM lParam);
	LRESULT onAcceptCurrentRemoteInvitation(WPARAM wParam, LPARAM lParam);
	LRESULT onLocalInviteAcceptedByPeer(WPARAM wParam, LPARAM lParam);
	LRESULT onRemoteInviteAccepted(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeComboRole();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnSendmsg();
	afx_msg void OnBnClickedBtnpk();
	afx_msg void OnBnClickedBtnpkend();

	afx_msg void OnBnClickedBtnCapturetype();
	afx_msg void OnCbnSelchangeComboCamear();
	afx_msg void OnNMReleasedcaptureSliderAudio(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnAudiomixing();

	afx_msg void OnBnClickedBtnRetate();
	afx_msg void OnBnClickedBtnMirror();
};
