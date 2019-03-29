#include "DebugInformation.h"

DebugInformation & DebugInformation::getInstance()
{
	static DebugInformation object;
	return object;
}

void DebugInformation::clear()
{
	renderedEntitiesCounter = 0;
	updatedEntitiesCounter = 0;
}
