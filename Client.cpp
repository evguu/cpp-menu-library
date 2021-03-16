#include "Client.h"
#include "CMMStack.h"

namespace AI
{
	void Client()
	{
		LM_DECL_START(Client_DataControl);
		LM_ADD_BUTTON("Назад", []() {LM_ID(Client_DataControl)->reset(); Menu::popStack(); });
		LM_DECL_END;
	}
}
