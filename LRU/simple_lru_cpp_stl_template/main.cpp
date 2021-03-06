#include "lru.hpp"

#define HEAP_CAPACITY 1000000
#define CACHE_SIZE 100000
#define MAX_THREADS 10

void * refThread(void *arg) {
    unsigned long key,i;
    //pid_t tid = syscall(__NR_gettid);
    cache<unsigned long, string> *c = static_cast<cache<unsigned long, string> *>(arg);
    srandom((unsigned long)time(NULL));
    for (i=0; i<HEAP_CAPACITY; i++) {
        key = random()%HEAP_CAPACITY;
        c->refereCache(key);
    }
    return NULL;
}



int main(void) {
    unsigned long ret,i;

    cache<unsigned long, string> *c = new cache<unsigned long, string>(HEAP_CAPACITY, CACHE_SIZE);
    pthread_t refThr[MAX_THREADS];

    for (i=0; i<MAX_THREADS; i++) {
        ret = pthread_create(&refThr[i], NULL, refThread, c);
        if (ret != 0) {
            cout << endl << "Thread create failed." << endl;
            return -1;
        }
    }
    for (i=0; i<MAX_THREADS; i++)
        pthread_join(refThr[i], NULL);
    return 0;
}
