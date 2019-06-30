/* Addition for musl-sgx */

extern void* sgx_ocalloc(unsigned long size);
extern void sgx_ocfree(void);

extern void ocall_print_string(const char *str);
extern void ocall_print_long(long l);

extern long ocall_write(unsigned long* ret, long fd, long buf, long len);
//extern long ocall_writev(unsigned long* ret, long fd, long buf, long len);
extern long ocall_writev(unsigned long* ret, long fd, long buf, long len);


