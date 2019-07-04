#if defined(__cplusplus)
extern "C" {
#endif
#include <stdio.h>
#include <errno.h>
#include <stdlib.h> 

#include <stddef.h>

#include <locale.h>

#include <string.h>
#include <time.h>
//#include <localeinfo.h>

void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}


unsigned long ocall_syscall0(long n)
{
	unsigned long ret;
	//printf("The enclave tried to perform syscall %ld: %ld\n", n, a1);
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	//printf("Syscall result: %ld\n", ret);
	return ret;
}


unsigned long ocall_syscall1(long n, long a1)
{
	unsigned long ret;
	//printf("The enclave tried to perform syscall %ld: %ld\n", n, a1);
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	//printf("Syscall result: %ld\n", ret);
	return ret;
}

unsigned long ocall_syscall2(long n, long a1, long a2)
{
	unsigned long ret;
	struct timespec ts;
	struct timespec tsend;
	struct timespec tres;

	clock_gettime(CLOCK_REALTIME, &ts);
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
						  : "rcx", "r11", "memory");

	clock_gettime(CLOCK_REALTIME, &tsend);
		timespec_diff(&ts, &tsend, &tres);
		printf("native The enclave tried to perform syscall %ld: %d seconds %d nano seconds \n", n, tres.tv_sec, tres.tv_nsec);
	//printf("The enclave tried to perform syscall %ld: %ld, %ld\n", n, a1, a2);
	//printf("Syscall result: %ld\n", ret);
	//printf("Errno value: %s\n", strerror(errno));
	return ret;
}

unsigned long ocall_syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;
	struct timespec ts;
	struct timespec tsend;
	struct timespec tres;

	//if(n==19|| n ==20 || n==41 || n == 42 || n==43 || n== 49 || n==23 || n ==55 || n == 72){
		clock_gettime(CLOCK_REALTIME, &ts);
 
       // }
	
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
                                                  "d"(a3) : "rcx", "r11", "memory");

	//if(n==19|| n ==20 || n==41 || n == 42 || n==43 || n== 49 || n==23 || n ==55 || n == 72){
		clock_gettime(CLOCK_REALTIME, &tsend);
		timespec_diff(&ts, &tsend, &tres);
		printf("native The enclave tried to perform syscall %ld: %d seconds %d nano seconds \n", n, tres.tv_sec, tres.tv_nsec);
 
      //  }
	
	//printf("The enclave tried to perform syscall %ld: %ld, %ld, %ld\n", n, a1, a2, a3);
	//printf("Syscall result: %ld\n", ret);
	//printf("Errno value: %s\n", strerror(errno));
	return ret;
}

unsigned long ocall_syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;
	//printf("The enclave tried to perform syscall %ld: %ld, %ld, %ld, %ld\n", n, a1, a2, a3, a4);
	register long r10 __asm__("r10") = a4;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
                                                  "d"(a3), "r"(r10) : "rcx", "r11", "memory");
	//printf("Syscall result: %ld\n", ret);
	//printf("Errno value: %s\n", strerror(errno));
	return ret;
}

extern long __clone(long a1, long a2, long a3, long a4);
unsigned long ocall_syscallclone(long a1, long a2, long a3, long a4)
{
	unsigned long ret;
	//printf("The enclave tried to perform syscall %ld: %ld, %ld, %ld, %ld\n", n, a1, a2, a3, a4);
	/*register long r10 __asm__("r10") = a4;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
                                                  "d"(a3), "r"(r10) : "rcx", "r11", "memory");*/
	ret = __clone(a1, a2, a3, a4);
	printf("Syscall result: %ld\n", ret);
	printf("Errno value: %s\n", strerror(errno));
	return ret;
}

unsigned long ocall_syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;
	//printf("The enclave tried to perform syscall %ld: %ld, %ld, %ld, %ld, %ld\n", n, a1, a2, a3, a4, a5);
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
                                                  "d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
	//printf("Syscall result: %ld\n", ret);
	return ret;
}

unsigned long ocall_syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;
	//printf("The enclave tried to perform syscall %ld: %ld, %ld, %ld, %ld, %ld, %ld\n", n, a1, a2, a3, a4, a5, a6);
	register long r10 __asm__("r10") = a4;
	register long r8 __asm__("r8") = a5;
	register long r9 __asm__("r9") = a6;
	__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
                                                  "d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
	//printf("Syscall result: %ld\n", ret);
	return ret;
}

void* ocall_malloc(int len)
{
    void* ret;
    ret = malloc(len);
    return ret;

}

void ocall_free(unsigned char* str)
{
      free(str);
}


#if defined(__cplusplus)
}
#endif
