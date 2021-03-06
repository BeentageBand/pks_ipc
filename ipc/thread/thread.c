#include "thread-internal.h"
#include "logger/logger.h"
#include "ipc/semaphore/semaphore.h"

static void thread_cbk_delete(union Thread * const obj);

static void thread_delete(union Thread * const obj);
static void thread_run(union Thread * const thread);
static void thread_wait(union Thread * const thread, IPC_Clock_T const wait_ms);
static void thread_ready(union Thread * const thread);
static void thread_join(union Thread * const thread, IPC_Clock_T const wait_ms);
static void thread_runnable(union Thread * const thread);

void thread_override(union Thread_Class * const clazz)
{
  clazz->Class.destroy = (Class_Delete_T) thread_delete;
  clazz->join = thread_join;
  clazz->wait = thread_wait;
  clazz->run = thread_run;
  clazz->ready = thread_ready;
  clazz->runnable = thread_runnable;
}

void thread_delete(union Thread * const thread)
{
  if(ThreadCbk_join_thread(thread->cbk, thread))
    {
      ThreadCbk_unregister_thread(thread->cbk, thread);
      thread->cbk = NULL;
    }
}

void thread_join(union Thread * const thread, IPC_Clock_T const wait_ms)
{
  ThreadCbk_join_thread(thread->cbk, thread);
}


void thread_run(union Thread * const thread)
{
  if(ThreadCbk_run_thread(thread->cbk, thread))
  {
      thread->ready = true;
  }
}

void thread_runnable(union Thread * const thread){}//Implements!

void thread_wait(union Thread * const thread, uint32_t const wait_ms)
{
  Barrier_wait(thread->barrier, wait_ms);
}

void thread_ready(union Thread * const thread)
{
  Barrier_ready(thread->barrier);
}

void Thread_populate(union Thread * const thread, union ThreadCbk * const cbk, IPC_TID_T const id, union Barrier * const barrier)
{
  Object_populate(&thread->Object, &Get_Thread_Class()->Class);
  thread->id = id;
  thread->cbk = cbk;
  thread->barrier = barrier;
  thread->ready = false;
  ThreadCbk_register_thread(thread->cbk, thread);
}
