#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;


  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}


#ifdef LAB_PGTBL
int
sys_pgaccess(void)
{
  // lab pgtbl: your code here.
  uint64 p1,p2;
  int n; 
  argint(1, &n);//LEN
  if (n>63)
  return -1;//upbound for len.
  if (myproc()->pgaccess_flag==0)
  {
    myproc()->pgaccess_flag=1;
    argaddr(0,&p1);//UVA
    argaddr(2, &p2);//UVA
    pagetable_t pagetable = myproc()->pagetable;
    pagetable_t pagetable1;
    for (int i = 0; i < n; i++)
    {
      uint64 va = PGROUNDDOWN(p1+i*PGSIZE);
        if(va >= MAXVA)
        panic("pgaccess fail");
        pte_t *pte=&pagetable[PX(2,va)];
        if(*pte & PTE_V){
        pagetable1=(pagetable_t)PTE2PA(*pte);pte=&pagetable1[PX(1,va)];
        }else{
        panic("pgaccess fail");}       
        if (*pte & PTE_V){
        pagetable1=(pagetable_t)PTE2PA(*pte);pte=&pagetable1[PX(0,va)];
        }else{
        panic("pgaccess fail");}
        if((*pte&PTE_V)&&(*pte&PTE_A))
        {*pte &= ~PTE_A;}
    }
    return 0;
  }else if (myproc()->pgaccess_flag==1)
  {
    uint64 temp=0;
    argaddr(0,&p1);//UVA
    
    argaddr(2, &p2);//UVA
    pagetable_t pagetable = myproc()->pagetable;
    pagetable_t pagetable1;
    for (int i = 0; i < n; i++)
    {
      uint64 va = PGROUNDDOWN(p1+i*PGSIZE);
        if(va >= MAXVA)
        panic("pgaccess fail");
        pte_t *pte=&pagetable[PX(2,va)];
        if(*pte & PTE_V){
        pagetable1=(pagetable_t)PTE2PA(*pte);pte=&pagetable1[PX(1,va)];
        }else{
        panic("pgaccess fail");}       
        if (*pte & PTE_V){
        pagetable1=(pagetable_t)PTE2PA(*pte);pte=&pagetable1[PX(0,va)];
        }else{
        panic("pgaccess fail");}
        if((*pte&PTE_V)&&(*pte&PTE_A))
        {temp=temp|(1<<(i));*pte &= ~PTE_A;}
    }
    if(copyout(pagetable, p2, (char *)&temp, sizeof(temp)) < 0)
    return -1;

    return 0;
  }
  else{
    panic("pgaccess fail");
  }
  return 0; //never down here
}
#endif

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
