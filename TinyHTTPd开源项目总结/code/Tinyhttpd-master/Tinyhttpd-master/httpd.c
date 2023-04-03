/* J. David's webserver */
/* This is a simple webserver.
 * Created November 1999 by J. David Blackstone.
 * CSE 4344 (Network concepts), Prof. Zeigler
 * University of Texas at Arlington
 */
 /* This program compiles for Sparc Solaris 2.6.
  * To compile for Linux:
  *  1) Comment out the #include <pthread.h> line.
  *  2) Comment out the line that defines the variable newthread.
  *  3) Comment out the two lines that run pthread_create().
  *  4) Uncomment the line that runs accept_request().
  *  5) Remove -lsocket from the Makefile.
  */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>

#define ISspace(x) isspace((int)(x))

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
#define STDIN   0
#define STDOUT  1
#define STDERR  2

void accept_request(void*);
void bad_request(int);
void cat(int, FILE*);
void cannot_execute(int);
void error_die(const char*);
void execute_cgi(int, const char*, const char*, const char*);
int get_line(int, char*, int);
void headers(int, const char*);
void not_found(int);
void serve_file(int, const char*);
int startup(u_short*);
void unimplemented(int);

/**********************************************************************/
// 服务器
int main(void)
{
	int server_sock = -1;    //1 创建socket
	u_short port = 4000;     // 定义端口
	int client_sock = -1; // 通讯套接字
	//2 创建客户端的协议地址簇
	struct sockaddr_in client_name;
	socklen_t  client_name_len = sizeof(client_name);
	pthread_t newthread_id;

	//开启端口
	server_sock = startup(&port);  // startup是自己写的函数
	printf("HTTP在 %d端口上运行\n", port);
	// 建立服务端套接字，并处于监听状态
	while (1)
	{
		// 接收客户端请求
		client_sock = accept(server_sock, (struct sockaddr*)&client_name,
			&client_name_len);
		if (client_sock == -1)
			error_die("accept");
		// 开辟新的线程来运行线程函数 accept_request    传入参数: client_sock服务器接受的请求
		if (pthread_create(&newthread_id, NULL, accept_request,
			(void*)&client_sock) != 0)
		{
			perror("pthread_create");
		}
	}
	close(server_sock);
	return(0);
}

