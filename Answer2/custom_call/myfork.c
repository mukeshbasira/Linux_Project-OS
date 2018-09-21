#include <linux/kernel.h>
#include <linux/sched/task.h>

asmlinkage int __x64_sys_myfork(void)
{

printk("my fork");
return _do_fork(SIGCHLD,0,0,NULL,NULL,0);
}


