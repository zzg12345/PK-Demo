#include "pch.h"
#include "VideoFrameObserver.h"

//see the header file for details
bool CGrayVideoProcFrameObserver::onCaptureVideoFrame(VideoFrame & videoFrame)
{
	int nSize = videoFrame.height * videoFrame.width;
	//set UV to 128 to mask color information
	if (0)
	{
		if (fpLocal != nullptr)
		{
			int ysize = videoFrame.yStride * videoFrame.height;
			int usize = videoFrame.uStride * videoFrame.height / 2;
			int vsize = videoFrame.vStride * videoFrame.height / 2;
			unsigned char *temp = (unsigned char *)malloc(ysize + usize + vsize);

			memcpy(temp, videoFrame.yBuffer, ysize);
			memcpy(temp + ysize, videoFrame.uBuffer, usize);
			memcpy(temp + ysize + usize, videoFrame.vBuffer, vsize);

			fwrite(temp, 1, nSize, fpLocal);
			free(temp);
		}
	}

	videoFrame.rotation = 180;
	memset(videoFrame.uBuffer, 200, nSize / 4);
	memset(videoFrame.vBuffer, 128, nSize / 4);
	return true;
}

bool CGrayVideoProcFrameObserver::onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame)
{
	if (0)
	{
		int nSize = videoFrame.height * videoFrame.width;
		if (fpRemote != nullptr)
		{
			int ysize = videoFrame.yStride * videoFrame.height;
			int usize = videoFrame.uStride * videoFrame.height / 2;
			int vsize = videoFrame.vStride * videoFrame.height / 2;
			unsigned char *temp = (unsigned char *)malloc(ysize + usize + vsize);

			memcpy(temp, videoFrame.yBuffer, ysize);
			memcpy(temp + ysize, videoFrame.uBuffer, usize);
			memcpy(temp + ysize + usize, videoFrame.vBuffer, vsize);

			fwrite(temp, 1, nSize, fpRemote);
			free(temp);
		}
	}
	videoFrame.rotation = 90;
	return true;
}

void CGrayVideoProcFrameObserver::InitFileObjet()
{
	if (fpLocal != nullptr)
	{
		return;
	}
	fpLocal = fopen("local_420.yuv", "wb+");
	if (fpLocal == nullptr)
	{
		OutputDebugStringW(L"fopen fpLocal error");
	}
	fpRemote = fopen("remote_420.yuv", "wb");
	if (fpRemote == nullptr)
	{
		OutputDebugStringW(L"fopen fpRemote error");
	}
}

void CGrayVideoProcFrameObserver::CloseFileObjet()
{
	if (fpLocal != nullptr)
	{
		fclose(fpLocal);
		fpLocal = nullptr;
	}
	if (fpRemote != nullptr)
	{
		fclose(fpRemote);
		fpRemote = nullptr;
	}
}

//see the header file for details
bool CAverageFilterVideoProcFrameObserver::onCaptureVideoFrame(VideoFrame & videoFrame)
{
	static int step = 1;
	static bool flag = true;
	if (flag)
	{
		step += 2;
	}
	else {
		step -= 2;
	}
	if (step >= 151)
	{
		flag = false;
		step -= 4;
	}
	else if (step <= 0) {
		flag = true;
		step += 4;
	}
	AverageFiltering((unsigned char *)videoFrame.yBuffer, videoFrame.width, videoFrame.height, step);
	AverageFiltering((unsigned char *)videoFrame.uBuffer, videoFrame.width / 2, videoFrame.height / 2, step);
	AverageFiltering((unsigned char *)videoFrame.vBuffer, videoFrame.width / 2, videoFrame.height / 2, step);
	return true;
}

//see the header file for details
bool CAverageFilterVideoProcFrameObserver::onRenderVideoFrame(const char* channelId, rtc::uid_t remoteUid, VideoFrame& videoFrame)
{
	return true;
}


static inline int countSize(int row, int col, int width, int height, int r) {
	int x, y;
	if (row + r >= height)
		x = r * 2 + 1 - (row + r - height + 1);
	else if (row < r)
		x = r + row + 1;
	else
		x = r * 2 + 1;
	if (col + r >= width)
		y = r * 2 + 1 - (col + r - width + 1);
	else if (col < r)
		y = r + col + 1;
	else
		y = r * 2 + 1;
	return x * y;
}
int dataBuffers[1920][1080][2];
//average filtering algorithm
void CAverageFilterVideoProcFrameObserver::AverageFiltering(unsigned char * data, int width, int height, int step)
{
	memset(dataBuffers, 0, sizeof(dataBuffers));
	if (step > width || step > height)
		return;
	if (step == 1)return;
	int halfstep = step / 2;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j <= halfstep; j++)
		{
			dataBuffers[i][0][0] += data[i*width + j];
		}
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j <= halfstep; j++)
		{
			dataBuffers[0][i][1] += data[j*width + i];
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 1; j < width; j++)
		{
			if (j <= halfstep)
			{
				dataBuffers[i][j][0] = dataBuffers[i][j - 1][0] + data[i*width + j + halfstep];
			}
			else {
				dataBuffers[i][j][0] = dataBuffers[i][j - 1][0] - data[i*width + j - halfstep - 1] + (j + halfstep < width ? data[i*width + j + halfstep] : 0);
			}
		}
	}

	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i <= halfstep)
			{
				dataBuffers[i][j][1] = dataBuffers[i - 1][j][1] + data[(i + halfstep)*width + j];
			}
			else {
				dataBuffers[i][j][1] = dataBuffers[i - 1][j][1] - data[(i - halfstep - 1)*width + j] + (i + halfstep < height ? data[(i + halfstep)*width + j] : 0);
			}
		}
	}

	int ans = 0;
	int prev = 0;
	for (int i = 0; i <= halfstep; i++)
	{
		ans += dataBuffers[i][0][0];
	}
	prev = ans;
	data[0] = ans / ((halfstep + 1)*(halfstep + 1));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 && j == 0)continue;
			if (j == 0)
			{
				if (i > halfstep && i < height - halfstep)
				{
					ans = prev +
						dataBuffers[i + halfstep][0][0] -
						dataBuffers[i - halfstep - 1][0][0];
					prev = ans;
					data[i*width + j] = ans / countSize(i, j, width, height, halfstep);
				}
				else if (i <= halfstep)
				{
					ans = prev +
						dataBuffers[i + halfstep][0][0];
					prev = ans;
					data[i*width + j] = ans / countSize(i, j, width, height, halfstep);
				}
				else {
					ans = prev -
						dataBuffers[i - halfstep - 1][0][0];
					prev = ans;
					data[i*width + j] = ans / countSize(i, j, width, height, halfstep);
				}
			}
			else if (j + halfstep >= width) {
				ans -= dataBuffers[i][j - halfstep - 1][1];
				data[i*width + j] = ans / countSize(i, j, width, height, halfstep);
			}
			else if (j < halfstep) {
				ans += dataBuffers[i][j + halfstep][1];
				data[i*width + j] = ans / countSize(i, j, width, height, halfstep);
			}
			else
			{
				ans += dataBuffers[i][j + halfstep][1] - dataBuffers[i][j - halfstep - 1][1];
				data[i*width + j] = ans / countSize(i, j, width, height, halfstep);
			}
		}
	}
}