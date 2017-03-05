#include "ProckFPS.h"

#include "Nodes/ProckNodeSubclasses.h"

#include "Utils/Config.h"
#include <queue>

/*
	Spawn- recursive creation of boxes
*/

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

		currOffset += extent.X + FRAME_X_OFFSET * 3;
		child->box->SetActorRelativeLocation(FVector(currOffset, extent.Y, extent.Z + FRAME_Z_OFFSET));
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


/*
    Activation- toggling boxes on or off based on runstate.
	The default Base_Activate covers a lot more cases here.
*/

// Leaf Nodes
void Base_Activate(ProckNode *n, bool state) {
    if (n->box) {
        n->box->SetRunstate(state);
    }
}

// "Basic" Operators
void Assignment_Activate(PNAssignment *n, bool state) {
    Base_Activate(n, state);

    n->Target()->Activate(state);
    n->Value()->Activate(state);
}

void BinaryOperator_Activate(PNBinaryOperator *n, bool state) {
    Base_Activate(n, state);
   
    n->First()->Activate(state);
    n->Second()->Activate(state);
}

// Collections of Nodes
void List_Activate(PNList *n, bool state) {
    for (ProckNode *child : *n->NodeList()) {
        if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
            continue;
        }

        child->Activate(state);
    };
}

void ProckNode::Activate(bool state) {
	switch (Type()) {

	// Basic Operators
	case PNT_Assignment:        Assignment_Activate((PNAssignment *) this, state); break;
	case PNT_BinaryOperator:    BinaryOperator_Activate((PNBinaryOperator *) this, state); break;

	// Collections
	case PNT_List:              List_Activate((PNList *) this, state); break;

	// Basic box
	default:                    Base_Activate(this, state); break;
	}
}


/*
	Assignment - filling the sublabel on a node.
	The default case again covers a lot of subcases
*/

void Base_Assign(ProckNode *n, PyObject *locals, bool empty) {
	if (!n->box) {
		return;
	}

	if (empty) {
		n->box->SetRunValue("");
	}
}

void Name_Assign(PNName *n, PyObject *locals, bool empty) {
	if (empty) {
		n->box->SetRunValue("");
		return;
	}

	PyObject *target = PyDict_GetItemString(locals, n->Value());

	if (!target) {
		UE_LOG(LogProck, Error, TEXT("Unable to find local variable to match name node: %s"), ANSI_TO_TCHAR(n->Value()));
	} else {
		n->box->SetRunValue(PyString_AsString(PyObject_Str(target)));
	}
}

// "Basic" Operators
void Assignment_Assign(PNAssignment *n, PyObject *locals, bool empty) {
	n->Target()->Assign(locals, empty);
    n->Value()->Assign(locals, empty); 
}

void BinaryOperator_Assign(PNBinaryOperator *n, PyObject *locals, bool empty) {
    n->First()->Assign(locals, empty);
    n->Second()->Assign(locals, empty); 
}

// Collections of Nodes
void List_Assign(PNList *n, PyObject *locals, bool empty) {
	for (ProckNode *child : *n->NodeList()) {
		if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
			continue;
		}

		child->Assign(locals, empty);
	};
}

void ProckNode::Assign(PyObject *locals, bool empty) {
	switch (Type()) {
	// The first, obvious assign node
	case PNT_Name:				Name_Assign((PNName *) this, locals, empty); break;

	// Basic Operators
	case PNT_Assignment:        Assignment_Assign((PNAssignment *) this, locals, empty); break;
	case PNT_BinaryOperator:    BinaryOperator_Assign((PNBinaryOperator *) this, locals, empty); break;

	// Collections
	case PNT_List:              List_Assign((PNList *) this, locals, empty); break;

	// Basic box
	default:                    Base_Assign(this, locals, empty); break;
	}
}
