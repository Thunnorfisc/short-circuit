/*
* @author	William Wibisana Dumnanauw (williamwibisana.d)
* @brief	The file contains individual event related structs and enums
* @file		worldEvent.h
* All content © 2024 DigiPen Institute of Technology Singapore, all rights reserved.
*/
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
	//-----------------// // is used to count the number of non-special events
	// Special events
	SPECIAL_START = 10,
	MIDBOSS_BATTLE,
	BOSS_BATTLE,
	STARTING_NODE,
	SPECIAL_END
} EventType;

/*!
* @struct This is an individual Event Node
* @brief This struct is designed to be one event node
* @param id				int				The identifier for the node
* @param type			EventType		The type of event the node has
* @param location		CP_Vector		The x and y coordinates of it's actual location on screen
* @param bound			CP_Vector		The x and y bound the node is located in
* @param event_sprite	CP_Vector		The sprite used for the event, depending on type
* @param next_nodes		LinkedList		The list of IDs of nodes connected to this node
*										on the next x bound
*/
typedef struct EventNode {
	int id;
	EventType type;
	CP_Vector location;
	CP_Vector bound;
	CP_Image event_sprite;
	LinkedList next_nodes;
} EventNode;

/*!
* @struct This is an Event Type Map
* @brief This struct is for making sure the number of events are balanced in the world map
* @param type			EventType		The type of event
* @param number			int				The number of event allowed for each type
*/
typedef struct EventTypeMap {
	EventType type;
	int number;
} EventTypeMap;