/*=====================================================================================*/
/**
 * mailbox.cpp
 * author : puch
 * date : Oct 22 2015
 *
 * description : Any comments
 *
 */
/*=====================================================================================*/
#define CLASS_IMPLEMENTATION
/*=====================================================================================*
 * Project Includes
 *=====================================================================================*/
#include "publisher.h"
#include "mailbox.h"
/*=====================================================================================* 
 * Standard Includes
 *=====================================================================================*/

/*=====================================================================================* 
 * Local X-Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Define Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Type Definitions
 *=====================================================================================*/
 
/*=====================================================================================* 
 * Local Function Prototypes
 *=====================================================================================*/
static void Mailbox_Ctor(Mailbox_T * const this, IPC_Task_Id_T const owner, uint32_t const mail_elems, size_t const data_size);
/*=====================================================================================* 
 * Local Object Definitions
 *=====================================================================================*/
CLASS_DEFINITION
/*=====================================================================================* 
 * Exported Object Definitions
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Inline-Function Like Macros
 *=====================================================================================*/

/*=====================================================================================* 
 * Local Function Definitions
 *=====================================================================================*/
void Mailbox_init(void)
{
   printf("%s \n", __FUNCTION__);
   Mailbox_Obj.owner = 0;
   Mailbox_Obj.mailbox = NULL;
   Mailbox_Obj.data_size = 0;

   Mailbox_Vtbl.Object.rtti = &Mailbox_Rtti;
   Mailbox_Vtbl.Object.destroy = Mailbox_Dtor;
   Mailbox_Vtbl.ctor = Mailbox_Ctor;
   Mailbox_Vtbl.subscribe = NULL;
   Mailbox_Vtbl.unsubscribe = NULL;
   Mailbox_Vtbl.push_mail = NULL;
   Mailbox_Vtbl.pop_mail= NULL;
   Mailbox_Vtbl.dump = NULL;
   Mailbox_Vtbl.get_mail_by_mail_id = NULL;
   Mailbox_Vtbl.get_first_mail = NULL;

}
void Mailbox_shut(void) {}

void Mailbox_Dtor(Object_T * const obj)
{
   Mailbox_T * this = _dynamic_cast(Mailbox, obj);
   _delete(this->mailbox);
}

/*=====================================================================================* 
 * Exported Function Definitions
 *=====================================================================================*/
void Mailbox_Ctor(Mailbox_T * const this, IPC_Task_Id_T const owner, uint32_t const mail_elems, size_t const data_size)
{
   this->owner = owner;
   this->mailbox = Vector_Mail_new();
   Isnt_Nullptr(this->mailbox,);
   this->mailbox->vtbl->reserve(this->mailbox, mail_elems);
   this->data_size = data_size;
}
/*=====================================================================================* 
 * mailbox.cpp
 *=====================================================================================*
 * Log History
 *
 *=====================================================================================*/
