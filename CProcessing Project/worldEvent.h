#pragma once
#include "cprocessing.h"
#include "linkedlist.h"
// The type of event, it gives the event node the type of event that should occur when activated
typedef enum EventType {
	START, // This is the starter for event types, it is not an event type.
	       // Put 0 for event type attribute in event chain file to randomize to a non-special event.
	// Non-special events
	BATTLE,
	ITEM,
	SHOP,
	NON_SPECIAL_TYPE_END, // This is a non-special type ender, it is not an event type and
	//-----------------// // is used to count the numbe of non-special events
	// Special events
	MIDBOSS_BATTLE = 11,
	BOSS_BATTLE
} EventType;

// The node for events
typedef struct EventNode {
	int id;
	EventType type;
	CP_Vector location;
	CP_Vector bound;
	LinkedList next_nodes;
} EventNode;

typedef struct EventTypeMap {
	EventType type;
	int number;
} EventTypeMap;