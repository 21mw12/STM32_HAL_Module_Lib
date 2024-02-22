#include "TIMSoft.h"

void TIMSoft_SetTimeOut(sTimerSoft* pTimer, uint32_t Timeout) {
	pTimer->timeout = HAL_GetTick() + Timeout;
}

void TIMSoft_Check(sTimerSoft pTimer) {
	if (pTimer.timeout <= HAL_GetTick()) {
		pTimer.func(pTimer.args);
	}
}

void TIMSoft_Clear(sTimerSoft* pTimer) {
	pTimer->timeout = UINT32_MAX;
}
