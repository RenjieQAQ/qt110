#pragma once

//[00] :55 aa 55 aa 01 00 8e 00 00 00
//[01] : 31 00 14 00 0a 00 07 00 1a 00
//[02] : 00 00 01 00 2d 00 53 00 4e 00
//[03] : 6f 00 01 00 00 00 00 00 01 00
//[04] : 02 00 03 00 21 4a 00 18 04 44
//[05] : 00 00 00 00 00 00 43 00 4e 00
//[06] : 59 00 00 00 02 00 64 00 0a 00
//[07] : 4f 00 4b 00 31 00 32 00 33 00
//[08] : 34 00 35 00 36 00 37 00 38 00
//[09] : 00 00 00 00 48 00 65 00 6e 00
//[10] : 67 00 51 00 69 00 61 00 6e 00
//[11] : 67 00 30 00 30 00 37 00 00 00
//[12] : 00 00 00 00 00 00 00 00 00 00
//[13] : 00 00 00 00 00 00 00 00 00 00
//[14] : 00 00 00 00

#include <string.h>
#include <assert.h> 
#include "fsnMsg.h"
#include "netFrame.h"

#include <QTNetwork/Qtnetwork>
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;



class decodeFrame
{
	/*flag
	0：没有帧头
	1：检测到帧头
	2：检测到长度和cmd
	3：帧尾完整
	*/

	/*解析状态*/
	int flag;
	int index;
	uint32_t restNum;

	/*输入信息*/
	unsigned char * buf;
	int offset;//输入数据的偏移
	int length;

	/*解析结果*/
	netFrame frame;

	//TCP_FSN_Msg msg_b;
	//TCP_FSN_Msg_Sml msg_s;
	//DebugMsg debugMsg;
	//unsigned char *save_data;


public:
	decodeFrame() {
		flag = 0;
		index = 0;
		offset = 0;
		length = 0;
		buf = NULL;
	}
	~decodeFrame() {

	}
	inline void frameReset() {
		index = 0;
		flag = 0;
	}
	void caseGetLength(unsigned char ch);
	void caseHead(unsigned char ch);
	bool checkEnd();
	void input(unsigned char ch) {
		switch (flag)
		{
		case 0:
			caseHead(ch);
			break;
		case 1:
			caseGetLength(ch);
			break;
		case 2:

			break;
		case 3:
			break;
		default:
			break;
		}
	}
	int inputs(char *arr, int length) {
		buf = (unsigned char *)arr;
		this->length = length;
		offset = 0;
		return 0;
	}
	int decode(){
		//unsigned char *s = (unsigned char *)arr;
		for (int i = offset;i < length;i++) {
			if (flag < 2)
				input(buf[i]);
			else{
				if ((length - i) >= restNum) {
					memcpy((unsigned char *)frame.data+index-12, buf + i, restNum);
					index += restNum;
					i += restNum;
					if (checkEnd()) {
						frameReset();
						offset = i;
						return 0;//找到正常帧，退出
					}
				/*	int len = length - i - validNum;
					save_data = new unsigned char[len];
					memcpy(pmsg, s + i+ validNum, len);*/
					break;
				}
				else {//将剩余缓存全部纳入包中
					memcpy((unsigned char *)frame.data + index - 12, buf + i, length - i);
					index += length - i;
					restNum = restNum - (length - i);
					break;
				}
			}
		}
		
		offset = length;
		return -1;
	}
	netFrame & getFrame() {
		return frame;
	}
	void clear() {
		flag = 0;
		index = 0;

		length = 0;
		offset = 0;
		buf = NULL;

	
		restNum = 0;
	}
	bool isEmpty() {
		if ( offset== length )
			return true;
		else
			return false;
	}
};

/*


*/


