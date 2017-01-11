// Fill out your copyright notice in the Description page of Project Settings.

#include "ProckFPS.h"
#include "BaseGameMode.h"

#include "Nodes/ProckNodeSubclasses.h"
#include "Actors/ScopeActor.h"
#include "Actors/GhostActor.h"

#include "Utils/Config.h"


ABaseGameMode::ABaseGameMode() {
	UConfig::world = GetWorld();	
}

// PHYSICS TESTING
void InitialiseSystem(void);
void SetupParticles(int, int);

int nparticles = 3;
PARTICLE *particles;
int nsprings = 3;
PARTICLESPRING *springs;
PARTICLEPHYS physical;

void ABaseGameMode::BeginPlay() {
	// PHYSICS TESTING
	a = UConfig::world->SpawnActor<ABoxActor>(UConfig::boxBPClass);
	b = UConfig::world->SpawnActor<ABoxActor>(UConfig::boxBPClass);
	c = UConfig::world->SpawnActor<ABoxActor>(UConfig::boxBPClass);

	InitialiseSystem();

	return;
	// END PHYSICS TESTING

	// Load the room instance which starts the game in the map
	for (TActorIterator<ABoxActor> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		room = *ActorItr;
	}

	if (!room) {
		UE_LOG(LogProck, Error, TEXT("Room doesnt exist, can't load"));
		return;
	}

	peter = new Peter();
	ProckNode *root = peter->LoadPython();
	TArray<AGhostActor *> ghosts;

	if (root) {
		// The first box is already placed, assign it as the root's box
		root->box = room;
		root->Spawn(nullptr, FVector(), ghosts);
	}
}

// PHYSICS TESTING
void ABaseGameMode::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	dt += DeltaSeconds;

	// Trying to roll over dt to avoid instability issues with euler's method. Seems to work? 
	// I think the time issues with euler present themselves in long-running simulations. Since we update 
	// "instantaneously," I'm hoping the problem is just solved?
	if (dt > 1) {
		dt = 0;
	}

	UpdateParticles(particles, nparticles, physical, springs, nsprings, dt, 0);

	UE_LOG(LogProck, Log, TEXT("dt: %.3f"), dt);

	int i, p1, p2;

	// Update box positions
	for (i = 0; i < nparticles; i++) {
		if (i == 0) {
			a->SetActorLocation(FVector(particles[i].p));
		}

		if (i == 1) {
			b->SetActorLocation(FVector(particles[i].p));
		}

		if (i == 2) {
			c->SetActorLocation(FVector(particles[i].p));
		}
	}

	for (i = 0; i<nsprings; i++) {
		p1 = springs[i].from;
		p2 = springs[i].to;
		/* Display a spring between point p1 and p2 */
	}
}

/*
Set up the particle system.
Initialise all variables to default values
*/
void SetupParticles(int np, int ns) {
	int i;

	nparticles = np;
	nsprings = ns;

	particles = (PARTICLE *)malloc(nparticles * sizeof(PARTICLE));
	springs = (PARTICLESPRING *)malloc(nsprings * sizeof(PARTICLESPRING));

	for (i = 0; i<np; i++) {
		particles[i].m = 1;
		particles[i].fixed = false;
		particles[i].v.X = 0;
		particles[i].v.Y = 0;
		particles[i].v.Z = 0;
	}

	for (i = 0; i<ns; i++) {
		springs[i].springconstant = 0.1;
		springs[i].dampingconstant = 0.05;
		springs[i].restlength = 20;
	}

	physical.gravitational = 0;
	physical.viscousdrag = 0.1;
}

/*
Create 5 particles
The particles are placed randomly on the interval -5 -> 5
*/
void InitialiseSystem(void) {
	int i;

	SetupParticles(5, 9);

	/* Random positions */
	for (i = 0; i<5; i++) {
		particles[i].p.X = 100 * (rand() % 1000) / 1000.0;
		particles[i].p.Y = 100 * (rand() % 1000) / 1000.0;
		particles[i].p.Z = 100 * (rand() % 1000) / 1000.0;
	}

	/* Edges */
	springs[0].from = 0; springs[0].to = 1;
	springs[1].from = 0; springs[1].to = 2;
	springs[2].from = 0; springs[2].to = 3;
	springs[3].from = 4; springs[3].to = 1;
	springs[4].from = 4; springs[4].to = 2;
	springs[5].from = 4; springs[5].to = 3;
	springs[6].from = 1; springs[6].to = 2;
	springs[7].from = 2; springs[7].to = 3;
	springs[8].from = 3; springs[8].to = 1;
}

