// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "ProckNode.h"

ProckNode::ProckNode() {
	resolved = false;
	children = {};
	type = PNT_Unresolved;
}

ProckNode::~ProckNode() {
	children = {};
	type = PNT_Unresolved;
	parent = nullptr;
}

void ProckNode::print(char *subclass) {
	char *val = "null\0";
	char *typ;

	//if (value != nullptr) {
	//	val = value;
	//}

	// Make the types human readable
	switch (type) {
	case PNT_Root:
		typ = "PNT_Root\0";
		break;
	case PNT_Assignment:
		typ = "PNT_Assignment\0";
		break;
	case PNT_Addition:
		typ = "PNT_Addition\0";
		break;
	case PNT_Unknown:
		typ = "PNT_Unknown\0";
		break;
	case PNT_Unresolved:
		typ = "PNT_Unresolved\0";
		break;
	default:
		typ = "PNT_Unknown\0";
		break;
	}

	// Note that you must have null terminated strings here
	UE_LOG(LogProck, Log, TEXT("%s: Type: %s, Value: %s, Children: %d"), UTF8_TO_TCHAR(subclass), UTF8_TO_TCHAR(typ), UTF8_TO_TCHAR(val), children.size());
}