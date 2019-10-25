# log
## 嵌入式软件开发中比较实用的日志打印功能
### 功能：

1.打印时间戳、标签、文件名、函数名、行号、信息

2.日志可以同时输出到文件

3.当日志超过预设大小时自动删除日志文件前半部分，保留后半部分

4.日志路径、日志大小、日志开关、是否写入文件等都可以通过配置文件配置


### 效果预览
```
[2019-10-25 17:27:52] [INFO ][main.c->main(15)]:this is test message, i is [0], name is [unflypig]
[2019-10-25 17:27:52] [DEBUG][main.c->main(16)]:this is test message, i is [2], name is [unflypig]
[2019-10-25 17:27:52] [ERROR][main.c->main(17)]:this is test message, i is [4], name is [unflypig]
[2019-10-25 17:27:52] [WARN ][main.c->main(18)]:this is test message, i is [6], name is [unflypig]
```
### 配置文件格式（默认路径为/etc/conf.d/my_log.conf）

```
#是否同步写入到文件中ON/OFF 是/否
WRITE_TO_FILE=ON
#日志文件最大限制（单位为MB）
LOG_LIMIT_SIZE_M=1
#DEBUG级别的日志打印开关ON/OFF 打印/不打印
LOG_DEBUG_SWITCH=ON
```
