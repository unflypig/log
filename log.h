/*================================================================
*   Copyright (C) 2019 Sangfor Ltd. All rights reserved.
*
*   文件名称：log.h
*   创 建 者：zt
*   创建日期：2019年10月25日
*   描    述：
*
================================================================*/
#ifndef __LOG_H__
#define __LOG_H__
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define ON 1
#define OFF 0
#define LOG_CONF_FILE_PATH "/etc/conf.d/my_log.conf"
enum ENUM_LEVEL {DEBUG = 1, INFO = 2, ERROR = 3, WARN = 4};
//针对某一类别日志的打印开关,ON/OFF 打印/不打印

extern int LOG_DEBUG_SWITCH;
extern int LOG_INFO_SWITCH;
extern int LOG_ERROR_SWITCH;
extern int LOG_WARN_SWITCH;
extern int write_log_to_file;/*写入文件开关0/1 写入文件/不写入文件*/
extern unsigned long int log_limit_size;//日志文件最大限制,默认为10KB
extern char log_file_path[64];//日志文件默认存储路径
/*
 * 删除尺寸超过log_limit_size的日志文件
 *删除操作将删除日志文件前办部分，保留后半部分
 */
#define DEL_OUT_SIZE_FILE(path)do{\
    FILE *fp = fopen(path, "r");\
    if(fp != NULL) {\
        unsigned int line_num = 0;\
        unsigned int line_num_tmp = 0;\
        char *line_buff = (char *)malloc((sizeof(char))*1024);\
        char *all_buff = (char *)malloc(sizeof(char)*log_limit_size);\
        /*get file line num*/\
        while(fgets(line_buff, 128, fp) != NULL){\
            line_num_tmp++;\
        }\
        line_num = line_num_tmp;\
        line_num_tmp = 0;\
        rewind(fp);\
        while(fgets(line_buff, 128, fp) != NULL){\
            line_num_tmp++;\
            if(line_num_tmp > (line_num / 2)) {\
                /*printf("line[%d]:%s", line_num, line_buff);*/\
                strcat(all_buff, line_buff);\
            }\
        }\
        /*printf("all_buff is {%s}\n",all_buff);*/\
        fclose(fp);\
        FILE *fp_new = fopen(path, "w");\
        fwrite(all_buff, strlen(all_buff), 1, fp_new);\
        fclose(fp_new);\
        free(line_buff);\
        free(all_buff);\
    }else{\
        printf("open [%s] fail\n",path);\
    }\
}while(0)
#define LOG(level, format,...)do{\
    /*GET_LOG_CONF();*/\
    char log_pre[8] = {'\0'};\
    int print_log = OFF;\
    switch(level){\
        case DEBUG:\
            if(!LOG_DEBUG_SWITCH) {\
                break;\
            }\
            strncpy(log_pre, "DEBUG", 5);\
            print_log = ON;\
            break;\
        case INFO:\
            if(!LOG_INFO_SWITCH) {\
                break;\
            }\
            strncpy(log_pre, "INFO", 4);\
            print_log = ON;\
            break;\
        case ERROR:\
            if(!LOG_ERROR_SWITCH) {\
                break;\
            }\
            strncpy(log_pre, "ERROR", 5);\
            print_log = ON;\
            break;\
        case WARN:\
            if(!LOG_WARN_SWITCH) {\
                break;\
            }\
            strncpy(log_pre, "WARN", 4);\
            print_log = ON;\
            break;\
        default:\
            printf("unknow level\n");\
            break;\
    }\
    if(print_log){\
        static unsigned int long log_file_lines = 0;\
        static char time_strap[64] = {'\0'};\
        time_t timep;\
        struct tm *p;\
        unsigned long file_size = -1;\
        struct stat log_file_stat;\
        if(stat(log_file_path, &log_file_stat) == 0) {\
            file_size = log_file_stat.st_size;\
            if(file_size > log_limit_size) {\
                printf("log current size[%lu] is more than [%lu]\n", file_size, log_limit_size);\
                DEL_OUT_SIZE_FILE(log_file_path);\
            }else{\
                /*printf("log current size[%lu] is not more than [%lu]\n", file_size, log_limit_size);*/\
            }\
        }else{\
            /*printf("get stat of [%s] fail\n", log_file_path);*/\
        }\
        time(&timep);\
        p=localtime(&timep);\
        sprintf(time_strap, "[%4d-%02d-%02d %02d:%02d:%02d]",(1900+p->tm_year), (1+p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);\
        printf("%s [%-5s]["__FILE__"->%s(%d)]:"format "\n",time_strap, log_pre, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
        if(write_log_to_file){\
            FILE *log_p;\
            log_p = fopen(log_file_path, "a+");\
            if(log_p) {\
                fprintf(log_p, "%s [%-5s]["__FILE__"->%s(%d)]:"format "\n",time_strap, log_pre, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
                fclose(log_p);\
            }\
        }\
    }\
}while(0)
/*
 * 日志配置文件格式为 key=value
 *LOG_PATH=/tmp/my.log(日志路径)
 *WRITE_TO_FILE=ON/OFF(是否将日志写入文件ON/OFF 写入/不写入)
 *LOG_LIMIT_SIZE_M=1(日志文件大小限制(以M为单位,若日志文件超过该大小，将删除前半部分日志，保留最新日志))
 *LOG_DEBUG=ON/OFF(打印调试日志 ON/OFF 打印/不打印)
 */
    int log_init();
#endif
