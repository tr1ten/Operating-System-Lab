from threading import *
import random
import time
readcnt = 0
mutex = Semaphore()
wrt = Semaphore()
def reader():
    global readcnt
    mutex.acquire()
    readcnt+=1
    if(readcnt==1):
      wrt.acquire()
    mutex.release()

    print("reader is reading!...")
    time.sleep(1)

    mutex.acquire()
    readcnt-=1
    if(readcnt==0):
       wrt.release()
    mutex.release()


def writer():
   
   wrt.acquire()
   print("writer is acquiring lock...")
   
   print("writer is writing!...")
   time.sleep(2)
   print("writer is releasing lock...")
   wrt.release()



if __name__ == "__main__":
   
   for i in range(1,3):
     rand = random.randint(1,100)
     if(rand >50):
        thread1 = Thread(target = reader)
        thread1.start()
     else:
        thread2 = Thread(target=writer)
        thread2.start()
   thread1.join()
   thread2.join()