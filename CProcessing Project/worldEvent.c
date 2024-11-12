#include "worldEvent.h"

EventNode Event_Initialize(int id, EventType type, float location_x, float location_y, float bound_x, float bound_y)
{
	EventNode event;
	event.id = id;
	event.type = type;
	event.location = CP_Vector_Set(location_x, location_y);
	event.bound = CP_Vector_Set(bound_x, bound_y);
	return event;
}
