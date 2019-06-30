#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

//#include "enclave.h"
#include <sys/timeb.h>
#include <time.h>
extern void ocall_print_string(const char *str);
extern void ocall_print_long(long l);
extern void ocall_print_time(long n, long l);
extern void ocall_print_timeend(long n, long l);
extern void ocall_print_timeres(long n, long l, long s);
extern unsigned long enclave_open(long a1, long a2, long a3);
extern unsigned long enclave_open2(long a1, long a2);
extern unsigned long enclave_close(long a1);
extern unsigned long enclave_readv(long a1, long a2, long a3);
extern unsigned long enclave_writev(long a1, long a2, long a3);
extern unsigned long enclave_clock_gettime(long a1, long a2);
extern unsigned long enclave_getsid(long a1);
extern unsigned long enclave_shutdown(long a1, long a2);
extern unsigned long enclave_listen(long a1, long a2);
extern unsigned long enclave_read(long a1, long a2, long a3);
extern unsigned long enclave_write(long a1, long a2, long a3);
extern unsigned long enclave_socket(long a1, long a2, long a3);

extern unsigned long enclave_connect(long a1, long a2, long a3);
extern unsigned long enclave_accept(long a1, long a2, long a3);
extern unsigned long enclave_sendmsg(long a1, long a2, long a3);
extern unsigned long enclave_recvmsg(long a1, long a2, long a3);
extern unsigned long enclave_bind(long a1, long a2, long a3);
extern unsigned long enclave_getsockname(long a1, long a2, long a3);
extern unsigned long encalve_getpeername(long a1, long a2, long a3);
extern unsigned long enclave_socketpair(long a1, long a2, long a3, long a4);
extern unsigned long enclave_setsockopt(long a1, long a2, long a3, long a4, long a5);
extern unsigned long enclave_getsockopt(long a1, long a2, long a3, long a4, long a5);
extern unsigned long enclave_sendto(long a1, long a2, long a3, long a4, long a5, long a6);
extern unsigned long enclave_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6);
extern unsigned long enclave_fcntl(long a1, long a2, long a3);
extern unsigned long enclave_select(long a1, long a2, long a3, long a4, long a5);
extern unsigned long enclave_accept(long a1, long a2, long a3);
extern unsigned long enclave_close(long a1);
extern unsigned long enclave_lseek(long a1, long a2, long a3);
extern unsigned long enclave_poll(long a1, long a2, long a3);
extern unsigned long enclave_ioctl(long a1, long a2, long a3);
extern unsigned long enclave_nanosleep(long a1, long a2);
extern unsigned long enclave_stat(long a1, long a2);
extern unsigned long enclave_getdents(long a1, long a2, long a3);
extern unsigned long enclave_exit_group(long a1);
extern unsigned long enclave_pipe2(long a1, long a2);
extern unsigned long enclave_clone(long a1, long a2, long a3, long a4);
extern unsigned long enclave_fork();
extern unsigned long enclave_vfork();
extern unsigned long enclave_dup2(long a1, long a2);
extern unsigned long enclave_execve(long a1, long a2, long a3);
extern unsigned long enclave_wait4(long a1, long a2, long a3, long a4);
extern unsigned long enclave_getcwd(long a1, long a2);
extern unsigned long enclave_chdir(long a1);
extern unsigned long enclave_fstat(long a1, long a2);
extern unsigned long enclave_mmap(long a1, long a2, long a3, long a4, long a5, long a6);



