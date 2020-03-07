#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/net.h>
#include<linux/socket.h>
#include<linux/in.h>
#include<linux/slab.h>
#include<linux/sched.h>
#include<linux/syscalls.h>

#define PORT 65656
int init_module(void) 
{
  struct socket *sock;
  struct sockaddr_in servaddr;
  struct iovec iov;
  struct msghdr sock_msg;
  int error,length,rva;
  char *str;
  unsigned long int INAAR = 0x7f000001;

  str = "Hello World!";
  length = sizeof(str);
  error = sock_create( AF_INET, SOCK_DGRAM, IPPROTO_UDP, &sock);
  if (error < 0)
  {
    printk(KERN_ALERT "\nCan`t create a socket");
    goto out;
  }
	else 
	printk(KERN_ALERT" \n socket created succesfully");
  memset(&servaddr,0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  servaddr.sin_addr.s_addr =htonl(INAAR);
  //Local host IP add 127.0.0.1

  iov.iov_base = str;
  iov.iov_len = length; 
  sock_msg.msg_name=&servaddr;
  sock_msg.msg_namelen=sizeof(struct sockaddr_in);
  sock_msg.msg_control=NULL;
  sock_msg.msg_controllen=0;
  sock_msg.msg_flags=0;
  
  rva = sock_sendmsg(sock , &sock_msg);
  
  printk(KERN_ALERT "\nMessage sent to local host ");
  
  out:
	return 0;
}
