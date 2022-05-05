#pragma once
#include "pch.h"

// Video gray scale processing Frame Observer
class CGrayVideoProcFrameObserver :
	public agora::media::IVideoFrameObserver
{
private:
	FILE *fpLocal;
	FILE *fpRemote;
public:
	void InitFileObjet();
	void CloseFileObjet();
	virtual ~CGrayVideoProcFrameObserver() {  }
	/**
	 * Occurs each time the SDK receives a video frame captured by the local camera.
	 *
	 * After you successfully register the video frame observer, the SDK triggers this callback each time
	 * a video frame is received. In this callback, you can get the video data captured by the local
	 * camera. You can then pre-process the data according to your scenarios.
	 *
	 * After pre-processing, you can send the processed video data back to the SDK by setting the
	 * `videoFrame` parameter in this callback.
	 *
	 * @param videoFrame A pointer to the video frame: VideoFrame
	 * @return Determines whether to ignore the current video frame if the pre-processing fails:
	 * - true: Do not ignore.
	 * - false: Ignore, in which case this method does not sent the current video frame to the SDK.
	*/
	virtual bool onCaptureVideoFrame(VideoFrame& videoFrame)override;

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

	virtual bool onPreEncodeScreenVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryPreEncodeCameraVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onPreEncodeVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryPreEncodeScreenVideoFrame(VideoFrame& videoFrame)override { return true; }
};


// Video gray scale processing Frame Observer
class CAverageFilterVideoProcFrameObserver :
	public agora::media::IVideoFrameObserver
{
private:
	unsigned char * m_buffer = new unsigned char[1920 * 1280 * 3];
	unsigned char * m_height = new unsigned char[1920];
public:

	/**
	 * Occurs each time the SDK receives a video frame captured by the local camera.
	 *
	 * After you successfully register the video frame observer, the SDK triggers this callback each time
	 * a video frame is received. In this callback, you can get the video data captured by the local
	 * camera. You can then pre-process the data according to your scenarios.
	 *
	 * After pre-processing, you can send the processed video data back to the SDK by setting the
	 * `videoFrame` parameter in this callback.
	 *
	 * @param videoFrame A pointer to the video frame: VideoFrame
	 * @return Determines whether to ignore the current video frame if the pre-processing fails:
	 * - true: Do not ignore.
	 * - false: Ignore, in which case this method does not sent the current video frame to the SDK.
	*/
	virtual bool onCaptureVideoFrame(VideoFrame& videoFrame)override;
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
	void AverageFiltering(unsigned char * data, int width, int height, int step);


	virtual bool onScreenCaptureVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryCameraCaptureVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onTranscodedVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryScreenCaptureVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onMediaPlayerVideoFrame(VideoFrame& videoFrame, int mediaPlayerId) override { return true; }

	virtual bool onPreEncodeScreenVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryPreEncodeCameraVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onPreEncodeVideoFrame(VideoFrame& videoFrame)override { return true; }
	virtual bool onSecondaryPreEncodeScreenVideoFrame(VideoFrame& videoFrame)override { return true; }
};