static __inline long __syscall0(long n)
{
	unsigned long ret;
		ocall_print_long(n);
	switch(n){
		case 57: //fork
			ret = enclave_fork();
			break;
		case 58: //vfork
			ret = enclave_vfork();
			break;


        }
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	unsigned long ret;
	/*ocall_print_long(n);
			ocall_print_long(a1);*/
	switch( n ){
		case 3: //close
			ret = enclave_close(a1);
			break;
		case 124: // getsid
			ret = enclave_getsid(a1);
			break;
		case 231: //exit_group
			ret = enclave_exit_group(a1);
			break;
		case 80: //chdir
			ret =  enclave_chdir(a1);
			break;
		default:
			//ocall_print_string("not handled system call, the system call num is :");
			ocall_print_long(n);
			ocall_print_long(a1);
			__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	unsigned long ret;
	struct timespec ts;
	struct timespec tsend;
	struct timespec tres;
	/*ocall_print_long(n);
			ocall_print_long(a1);
			ocall_print_long(a2);	*/
	switch( n ){
		
		case 4: //stat
			ret = enclave_stat(a1, a2);
			break;
	
		case 5: //fstat
			ret = enclave_fstat(a1, a2);
			break;

		case 2: //open
			ret = enclave_open2(a1, a2);
			break;

		case 33: //dup2
			ret = enclave_dup2(a1, a2);
			break;

		case 48: //shutdown
			ret =  enclave_shutdown(a1, a2);
			break;
		case 79: //getcwd
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_getcwd(a1, a2);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			
			
			break;

		case 228: //clock_gettime


			ret = enclave_clock_gettime(a1, a2);
			
			break;
		case 293: //pipe2
			ret = enclave_pipe2(a1, a2);
			break;
		default:
			ocall_print_long(n);
			ocall_print_long(a1);
			ocall_print_long(a2);
			__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
						  : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;

	/*ocall_print_long(n);
			ocall_print_long(a1);
			ocall_print_long(a2);
			ocall_print_long(a3);*/
	struct timespec ts;
	struct timespec tsend;
	struct timespec tres;
	switch( n ){
		case 0: // read
			ret = enclave_read(a1, a2, a3);
			break;
		case 1: //write
			ret = enclave_write(a1, a2, a3);
			break;	
		case 2: //open
clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_open(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			
		
			break;		
		
		case 8: //lseek
			ret = enclave_lseek(a1, a2, a3);
			break;
		case 16: //ioctl
			ret = enclave_ioctl(a1, a2, a3); //Simply don't perform syscall TODO: handle this
			break;
		case 19: //readv
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_readv(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			
			break;
		case 20: //writev
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_writev(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }
			ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			
			break;
		case 42: //connect
			ret = enclave_connect(a1, a2, a3);
			break;
		case 43: //accept
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_accept(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }
			ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			
			break;
		case 46: //sendmsg
			ret = enclave_sendmsg(a1, a2, a3);
			break;
		case 47: //recvmsg
			ret = enclave_recvmsg(a1, a2, a3);
			break;
		case 59: //execve
			ret = enclave_execve(a1, a2, a3);
			break;
		case 72: // fcntl
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_fcntl(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }
			ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			break;
		case 217://getdents64
			ret = enclave_getdents(a1, a2, a3);
			break;
		default:
			ocall_print_long(n);
			ocall_print_long(a1);
			ocall_print_long(a2);
			ocall_print_long(a3);

			__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
								  "d"(a3) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	/*ocall_print_long(n);
			ocall_print_long(a1);
			ocall_print_long(a2);
			ocall_print_long(a3);
			ocall_print_long(a4);	*/
	switch( n ){
		case 13: //rt_sigaction
			ret = 0; //Simply don't perform syscall TODO: handle this
			break;
		case 14: //rt_sigprocmask
			ret = 0; //Simply don't perform syscall TODO: handle this
			break;
		case 53: // socketpair
			ret = enclave_socketpair(a1, a2, a3, a4);
			break;
		case 61: //wait4
			ret = enclave_wait4(a1, a2, a3, a4);
			break;
		default:
			ocall_print_long(n);
			ocall_print_long(a1);
			ocall_print_long(a2);
			ocall_print_long(a3);
			ocall_print_long(a4);
			__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10): "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	/*ocall_print_long(n);
		ocall_print_long(a1);
		ocall_print_long(a2);
		ocall_print_long(a3);
		ocall_print_long(a4);
		ocall_print_long(a5);	*/
	struct timespec ts;

	switch(n){
	
		case 0: // read
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_sec);
			ret = enclave_read(a1, a2, a3);
			break;
		case 55: //getsockopt
			ret = enclave_getsockopt(a1, a2, a3, a4, a5);
			break;


        default:
		ocall_print_long(n);
		ocall_print_long(a1);
		ocall_print_long(a2);
		ocall_print_long(a3);
		ocall_print_long(a4);
		ocall_print_long(a5);
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;
	/*ocall_print_long(n);
			ocall_print_long(a1);
			ocall_print_long(a2);
			ocall_print_long(a3);
			ocall_print_long(a4);
			ocall_print_long(a5);
			ocall_print_long(a6);	*/
	//struct timespec ts;
	struct timespec ts;
	struct timespec tsend;
	struct timespec tres;
	switch(n){
		case 0: // read
			
			//clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_sec);
			ret = enclave_read(a1, a2, a3);
			break;
		case 2: //open
			//clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_sec);
			ret = enclave_open(a1, a2, a3);
			break;
		case 3: //close
			ret = enclave_close(a1);
			break;
		case 7: //POLL
			ret = enclave_poll(a1, a2, a3);
			break;
		case 9: //mmap
			ret = enclave_mmap(a1, a2, a3, a4, a5, a6);
			break;
		case 23: //select
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_select(a1, a2, a3, a4, a5);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }
ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			break;
		case 35: //nanosleep
			ret = enclave_nanosleep(a1, a2);
			break;
		case 41: //socket
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_socket(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }
ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			
			break;
		case 43: //accept

					clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_accept(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }

	ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);		
			break;
		case 44: //sendto
			ret = enclave_sendto(a1, a2, a3, a4, a5, a6);
			break;
		case 45: //recvfrom
			ret = enclave_recvfrom(a1, a2, a3, a4, a5, a6);
			break;
		case 49: //bind
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_bind(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }

		ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			break;
		case 50: //listen
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_listen(a1, a2);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }

		ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);	
			break;
		case 51: //getsockname
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_getsockname(a1, a2, a3);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }
ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			break;
		case 52: //getpeername
			ret = encalve_getpeername(a1, a2, a3);
			break;
		case 54: //setsockopt
			clock_gettime(CLOCK_REALTIME, &ts);
			//ocall_print_time(n, ts.tv_nsec);
			ret = enclave_setsockopt(a1, a2, a3, a4, a5);
			clock_gettime(CLOCK_REALTIME, &tsend);
			//ocall_print_timeend(n, tsend.tv_nsec);
			if ((tsend.tv_nsec - ts.tv_nsec) < 0) {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec - 1;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec + 1000000000;
    } else {
        tres.tv_sec = tsend.tv_sec - ts.tv_sec;
        tres.tv_nsec = tsend.tv_nsec - ts.tv_nsec;
    }
		ocall_print_timeres(n, tres.tv_sec, tres.tv_nsec);
			break;

        default:
		ocall_print_long(n);
		ocall_print_long(a1);
		ocall_print_long(a2);
		ocall_print_long(a3);
		ocall_print_long(a4);
		ocall_print_long(a5);
		ocall_print_long(a6);
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
						  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
        }
	return ret;
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"
#define VDSO_GETCPU_SYM "__vdso_getcpu"
#define VDSO_GETCPU_VER "LINUX_2.6"
