#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <iostream>
#include<cstring>
struct message
{
 long msgtype;
 char buffer[80] = {0};
};

int main()
{
//создание файла в который будем писать
int file = open("message.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
int message = open("temp.tmp", O_CREAT | O_TRUNC, 0666);
close(message);
//создание очереди
key_t queue_key = ftok("temp.tmp", 1);
std::cout << "Key " << queue_key << std::endl;
int msgq = msgget(queue_key, IPC_CREAT | 0666);
if(msgq == -1)
{
 std::cout << "ошибка создания очереди\n";
	return -1;
}
//создания буфера
struct message msg;
bzero(&msg, sizeof(msg));
//ожидания сообщения
while(true)
{
int r = msgrcv(msgq, &msg, sizeof(msg), 0, 0);
std::cout << r << " " << errno <<" " << EINVAL << std::endl;
if(strlen(msg.buffer) > 0)
{
std::cout << msg.buffer << std::endl;
break;
}
}
close(file);
return 0;
}
