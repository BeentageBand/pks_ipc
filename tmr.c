#include "tmr.h"
#include "ipc.h"
#include "ipc_helper.h"

static void timer_delete(struct Object * const obj);
static void timer_start(union Timer * const);
static void timer_set_time(union Timer * const, IPC_Clock_T const, bool const);
static void timer_reset(union Timer * const);
static void timer_stop(union Timer * const);
static void timer_on_tout(union Timer * const);

static union Timer Timer = {NULL};

struct Timer_Class Timer_Class = 
{
    {timer_delete, NULL},
    timer_start,
    timer_set_time,
    timer_reset,
    timer_stop,
    timer_on_tout
}Timer_Class_T;

void timer_delete(struct Object * const obj)
{
    union Timer * const this = (union Timer *)Object_Cast(&Timer_Class, obj);
    Isnt_Nullptr(this,);
    this->vtbl->stop(this);
    ipc_helper->vtbl->free_timer(ipc_helper, this);
}

void timer_start(union Timer * const this)
{
  if(this->is_active)
  {
    IPC_Helper_T * ipc_helper = IPC_get_instance();
    Isnt_Nullptr(ipc_helper,);
    ipc_helper->vtbl->run_timer(ipc_helper, this);
    this->is_active = true;
  }
}

void timer_set_time(union Timer * const this, IPC_Clock_T const tout_ms, bool const is_periodic)
{
    this->is_periodic = is_periodic;
    this->tout_ms = tout_ms;
}

void timer_reset(union Timer * const this)
{
  IPC_Helper_T * ipc_helper = IPC_get_instance();
  Isnt_Nullptr(ipc_helper,);
  ipc_helper->vtbl->run_timer(ipc_helper, this);
}

void timer_stop(union Timer * const this)
{
  IPC_Helper_T * ipc_helper = IPC_get_instance();
  Isnt_Nullptr(ipc_helper,);
  ipc_helper->vtbl->stop_timer(ipc_helper, this);
  this->is_active = false;
}

void timer_on_tout(union Timer * const this)
{
    IPC_Send(this->mid, this->tid, NULL, 0);
}

void Populate_Timer(union Timer * const this, IPC_MID_T const mid)
{
    if(NULL == Timer.vtbl)
    {
        Timer.vtbl = &Timer_Class;
        Timer.is_periodic = false;
        Timer.mid = 0;
    }
    _clone(this, Timer);
    this->mid = mid;
    this->tid = IPC_Self();
    IPC_Helper_T * ipc_helper = IPC_get_instance();
    Isnt_Nullptr(ipc_helper,);
    ipc_helper->vtbl->alloc_timer(ipc_helper, this);
}