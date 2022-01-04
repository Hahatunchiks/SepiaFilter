#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


int main(void) {
    struct rusage r;
    struct timeval start;
    struct timeval end;
    getrusage( RUSAGE_SELF, &r );
    start = r.ru_utime;
    for( uint64_t i = 0; i < 100; i++ )
        system( "./build/main ./photo/copy.bmp ./photo/out.bmp 0" );
    getrusage( RUSAGE_SELF, &r );
    end = r.ru_utime;
    long res = ( ( end.tv_sec - start.tv_sec ) * 1000000L ) + end.tv_usec - start.tv_usec;
    printf( "C impl: Time elapsed in microseconds: %ld\n", res );

    getrusage( RUSAGE_SELF, &r );
    start = r.ru_utime;
    for( uint64_t i = 0; i < 100; i++ )
        system( "./build/main ./photo/copy.bmp ./photo/out.bmp 1" );
    getrusage( RUSAGE_SELF, &r );
    end = r.ru_utime;
    res = ( ( end.tv_sec - start.tv_sec ) * 1000000L ) + end.tv_usec - start.tv_usec;
    printf( "SIMD impl: Time elapsed in microseconds: %ld\n", res );

    return 0;
}