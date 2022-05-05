#include "pch.h"
#include "commonFun.h"
#include "RTMWrap.h"
#include "AgoraRTMInstance.h"

void CRTMCallEventHandler::onLocalInvitationReceivedByPeer(ILocalCallInvitation *localInvitation)
{
	(ILocalCallInvitation *)localInvitation;
	string calledId = to_string(GetCurrentProcessId()) + "onLocalInvitationReceivedByPeer->getCalleeId() :";
	calledId += localInvitation->getCalleeId();
	OutputDebugStringA(calledId.c_str());
}

void CRTMCallEventHandler::onLocalInvitationCanceled(ILocalCallInvitation *localInvitation)
{
	(ILocalCallInvitation *)localInvitation;
	string calledId = to_string(GetCurrentProcessId()) + "onLocalInvitationCanceled->getCalleeId() :";
	calledId += localInvitation->getCalleeId();
	OutputDebugStringA(calledId.c_str());

	PostMessage(m_MsgWnd, WM_InviteCanceled, (WPARAM)localInvitation, NULL);
}

void CRTMCallEventHandler::onLocalInvitationFailure(ILocalCallInvitation *localInvitation, LOCAL_INVITATION_ERR_CODE errorCode)
{
	(ILocalCallInvitation *)localInvitation;
	(LOCAL_INVITATION_ERR_CODE)errorCode;
	string calledId = to_string(GetCurrentProcessId()) + localInvitation->getCalleeId();
	calledId += "onLocalInvitationFailure errorCode:";
	calledId += to_string(errorCode);
	OutputDebugStringA(calledId.c_str());
}


void CRTMCallEventHandler::onRemoteInvitationReceived(IRemoteCallInvitation *remoteInvitation)
{
	(IRemoteCallInvitation *)remoteInvitation;
	string calledId = to_string(GetCurrentProcessId()) + "onRemoteInvitationReceived ->getCalleeId() :";
	calledId += remoteInvitation->getCallerId();
	OutputDebugStringA(calledId.c_str());

	PostMessage(m_MsgWnd, WM_InviteReceived, (WPARAM)remoteInvitation, NULL);
}

void CRTMCallEventHandler::onLocalInvitationAccepted(ILocalCallInvitation *localInvitation, const char *response)
{
	(ILocalCallInvitation *)localInvitation;
	(const char *)response;
	string calledId = to_string(GetCurrentProcessId()) + "  onLocalInvitationAccepted->getCalleeId() :";
	calledId += localInvitation->getCalleeId();
	OutputDebugStringA(calledId.c_str());

	PostMessage(m_MsgWnd, WM_InviteAcceptedByPeer, (WPARAM)localInvitation, NULL);
}

void CRTMCallEventHandler::onLocalInvitationRefused(ILocalCallInvitation *localInvitation, const char *response)
{
	(ILocalCallInvitation *)localInvitation;
	(const char *)response;
	string calledId = to_string(GetCurrentProcessId()) + "onLocalInvitationRefused ->getCalleeId() :";
	calledId += localInvitation->getCalleeId();
	calledId += localInvitation->getResponse();
	OutputDebugStringA(calledId.c_str());

	PostMessage(m_MsgWnd, WM_InviteRefusedByPeer, (WPARAM)localInvitation, NULL);
}

void CRTMCallEventHandler::onRemoteInvitationRefused(IRemoteCallInvitation *remoteInvitation)
{
	(IRemoteCallInvitation *)remoteInvitation;
	string calledId = to_string(GetCurrentProcessId()) + "onRemoteInvitationRefused ->getCalleeId() :";
	calledId += remoteInvitation->getCallerId();
	OutputDebugStringA(calledId.c_str());

	PostMessage(m_MsgWnd, WM_InviteRefused, (WPARAM)remoteInvitation, NULL);
}

void CRTMCallEventHandler::onRemoteInvitationAccepted(IRemoteCallInvitation *remoteInvitation)
{
	(IRemoteCallInvitation *)remoteInvitation;
	string calledId = to_string(GetCurrentProcessId()) + "onRemoteInvitationAccepted ->getCalleeId() :";
	calledId += remoteInvitation->getCallerId();
	OutputDebugStringA(calledId.c_str());
	PostMessage(m_MsgWnd, WM_InviteAccepted, (WPARAM)remoteInvitation, NULL);
}

void CRTMCallEventHandler::onRemoteInvitationFailure(IRemoteCallInvitation *remoteInvitation, REMOTE_INVITATION_ERR_CODE errorCode)
{
	(IRemoteCallInvitation *)remoteInvitation;
	string calledId = to_string(GetCurrentProcessId()) + "onRemoteInvitationFailure  error :";
	//calledId += remoteInvitation->getCallerId();
	calledId += to_string(errorCode);
	OutputDebugStringA(calledId.c_str());
}

void CRTMCallEventHandler::onRemoteInvitationCanceled(IRemoteCallInvitation *remoteInvitation)
{
	(IRemoteCallInvitation *)remoteInvitation;
	string calledId = "onRemoteInvitationCanceled ->getCalleeId() :";
	calledId += remoteInvitation->getCallerId();
	OutputDebugStringA(calledId.c_str());

	PostMessage(m_MsgWnd, WM_InviteCanceledByPeer, (WPARAM)remoteInvitation, NULL);
}


