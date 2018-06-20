#include  <cpu.h>
#include  <lib_mem.h>
#include  <os.h>

#include  "app_cfg.h"
#include  "loader.h"

int  main(void)
{
	CPU_IntInit();

	Mem_Init();                                                 /* Initialize Memory Managment Module                   */
	CPU_IntDis();                                               /* Disable all Interrupts                               */
	CPU_Init();                                                 /* Initialize the uC/CPU services                       */

	OSInit();                                                   /* Initialize uC/OS-II                                  */

	if (MenuLoader() != 0)
		return 1;

	OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)   */

	while (DEF_ON) {                                            /* Should Never Get Here.                               */
		;
	}
	return 0;
}
