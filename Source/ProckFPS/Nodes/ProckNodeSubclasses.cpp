#include "ProckFPS.h"

#include "Nodes/ProckNodeSubclasses.h"

#include "Utils/Config.h"
#include <queue>

// Line Utility Method
void Connect(ProckNode *from, ProckNode *to) {
	ALineActor* line = UConfig::world->SpawnActor<ALineActor>(UConfig::lineBPClass);
	line->From = from->box;
	line->To = to->box;
}

// Leaf Nodes
void Base_Spawn(ProckNode *n) {
	n->box = UConfig::world->SpawnActor<ABoxActor>(UConfig::boxBPClass);
	n->box->SetText(n->Name());
	n->box->SizeFitContents();
}

void Int_Spawn(PNInt *n) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
}

void Name_Spawn(PNName *n) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
}


// "Basic" Operators
void Assignment_Spawn(PNAssignment *n) {
	Base_Spawn(n);

	// Assignmnent doesnt have its own box; hide it
	n->box->GetRootComponent()->SetVisibility(false, true);

	n->Target()->Spawn(n, FVector(BOX_X_OFFSET, 0, 0));
	n->Value()->Spawn(n, FVector(-BOX_X_OFFSET, 0, 0));

	Connect(n->Value(), n->Target());
}

void BinaryOperator_Spawn(PNBinaryOperator *n) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
	n->box->SizeFitContents();

	n->First()->Spawn(n, FVector(-BOX_X_OFFSET, 0, BOX_Z_OFFSET));
	n->Second()->Spawn(n, FVector(-BOX_X_OFFSET, 0, -BOX_Z_OFFSET));

	Connect(n->First(), n);
	Connect(n->Second(), n);
}


// Collections of Nodes
void List_Spawn(PNList *n) {
	FVector curr, origin, extent;
	float currOffset = 0.f;

	for (ProckNode *child : *n->NodeList()) {
		if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
			continue;
		}

		child->Spawn(n, FVector(0, 0, 0));
		child->box->GetActorBounds(false, origin, extent);

		currOffset += extent.X + FRAME_X_OFFSET;
		child->box->SetActorRelativeLocation(FVector(currOffset, extent.Y, extent.Z + FRAME_Z_OFFSET));

		// Set the new box as the next line of code, which connects it to the scope
		//n->Scope->DrawScopeInBox();
		//n->Scope->SetNextLine(child->box);
	};
}

// This function switches on the type of the passed node and invokes a respective _Spawn function if one exists, 
// else calls Base_Spawn. Each type check here is basically the implementation of another node "drawing" type.
// When creating new _Spawn methods, please give them the same name as the node being targeted
//
// Note that this design intentionally allows for a single _Spawn method to handle multiple node types.
//
// Attaches to the passed node at the relative position. Root nodes are passed null and 0 as params. 
void ProckNode::Spawn(ProckNode *node, FVector pos) {
	switch (Type()) {

	// Leaf Nodes
	case PNT_Name:				Name_Spawn((PNName *) this); break;  
	case PNT_Int:				Int_Spawn((PNInt *) this); break; 

	// Basic Operators
	case PNT_Assignment:		Assignment_Spawn((PNAssignment *) this); break; 
	case PNT_BinaryOperator:	BinaryOperator_Spawn((PNBinaryOperator *) this); break; 

	// Collections
	case PNT_List:				List_Spawn((PNList *) this); break; 

	// Basic box
	default:					Base_Spawn(this); break; 
	}

	// NOTE: Because this happens after each box calls "spawn" the position of the box changes after the method is updated the original "SetLine" doesn't work well
	// Need to do another pass or find a better way of attaching the spline

	// Check the box for existence since name nodes dont spawn anything
	if (node && box) {
		box->AttachToActor(node->box, FAttachmentTransformRules::SnapToTargetIncludingScale);
		box->SetActorRelativeLocation(pos);
	}
}
