#pragma once
#include "pch.h"
#include "DirectShow/AgVideoBuffer.h"
#include "DirectShow/AGDShowVideoCapture.h"

typedef struct _VIDEO_BUFFER {
	BYTE m_lpImageBuffer[VIDEO_BUF_SIZE];
	int  timestamp;
}VIDEO_BUFFER, *PVIDEO_BUFFER;

class CExtendVideoFrameObserver :
	public agora::media::IVideoFrameObserver
{
public:
	CExtendVideoFrameObserver() { m_lpBuffer = new BYTE[VIDEO_BUF_SIZE]; }
	virtual ~CExtendVideoFrameObserver() { if (m_lpBuffer)delete[]m_lpBuffer; }
	/*
		Obtain video data from the local camera.After successfully registering
		a video data observer, the SDK triggers this callback when each video
		frame is captured. You can retrieve the video data from the local camera
		in the callback, and then pre-process the video data according to the needs
		of the scene.After the preprocessing is done, you can send the processed
		video data back to the SDK in this callback.
		annotations:
		If the video data type you get is RGBA, Agora does not support sending the
		processed RGBA data back to the SDK through this callback.
		parameter:
		videoFrame :VideoFramedata, see VideoFrame for more details
		return If the video pre-processing fails,whether to ignore the video frame:
		True: No ignore.
		False: Ignored, the frame data is not sent back to the SDK.
	*/
	virtual bool onCaptureVideoFrame(VideoFrame& videoFrame) override;
	/**
	 * Occurs each time the SDK receives a video frame sent by the remote user.
	 *
	 * After you successfully register the video frame observer, the SDK triggers this callback each time a
	 * video frame is received. In this callback, you can get the video data sent by the remote user. You
	 * can then post-process the data according to your scenarios.
	 *
	 * After post-processing, you can send the processed data back to the SDK by setting the `videoFrame`
	 * parameter in this callback.
	 *
	 * @param uid ID of the remote user who sends the current video frame.
	 * @param connectionId ID of the connection.
	 * @param videoFrame A pointer to the video frame: VideoFrame
	 * @return Determines whether to ignore the current video frame if the post-processing fails:
	 * - true: Do not ignore.
	 * - false: Ignore, in which case this method does not sent the current video frame to the SDK.
	 */
	virtual bool onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame)override;

	virtual bool onScreenCaptureVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryCameraCaptureVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onTranscodedVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryScreenCaptureVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId) override { return true; }
private:
	LPBYTE				m_lpImageBuffer;
	LPBYTE				m_lpY;
	LPBYTE				m_lpU;
	LPBYTE				m_lpV;
	VIDEO_BUFFER		m_videoBuffer;
	BYTE				* m_lpBuffer;
};