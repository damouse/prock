#include "ProckFPS.h"

#include "Nodes/ProckNodeSubclasses.h"
#include "Actors/ScopeActor.h"
#include "Actors/GhostActor.h"
#include "Actors/PathSegmentComponent.h"

#include "Utils/Config.h"
#include <queue>

// Parallel splines
//https://answers.unrealengine.com/questions/319813/parallel-splines.html

// Leaf Nodes
void Base_Spawn(ProckNode *n) {
	n->box = UConfig::world->SpawnActor<ABoxActor>(UConfig::boxBPClass);
	n->box->SetText(n->Name());
	n->box->SizeFitContents();
}

void Int_Spawn(PNInt *n, TArray<AGhostActor*> ghosts) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
}

void Name_Spawn(PNName *n, TArray<AGhostActor*> ghosts) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
}


// "Basic" Operators
void Assignment_Spawn(PNAssignment *n, TArray<AGhostActor*> ghosts) {
	Base_Spawn(n);

	// Assignmnent doesnt have its own box; hide it
	n->box->GetRootComponent()->SetVisibility(false, true);

	// Draw the pathline
	APathSegment* segment = UConfig::world->SpawnActor<APathSegment>(UConfig::segmentBPClass);
	segment->InitializeSegment(n->box, n->box, true, false, ghosts);
	n->box->PathSegments.Add(segment);

	n->Target()->Spawn(n, FVector(BOX_X_OFFSET, 0, -BOX_X_OFFSET), ghosts);
	n->Value()->Spawn(n, FVector(-BOX_X_OFFSET, 0, 0), ghosts);

	// onnect the Target box with its own pathline
	APathSegment* outgoing = UConfig::world->SpawnActor<APathSegment>(UConfig::segmentBPClass);
	outgoing->InitializeSegment(n->Target()->box, n->box, false, false, TArray<AGhostActor*>());
	n->box->PathSegments.Add(outgoing);

	// Merge the ghost into tthe array and return them all

	//n->Scope->Connect(n->Value(), n->Target());

	// Resize this box to fit its nested nodes
	n->box->NeedsRedraw();
}

void BinaryOperator_Spawn(PNBinaryOperator *n, TArray<AGhostActor*> ghosts) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
	n->box->SizeFitContents();

	n->First()->Spawn(n, FVector(-BOX_X_OFFSET, 0, BOX_Z_OFFSET), ghosts);
	n->Second()->Spawn(n, FVector(-BOX_X_OFFSET, 0, -BOX_Z_OFFSET), ghosts);

	//n->Scope->Connect(n->First(), n);
	//n->Scope->Connect(n->Second(), n);
}


// Collections of Nodes
void List_Spawn(PNList *n, TArray<AGhostActor*> ghosts) {
	FVector curr, origin, extent;
	float currOffset = 0.f;
	
	// Create a new scope blueprint actor and assign it both to this node and this box.
	// TODO: may not need both circular references
	//n->Scope = UConfig::world->SpawnActor<AScopeActor>(UConfig::scopeBPClass);
	//n->Scope->Root = n;
	//n->Scope->AttachToActor(n->box, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//n->Scope->SetActorRelativeLocation(FVector(0, 0, 0));

	//n->box->scope = n->Scope;

	for (ProckNode *child : *n->NodeList()) {
		if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
			continue;
		}

		child->Spawn(n, FVector(0, 0, 0), ghosts);
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
void ProckNode::Spawn(ProckNode *node, FVector pos, TArray<AGhostActor*> ghosts) {
	switch (Type()) {

	// Leaf Nodes
	case PNT_Name:				Name_Spawn((PNName *) this, ghosts); break;  
	case PNT_Int:				Int_Spawn((PNInt *) this, ghosts); break; 

	// Basic Operators
	case PNT_Assignment:		Assignment_Spawn((PNAssignment *) this, ghosts); break; 
	case PNT_BinaryOperator:	BinaryOperator_Spawn((PNBinaryOperator *) this, ghosts); break; 

	// Collections
	case PNT_List:				List_Spawn((PNList *) this, ghosts); break; 

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
