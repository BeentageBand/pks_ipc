define $(_flavor_)_$(_feat_)_MAKE

$(_flavor_)_$(_feat_)_inc=\
conditional.h \
ipc.h \
ipc_types.h \
ipc_helper.h \
ipc_posix.h \
mail.h \
mail_payload.h \
mailbox.h \
mutex.h \
publisher.h \
sem.h \
thread.h \
uptime.h \
worker.h \
worker_evs.h \

$(_flavor_)_$(_feat_)_lib_objs=\
conditional \
ipc \
ipc_helper \
ipc_posix \
mail \
mail_payload \
mailbox \
mutex \
publisher \
semaphore \
thread \
uptime \
worker \

$(_flavor_)_$(_feat_)_lib=ipc

endef

include $(PROJ_MAK_DIR)/epilog.mk
