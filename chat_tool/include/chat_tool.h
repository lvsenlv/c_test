/*************************************************************************
	> File Name: chat_tool.h
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 16?47分09秒
 ************************************************************************/

#ifndef __CHAT_TOOL_H
#define __CHAT_TOOL_H

#include "common.h"

#define MESSAGE_FILE                        "/root/.message_file"
#define TEMP_MESSAGE_FILE                   "/root/.temp_message_file"
#define BUF_SIZE                            1024

void *receive_message(void *arg);
void *send_message(void *arg);



/*************************************************************************
                            about window
 ************************************************************************/

#include <ncurses.h>

#define OUTPUT_START_Y                      0
#define OUTPUT_START_X                      0
#define OUTPUT_END_Y                        (LINES - OUTPUT_START_Y - 1)
#define OUTPUT_END_X                        (COLS  - OUTPUT_START_X - 1)

#define INPUT_BOX_LINES                     (LINES/5)
#define INPUT_BOX_START_Y                   (OUTPUT_END_Y - INPUT_BOX_LINES)
#define INPUT_BOX_START_X                   (OUTPUT_START_X + 1)
#define INPUT_START_Y                       1
#define INPUT_START_X                       1

void draw_std_screen(void);
void draw_input_box(void);

#endif

