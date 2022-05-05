#include "pch.h"
#include "ExtendVideoFrameObserver.h"


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
bool CExtendVideoFrameObserver::onCaptureVideoFrame(VideoFrame & videoFrame)
{
	int bufSize = videoFrame.width * videoFrame.height * 3 / 2;
	int timestamp = GetTickCount();
	//read video capture buffer data and get timestamp copy to video Frame.
	if (CAgVideoBuffer::GetInstance()->readBuffer(m_lpBuffer, bufSize, timestamp)) {
		memcpy_s(m_videoBuffer.m_lpImageBuffer, bufSize, m_lpBuffer, bufSize);
		m_videoBuffer.timestamp = timestamp;
	}
	else
		OutputDebugString(L"readBuffer failed");
	m_lpY = m_videoBuffer.m_lpImageBuffer;
	m_lpU = m_videoBuffer.m_lpImageBuffer + videoFrame.height * videoFrame.width;
	m_lpV = m_videoBuffer.m_lpImageBuffer + 5 * videoFrame.height * videoFrame.width / 4;
	//copy yuv data to video frame.
	memcpy_s(videoFrame.yBuffer, videoFrame.height * videoFrame.width, m_lpY, videoFrame.height * videoFrame.width);
	videoFrame.yStride = videoFrame.width;
	memcpy_s(videoFrame.uBuffer, videoFrame.height * videoFrame.width / 4, m_lpU, videoFrame.height * videoFrame.width / 4);
	videoFrame.uStride = videoFrame.width / 2;
	memcpy_s(videoFrame.vBuffer, videoFrame.height * videoFrame.width / 4, m_lpV, videoFrame.height * videoFrame.width / 4);
	videoFrame.vStride = videoFrame.width / 2;
	//set video frame type.
	videoFrame.type = agora::media::base::VIDEO_PIXEL_I420;
	//set video rotation.
	videoFrame.rotation = 0;
	return true;
}

bool CExtendVideoFrameObserver::onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame)
{
	return false;
}