/**********************************************************************/
/*该函数启动监听web连接的进程
*在指定端口。如果端口为0，则动态分配
*端口，并修改原来的端口变量以反映实际
*端口。
*参数:指向包含要连接端口的变量的指针
返回:套接字*/
/**********************************************************************/
int startup(u_short* port)
{
	int httpd = 0;
	int on = 1;
	struct sockaddr_in servAddr; // 服务器协议地址簇
	// 建立服务端套接字
	httpd = socket(PF_INET, SOCK_STREAM, 0);  // 使用 IPv4 TCP
	if (httpd == -1)
		error_die("socket");
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(*port);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);  //INADDR_ANY泛指本机的意思
	socklen_t len = sizeof(servAddr);

	//
	if ((setsockopt(httpd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) < 0)
	{
		error_die("setsockopt failed");
	}

	// 绑定
	if (bind(httpd, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
		printf("绑定失败：%m\n"), exit(-2);
	printf("绑定成功!\n");
	// 没有端口的话, 动态申请一个端口
	if (*port == 0)
	{
		if (getsockname(httpd, (struct sockaddr*)&servAddr, &len) == -1)
			error_die("getsockname");
		*port = ntohs(servAddr.sin_port);
	}

	// 监听, 请求队列长度 5
	if (listen(httpd, 5) < 0)
		error_die("listen");
	return(httpd);
}

/**********************************************************************/
/* A request has caused a call to accept() on the server port to
 * return.  Process the request appropriately.
 * Parameters: the socket connected to the client */
 /**********************************************************************/
// 线程函数, 处理通讯套接字的通讯
void accept_request(void* arg)
{	// 通讯
	int client = *((int*)arg);
	char buf[1024];
	size_t numchars;
	char method[255];
	char url[255];
	char path[512];
	size_t i, j;
	struct stat st;   //文件状态信息
	int cgi = 0;      /* 如果服务器决定这是一个CGI，则为true*/
	char* query_string = NULL;

	// 读取套接字的一行,获取一行HTTP请求报文
	numchars = get_line(client, buf, sizeof(buf)); // numchars长度 /get_line自定义函数
	// 得到的报文:  [方法 url 协议]
	i = 0; j = 0;
	// 复制buf中的方法到 method
	while (!ISspace(buf[i]) && (i < sizeof(method) - 1)) //根据空格定位方法
	{
		method[i] = buf[i];
		i++;
	}
	j = i;
	method[i] = '\0';
	// strcasecmp函数比较时忽略大小写
	//只实现了get post 方法,其余的就会用unimplemented告知未实现
	if (strcasecmp(method, "GET") && strcasecmp(method, "POST"))
	{//如果不是get或者post方法就会打印出错误
		unimplemented(client); // 自定义函数
		return;
	}
	//cgi为标志位，1表示开启CGI解析(POST方法)
	if (strcasecmp(method, "POST") == 0)
		cgi = 1;

	//跳过方法后面的空白字符, 跳过空格
	while (ISspace(buf[j]) && (j < numchars))
		j++;
	//
	i = 0;
	//获取url
	while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < numchars))
	{
		url[i] = buf[j];
		i++; j++;
	}
	url[i] = '\0';
	//如果是get方法，url可能带？参数
	if (strcasecmp(method, "GET") == 0)
	{
		query_string = url;
		while ((*query_string != '?') && (*query_string != '\0'))
			query_string++;
		if (*query_string == '?')
		{ //带参数需要执行cgi，解析参数
			cgi = 1;
			*query_string = '\0';
			query_string++;
		}
	}
	//以上 将起始行 解析完毕

	sprintf(path, "htdocs%s", url);
	//如果path是一个目录，默认设置首页为index.html
	if (path[strlen(path) - 1] == '/')
		strcat(path, "index.html"); //追加,连接函数
	// 得到网站首页路径, 说白了就是创建文件
	/*网站:---- > 文件夹
	  网页:---- > 文件:   文本, 图片, 链接, 动图, html
	*/

	// 如果有执行权限，则认为是 .cgi 脚本
	 //函数定义:    int stat(const char *file_name, struct stat *buf);
	 //函数说明:   获取文件信息，并保存在buf所指的结构体stat中
	 //返回值:     执行成功则返回0，失败返回-1，错误代码存于errno（需要include <errno.h>）
	if (stat(path, &st) == -1)
	{// 如果文件没有创建
		//访问的网页不存在，则不断的读取剩余的请求头部信息，并丢弃错误404
		while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
			numchars = get_line(client, buf, sizeof(buf)); // 丢弃
		not_found(client); // 发出信息, 错误404
	}
	else
	{//文件创建成功
		//第一种情况就是path是一个目录，那么主动转到主页index.html上。serve_file()
		//后面一种情况,采用cgi处理。execute_cgi()

		//S_IFDIR 判断是否为目录
		if ((st.st_mode & S_IFMT) == S_IFDIR)
			strcat(path, "/index.html");
		//S_IXUSR：文件所有者具有可执行权限，
		//S_IXGRP：用户组具有可执行权限
		if ((st.st_mode & S_IXUSR) ||
			(st.st_mode & S_IXGRP) ||
			(st.st_mode & S_IXOTH))
			cgi = 1;
		if (cgi == 0)
		{//将静态文件返回
			//发送HTTP响应头和index.html 文件内容给客户端
			serve_file(client, path);  // 发送htdocs/index.html
		}
		else
		{
			//子进程执行CGI程序，结果由父进程发送给客户端
			execute_cgi(client, path, method, query_string); // 执行 CGI 脚本
		}
	}

	close(client);
}

