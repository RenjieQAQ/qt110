#include "myvlc.h"

BOOL lock = FALSE;
static int ch_id=0;


int cVedio::getID()
{
	return ++ch_id;
}
int getID()
{
	return ch_id;
}

void saveImage(Mat& img,int id, int iFrame)
{
	char szFilename[32];
	sprintf_s(szFilename, "img/ch%dFrame%d.jpg", id,iFrame);
	imwrite(szFilename, img);
}
void buffer2RBG(uint8_t * buff, Mat& img)
{
	int width = img.cols;
	int height = img.rows;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			img.at<Vec3b>(i, j)[0] = *(buff + i*width * 3 + j * 3);
			img.at<Vec3b>(i, j)[1] = *(buff + i*width * 3 + j * 3 + 1);
			img.at<Vec3b>(i, j)[2] = *(buff + i*width * 3 + j * 3 + 2);
		}
	}
}
void buffer2img(Mat&img, uint8_t *buff)
{
	int width = img.cols;
	int height = img.rows;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			img.at<uint8_t>(i, j) = *(buff + i*width + j);
		}
	}
}
void showImg(Mat& img, QLabel * pLabel, int showMethod = 0)
{
	int w, h;
	Mat tmp;
	if (showMethod)//根据图片大小显示
	{
		w = img.cols;
		h = img.rows;
		pLabel->resize(w, h);
		tmp = img;
	}
	else //根据控件大小显示
	{
		resize(img, tmp, Size(pLabel->width(), pLabel->height()), 0, 0, CV_INTER_LINEAR);
	}
	cv::cvtColor(tmp, tmp, CV_RGB2RGBA);
	QImage image = QImage((tmp.data),
		tmp.cols, tmp.rows, QImage::Format_RGB32);
	pLabel->setPixmap(QPixmap::fromImage(image));
	pLabel->show();
}
void *libvlc_video_lock_cb_callback(void *opaque, void **planes)
{
//	Lock();
	cVedio * v = (cVedio *)opaque;
	*planes = (uint8_t *)v->buffer;
	return NULL;
}
void libvlc_video_unlock_cb_callback(void *opaque, void *picture,
	void *const *planes)
{
//	lock = FALSE;
	//*planes = (uint8_t *)opaque;
	//cout << "unlock" << endl;
}
void libvlc_video_display_cb_callback(void *opaque, void *picture)
{
	Lock();
		cVedio * v = (cVedio *)opaque;
//		Mat img(v->height, v->width, CV_8UC3);
	//	Mat *img = v->pQtWidget->img_r;
		buffer2RBG(v->buffer, *(v->img));

		if ((v->pQtWidget->pPlayBar->playFlag == 1))
		{
			//if (v->img->empty()) 
			showImg(*(v->img), v->pLabel);
			//if ((v->cnt % 25 == 0) && (v->pQtWidget->pPlayBar->saveFlag == 1))
			if ( (v->pQtWidget->pPlayBar->saveFlag == 1))
			{
				if (v->iFrame == 1000)v->iFrame = 0;
				saveImage(*(v->img), v->id, v->iFrame++);
			}
			v->cnt++;
	//		_sleep(1000 / 25);

		}
		//Mat tmp;
		//cv::cvtColor(*(v->img), tmp, CV_RGB2RGBA);
		//*(v->qImg) = QImage((tmp.data),
		//	tmp.cols, tmp.rows, QImage::Format_RGB32);
		/*if ((v->cnt % 25 == 0))
			saveImage(*img,v->id, v->iFrame++);
		v->cnt++;*/

	/*	imshow(v->url, *img);
		if(waitKey(1)>=0)v->isEnd=1;*/
	DisLock();
}

BOOL IsLock()
{
	return lock;
}
void Lock()
{
	lock = TRUE;
}
void DisLock()
{
	lock = FALSE;
}

/**
cVedio* vedio = (cVedio*)Param;
*/
void* getVedio(void* Param)
{
	cVedio* vedio = (cVedio*)Param;
	libvlc_instance_t * inst;
	libvlc_media_player_t *mp;
	libvlc_media_t *m;
	libvlc_media_track_t * track;

	libvlc_time_t length;
	int wait_time = 2000;

	while (vedio->pQtWidget->isStoped());

	inst = libvlc_new(0, NULL);
	m = libvlc_media_new_location(inst, vedio->url);
	mp = libvlc_media_player_new_from_media(m);
	libvlc_media_release(m);

	/*libvlc_video_set_callbacks(mp, libvlc_video_lock_cb_callback, NULL, NULL, vedio);
	libvlc_video_set_format(mp, "RV24", 704, 480, 704 * 3);*/
	libvlc_media_player_play(mp);
	Sleep(wait_time);
	length = libvlc_media_player_get_length(mp);
	vedio->width = libvlc_video_get_width(mp);
	vedio->height = libvlc_video_get_height(mp);
//	printf("Stream Duration: %ds\n", length / 1000);
//	printf("Resolution: %d x %d\n", vedio->width, vedio->height);
//	QMessageBox::information(vedio->pQtWidget, ("close"), ("close!!"));
	vedio->img=new Mat(vedio->height, vedio->width, CV_8UC3);
	vedio->qImg = new QImage(vedio->width, vedio->height, QImage::Format_RGB32);
	if (vedio->width != 0)
	{
		//QMessageBox::information(vedio->pQtWidget, ("close"), ("close!!"));
	//	MyThread show1(qtPlay, vedio);
		libvlc_media_player_stop(mp);
		libvlc_video_set_callbacks(mp, libvlc_video_lock_cb_callback, libvlc_video_unlock_cb_callback,
			libvlc_video_display_cb_callback, vedio);
		libvlc_video_set_format(mp, "RV24", vedio->width, vedio->height, vedio->width * 3);
		libvlc_media_player_play(mp);
	}
	while (1);
	getchar();
	libvlc_media_player_stop(mp);
	libvlc_media_player_release(mp);
	libvlc_release(inst);
	//	pthread_attr_destroy(&attr);
	return NULL;
}


