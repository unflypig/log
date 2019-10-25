/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：main.c
*   创 建 者：zt
*   创建日期：2019年10月25日
*   描    述：
*
================================================================*/
#include "log.h"
int main(int argc, char* argv[]){
    char *name = "unflypig";
    int i = 0;
    log_init();
    LOG(INFO,"this is test message, i is [%d], name is [%s]", i++, name);
    LOG(DEBUG,"this is test message, i is [%d], name is [%s]", i++, name);
    LOG(ERROR,"this is test message, i is [%d], name is [%s]", i++, name);
    LOG(WARN,"this is test message, i is [%d], name is [%s]", i++, name);
    return 0;
}


