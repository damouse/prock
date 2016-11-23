#include "ProckFPS.h"
#include "Nodes/ProckNodeSubclasses.h"
#include "Glue/Scope.h"
#include "Utils/Config.h"
#include <queue>


// Leaf Nodes
void Base_Spawn(ProckNode *n) {
	n->box = UConfig::world->SpawnActor<ABoxActor>(UConfig::boxBPClass);
	n->box->SetText(n->Name());
	n->box->SetActorScale3D(FVector(BOX_RESCALE));
	n->box->SizeFitContents();
}

void Name_Spawn(PNName *n) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
}

void Int_Spawn(PNInt *n) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
}

// "Basic" Operators
void Assignment_Spawn(PNAssignment *n) {
	Base_Spawn(n);

	// Assignmnent doesnt have its own box; hide it
	n->box->GetRootComponent()->SetVisibility(false, true);

	// Add this variable to the scope. If scope rejects the new variable that means n->Target is not a Name node, its 
	// an expression: don't spawn it
	if (!n->Scope->NewVariable(n->Target())) {
		n->Target()->Spawn(n, FVector(30, 0, 0));
	}

	n->Value()->Spawn(n, FVector(-30, 0, 0));
}

void BinaryOperator_Spawn(PNBinaryOperator *n) {
	Base_Spawn(n);
	n->box->SetText(n->Value());
	n->box->SizeFitContents();

	n->First()->Spawn(n, FVector(-30, 0, 20));
	n->Second()->Spawn(n, FVector(-30, 0, -20));
}

// Collections of Nodes
void List_Spawn(PNList *n) {
	float offset = 20.f;
	float currOffset = 0.f;

	n->Scope = new Scope();

	for (ProckNode *child : *n->NodeList()) {
		// Skip comments and endlines for now. Comments could be useful in the future
		if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
			continue;
		}

		child->Spawn(n, FVector(currOffset, 0, 0));
		currOffset = currOffset + offset;
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
	// Always pass our scope down to the next node. Construction happens in appropriate Spawn function
	if (node) {
		Scope = node->Scope;
	}

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

	if (node) {
		box->AttachToComponent(node->box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		box->SetActorScale3D(FVector(BOX_RESCALE));
		box->SetActorRelativeLocation(pos);
	}
}
