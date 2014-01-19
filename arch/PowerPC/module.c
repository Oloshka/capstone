/* Capstone Disassembler Engine */
/* By Nguyen Anh Quynh <aquynh@gmail.com>, 2013 */

#include "../../utils.h"
#include "../../MCRegisterInfo.h"
#include "PPCDisassembler.h"
#include "PPCInstPrinter.h"
#include "mapping.h"

void enable_powerpc() {};

static cs_err init(cs_struct *ud)
{
	MCRegisterInfo *mri = cs_mem_malloc(sizeof(*mri));

	PPC_init(mri);
	ud->printer = PPC_printInst;
	ud->printer_info = mri;
	ud->getinsn_info = mri;
	ud->disasm = PPC_getInstruction;
	ud->post_printer = PPC_post_printer;

	ud->reg_name = PPC_reg_name;
	ud->insn_id = PPC_get_insn_id;
	ud->insn_name = PPC_insn_name;

	return CS_ERR_OK;
}

static cs_err option(cs_struct *handle, cs_opt_type type, size_t value)
{
	if (type == CS_OPT_SYNTAX)
		handle->syntax = value;

	return CS_ERR_OK;
}

static void destroy(cs_struct *handle)
{
}

void PPC_enable(void)
{
	arch_init[CS_ARCH_PPC] = init;
	arch_option[CS_ARCH_PPC] = option;
	arch_destroy[CS_ARCH_PPC] = destroy;

	// support this arch
	all_arch |= (1 << CS_ARCH_PPC);
}
