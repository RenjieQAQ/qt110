
#include "netFrame.h"

void frameWriter::command(uint8_t function, uint8_t type) {
	frame.cmd = (uint16_t)function * 256;
	frame.cmd += type;
	frame.msg_length = 0;
	send();
}
void frameWriter::cmdFix(uint8_t type) {
	frame.cmd = CMD_FIX*256;
	frame.cmd += type;
	frame.msg_length = 0;
	send();
}
