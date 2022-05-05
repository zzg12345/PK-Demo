// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"
#include "CConfig.h"
#include <IAgoraRtcEngine.h>
#include <IAgoraMediaEngine.h>
#include <convert.h>
#include <string>
#include <atlconv.h>
#include "AGVideoWnd.h"
#include "RTMStruct.h"


#pragma comment(lib, "agora_rtc_sdk.dll.lib")
#pragma comment(lib, "libagora_segmentation_extension.dll.lib")
//#pragma comment(lib, "libagora_video_process.dll.lib")
#pragma comment(lib, "libagora-ffmpeg.dll.lib")


using namespace std;
using namespace agora;
using namespace agora::rtc;
using namespace agora::media;
//using namespace SingleDesc;


#define APP_ID     "<enter your agora app id>"
#define APP_TOKEN  "" 
#define PK_CHANNLE "pk123"

#define WM_MSGID(code) (WM_USER+0x200+code)
//Agora Event Handler Message and structure

#define EID_JOINCHANNEL_SUCCESS			0x00000001
#define EID_LEAVE_CHANNEL				0x00000002
#define EID_USER_JOINED					0x00000003
#define EID_USER_OFFLINE				0x00000004

#define EID_INJECT_STATUS				0x00000005
#define EID_RTMP_STREAM_STATE_CHANGED	0x00000006
#define EID_REMOTE_VIDEO_STATE_CHANGED	0x00000007
#define RECV_METADATA_MSG				0x00000008
#define MEIDAPLAYER_STATE_CHANGED		0x00000009
#define MEIDAPLAYER_POSTION_CHANGED		0x0000000A
#define EID_LOCAL_VIDEO_STATE_CHANGED				0x0000000B
#define EID_LASTMILE_QUAILTY						0x0000000C
#define EID_LASTMILE_PROBE_RESULT					0x0000000D
#define EID_AUDIO_VOLUME_INDICATION					0x0000000E
#define EID_AUDIO_ACTIVE_SPEAKER					0x0000000F
#define EID_RTC_STATS								0x00000010
#define EID_REMOTE_AUDIO_STATS						0x00000011
#define EID_REMOTE_VIDEO_STATS						0x00000012
#define EID_LOCAL_VIDEO_STATS						0x00000013
#define EID_CHANNEL_MEDIA_RELAY_STATE_CHNAGENED		0x00000014
#define EID_CHANNEL_MEDIA_RELAY_EVENT		 		0x00000015
#define mediaPLAYER_STATE_CHANGED					0x00000016
#define mediaPLAYER_POSTION_CHANGED					0x00000017
#define EID_REMOTE_AUDIO_MIXING_STATE_CHANED	    0x00000018
#define EID_REMOTE_CHANNEL_MDIA_REPLAY	            0x00000019
#define EID_CHANNEL_REPLAY_STATE_CHANGED	        0x00000020
#define mediaPLAYER_EVENT					        0x00000021
#define EID_NETWORK_QUALITY                         0x00000022

#define EID_LOCAL_AUDIO_STATS                        0x00000024
#define EID_LOCAL_AUDIO_STATE_CHANED                0x00000025
#define EID_REMOTE_AUDIO_STATE_CHANGED               0x00000027

#define EID_CHANNEL_WARN				0x0000000B
#define EID_CHANNEL_ERROR				0x0000000B
#define EID_CHANNEL_REJOIN_CHANENL		0x0000000B
#define EID_CHANNEL_WARN				0x0000000B

typedef struct _tagRtmpStreamStateChanged {
	char* url;
	int state;
	int error;
}RtmpStreamStreamStateChanged, *PRtmpStreamStreamStateChanged;

typedef struct _tagVideoStateStateChanged {
	agora::rtc::uid_t uid;
	agora::rtc::REMOTE_VIDEO_STATE   state;
	agora::rtc::REMOTE_VIDEO_STATE_REASON reason;
}VideoStateStateChanged, *PVideoStateStateChanged;

typedef struct _tagAudioMixingState {
	int state;
	int error;

}AudioMixingState, *PAudioMixingState;
typedef struct _tagNetworkQuality {
	uid_t uid;
	int txQuality;
	int rxQuality;
}NetworkQuality, *PNetworkQuality;

typedef struct _tagRemoteAudioState {
	uid_t uid;
	REMOTE_AUDIO_STATE state;
	REMOTE_AUDIO_STATE_REASON reason;
	int elapsed;
}RemoteAudioState, *PRemoteAudioState;

typedef struct _tagRemoteVideoState {
	uid_t uid;
	REMOTE_VIDEO_STATE state;
	REMOTE_VIDEO_STATE_REASON reason;
	int elapsed;
}RemoteVideoState, *PRemoteVideoState;
#endif //PCH_H
