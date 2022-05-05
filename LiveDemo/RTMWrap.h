#ifndef __SINGLEWRAP_H__
#define __SINGLEWRAP_H__

//#include "pch.h"
#include "IAgoraRtmService.h"
#include "IAgoraRtmCallManager.h"
#include <string>
using namespace agora::rtm;
using namespace std;

class CRTMCallEventHandler :public IRtmCallEventHandler
{
	HWND m_MsgWnd;
public:
	void SetWnd(HWND wnd) { m_MsgWnd = wnd; };
	/**
 Callback to the caller: occurs when the callee receives the call invitation.

 @param localInvitation An ILocalCallInvitation object.
 */
	virtual void onLocalInvitationReceivedByPeer(ILocalCallInvitation *localInvitation);


	/**
	 Callback to the caller: occurs when the caller cancels a call invitation.

	 @param localInvitation An ILocalCallInvitation object.
	 */
	virtual void onLocalInvitationCanceled(ILocalCallInvitation *localInvitation);


	/**
	 Callback to the caller: occurs when the life cycle of the outgoing call invitation ends in failure.

	 @param localInvitation An ILocalCallInvitation object.
	 @param errorCode The error code. See #LOCAL_INVITATION_ERR_CODE.
	 */
	virtual void onLocalInvitationFailure(ILocalCallInvitation *localInvitation, LOCAL_INVITATION_ERR_CODE errorCode);


	/**
	 Callback to the caller: occurs when the callee accepts the call invitation.

	 @param localInvitation An ILocalCallInvitation object.
	 @param response The callee's response to the call invitation.
	 */
	virtual void onLocalInvitationAccepted(ILocalCallInvitation *localInvitation, const char *response);


	/**
	 Callback to the caller: occurs when the callee refuses the call invitation.

	 @param localInvitation An ILocalCallInvitation object.
	 @param response The callee's response to the call invitation.
	 */
	virtual void onLocalInvitationRefused(ILocalCallInvitation *localInvitation, const char *response);


	/**
	 Callback for the callee: occurs when the callee refuses a call invitation.

	 @param remoteInvitation An IRemoteCallInvitation object.
	 */
	virtual void onRemoteInvitationRefused(IRemoteCallInvitation *remoteInvitation);


	/**
	 Callback to the callee: occurs when the callee accepts a call invitation.

	 @param remoteInvitation An IRemoteCallInvitation object.
	 */
	virtual void onRemoteInvitationAccepted(IRemoteCallInvitation *remoteInvitation);


	/**
	 Callback to the callee: occurs when the callee receives a call invitation.

	 @param remoteInvitation An IRemoteCallInvitation object.
	 */
	virtual void onRemoteInvitationReceived(IRemoteCallInvitation *remoteInvitation);
	//{
	//	(IRemoteCallInvitation *)remoteInvitation;
	//}
	/**
	 Callback to the callee: occurs when the life cycle of the incoming call invitation ends in failure.

	 @param remoteInvitation An IRemoteCallInvitation object.
	 @param errorCode The error code. See #REMOTE_INVITATION_ERR_CODE.
	 */
	virtual void onRemoteInvitationFailure(IRemoteCallInvitation *remoteInvitation, REMOTE_INVITATION_ERR_CODE errorCode);


	/**
	 Callback to the callee: occurs when the caller cancels the call invitation.

	 @param remoteInvitation An IRemoteCallInvitation object.
	 */
	virtual void onRemoteInvitationCanceled(IRemoteCallInvitation *remoteInvitation);

};


class CRTMCallBack :public agora::rtm::IRtmServiceEventHandler,
  public agora::rtm::IChannelEventHandler {
public:
  CRTMCallBack(HWND wnd);
  ~CRTMCallBack();

  void setCallBackWnd(HWND wnd);
  void setJoinChannel(const std::string & channelId) {
    m_channeId = channelId;
  }

protected:
  // Inherited from |agora::rtm::IRtmServiceEventHandler|
  void onLoginSuccess() override;

  void onLoginFailure(LOGIN_ERR_CODE errorCode) override;

  void onLogout(LOGOUT_ERR_CODE errorCode) override;

  void onConnectionStateChanged(CONNECTION_STATE state, CONNECTION_CHANGE_REASON reason) override;

  void onSendMessageResult(long long messageId, PEER_MESSAGE_ERR_CODE errorCode) override;

  void onMessageReceivedFromPeer(const char *peerId, const IMessage *message) override;

  // Inherited from |agora::rtm::IChannelEventHandler|
  void onJoinSuccess() override;

  void onJoinFailure(JOIN_CHANNEL_ERR errorCode) override;

  void onLeave(LEAVE_CHANNEL_ERR errorCode) override;

  void onMessageReceived(const char *userId, const IMessage *message) override;

  void onSendMessageResult(long long messageId, CHANNEL_MESSAGE_ERR_CODE state) override;

  void onMemberJoined(IChannelMember *member) override;

  void onMemberLeft(IChannelMember *member) override;

  void onGetMembers(IChannelMember **members, int userCount, GET_MEMBERS_ERR errorCode) override;

private:
  inline void postMsg(UINT msg, WPARAM wParam = NULL, LPARAM lParam = NULL);

private:
  HWND m_MsgWnd;
  std::string m_channeId;
};


#endif