/*
Update the forces on each particle
*/
void CalculateForces(PARTICLE *p, int np, PARTICLEPHYS phys, PARTICLESPRING *s, int ns) {
	int i, p1, p2;
	FVector down(0.0,0.0,-1.0);
	FVector zero(0.0,0.0,0.0);
	FVector f;
	double len, dx, dy, dz;

	for (i = 0; i<np; i++) {
		p[i].f = zero;
		if (p[i].fixed)
			continue;

		/* Gravitation */
		p[i].f.X += phys.gravitational * p[i].m * down.X;
		p[i].f.Y += phys.gravitational * p[i].m * down.Y;
		p[i].f.Z += phys.gravitational * p[i].m * down.Z;

		/* Viscous drag */
		p[i].f.X -= phys.viscousdrag * p[i].v.X;
		p[i].f.Y -= phys.viscousdrag * p[i].v.Y;
		p[i].f.Z -= phys.viscousdrag * p[i].v.Z;
	}

	/* Handle the spring interaction */
	for (i = 0; i<ns; i++) {
		p1 = s[i].from;
		p2 = s[i].to;

		dx = p[p1].p.X - p[p2].p.X;
		dy = p[p1].p.Y - p[p2].p.Y;
		dz = p[p1].p.Z - p[p2].p.Z;
    
		len = sqrt(dx*dx + dy*dy + dz*dz);

		f.X = s[i].springconstant  * (len - s[i].restlength);
		f.X += s[i].dampingconstant * (p[p1].v.X - p[p2].v.X) * dx / len;
		f.X *= -dx / len;

		f.Y = s[i].springconstant  * (len - s[i].restlength);
		f.Y += s[i].dampingconstant * (p[p1].v.Y - p[p2].v.Y) * dy / len;
		f.Y *= -dy / len;

		f.Z = s[i].springconstant  * (len - s[i].restlength);
		f.Z += s[i].dampingconstant * (p[p1].v.Z - p[p2].v.Z) * dz / len;
		f.Z *= -dz / len;

		if (!p[p1].fixed) {
			p[p1].f.X += f.X;
			p[p1].f.Y += f.Y;
			p[p1].f.Z += f.Z;
		}

		if (!p[p2].fixed) {
			p[p2].f.X -= f.X;
			p[p2].f.Y -= f.Y;
			p[p2].f.Z -= f.Z;
		}
	}
}

/*
Perform one step of the solver
*/
void UpdateParticles(PARTICLE *p, int np, PARTICLEPHYS phys, PARTICLESPRING *s, int ns, double dt, int method) {
	int i;
	PARTICLEDERIVATIVES *deriv;
	PARTICLE *ptmp;
	deriv = (PARTICLEDERIVATIVES *)malloc(np * sizeof(PARTICLEDERIVATIVES));

	CalculateForces(p, np, phys, s, ns);
	CalculateDerivatives(p, np, deriv);
	ptmp = (PARTICLE *)malloc(np * sizeof(PARTICLE));

	for (i = 0; i<np; i++) {
		ptmp[i] = p[i];
		ptmp[i].p.X += deriv[i].dpdt.X * dt / 2;
		ptmp[i].p.Y += deriv[i].dpdt.Y * dt / 2;
		ptmp[i].p.Z += deriv[i].dpdt.Z * dt / 2;
		ptmp[i].p.X += deriv[i].dvdt.X * dt / 2;
		ptmp[i].p.Y += deriv[i].dvdt.Y * dt / 2;
		ptmp[i].p.Z += deriv[i].dvdt.Z * dt / 2;
	}

	CalculateForces(ptmp, np, phys, s, ns);
	CalculateDerivatives(ptmp, np, deriv);

	for (i = 0; i<np; i++) {
		p[i].p.X += deriv[i].dpdt.X * dt;
		p[i].p.Y += deriv[i].dpdt.Y * dt;
		p[i].p.Z += deriv[i].dpdt.Z * dt;
		p[i].v.X += deriv[i].dvdt.X * dt;
		p[i].v.Y += deriv[i].dvdt.Y * dt;
		p[i].v.Z += deriv[i].dvdt.Z * dt;
	}

	free(ptmp);
  free(deriv);
}

void CalculateDerivatives(PARTICLE *p, int np, PARTICLEDERIVATIVES *deriv) {
  int i;

	for (i = 0; i<np; i++) {
		deriv[i].dpdt.X = p[i].v.X;
		deriv[i].dpdt.Y = p[i].v.Y;
		deriv[i].dpdt.Z = p[i].v.Z;
		deriv[i].dvdt.X = p[i].f.X / p[i].m;
		deriv[i].dvdt.Y = p[i].f.Y / p[i].m;
		deriv[i].dvdt.Z = p[i].f.Z / p[i].m;
	}
}
