#include "InsuranceService.h"
#include "CMMStack.h"


namespace AI
{
	void InsuranceService()
	{
		LM_DECL_START(InsuranceService_DataControl);
		LM_ADD_BUTTON("Назад", []() {LM_ID(InsuranceService_DataControl)->reset(); Menu::popStack(); });
		LM_DECL_END;
	}
}