CRTMCallBack::CRTMCallBack(HWND wnd) :m_MsgWnd(wnd)
{
}

CRTMCallBack::~CRTMCallBack()
{
  m_MsgWnd = nullptr;
}

void CRTMCallBack::setCallBackWnd(HWND wnd)
{
  m_MsgWnd = wnd;
}

// Inherited from |agora::rtm::IRtmServiceEventHandler|
void CRTMCallBack::onLoginSuccess() 
{
  PAG_SIGNAL_LOGINSUCCESS lpData = new AG_SIGNAL_LOGINSUCCESS;
  lpData->fd = 0;
  lpData->uid = 0;

  postMsg(WM_LoginSuccess, WPARAM(lpData));
}

void CRTMCallBack::onLoginFailure(LOGIN_ERR_CODE errorCode) 
{
  PAG_SIGNAL_LOGINFAILED lpData = new AG_SIGNAL_LOGINFAILED;
  lpData->ecode = errorCode;

  postMsg(WM_LoginFailed, WPARAM(lpData), LPARAM(errorCode));
}

void CRTMCallBack::onLogout(LOGOUT_ERR_CODE errorCode) 
{
  PAG_SIGNAL_LOGOUT lpData = new AG_SIGNAL_LOGOUT;
  lpData->ecode = errorCode;

  postMsg(WM_LogOut, WPARAM(lpData), LPARAM(errorCode));
}

void CRTMCallBack::onConnectionStateChanged(CONNECTION_STATE state, CONNECTION_CHANGE_REASON reason) 
{
}

void CRTMCallBack::onSendMessageResult(long long messageId, PEER_MESSAGE_ERR_CODE errorCode) 
{
	PAG_SIGNAL_MESSAGESENDSUCCESS  lpData = new AG_SIGNAL_MESSAGESENDSUCCESS;
	lpData->messageID = utf82gbk(std::to_string(messageId));

	postMsg(WM_MessageSendSuccess, WPARAM(lpData));;
}

//p2p
void CRTMCallBack::onMessageReceivedFromPeer(const char *peerId, const IMessage *message) 
{
  PAG_SIGNAL_MESSAGEINSTANCERECEIVE lpData = new AG_SIGNAL_MESSAGEINSTANCERECEIVE;
  lpData->account = utf82gbk(peerId);
  lpData->uid = 0;
  lpData->msg = utf82gbk(message->getText());

  postMsg(WM_MessageInstantReceive, WPARAM(lpData));
}

// Inherited from |agora::rtm::IChannelEventHandler|
void CRTMCallBack::onJoinSuccess() 
{
  PAG_SIGNAL_CHANNELJOIN lpData = new AG_SIGNAL_CHANNELJOIN;
  lpData->channelID = utf82gbk(m_channeId.c_str());

  postMsg(WM_ChannelJoined, WPARAM(lpData));
}

void CRTMCallBack::onJoinFailure(JOIN_CHANNEL_ERR errorCode) 
{
  PAG_SIGNAL_CHANNELJOINFAILED lpData = new AG_SIGNAL_CHANNELJOINFAILED;
  lpData->channelID = utf82gbk(m_channeId);
  lpData->ecode = errorCode;

  postMsg(WM_ChannelJoinedFailed, WPARAM(lpData));
}

void CRTMCallBack::onLeave(LEAVE_CHANNEL_ERR errorCode) 
{
  PAG_SIGNAL_CHANNELLEAVE lpData = new AG_SIGNAL_CHANNELLEAVE;
  lpData->channelID = utf82gbk(m_channeId);
  lpData->ecode = errorCode;

  postMsg(WM_ChannelLeaved, WPARAM(lpData));
}

//in channel
void CRTMCallBack::onMessageReceived(const char *userId, const IMessage *message) 
{
  PAG_SIGNAL_MESSAGECHANNELRECEIVE lpData = new AG_SIGNAL_MESSAGECHANNELRECEIVE;
  lpData->account = utf82gbk(userId);
  lpData->channelID = utf82gbk(m_channeId);
  lpData->uid = 0;
  lpData->msg = utf82gbk(message->getText());

  postMsg(WM_MessageChannelReceive, WPARAM(lpData));
}

void CRTMCallBack::onSendMessageResult(long long messageId, CHANNEL_MESSAGE_ERR_CODE state) 
{
  PAG_SIGNAL_MESSAGESENDSUCCESS  lpData = new AG_SIGNAL_MESSAGESENDSUCCESS;
  lpData->messageID = utf82gbk(std::to_string(messageId));
  lpData->state = state;
  postMsg(WM_MessageSendSuccess, WPARAM(lpData));;
}

void CRTMCallBack::onMemberJoined(IChannelMember *member) 
{
}

void CRTMCallBack::onMemberLeft(IChannelMember *member) 
{
}

void CRTMCallBack::onGetMembers(IChannelMember **members, int userCount, GET_MEMBERS_ERR errorCode)
{
}

void CRTMCallBack::postMsg(UINT msg, WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL*/)
{
  ::PostMessage(m_MsgWnd, msg, wParam, lParam);
}
