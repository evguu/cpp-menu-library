#include "Choice.h"

const string Choice::noChoicesFoundMessage = "LML_RESERVED_MESSAGE::NO_CHOICES_FOUND";


clock_t _lastClock = 0;
bool _wasPreviousDirectionRight = false;
int _timeCounter = 0;
const int _maximalComboInterval = 200;
const int _maxTrueSpeed = 64;
const int _doublingTime = 3000;

void Choice::processKeyEvent(KeyEvent keyEvent)
{
	if (keyEvent.isLeftRight())
	{
		bool isRight = (keyEvent.code == KC_RIGHT);
		if (options.size() > 1)
		{
			int timeElapsed = (long)(((double)clock() - _lastClock) / CLOCKS_PER_SEC * 1000);
			if ((timeElapsed < _maximalComboInterval) && !(_wasPreviousDirectionRight^isRight))
			{
				_timeCounter += timeElapsed;
			}
			else
			{
				_timeCounter = 0;
				_wasPreviousDirectionRight = isRight;
			}
			int trueSpeed = 1 << (2 * _timeCounter / _doublingTime);
			if (trueSpeed > _maxTrueSpeed)
			{
				trueSpeed = _maxTrueSpeed;
			}
			activeOption = (options.size() + (isRight ? (1) : (-1)) * trueSpeed + activeOption) % options.size();
		}
		_lastClock = clock();
	}
}

