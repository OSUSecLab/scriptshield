#if defined(__cplusplus)
extern "C" {
#endif
#include <string.h>
#include <time.h>
#include "Enclave_t.h" 
#include "sys/types.h"

//#include <bits/alltypes.h>
//#include <linux/limits.h> //Determine PATH_MAX
/*It appears I don't have access to PATH_MAX when
compiling this, so I'll just choose a value.  This
could eventually cause problems.
*/
#define PATH_MAX 4096

//Supported syscalls
#define READ 0
#define WRITE 1
#define OPEN 2
#define CLOSE 3
#define STAT 4
#define FSTAT 5
#define POLL 7
#define LSEEK 8
#define MMAP 9
#define IOCTL 16
#define READV 19
#define WRITEV 20
#define SELECT 23
#define DUP2 33
#define NANOSLEEP 35
#define SOCKET 41
#define CONNECT 42
#define ACCEPT 43
#define SENDTO 44
#define RECVFROM 45
#define SENDMSG 46
#define RECVMSG 47
#define SHUTDOWN 48
#define BIND 49
#define LISTEN 50
#define GETSOCKNAME 51
#define GETPEERNAME 52
#define SOCKETPAIR 53
#define SETSOCKOPT 54
#define GETSOCKOPT 55
#define CLONE 56
#define FORK 57
#define VFORK 58
#define EXECVE 59
#define WAIT4 61
#define FCNTL 72
#define GETCWD 79
#define CHDIR 80
#define GETSID 124
#define GETDENTS 217
#define CLOCK_GETTIME 228
#define EXIT_GROUP 231
#define PIPE 293
extern void* sgx_ocalloc(unsigned long size);
extern void sgx_ocfree(void);

# define _SIGSET_NWORDS (1024 / (8 * sizeof (unsigned long int)))

struct sigset_t
  {
    unsigned long int __val[_SIGSET_NWORDS];
  };

struct sched_param
  {
    int __sched_priority;
  };

struct __spawn_action
 {
   enum
   {
     spawn_do_close,
     spawn_do_dup2,
     spawn_do_open
   } tag;
 
   union
   {
     struct
     {
       int fd;
     } close_action;
     struct
     {
       int fd;
       int newfd;
     } dup2_action;
     struct
     {
       int fd;
       const char *path;
       int oflag;
       int mode;
     } open_action;
   } action;
 };


struct posix_spawnattr_t
{
  short int __flags;
  int __pgrp;
  struct sigset_t __sd;
  struct sigset_t __ss;
  struct sched_param __sp;
  int __policy;
  int __pad[16];
} ;



struct posix_spawn_file_actions_t
{
  int __allocated;
  int __used;
  struct __spawn_action *__actions;
  int __pad[16];
} ;

struct args {
	int p[2];
	struct sigset_t oldmask;
	const char *path;
	int (*exec)(const char *, char *const *, char *const *);
	const struct posix_spawn_file_actions_t *fa;
	const struct posix_spawnattr_t * attr;
	char *const *argv, *const *envp;
};

struct args *arg_global;
typedef int (*func_ptr)(void*);
func_ptr childfunc_addr;
 
struct enclave_iovec {
        void *iov_base;
        unsigned long iov_len;
};

struct enclave_timespec {
	long tv_sec;
	long tv_nsec;
};

struct enclave_sockaddr {
	long sa_family;
	char sa_data[14];
};

struct enclave_timeval {
               long    tv_sec;         /* seconds */
               long    tv_usec;        /* microseconds */
           };


#define __FD_SETSIZE 1024
#define __NFDBITS (8 * sizeof(unsigned long))
#define __FDSET_LONGS (__FD_SETSIZE/__NFDBITS)
struct enclave_fd_set{
  unsigned long fds_bits[__FDSET_LONGS];
};

struct enclave_pollfd {
               int   fd;         /* file descriptor */
               short events;     /* requested events */
               short revents;    /* returned events */
           };

//struct msghdr {
//    void         *msg_name;       /* optional address */
//    socklen_t     msg_namelen;    /* size of address */
//    struct iovec *msg_iov;        /* scatter/gather array */
//    size_t        msg_iovlen;     /* # elements in msg_iov */
//    void         *msg_control;    /* ancillary data, see below */
//    size_t        msg_controllen; /* ancillary data buffer len */
//    int           msg_flags;      /* flags on received message */
//};



struct stat
  {
    long st_dev;             /* Device.  */

    long st_ino;             /* File serial number.  */


    long st_nlink;         /* Link count.  */
    int st_mode;           /* File mode.  */

    int st_uid;             /* User ID of the file's owner. */
    int st_gid;             /* Group ID of the file's group.*/

    int __pad0;

    long st_rdev;            /* Device number, if device.  */


    long st_size;                    /* Size of file, in bytes.  */

    long st_blksize;     /* Optimal block size for I/O.  */

    long st_blocks;               /* Number 512-byte blocks allocated. */


    /* Nanosecond resolution timestamps are stored in a format
       equivalent to 'struct timespec'.  This is the type used
       whenever possible but the Unix namespace rules do not allow the
       identifier 'timespec' to appear in the <sys/stat.h> header.
       Therefore we have to handle the use of this header in strictly
       standard-compliant sources special.  */
    struct enclave_timespec st_atim;            /* Time of last access.  */
    struct enclave_timespec st_mtim;            /* Time of last modification.  */
    struct enclave_timespec st_ctim;            /* Time of last status change.  */
# define st_atime st_atim.tv_sec        /* Backward compatibility.  */
# define st_mtime st_mtim.tv_sec
# define st_ctime st_ctim.tv_sec


    long int __glibc_reserved[3];


    unsigned long int __glibc_reserved4;
    unsigned long int __glibc_reserved5;

  };


struct dirent {
	long d_ino;
	long d_off;
	unsigned short d_reclen;
	unsigned char d_type;
	char d_name[256];
};


struct rusage {
    struct enclave_timeval ru_utime; /* user CPU time used */
    struct enclave_timeval ru_stime; /* system CPU time used */
    long   ru_maxrss;        /* maximum resident set size */
    long   ru_ixrss;         /* integral shared memory size */
    long   ru_idrss;         /* integral unshared data size */
    long   ru_isrss;         /* integral unshared stack size */
    long   ru_minflt;        /* page reclaims (soft page faults) */
    long   ru_majflt;        /* page faults (hard page faults) */
    long   ru_nswap;         /* swaps */
    long   ru_inblock;       /* block input operations */
    long   ru_oublock;       /* block output operations */
    long   ru_msgsnd;        /* IPC messages sent */
    long   ru_msgrcv;        /* IPC messages received */
    long   ru_nsignals;      /* signals received */
    long   ru_nvcsw;         /* voluntary context switches */
    long   ru_nivcsw;        /* involuntary context switches */
};


unsigned long enclave_open(long pathname, long flags, long mode){
	//ocall_print_long(mode);
	unsigned long ret = -1;
	unsigned long len = strnlen((const char*) pathname, PATH_MAX);
	void* buf = sgx_ocalloc(len+1);
	strncpy(buf, (const char*) pathname, len+1);
	ocall_syscall3(&ret, OPEN, (long)buf, flags, mode); 
        sgx_ocfree();
	return ret;
}

unsigned long enclave_open2(long pathname, long flags){
	//ocall_print_long(mode);
	unsigned long ret = -1;
	unsigned long len = strnlen((const char*) pathname, PATH_MAX);
	void* buf = sgx_ocalloc(len+1);
	strncpy(buf, (const char*) pathname, len+1);
	ocall_syscall3(&ret, OPEN, (long)buf, flags, 0); 
        sgx_ocfree();
	return ret;
}

unsigned long enclave_close(long fd){
	unsigned long ret = -1;
	ocall_syscall1(&ret, CLOSE, fd);
	return ret;
}

unsigned long enclave_readv(long fd, long iov, long iovcnt){
        unsigned long total = 0;
        long i,j = 0;
        unsigned char* buf;
        unsigned long* sbuf;
	unsigned long iovec_offs = 0;
        unsigned long offset = 0;
        unsigned long ret = -1;
        struct enclave_iovec* iovs = (struct enclave_iovec*) iov;
	total = iovcnt*sizeof(struct enclave_iovec);//First, we copy all the strucs, then the arrays 
	offset = total;//Set the offset to reside after the structs so all strings are copied after the structs
        for( i = 0; i < iovcnt; i++ ){
                total += iovs[i].iov_len;
        }
        buf = (unsigned char*)sgx_ocalloc(total);
        for( i = 0; i < iovcnt; i++ ){
		memcpy(buf+iovec_offs, &iovs[i], sizeof(struct enclave_iovec));
		((struct enclave_iovec*) (buf+iovec_offs))->iov_base = (buf + offset);//Set new iovec to point to address of new string buffer
		iovec_offs += sizeof(struct enclave_iovec);
		//memcpy(buf+offset, iovs[i].iov_base, iovs[i].iov_len);
		offset += iovs[i].iov_len;
        }
	ocall_syscall3(&ret, READV, fd, (long)buf, iovcnt);
	offset = iovcnt*sizeof(struct enclave_iovec);
	iovec_offs = 0;
	for( i = 0; i < iovcnt; i++ ){
		//memcpy(&iovs[i], buf+iovec_offs, sizeof(struct enclave_iovec));
		//((struct enclave_iovec*) (buf+iovec_offs))->iov_base = (buf + offset);//Set new iovec to point to address of new string buffer
		iovec_offs += sizeof(struct enclave_iovec);
		memcpy(iovs[i].iov_base, buf+offset, iovs[i].iov_len);//Copy back in to buffer
		offset += iovs[i].iov_len;
        }
        sgx_ocfree();
	if (ret > total){abort();}
        return ret;
}

unsigned long enclave_writev(long fd, long iov, long iovcnt){
        unsigned long total = 0;
        long i,j = 0;
        unsigned char* buf;
        unsigned long* sbuf;
	unsigned long iovec_offs = 0;
        unsigned long offset = 0;
        unsigned long ret = -1;
        struct enclave_iovec* iovs = (struct enclave_iovec*) iov;
	total = iovcnt*sizeof(struct enclave_iovec);//First, we copy all the strucs, then the arrays 
	offset = total;//Set the offset to reside after the structs so all strings are copied after the structs
        for( i = 0; i < iovcnt; i++ ){
                total += iovs[i].iov_len;
        }
        buf = (unsigned char*)sgx_ocalloc(total);
        for( i = 0; i < iovcnt; i++ ){
		memcpy(buf+iovec_offs, &iovs[i], sizeof(struct enclave_iovec));
		((struct enclave_iovec*) (buf+iovec_offs))->iov_base = (buf + offset);//Set new iovec to point to address of new string buffer
		iovec_offs += sizeof(struct enclave_iovec);
		memcpy(buf+offset, iovs[i].iov_base, iovs[i].iov_len);
		offset += iovs[i].iov_len;
                /*sbuf = (unsigned long*)(buf+offset);
                *sbuf = iovs[i].iov_len;
                offset+=sizeof(unsigned long);
                for( j = 0; j < iovs[i].iov_len; j++ ){
                        buf[offset] = *((unsigned char*)iovs[i].iov_base + offset);//Perhaps this doesn't directly contain the data?  Something is wrong?
                        offset++;
                }*/
        }
        //ocall_writev(&ret, fd, (long)buf, iovcnt);
	ocall_syscall3(&ret, WRITEV, fd, (long)buf, iovcnt);
        sgx_ocfree();
        return ret;
}

unsigned long enclave_clock_gettime(long clk_id, long tp){
	unsigned char* buf;
	unsigned long ret = -1;
	buf = (unsigned char*)sgx_ocalloc(sizeof(struct enclave_timespec));
	ocall_syscall2(&ret, CLOCK_GETTIME, clk_id, (long)buf);
	//memcpy((long*)tp, buf, sizeof(struct enclave_timespec));
	memcpy((struct enclave_timespec *)tp, buf, sizeof(struct enclave_timespec));
	sgx_ocfree();
	return ret;
}

unsigned long enclave_getsid(long pid){
        unsigned long ret = -1;
        ocall_syscall1(&ret, GETSID , pid);
        return ret;
}


unsigned long enclave_read(long fd, long buf, long count){
        unsigned long ret = -1;
	unsigned char* buf1;
        buf1 = (unsigned char*)sgx_ocalloc(count);
        
	ocall_syscall3(&ret, READ, fd, (long)buf1, count);
	memcpy((void*)buf, buf1, count);
        sgx_ocfree();
        return ret;
}

unsigned long enclave_write(long fd, long buf, long count){
	unsigned long ret = -1;
	unsigned char* buf1;
        buf1 = (unsigned char*)sgx_ocalloc(count);
        memcpy(buf1, (void*)buf, count);
	ocall_syscall3(&ret, WRITE, fd, (long)buf1, count);
	
        sgx_ocfree();
        return ret;
}

unsigned long enclave_setsockopt(long sockfd, long level, long optname, long optval, long optlen){
	unsigned long ret = -1;
	unsigned char* buf;
	void* buffer;
	buf = (void*)sgx_ocalloc(optlen);
	memcpy(buf, (void*)optval, optlen);
	ocall_syscall5(&ret, SETSOCKOPT, sockfd, level, optname, (long)buf, optlen);
	sgx_ocfree();
	//memcpy(buffer, buf, optlen);
	return ret;
	//return *buffer;
}

unsigned long enclave_getsockopt(long sockfd, long level, long optname, long optval, long optlen){
	unsigned long ret = -1;
	void* buffer;
	buffer = (void*)sgx_ocalloc(optlen);
	ocall_syscall5(&ret, GETSOCKOPT, sockfd, level, optname, (long)buffer, optlen);
	memcpy((void *)optval, buffer, optlen);
	sgx_ocfree();
	return ret;
}

unsigned long enclave_getsockname(long sockfd, long addr, long addrlen){
	unsigned long ret = -1;
	unsigned char* buffer;
	int len = *((int*)addrlen);
	buffer = (unsigned char*)sgx_ocalloc(len + sizeof(int));//Perhaps addrlen is an int*
	*(buffer+len) = len;
	ocall_syscall3(&ret, GETSOCKNAME, sockfd, (long)buffer, (long)(buffer+len) );
	memcpy(addr, buffer, len);
	*((int*)addrlen) = *(int*)(buffer+len);
	sgx_ocfree();
	return ret;
}


unsigned long enclave_socket(long domain, long type, long protocol){
	unsigned long ret = -1;
	ocall_syscall3(&ret, SOCKET, domain, type, protocol);
	return ret;
}

unsigned long enclave_fcntl(long int fd, int cmd, long arg){
	unsigned long ret = -1;
	ocall_syscall3(&ret, FCNTL, fd, cmd, arg);
	return ret;
}

unsigned long enclave_bind(long socket, long address, long address_len){
	unsigned long ret = -1;
	unsigned char * buff;
	buff = (unsigned char*)sgx_ocalloc(sizeof(struct enclave_sockaddr));
	memcpy(buff, (struct enclave_sockaddr*) address, sizeof(struct enclave_sockaddr));
	ocall_syscall3(&ret, BIND, socket, (long)buff, address_len);
	sgx_ocfree();
	return ret;
}

unsigned long enclave_listen(long sockfd, long backlog){
	unsigned long ret = -1;
	ocall_syscall2(&ret, LISTEN, sockfd, backlog);
	return ret;
}

unsigned long enclave_select(long nfds, long readfds, long writefds,
                  long exceptfds, long timeout){
	unsigned long ret = -1;
	unsigned char *read;
	unsigned char *write;
	unsigned char *except;
	unsigned char *time;

	ocall_malloc(&read, sizeof(struct enclave_fd_set));

	ocall_malloc(&write, sizeof(struct enclave_fd_set));
	ocall_malloc(&except, sizeof(struct enclave_fd_set));
	ocall_malloc(&time, sizeof(struct enclave_timeval));

	if((struct enclave_fd_set*)readfds != NULL)
	{memcpy(read, (struct enclave_fd_set*)readfds, sizeof(struct enclave_fd_set));}
	else
	{
		read = NULL;
	}
	if((struct enclave_fd_set*)writefds != NULL){
	memcpy(write, (struct enclave_fd_set*)writefds, sizeof(struct enclave_fd_set));}
	else
	{
		write = NULL;
	}
        if((struct enclave_fd_set*)exceptfds != NULL)
	  { 
            memcpy(except, (struct enclave_fd_set*)exceptfds, sizeof(struct enclave_fd_set));
          }
	else
          {
            except = NULL;
          }

	if((struct enclave_timeval*)timeout != NULL)
	  {
	    memcpy(time, (struct enclave_timeval*)timeout, sizeof(struct enclave_timeval));
	  }
	else
	  {
	    time = NULL;
	  }
	
	ocall_syscall5(&ret, SELECT, nfds, (long)read, (long)write, (long)except, (long)time );

	if(time != NULL){
	memcpy(timeout, time, sizeof(struct enclave_timeval));
	}

	if(read != NULL){
	memcpy(readfds, read, sizeof(struct enclave_fd_set));
	}

	if(write != NULL){
	memcpy(writefds, write, sizeof(struct enclave_fd_set));
	}

	if(except != NULL){
	memcpy(exceptfds, except, sizeof(struct enclave_fd_set));
	}

	ocall_free(read);
	ocall_free(write);
	ocall_free(except);
	ocall_free(time);
	return ret;
}

unsigned long enclave_accept(long sockfd, long addr, long addrlen){
	unsigned long ret = -1;
	unsigned char* buffer;
	int len;
	if((int*) addrlen != NULL){
		len = *((int*)addrlen);
        }
	else
	{
		len = 0;
	}
	
	buffer = (unsigned char*)sgx_ocalloc(sizeof(struct enclave_sockaddr) + sizeof(int));
	memset(buffer, 0, sizeof(struct enclave_sockaddr));	
	//Perhaps addrlen is an int*
	/*if((struct enclave_sockaddr*)addr != NULL){
        	memcpy(buffer, addr, sizeof(struct enclave_sockaddr));
	}
	else{
		buffer = NULL;
	}*/
	*(buffer+len) = len;
	ocall_syscall3(&ret, ACCEPT, sockfd, (long)buffer, (long)(buffer+len) );
	memcpy(addr, buffer, len);
	*((int*)addrlen) = *(int*)(buffer+len);
	sgx_ocfree();
	return ret;
}
	

unsigned long enclave_recvfrom(long sockfd, long buf,long len, long flags,
               long  src_addr,long addrlen){
	unsigned long ret = -1;
	unsigned char * buffer;
	buffer = (unsigned char*)sgx_ocalloc(len);
	memset(buffer,0, len);
	ocall_syscall6(&ret, RECVFROM, sockfd, (long)buffer, len, flags, NULL, NULL);
	memcpy(buf, buffer, len);
	sgx_ocfree();
	return ret;
}

unsigned long enclave_sendto(long sockfd, long buf, long len, long flags,
               long dest_addr, long addrlen){

	unsigned long ret = -1;
	unsigned char * buffer;
	buffer = (unsigned char*)sgx_ocalloc(len);
	if(buf != NULL){
	memcpy(buffer, buf, len);
	}
	else{

		buffer = NULL;
	}
	
	unsigned char *dest;
	dest = (unsigned char*)sgx_ocalloc(sizeof(struct enclave_sockaddr));
	if((struct sockaddr*) dest_addr != NULL){
		memcpy(dest,(struct sockaddr*) dest_addr, sizeof(struct enclave_sockaddr));
	}
	else{
		dest = NULL;		
	}
	ocall_syscall6(&ret, SENDTO, sockfd, (long)buffer, len, flags, (long)dest, addrlen);

	sgx_ocfree();
	return ret;
}


unsigned long encalve_getpeername(long sockfd, long addr, long addrlen){

	unsigned long ret = -1;
	unsigned char* buffer;
	int len = *((int*)addrlen);
	buffer = (unsigned char*)sgx_ocalloc(len + sizeof(int));//Perhaps addrlen is an int*
	*(buffer+len) = len;
	ocall_syscall3(&ret, GETPEERNAME, sockfd, (long)buffer, (long)(buffer+len) );
	memcpy(addr, buffer, len);
	*((int*)addrlen) = *(int*)(buffer+len);
	sgx_ocfree();
	return ret;

}

unsigned long enclave_lseek(long fd, long offset, long whence){
	unsigned long ret = -1;
	ocall_syscall3(&ret, LSEEK, fd, offset, whence);
	return ret;
}

unsigned long enclave_connect(long sockfd, long addr, long addrlen){
	unsigned long ret = -1;
	unsigned char* buffer;
	buffer = (unsigned char*)sgx_ocalloc(addrlen);
	if((struct enclave_sockaddr*)addr != NULL){
		memcpy(buffer, addr, addrlen);
	}
	else{
		buffer = NULL;
	}
	ocall_syscall3(&ret, CONNECT, sockfd, (long)buffer, addrlen);
	
	sgx_ocfree();
	return ret;


}

unsigned long enclave_poll(long fds, long nfds, long timeout){
	unsigned ret = -1;
	unsigned char *buffer;
	buffer = (unsigned char *)sgx_ocalloc(sizeof(struct enclave_pollfd));
	if((struct enclave_pollfd*)fds != NULL){

		memcpy(buffer, fds, sizeof(struct enclave_pollfd));
	}
	else{
		buffer = NULL;
	}
	ocall_syscall3(&ret, POLL, (long)buffer, nfds, timeout);
	sgx_ocfree();
	return ret;
}

	

unsigned long enclave_shutdown(long sockfd, long how){
	unsigned long ret = -1;
	ocall_syscall2(&ret, SHUTDOWN, sockfd, how);
	return ret;
}

unsigned long enclave_ioctl(long fd, long request, long arg){
	unsigned long ret = -1;
	ocall_syscall3(&ret, IOCTL, fd, request, arg);
	return ret;

}

unsigned long enclave_socketpair(long domain, long type, long protocol, long sv[2]){
	unsigned long ret = -1;
	unsigned char *buffer;
	buffer = (unsigned char *)sgx_ocalloc(2*sizeof(int));
	ocall_syscall4(&ret, SOCKETPAIR, domain, type, protocol, (long)(buffer));
	memcpy(sv, buffer, 2*sizeof(int));
	sgx_ocfree();
	return ret;


}

unsigned long enclave_nanosleep(long req, long rem){
	unsigned long ret = -1;
	unsigned char *buffer;
	buffer = (unsigned char*)sgx_ocalloc(2*sizeof(struct enclave_timespec));
	memcpy(buffer, req, sizeof( struct enclave_timespec ));
	memcpy(buffer+sizeof(struct enclave_timespec), rem, sizeof(struct enclave_timespec));
	ocall_syscall2(&ret, NANOSLEEP, (long)buffer, (long)buffer+sizeof(struct enclave_timespec) );
	sgx_ocfree();	
	return ret;

}

unsigned long enclave_stat(long pathname, long statbuf){
	
	int c =1;
	char* p = (char*)pathname;
	while(*p != '\0'){
		c++;
		(char*)p++;
			}
	
	unsigned long ret = -1;
	unsigned char* buffer;
	buffer = (unsigned char *)sgx_ocalloc(c+sizeof(struct stat));
	memcpy(buffer, pathname, c);
	ocall_syscall2(&ret, STAT, (long)buffer, (long)(buffer+c));
	memcpy((struct stat *)statbuf, (buffer+c), sizeof(struct stat));
	sgx_ocfree();
	return ret;	
	
}


unsigned long enclave_fstat(long fd, long statbuf){
	unsigned long ret = -1;
	unsigned char* buffer;
	
	buffer = (unsigned char *)sgx_ocalloc(sizeof(struct stat));
	ocall_syscall2(&ret, FSTAT, fd, (long)(buffer));
	memcpy((struct stat *)statbuf, (buffer), sizeof(struct stat));
	sgx_ocfree();
	return ret;	
	
}
unsigned long enclave_getdents(long fd, long dirp, long count){
	unsigned long ret = -1;
	unsigned char* buffer;
        buffer = (unsigned char* )sgx_ocalloc(count);
	ocall_syscall3(&ret, GETDENTS, fd, (long)buffer, count);
	memcpy((struct dirent *)dirp, buffer, count);		
	sgx_ocfree();
	return ret;
}

unsigned long enclave_exit_group(long status){
	unsigned long ret;
	ocall_syscall1(&ret, EXIT_GROUP, status);
	return ret;

}


unsigned long enclave_pipe2(long pipefd, long flags){
	unsigned long ret;
	int* buffer;
	buffer = (int*)sgx_ocalloc(2*sizeof(int));
	ocall_syscall2(&ret, PIPE, (long)buffer, flags);
	memcpy(pipefd, buffer, 2*sizeof(int));
	sgx_ocfree();
	return ret;


}

unsigned long enclave_clone(long fn, long child_stack, long flags, long arg){
	unsigned long ret = -1;
	unsigned char* buffer;
	unsigned char* arg_clone;
	childfunc_addr = (int*) fn;
	
	arg_global = (struct args*) arg;
        int (*function_pointer)() = NULL;
        clone_ocall((long)& function_pointer);
	ocall_print_long((long)function_pointer);
	ocall_malloc(&buffer, 20000);
	ocall_print_string("before sys call\n");
        ret = 23008;
	ocall_print_string("after sys call\n");
	return ret;

}

unsigned long enclave_fork(){
	unsigned long ret = -1;
	ocall_syscall0(&ret, FORK);
	return ret;

}

unsigned long enclave_vfork(){
	unsigned long ret = -1;
	ocall_syscall0(&ret, VFORK);
	return ret;
}

unsigned long enclave_dup2(long oldfd, long newfd){
	unsigned long ret = -1;
	ocall_syscall2(&ret, DUP2, oldfd, newfd);
	return ret;
}

unsigned long enclave_execve(long filename, long argv, long envp){
	unsigned long ret = -1;
	unsigned char* buffer;
	int c =1;
	char* p = (char*)filename;
	while(*p != '\0'){
		c++;
		(char*)p++;
			}

	buffer = (unsigned char *)sgx_ocalloc(c+128);
	ocall_syscall3(&ret, EXECVE, (long) buffer, (long)(buffer+c), NULL);
	return ret;
}

void childfunc(){
	
	ocall_print_string("before childfunc\n");
        ocall_print_long((long)childfunc_addr);
        ocall_print_long((long)arg_global);
	
	ocall_print_string("after childfunc\n");
	
}

unsigned long enclave_wait4(long pid, long status, long options, long rusage){
	unsigned long ret = -1;
	unsigned char* buffer;
	buffer = (unsigned char *)sgx_ocalloc(sizeof(int)+sizeof(struct rusage));
	memcpy(buffer, status, sizeof(int));
	ocall_syscall4(&ret, WAIT4, (long)pid, (long)(buffer), options,(long)(buffer+sizeof(int)));
	return ret;
	
}


unsigned long enclave_getcwd(long buf, long size){
	unsigned long ret = -1;
	unsigned char* buffer;
	buffer = (unsigned char *)sgx_ocalloc(size);
	ocall_syscall2(&ret, GETCWD, (long)buffer, (long)size);
	memcpy(buf, buffer, size);
	return ret;


}


unsigned long enclave_chdir(long path){
	unsigned long ret = -1;
	unsigned char * buffer;
	int size = strlen(path);
        buffer = (unsigned char *)sgx_ocalloc(size);
	memcpy(buffer, path, size);
	ocall_syscall1(&ret, CHDIR, (long)buffer);
	
	return ret;



}

unsigned long enclave_mmap(long addr, long length, long port, long flags, long fd, long offset ){
	unsigned long ret = -1;
	unsigned char * buffer;

        buffer = (unsigned char *)sgx_ocalloc(8*sizeof(long));
	if(addr != NULL){
	memcpy(buffer, addr, 8*sizeof(long));}
	else{
		buffer = NULL;
	}
	ocall_syscall6(&ret, MMAP, (long)buffer, length, port, flags, fd, offset );
	
	return ret;



}

#if defined(__cplusplus)
}
#endif
