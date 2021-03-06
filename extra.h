#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#define gettid() syscall(SYS_gettid)
#define Fstat(fd, sbuf)         assert(fstat(fd,sbuf) >= 0)

int Open(char *file, int flags){
    int fd = open(file, flags);
    assert(fd >= 0);
    return fd;
}

double GetTime() {
    struct timeval t;
    int rc = gettimeofday(&t, NULL);
    assert(rc == 0);
    return (double) t.tv_sec + (double) t.tv_usec/1e6;
}


void Spin(int howlong) {
    double t = GetTime();
    while ((GetTime() - t) < (double) howlong)
	;
}

void* Malloc(size_t size){
    void *ptr = malloc(size);
    assert(ptr != NULL);
    return ptr;
}

void* Calloc(size_t num, size_t size){
    void *ptr = calloc(num, size);
    assert(ptr != NULL);
    return ptr;
}