/**********************************************************************/
/* Get a line from a socket, whether the line ends in a newline,
 * carriage return, or a CRLF combination.  Terminates the string read
 * with a null character.  If no newline indicator is found before the
 * end of the buffer, the string is terminated with a null.  If any of
 * the above three line terminators is read, the last character of the
 * string will be a linefeed and the string will be terminated with a
 * null character.
 * Parameters: the socket descriptor
 *             the buffer to save the data in
 *             the size of the buffer
 * Returns: the number of bytes stored (excluding null) */
 // 接收并处理客户端的请求报文
  /**********************************************************************/
int get_line(int sock, char* buf, int size)
{
	int i = 0;
	char c = '\0';
	int n;  //用于记录成功读取的字符数目

	while ((i < size - 1) && (c != '\n'))
	{
		n = recv(sock, &c, 1, 0);
		/*
		recv 的 flag 设为0
		此时的recv函数读取tcp buffer中的数据到buf中
		这里是一个字符一个字符的向外读
		*/
		/* DEBUG printf("%02X\n", c); */
		if (n > 0) // 读出数据成功
		{
			if (c == '\r')
			{
				n = recv(sock, &c, 1, MSG_PEEK);
				/*
			  考虑server向client发送数据"_META_DATA_\r\n_USER_DATA_"
			  把flags设置为MSG_PEEK时,仅把tcp buffer中的数据
			  读取到buf中，并不把已读取的数据从tcp buffer中移除，
			  再次调用recv仍可以读到刚才读到的数据
			  */
			  /* DEBUG printf("%02X\n", c); */
				if ((n > 0) && (c == '\n'))
					recv(sock, &c, 1, 0);  // 读出\n
				else
					/*
				如果回车符(\r)的后面不是换行符(\n)
				或者读取失败
				就把当前读取的字符置为换行，从而终止循环
				*/
					c = '\n';
			}
			/*依次向后读取*/
			buf[i] = c;
			i++;
		}
		else
			/*没有成功接收到字符，以换行符结尾，结束循环*/
			c = '\n';
	}
	buf[i] = '\0';

	return(i);
}

/**********************************************************************/
/*只实现了get post 方法,告知客户端其余方法未实现
 *Inform the client that the requested web method has not been
 * implemented.
 * Parameter: the client socket */
 /**********************************************************************/
