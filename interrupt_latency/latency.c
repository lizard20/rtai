/*
	Name:
		latency.c
	Type:
		Module
	Description:
		Install ISR to measure interrupt latency.
		An external  interrupt signal  is connected to parallel
		port (pin 10). Then we get the response in pin 2.
	Author:
		Aldo Núñez Tovar	
	License:
		GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
*/

#include <linux/module.h>
#include <linux/init.h>
#include <rtai.h>

#define IRQ 7				 	/* Parallel port interrupt number */
#define BASEPORT 0x378			/* Parallel port address */
#define CONT_MAX 10000

MODULE_AUTHOR ( "Aldo Núñez Tovar" );
MODULE_LICENSE ( "GPL"  );
MODULE_DESCRIPTION ( "Measuring latency" );

/* Function prototypes */
static int __init insert_module ( void );
static void __exit remove_module ( void );
static void isr_handler ( void ); 

unsigned int i = 0;

/* Interrupt handler */
static void
isr_handler ( void )
{
	outb ( 0x1, BASEPORT );
	for ( i = 0; i < CONT_MAX; i++ );
	outb ( 0x0, BASEPORT );

	rt_ack_irq ( IRQ );
}

/* Entry point */
static int __init
insert_module ( void )
{
	if ( rt_request_global_irq ( IRQ,  isr_handler ) ) 
	{
		printk ( ":( Fail interrupt request \n" );	
		return -EINVAL;	
	}

	/* Enable irq - 0001 0000 ~ 0x10 */
	outb ( 0x10, BASEPORT + 2 ); 
	rt_enable_irq ( IRQ );

	return 0;
}

/* Exit point */
static void __exit
remove_module ( void )
{
	/* Clean output */
	outb ( 0x0, BASEPORT );
	
	rt_disable_irq ( IRQ );
	rt_free_global_irq ( IRQ );
}

module_init ( insert_module );
module_exit ( remove_module );
