/*================================================================
 *   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
 *
 *   文件名称：log.c
 *   创 建 者：zt
 *   创建日期：2019年10月19日
 *   描    述：
 *
 ================================================================*/
#include "log.h"
int LOG_DEBUG_SWITCH = ON;
int LOG_INFO_SWITCH = ON;
int LOG_ERROR_SWITCH = ON;
int LOG_WARN_SWITCH = ON;
int write_log_to_file  = ON;/*写入文件开关0/1 写入文件/不写入文件*/
unsigned long int log_limit_size  = 1024 * 10;//日志文件最大限制,默认为10KB
char log_file_path[64] = "/tmp/my.log";//日志文件默认存储路径
/*
 * 日志配置文件格式为 key=value
 *LOG_PATH=/tmp/my.log(日志路径)
 *WRITE_TO_FILE=ON/OFF(是否将日志写入文件ON/OFF 写入/不写入)
 *LOG_LIMIT_SIZE_M=1(日志文件大小限制(以M为单位,若日志文件超过该大小，将删除前半部分日志，保留最新日志))
 *LOG_DEBUG=ON/OFF(打印调试日志 ON/OFF 打印/不打印)
 */
int log_init(){
    FILE *log_conf_file_p = fopen(LOG_CONF_FILE_PATH, "r");
    //读取日志配置文件，若该文件不存在则按默认参数配置
    if(log_conf_file_p != NULL) {
        char line_buff[64] = {'\0'};
        while(fgets(line_buff, 64, log_conf_file_p)){
            /*printf(" line is [%s]\n", line_buff);*/
            char *sep_symble = "=";
            char *p = strdup(line_buff);
            char *key;
            key = strsep(&p, sep_symble);
            /*strncpy(key, key_p, sizeof(key));*/
            /*printf(" key is [%s]\n", key);*/
            char *value = strdup(p);
            /*printf(" value is [%s]\n", value);*/
            if(strlen(key) > 0 && strlen(value) > 0) {
                if(!strncmp(key, "LOG_PATH", 8)) {
                    strncpy(log_file_path, value, sizeof(value));
                }else if(!strncmp(key, "WRITE_TO_FILE", 13)){
                    if(!strncmp(value, "ON", 2)) {
                        write_log_to_file = 1;
                    }else{
                        /*printf("WRITE_TO_FILE flag is not on [%s]\n", value);*/
                    }
                }else if(!strncmp(key, "LOG_LIMIT_SIZE_M", 16)){
                    if(atoi(value) >= 1) {
                        log_limit_size = 1024 * 1024 * atoi(value);
                    }
                }else if(!strncmp(key, "LOG_DEBUG_SWITCH", 16)){
                    if(!strncmp(value, "ON", 2)) {
                        LOG_DEBUG_SWITCH = ON;
                    }else if(!strncmp(value, "OFF", 3)){
                        LOG_DEBUG_SWITCH = OFF;
                    }
                    //printf("LOG_DEBUG_SWITCH = [%d]\n", LOG_DEBUG_SWITCH);
                }
            }
        }
        fclose(log_conf_file_p);
    }
}

