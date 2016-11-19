#include "ProckFPS.h"
#include "ProckNode.h"

// Leaf Nodes
void Base_Spawn(ProckNode *n) {
	n->box = ProckNode::world->SpawnActor<ABoxActor>(ProckNode::boxBPClass);
	n->box->SetText(n->Name());
	//n->box->SetActorScale3D(FVector(.2, .2, .2));
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

	// Assignmnent doesnt have its own box
	n->box->GetRootComponent()->SetVisibility(false, true);

	ProckNode *target = n->Target();
	ProckNode *value = n->Value();

	target->Spawn(n, FVector(30, 0, 0));
	value->Spawn(n, FVector(-30, 0, 0));

	//n->Attach(target, FVector(30, 0, 0));
	//n->Attach(value, FVector(-30, 0, 0));

	//value->box->ConnectToBox(target->box);
}

void BinaryOperator_Spawn(PNBinaryOperator *n) {
	Base_Spawn(n);
	n->box->SetText(n->Value());

	ProckNode *first = n->First();
	ProckNode *second = n->Second();

	first->Spawn(n, FVector(30, 0, 0));
	second->Spawn(n, FVector(30, 0, 0));

	//n->Attach(first, FVector(-5, 0, 3));
	//n->Attach(first, FVector(-5, 0, -3));

	//node->box->ConnectToBox(first->box);
	//node->box->ConnectToBox(second->box);
}

// Collections of Nodes
void List_Spawn(PNList *n) {
	float offset = 20.f;
	float currOffset = 0.f;

	std::vector<ProckNode *> *kids = n->NodeList();

	if (!kids) {
		UE_LOG(LogProck, Error, TEXT("PNList did not get a list back"));
		return;
	}

	for (ProckNode *child : *n->NodeList()) {
		// Skip comments and endlines for now. Comments could be useful in the future
		if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
			continue;
		}

		child->Spawn(n, FVector(currOffset, 0, 0));
		//n->Attach(child, FVector(currOffset, 0, 0));
		currOffset = currOffset + offset;
	};
}

// This function switches on the type of the passed node and invokes a respective _Spawn function if one exists, 
// else calls Base_Spawn. Each type check here is basically the implementation of another node "drawing" type.
// When creating new _Spawn methods, please give them the same name as the node being targeted
//
// Note that this design intentionally allows for a single _Spawn method to handle multiple node types.
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

	if (node) {
		box->AttachToComponent(node->box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		box->SetActorScale3D(FVector(.2, .2, .2));
		box->SetActorRelativeLocation(pos);
	}
}

