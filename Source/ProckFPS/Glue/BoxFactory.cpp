// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BoxFactory.h"

BoxFactory::BoxFactory(ProckNode *node) {
	root = node;
}

BoxFactory::~BoxFactory() {
	root = nullptr;
}

/*
// This function switches on the type of the passed node and invokes a respective _Spawn function if one exists, 
// else calls Base_Spawn. Each type check here is basically the implementation of another node "drawing" type.
// When creating new _Spawn methods, please give them the same name as the node being targeted
//
// Note that this design intentionally allows for a single _Spawn method to handle multiple node types.
//
// Attaches to the passed node at the relative position. Root nodes are passed null and 0 as params. 
void BoxFactory::Build(ProckNode *node, FVector pos) {
    switch (Type()) {

    // Leaf Nodes
    case PNT_Name:              Name_Build((PNName *) this); break;
    case PNT_Int:               Int_Build((PNInt *) this); break;

    // Basic Operators
    case PNT_Assignment:        Assignment_Build((PNAssignment *) this); break;
    case PNT_BinaryOperator:    BinaryOperator_Build((PNBinaryOperator *) this); break;

    // Collections
    case PNT_List:              List_Build((PNList *) this); break;

    // Basic box
    default:                    Base_Build(this); break;
    }

    if (node) {
        box->AttachToComponent(node->box->GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
        box->SetActorScale3D(FVector(BOX_RESCALE));
        box->SetActorRelativeLocation(pos);
    }
}

// Peter? Node?
void BoxFactory::Collect(PNList *n) {
    // Use two queues that swap like buffers to count depth
    std::queue<ProckNode *> q;

    for (ProckNode *child : *n->NodeList()) {
        // Skip comments and endlines for now. Comments could be useful in the future
        if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
            continue;
        }

        q.push(child);
    }

    ProckNode *curr = q.front();
    q.pop();

    while (curr) {
        switch (curr->Type()) {

        // Leaf Nodes
        case PNT_Name:              Name_Build((PNName *) curr); break;
        case PNT_Int:               Int_Build((PNInt *) curr); break;

        // Basic Operators
        case PNT_Assignment:        Assignment_Build((PNAssignment *) curr); break;
        case PNT_BinaryOperator:    BinaryOperator_Build((PNBinaryOperator *) curr); break;

        // Collections
        case PNT_List:              List_Build((PNList *) curr); break;

        // Basic box
        default:                    Base_Build(curr); break;
        }


        curr = q.front();
        q.pop();
    }
}

// Leaf Nodes
void BoxFactory::Base_Build(ProckNode *n) {
    n->box = ProckNode::world->SpawnActor<ABoxActor>(ProckNode::boxBPClass);
    n->box->SetText(n->Name());
    n->box->SetActorScale3D(FVector(BOX_RESCALE));
    n->box->SizeFitContents();
}

void BoxFactory::Name_Build(PNName *n) {
    Base_Build(n);
    n->box->SetText(n->Value());
}

void BoxFactory::Int_Build(PNInt *n) {
    Base_Build(n);
    n->box->SetText(n->Value());
}

// "Basic" Operators
void BoxFactory::Assignment_Build(PNAssignment *n) {
    Base_Build(n);

    // Assignmnent doesnt have its own box; hide it
    n->box->GetRootComponent()->SetVisibility(false, true);
    n->Target()->Spawn(n, FVector(30, 0, 0));
    n->Value()->Spawn(n, FVector(-30, 0, 0));
}

void BoxFactory::BinaryOperator_Build(PNBinaryOperator *n) {
    Base_Build(n);
    n->box->SetText(n->Value());
    n->box->SizeFitContents();

    n->First()->Spawn(n, FVector(-30, 0, 20));
    n->Second()->Spawn(n, FVector(-30, 0, -20));
}

// Collections of Nodes
void BoxFactory::List_Build(PNList *n) {
    float offset = 20.f;
    float currOffset = 0.f;

    for (ProckNode *child : *n->NodeList()) {
        // Skip comments and endlines for now. Comments could be useful in the future
        if (child->Type() == PNT_Comment || child->Type() == PNT_Endl) {
            continue;
        }

        child->Spawn(n, FVector(currOffset, 0, 0));
        currOffset = currOffset + offset;
    };
}

*/

/*
    Pass in ScopeNode into each spawn call, or alternatively set a field on the children 
    if the parent is a PNList to indicate scope

    Name Nodes trigger pathing: call a method on ScopeNode::PathIvar(). Create the path if it does not exist, else attach it to the current path 
    Also: spawn lines as actors.

    Can peter just take care of this? Give it the tree and have it "pre-load" 
    the important bits?

    Is "Scope" its own object, or a node? Could be either, a pointer to a shared instance.

    Scope = peter::collect(Node)

    Scope has:
        - lines []Line  // Why?
        - root ProckNode // Not clear this is needed
        - variables []GhostScopeVars // Only one we absolutely cannot do without

    Name nodes have to point to their ghosts such that the links can either be rewritten
    or drawn directly to the line. Is there any case in which we want to keep drawing 
    lines to boxes that are not scoped?

    line = SpawnActor<ALineActor>()
    line.connect(a, b)
        a.didConnect(line)
        b.didConnect(line)

    if a is a Name node it "forwards" the connection to its relevant path

    Why not check if isNameNode(a), then connect to appropriate path instead?
    Still need the Scope, but could attach the field to ProckNode instead 

    There are certain situations where we almost always want to collect the scope. 
    These are your functions, classes, etc. We don't need a scope class, but we 
    do want to collect the information somewhere.

    What does it look like to invert control on spawning? Ewww a queue.
*/
