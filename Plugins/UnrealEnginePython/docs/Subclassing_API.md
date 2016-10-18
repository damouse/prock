The Native Subclassing API
--------------------------

This is the most advanced way to use Python for your gameplay logic, developing plugins or automating tasks.

It resembles the native way you would work with unreal and c++ but in a (more or less ;) pythonic way.

The system is still under heavy development and new ideas are popping up constantly (the main objective is to simplify and speed up  end-users development)

Subclassing
-----------

You can define new classes using standard python subclassing:

```py
import unreal_engine as ue
from unreal_engine.classes import Character, PawnSensingComponent, Pawn

class Monster(Character):

    def __init__(self):
        sensor = self.add_actor_component(PawnSensingComponent, 'Sensor')
        sensor.SightRadius = 17000
        
    def OnSeePawn(self, pawn : Pawn):
        ue.print_string('seen {}'.format(pawn))
```

Properties
----------

Properties can be added to your class as static pyrhon class properties:

```py
import unreal_engine as ue
from unreal_engine.classes import Character, PawnSensingComponent, Pawn, FloatProperty

class Hero(Character):

    # you can set it from the editor
    UpSpeed = FloatProperty
    
    def ReceiveTick(self, DeltaSeconds: float):
        location = self.get_actor_location()
        location.z += self.UpSpeed * DeltaSeconds
        self.set_actor_location(location)
```


Functions and Events
--------------------

Reloading
---------