void unimplemented(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 501 Method Not Implemented\r\n");
	send(client, buf, strlen(buf), 0);  //发送
	sprintf(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/html\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "<HTML><HEAD><TITLE>Method Not Implemented\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "</TITLE></HEAD>\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "<BODY><P>HTTP request method not supported.\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "</BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
}
/**********************************************************************/
/* Give a client a 404 not found status message.
 向客户端发出信息(错误404)*/
 /**********************************************************************/
void not_found(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 404 NOT FOUND\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/html\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "<HTML><TITLE>Not Found</TITLE>\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "<BODY><P>The server could not fulfill\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "your request because the resource specified\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "is unavailable or nonexistent.\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "</BODY></HTML>\r\n");
	send(client, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Send a regular file to the client.  Use headers, and report
 * errors to client if they occur.
 * Parameters: a pointer to a file structure produced from the socket
 *              file descriptor
 *             the name of the file to serve */

 //path是一个目录，那么主动转到主页index.html上
  /**********************************************************************/
void serve_file(int client, const char* filename)
{
	// c语言的读写文件方式
	FILE* resource = NULL;
	int numchars = 1;
	char buf[1024];

	buf[0] = 'A'; buf[1] = '\0';
	//读取和丢弃报头headers
	while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
		numchars = get_line(client, buf, sizeof(buf));

	resource = fopen(filename, "r");	// 打开 index.html 文件
	if (resource == NULL)
		not_found(client); //发送404
	else
	{
		headers(client, filename);   // 发送 HTTP 响应头信息
		cat(client, resource);       // 发送 index.html 文件内容给客户端, 参数文件指针(resource)
	}
	fclose(resource); // 关闭文件
}

/**********************************************************************/
/* Return the informational HTTP headers about a file. */
/* Parameters: the socket to print the headers on
 *             the name of the file */
 // 发送报文头, 代码为200，意为成功！PERFECT!
  /**********************************************************************/
void headers(int client, const char* filename)
{
	char buf[1024];
	(void)filename;  /*可以使用文件名来确定文件类型吗*/

	strcpy(buf, "HTTP/1.0 200 OK\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy(buf, SERVER_STRING);
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-Type: text/html\r\n");
	send(client, buf, strlen(buf), 0);
	strcpy(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
}

/**********************************************************************/
/* Puts the entire contents of the file onto the socket. This function
* Named after the UNIX "cat" command, as it might be
* It's easier to just do things like pipe, fork, and exec(" cat ").
Parameter: Client socket descriptor
* FILE The file pointer to cat */
// 发送报文内容, 发送 index.html 文件内容给客户端
/**********************************************************************/
void cat(int client, FILE* resource)
{
	char buf[1024];
	//fgets函数按行方式写, 就是从resource(文件内容获取buf大小的内容)，只要还未取到文件结束符eof就一直取+发送。
	fgets(buf, sizeof(buf), resource);
	while (!feof(resource))
	{
		send(client, buf, strlen(buf), 0);
		fgets(buf, sizeof(buf), resource);
	}
}

/**********************************************************************/
/* Execute a CGI script.  Will need to set environment variables as
 * appropriate.
 * Parameters: client socket descriptor
 *             path to the CGI script */
 // 执行 CGI 脚本
// 参数: 通讯套接字 文件路径 方法 URL
  /**********************************************************************/
void execute_cgi(int client, const char* path,
	const char* method, const char* query_string)
{
	char buf[1024];
	int cgi_output[2];	//创建管道描述符号, 由父进程向子进程的输入管道
	int cgi_input[2];   //创建管道描述符号, 由子进程向父进程的输出管道
	pid_t pid;
	int status;
	int i;
	char c;
	int numchars = 1;
	int content_length = -1; //对 POST 的 HTTP 请求中找出 content_length

	//1.处理报文头(客户端发送的服务请求)阶段

	//判断是GET请求还是POST请求，如果是GET请求丢弃请求头，如果是POST请求，获得Content - Length。
	//接下来判断请求长度是否合法，如果请求不合法，调用bad_request。
	buf[0] = 'A'; buf[1] = '\0';
	if (strcasecmp(method, "GET") == 0)
		/*把所有的 HTTP header 读取并丢弃, 因为此时的参数已经被我们包含在query_string里了，因此我们已经把该拿的都拿到了，直接舍弃报文头没问题！*/
		while ((numchars > 0) && strcmp("\n", buf))  /* read & discard headers */
			numchars = get_line(client, buf, sizeof(buf));
	else if (strcasecmp(method, "POST") == 0) /*POST*/
	{
		/* 对 POST 的 HTTP 请求中找出 content_length */
		//一行一行地读取，并且最后也是读完并舍弃这个报文头
		numchars = get_line(client, buf, sizeof(buf));
		while ((numchars > 0) && strcmp("\n", buf))
		{
			/*利用 \0 进行分隔 */
			buf[15] = '\0';
			/* HTTP 请求的特点*/
			if (strcasecmp(buf, "Content-Length:") == 0)
				content_length = atoi(&(buf[16]));
			numchars = get_line(client, buf, sizeof(buf));
		}
		/*没有找到 content_length */
		if (content_length == -1)
		{
			/*错误请求*/
			bad_request(client);
			return;
		}
	}
	else/*HEAD or other*/
	{
	}

	//2.处理应答报文阶段

	/* 正确，HTTP 状态码 200 */
	sprintf(buf, "HTTP/1.0 200 OK\r\n");
	send(client, buf, strlen(buf), 0);
	/* 创建管道，进程写管道*/
	if (pipe(cgi_output) < 0)
	{
		printf("创建cgi_output管道失败:%m\n");
		/*错误处理*/
		cannot_execute(client);
		return;
	}
	/*建立管道，进程读管道*/
	if (pipe(cgi_input) < 0)
	{
		printf("创建cgi_input管道失败:%m\n");
		/*错误处理*/
		cannot_execute(client);
		return;
	}
	// 使用管道
	if ((pid = fork()) < 0)
	{// 进程开启失败
		/*错误处理*/
		cannot_execute(client);
		return;
	}
	//子进程
	if (pid == 0)
	{
		char meth_env[255];
		char query_env[255];
		char length_env[255];
		/* 把 STDOUT 重定向到 cgi_output 的写入端 */
		dup2(cgi_output[1], STDOUT); // STDOUT 1 表示终端输出
		/* 把 STDIN 重定向到 cgi_input 的读取端 */
		dup2(cgi_input[0], STDIN);   // STDIN 0 表示终端输入
		/* 关闭 cgi_input 的写入端 和 cgi_output 的读取端 */
		/* 关闭 cgi_input 的写入端 和 cgi_output 的读取端 */
		close(cgi_output[0]);
		close(cgi_input[1]);
		/*设置 request_method 的环境变量*/
		sprintf(meth_env, "REQUEST_METHOD=%s", method);
		putenv(meth_env); // 用于改变或增加环境变量的内容
		if (strcasecmp(method, "GET") == 0)
		{
			/*设置 query_string 的环境变量*/
			sprintf(query_env, "QUERY_STRING=%s", query_string);
			putenv(query_env);
		}
		else
		{   /* POST */
			/*设置 content_length 的环境变量*/
			sprintf(length_env, "CONTENT_LENGTH=%d", content_length);
			putenv(length_env);
		}
		/*用 execl 运行 cgi 程序*/
		execl(path, NULL);
		exit(0);
	}
	else
	{   // 父进程
		/* 关闭 cgi_input 的读取端 和 cgi_output 的写入端 */
		close(cgi_output[1]);
		close(cgi_input[0]);
		// 如果是post
		if (strcasecmp(method, "POST") == 0)
		{
			/*接收 POST 过来的数据*/
			for (i = 0; i < content_length; i++)
			{
				recv(client, &c, 1, 0); // 接收来自客户端的表单输入
				/*把 POST 数据写入 cgi_input，现在重定向到 STDIN */
				write(cgi_input[1], &c, 1); // 往管道输入端输入, 发送给子进程
			}
		}
		/*读取 cgi_output 的管道输出到客户端，读到子进程处理后的信息，发送给客户端*/
		while (read(cgi_output[0], &c, 1) > 0) //从管道输出端读取, 父进程通过read读取到子进程的输出后
			send(client, &c, 1, 0); // 发送到客户端
		/*关闭管道*/
		close(cgi_output[0]);
		close(cgi_input[1]);
		/*等待子进程*/
		waitpid(pid, &status, 0);
	}
}

/**********************************************************************/
/* 向客户端发出信息(400)
*参数:客户端socket */
/**********************************************************************/
void bad_request(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 400 BAD REQUEST\r\n");
	send(client, buf, sizeof(buf), 0);
	sprintf(buf, "Content-type: text/html\r\n");
	send(client, buf, sizeof(buf), 0);
	sprintf(buf, "\r\n");
	send(client, buf, sizeof(buf), 0);
	sprintf(buf, "<P>Your browser sent a bad request, ");
	send(client, buf, sizeof(buf), 0);
	sprintf(buf, "such as a POST without a Content-Length.\r\n");
	send(client, buf, sizeof(buf), 0);
}

/**********************************************************************/
/** 向客户端发出信息(500表示服务器自己炸了)
 /**********************************************************************/
void cannot_execute(int client)
{
	char buf[1024];

	sprintf(buf, "HTTP/1.0 500 Internal Server Error\r\n"); //500意思就是服务器自己炸了
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "Content-type: text/html\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "\r\n");
	send(client, buf, strlen(buf), 0);
	sprintf(buf, "<P>Error prohibited CGI execution.\r\n");
	send(client, buf, strlen(buf), 0);
}

/**********************************************************************/
//打印错误消息
/* Print out an error message with perror() (for system errors; based
 * on value of errno, which indicates system call errors) and exit the
 * program indicating an error. */
 /**********************************************************************/
void error_die(const char* sc)
{
	perror(sc);
	exit(1);
}