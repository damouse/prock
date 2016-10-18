# UnrealEnginePython
Embed Python in Unreal Engine 4

# How and Why ?

This is a plugin embedding a whole Python VM (versions 3.x [the default and suggested one] and 2.7) In Unreal Engine 4 (both the editor and runtime).

The Python VM tries to give easy access to all of the UE4 internal api + its reflection system. This means you can use the plugin to write other plugins, to automate tasks and to implement gameplay elements.

It is not meant as a way to avoid blueprints or c++ but as a good companion to them (albeit reducing the amount of c++ required for coding a game could be an interesting thing ;)

Another funny feature is that you can change your python code even after the project has been packaged. You can potentially build a completely new game from an already packaged one.

In addition to this, the plugin automatically adds an actor class (PyActor), a pawn class (PyPawn), a character class (PyCharacter) and a component class (PythonComponent) for "gentle" integration of python in your games.

In the development menu, you get access to the 'PythonConsole' too, you can use it to trigger python commands directly from the editor.

All of the exposed engine features are under the 'unreal_engine' virtual module (it is completely coded in c into the plugin, so do not expect to run 'import unreal_engine' from a standard python shell)

# Installation on Windows (64 bit)

The installation is pretty long (and boring) as you do not want the final users of the product to be required to install python, so we need to use the 'embedded python distribution' (available for windows in the official python site). Unfortunately the embedded distribution does not contain the python development headers so we need the official system-wide installation too.

* install Unreal Engine 4.12 and Python 3.5 as a system user
* run the unreal editor and create a new blank c++ project (NOT a blueprint one, otherwise visual studio will not be initialized)
* once the project is setup, close both unreal and visual studio
* move to the project directory (you can right click the project from the epic launcher and choose 'show in explorer')
* create a 'Plugins' directory into the project directory
* move into the just created Plugins directory and clone the repository:

```sh
git clone https://github.com/20tab/UnrealEnginePython
```

* from the explorer right click on the project main file and choose 'generate visual studio project files'
* open again visual studio, you should now see Plugins/UnrealEnginePython in your solution explorer
* before running the plugin build process you need to copy development headers and libs in the plugin directory (Plugins/UnrealEnginePython).
* create the directory Plugins/UnrealEnginePython/python35 (this is where the build script expects to find headers and static libs)
* copy "C:/Program Files/Python35/include" and "C:/Program Files/Python35/libs" into Plugins/UnrealEnginePython/python35
* run the compilation from visual studio
* once the compilation ends, copy the python35.dll (from "C:/Program Files/Python35" or from the embeded distribution) into the Binaries/Win64 directory of your project (you will find the plugin dll too in this directory)
* now you can re-run the unreal engine editor

If all goes well, open the output log and search for the string "Python". You should see the Python VM initialization message. It means your editor has now full python support.

To use python 2, follow the same approach but with a python27 directory (instead of python35) and change the pythonHome variable in /Source/UnrealEnginePython/UnrealEnginePython.Build.cs to "python27"

# Installation on MacOSX

On the Mac the installation is easier, as the final user is currently forced to install python on its system (there are obviously dozens of workarounds but at this stage of the project we prefer focusing on the api).

* install the latest official python distribution from python.org (the installation will end in the "/Library/Frameworks/Python.framework/Versions/3.5" directory).
* create a new unreal engine blank c++ project (NOT a blueprint one, otherwise XCode will not be initialized)
* create a Plugins directory in the project directory
* move to the Plugins directory and clone the plugin repository


```sh
git clone https://github.com/20tab/UnrealEnginePython
```

* restart the editor and a popup should appear asking your for confirmation of the build of the plugin.
* Once the plugin is built, go to the output log console and filter for 'Python'. You should see the Python VM banner.


For python 2 just change the pythonHome variable in /Source/UnrealEnginePython/UnrealEnginePython.Build.cs to "python27"

Upgrading on MacOSX
-------------------

To upgrade to the latest development version of UnrealEnginePython:
* move to the Plugins directory in the project directory and use git pull

```sh
git pull
```

* move to UnrealEnginePython/Binaries/Mac from the Plugin directory
* remove the plugin library UE4Editor-UnrealEnginePython.dylib to warn UnrealEngine to recompile the plugin

```sh
rm UE4Editor-UnrealEnginePython.dylib
```

* restart the editor and a popup should appear asking your for confirmation of the build of the plugin.
* Once the plugin is built, go to the output log console and filter for 'Python'. You should see the Python VM banner.

Installation On Linux (64 bit)
------------------------------

Currently the suggested distribution is Ubuntu Xenial (LTS 16.04) 64bit. Obviously you need to already have an Unreal Engine build (note that on ubuntu xenial you need to install the clang-3.5 package to build the editor). Both python2.7 and python3.5 are supported and the default configuration assumes python3 (so ensure to install the python3-dev package).

* Create a new C++ project and close the editor once the project is fully started
* go to the just created project directory and create the Plugins folder
* move to the Plugins folder and clone the plugin repository:


```sh
git clone https://github.com/20tab/UnrealEnginePython
```

* re-open your project, this time you will get a popup asking you for re-building the python plugin. Choose yes and wait.

NOTE: always run your project from a terminal so you can see startup logs (they are really useful when building the plugin the first time, if you cannot build the plugin, open an issue on github pasting the related log lines).

If you want to use python2 just edit the Source/UnrealEnginePython/UnrealEnginePython.Build.cs file and change the pythonHome string to "python27" (ensure to have the python2.7-dev package installed).

If you want to use an alternative python installation, go to the end of UnrealEnginePython.Build.cs, and change the paths of includes and libpython accordingly

Upgrade the plugin on Linux
---------------------------

Just remove the .so files in Plugins/UnrealEnginePython/Binaries/Linux and pull the latest code.

At the next run the build procedure wil be started again.

# Installation on other platforms

Currently only Windows, MacOSX and Linux are supported. We are investigating Android support too via the kivy project.

# Using Python with Unreal Engine (finally)

Creating a new blueprint class managed by python
------------------------------------------------

We are going to create a new Actor based on python (instead of C++ or blueprints)

This is the "gentle" approach, using a 'proxy' python class to speak with the UE4 api. Once you get familiar with the system, you can
go further and start working withe native subclassing api (https://github.com/20tab/UnrealEnginePython/blob/master/docs/Subclassing_API.md) 

In the content browser click on 'add new' and choose 'blueprint class'

In the classes menu choose 'PyActor':

![Alt text](screenshots/unreal_screenshot1.png?raw=true "Screenshot 1")

You now have a new asset, give it a meaningful name, and double click on it to start configuring it in the blueprint editor

![Alt text](screenshots/unreal_screenshot2.png?raw=true "Screenshot 2")

On the right (in the 'Details' tab) you will find the Python section.

For now only 'Python Module' and 'Python Class' are meaningful.

Go to the Content directory of your project and create a directory named 'Scripts'. This is where all of your python modules will reside. With your favourite text editor create a new python module (like funnygameclasses.py), and define a new class into it:

```py
import unreal_engine as ue

ue.log('Hello i am a Python module')

class Hero:

    # this is called on game start
    def begin_play(self):
        ue.log('Begin Play on Hero class')
        
    # this is called at every 'tick'    
    def tick(self, delta_time):
        # get current location
        location = self.uobject.get_actor_location()
        # increase Z honouring delta_time
        location.z += 100 * delta_time
        # set new location
        self.uobject.set_actor_location(location)

```

Now, go back to the blueprint editor and set 'funnygameclasses' in the 'Python Module' field, and 'Hero' in 'Python Class'

As you can see the actor will simply move over the z axis, but we need to give it some kind of visual representation to have a feedback in the scene. In the blueprint editor click on 'add component' and add some shape (a sphere, or a cube, or whatever you want). Save and Compile your blueprint.

Now you can drag the bluprint from the content browser to the scene and just click 'Play'.

You should see your actor moving along the 'z' axis at a speed of 1 meter per second

By default a 'begin_play' and a 'tick' method are expected (they will be automatically taken into account if found). In addition to them an 'automagic' system for defining event is available:

```py
def on_actor_begin_overlap(self, me, other_actor):
    pass

def on_actor_end_overlap(self, me, other_actor):
    pass
    
def on_actor_hit(self, me, other_actor, normal_impulse, hit_result):
    pass

...
```

Basically for each method startwing with 'on_' the related delegate/event is automatically configured (if available).

If you instead prefer to manually setup events, the following functions are exposed:

```py

class Ball:

    def begin_play(self):
        self.uobject.bind_event('OnActorBeginOverlap', self.manage_overlap)
        self.uobject.bind_action('Jump', ue.IE_PRESSED, self.uobject.jump)
        self.uobject.bind_key('K', ue.IE_PRESSED, self.you_pressed_K)
        self.uobject.bind_axis('MoveForward', self.move_forward)
        
    def manage_overlap(self, me, other):
        ue.print_string('overlapping ' + other.get_name())
        
    def you_pressed_K(self):
        ue.log_warning('you pressed K')
        
     def move_forward(self, amount):
        ue.print_string('axis value: ' + str(amount))
        

```


What is 'self.uobject' ?
------------------------

To allow seamless Python integration, each UObject of the engine is automatically mapped to a special Python Object (ue_PyUObject).

Whenever you want to access a UObject from python, you effectively get a reference to a ue_PyUObject exposing (via its methods) the features of the UObject (properties, functions, ....)

This special python object is cached into a c++ map in memory. (The key is the UObject pointer, the value is the ue_PyUObject pointer)

To be more clear, a call to:

```py
text_render_component = unreal_engine.find_class('TextRenderComponent')
```

will internally search for the 'TextRenderComponent' class (via unreal c++ reflection) and when found will check if it is available in the cache, otherwise it will create a new ue_PyUObject object that will be placed in the cache.

From the previous example the 'text_render_component' maintains a mapping to the UObject (well a UClass in this example).

Pay attention: the python class you map to the PyActor (or PyPawn, PyCharacter or PyComponent), is not a ue_PyUObject. It is a classic python class that holds a reference (via the 'uobject' field) to the related ue_PyUObject mapped object. The best technical term to describe those classes is 'proxy'.

Note about 'uobject' from now on
---------------------------------

In the following lines, whenever you find a reference to 'uobject' it is meant as a ue_PyUObject object.

Adding a python component to an Actor
-------------------------------------

This works in the same way as the PyActor class, but it is, well, a component. You can attach it (search for the 'Python' component) to any actor.

Remember that for components, the self.uobject field point to the component itself, not the actor.

To access the actor you can use:

```py
actor = self.uobject.get_owner()
```

The following example implements the third person official blueprint as a python component in non-evented way (this is an anti-pattern in unreal engine, see below for the evented-based approach):

```py
import unreal_engine as ue

class Player:
    def begin_play(self):
        # get a reference to the owing pawn (a character)
        self.pawn = self.uobject.get_owner()
        
        # allows the pawn to receive axis values
        self.pawn.bind_input_axis('TurnRate')
        self.pawn.bind_input_axis('LookUpRate')
        
        # the following two values are originally implemented as blueprint variable
        self.base_turn_rate = 45.0
        self.base_look_up_rate = 45.0
        
         # bind the other axis
        self.pawn.bind_input_axis('Turn')
        self.pawn.bind_input_axis('LookUp')

        self.pawn.bind_input_axis('MoveForward')
        self.pawn.bind_input_axis('MoveRight')
        
    def tick(self, delta_time):
        # z rotation
        turn_rate = self.pawn.get_input_axis('TurnRate') * self.base_turn_rate * delta_time
        self.pawn.add_controller_yaw_input(turn_rate)

        # y rotation
        look_up_rate = self.pawn.get_input_axis('LookUpRate') * self.base_look_up_rate * delta_time
        self.pawn.add_controller_pitch_input(look_up_rate)

        # mouse vertical
        self.pawn.add_controller_yaw_input(self.pawn.get_input_axis('Turn'))

        # mouse horizontal
        self.pawn.add_controller_pitch_input(self.pawn.get_input_axis('LookUp'))

        # get current control rotation
        rot = self.pawn.get_control_rotation()
        
        # move the character
        fwd = ue.get_forward_vector(0, 0, rot[2])
        right = ue.get_right_vector(0, 0, rot.yaw)

        self.pawn.add_movement_input(fwd, self.pawn.get_input_axis('MoveForward'))
        self.pawn.add_movement_input(right, self.pawn.get_input_axis('MoveRight'))

        # manage jump
        if self.pawn.is_action_pressed('Jump'):
            self.pawn.jump()
        if self.pawn.is_action_released('Jump'):
            self.pawn.stop_jumping()
```

And as promised the 'blessed' evented approach:

```py
class PlayerEvented:
    
    def begin_play(self):
        # get a reference to the owing pawn (a character)
        self.pawn = self.uobject.get_owner()

        # the following two values were originally implemented as blueprint variable
        self.base_turn_rate = 45.0
        self.base_look_up_rate = 45.0

        # bind axis events
        self.pawn.bind_axis('TurnRate', self.turn)
        self.pawn.bind_axis('LookUpRate', self.look_up)
        self.pawn.bind_axis('Turn', self.pawn.add_controller_yaw_input)
        self.pawn.bind_axis('LookUp', self.pawn.add_controller_pitch_input)

        self.pawn.bind_axis('MoveForward', self.move_forward)
        self.pawn.bind_axis('MoveRight', self.move_right)

        # bind actions
        self.pawn.bind_action('Jump', ue.IE_PRESSED, self.pawn.jump)
        self.pawn.bind_action('Jump', ue.IE_RELEASED, self.pawn.stop_jumping)

    def turn(self, axis_value):
        turn_rate = axis_value * self.base_turn_rate * self.uobject.get_world_delta_seconds()
        self.pawn.add_controller_yaw_input(turn_rate)

    def look_up(self, axis_value):
        look_up_rate = axis_value * self.base_look_up_rate * self.uobject.get_world_delta_seconds()
        self.pawn.add_controller_pitch_input(look_up_rate)

    def move_forward(self, axis_value):
        rot = self.pawn.get_control_rotation()
        fwd = ue.get_forward_vector(0, 0, rot[2])
        self.pawn.add_movement_input(fwd, axis_value)

    def move_right(self, axis_value):
        rot = self.pawn.get_control_rotation()
        right = ue.get_right_vector(0, 0, rot[2])
        self.pawn.add_movement_input(right, axis_value)
```

Native methods VS reflection
----------------------------

By default the UObject class defines __getattr__ and __setattr__ as wrappers for unreal properties and functions.

This means that calling:

```py
self.uobject.bCanBeDamaged = True
```

it is the same as

```py
self.uobject.set_property('bCanBeDamaged', True)
```

As well as function calls:

```py
vec = self.uobject.GetActorRightForward()
```

means

```py
vec = self.uobject.call_function('GetActorRightForward')
```

And more important (and handy) K2_ functions are automagically exposed too:

```py
vec = self.uobject.GetActorLocation()
```

is equal to:

```py
vec = self.uobject.call_function('K2_GetActorLocation')
```

Obviously you can combine methods/properties:

```py
self.uobject.CharacterMovement.MaxWalkSpeed = 600.0
```

Albeit the system allows for full unreal api usage, reflection is slower than native methods.

Try to use native methods whenever possible, and open pull request whenever you think a function should be exposed as native methods.

So

```py
vec = self.uobject.get_actor_location()
```

is way faster than

```py
vec = self.uobject.GetActorLocation()
```

Reflection based functions are those in camelcase (or with the first capital letter). Native functions instead follow the python style, with lower case, underscore-as-separator function names.

The automagic UClass and UEnums mappers
---------------------------------------

Instead of doing a gazilion of unreal_engine.find_class(name) calls, the plugin adds a 'magic' module called unreal_engine.classes. It allows to import unreal classes like python classes:

```py
from unreal_engine.classes import ActorComponent, ForceFeedbackEffect, KismetSystemLibrary

...
components = self.uobject.get_owner().GetComponentsByClass(ActorComponent)

...
self.force_feedback = ue.load_object(ForceFeedbackEffect, '/Game/vibrate')
self.uobject.get_player_controller().ClientPlayForceFeedback(self.force_feedback)

...
name = KismetSystemLibrary.GetObjectName(self.actor)
```

the last example, shows another magic feature: static classes function calls. Obviously in this specific case using self.actor.get_name() would have been the best approach, but this feature allows you to access your blueprint function libraries too.

Another example for adding a widget:

```py
from unreal_engine.classes import WidgetBlueprintLibrary

class PythonFunnyActor:
    def begin_play(self):
        WidgetBlueprintLibrary.Create(self.uobject, ue.find_class('velocity_C'))
```

And another complex example using enums, keyword arguments and output values (output values are appended after the return value):

```py

import unreal_engine as ue
from unreal_engine import FVector, FRotator, FTransform, FHitResult
from unreal_engine.classes import ActorComponent, ForceFeedbackEffect, KismetSystemLibrary, WidgetBlueprintLibrary
from unreal_engine.enums import EInputEvent, ETraceTypeQuery, EDrawDebugTrace

...

is_hitting_something, hit_result = KismetSystemLibrary.LineTraceSingle_NEW(self.actor, self.actor.get_actor_location(), FVector(300, 300, 300), ETraceTypeQuery.TraceTypeQuery1, DrawDebugType=EDrawDebugTrace.ForOneFrame)
if is_hitting_something:
    ue.log(hit_result)
```

The ue_site.py file
-------------------

On Editor/Engine start, the ue_site module is tried for import. You should place initialization code there. If the module cannot be imported, you will get a (harmful) message in the logs.

PyPawn
------

This works like PyActor, but this time you generate a new Pawn class (that you can posses with a controller)


The 'World' concept
-------------------

Every uobject is mapped to a world (UWorld in c++). Generally when you play on a Level your objects all live in the same world, but at the same time there could be multiple worlds (for example while testing in the editor there is a world for the editor and one for the simulation)

While it is pretty rare to reference other worlds, you may need to compare the world of two uobject's (for example you may have a reference in your python module to a uobject of a hidden world and you want to check if you need to use it).

The uobject.get_world() function returns a uobject representing the world (the C++ UWorld class)

The uobject api
---------------

Each uobject represent a UObject class of the Engine. This C++ class is basically the root of all the other classes (Actors, Pawns, components, properties ...). Thanks to Unreal Engine reflection system we do not need to implement a python class for each unreal engine class, but for performance reason we expose the most common methods. The uobject system checks for the type of the mapped C++ UObject and will call the method only if it is safe to call it.

Sometime methods are implemented for automatically getting the right object. As an example get_actor_location() when called over a component will automatically retrieve the related actor and will call C++ AActor::GetActorLocation() method over it.

When this automagic approach is too risky, the method will check for the uobject type and will raise an exception in the case of inconsistencies.

Remember, there is no need to implement every single engine class method, the reflection system is powerful enough to be governed only via properties and function calls (check the uobject call() method)

Most-used methods are implemented directly as uobject methods for performance reasons.

You can get the the list of uobject api methods here: https://github.com/20tab/UnrealEnginePython/blob/master/docs/uobject_API.md

Automatic module reloading (Editor only)
----------------------------------------

When in the editor, you can change the code of your modules mapped to proxies without restarting the project. The editor will reload the module every time a PyActor, PyPawn or PythonComponent is instantiated. This is obviously not the best approach. In the future we would like to implement timestamp monitoring on the file to reload only when needed.

Primitives and Math functions
-----------------------------

The plugin exposes FVector, FRotator, FQuat, FColor, FHitResult and a bunch of the internal handles.

Where meaningful math operations are exposed:


```py
import unreal_engine

class ActorGoingUp:
    def begin_play(self):
        # 1 meter by second
        self.speed = 100
    
    def tick(self, delta_time):
        # get the up vector
        up = self.uobject.get_up_vector()
        # get current position
        position = self.uobject.get_actor_location()
        # build a direction vector based on speed
        up_amount = up * self.speed * delta_time)
        # sum the direction to the position
        position += up_amount
        # set the new position
        self.uobject.set_actor_location(new_position)
```

Referencing objects
-------------------

You can use find_class(), find_struct() and find_object() functions to reference already loaded classes/objects.

If you need to reference assets (still) not loaded in the engine you can use load_struct(), load_class() or load_object():

```py
a_struct_data = ue.load_struct('/Game/Data')
ue.log(a_struct_data.as_dict())
```

or to find a specific asset:

```py
texture_class = ue.find_class('Texture2D')
a_specific_texture = ue.load_object(texture_class, '/Game/Textures/logo2')
```

The as_dict() method
--------------------

This special method can be called on any uobject: it will attempt to serialize it to a python dictionary

Navigation
---------

The only exposed navigation-related method is 'simple_move_to_location'. It expects a Pawn with a movement component (like a Character)

```py
class MoveToTargetComponent:

    def begin_play(self):
        # get a 'target point' reference from a pawn public property
        target = self.uobject.get_owner().get_property('target')
        self.uobject.get_owner().simple_move_to_location(target.get_actor_location())
        
    def tick(self, delta_time):
        pass
```

Another example for diablo-like movements (click to move, add this component to a character)

```py
class Walker:
    def begin_play(self):
        self.uobject.show_mouse_cursor()
    def tick(self, delta_time):
        if not self.uobject.is_input_key_down('LeftMouseButton'):
            return
        hit = self.uobject.get_hit_result_under_cursor(ue.COLLISION_CHANNEL_VISIBILITY)
        if not hit:
            return
        # hit is a unreal_engine.FHitResult object
        self.uobject.simple_move_to_location(hit.impact_point)
```

Physics
-------

The 'set_simulate_physics' method is exposed for enabling physic on PrimitiveComponent.

Remember that you cannot enable physics withotu setting the collision presetes accordingly:

```py

# PyActor with a staticmeshcomponent (a sphere)
# when overlapped it became a physic object
class Ball:

    def begin_play(self):
        self.sphere = self.uobject.get_actor_component_by_type(ue.find_class('StaticMeshComponent'))
        
    def tick(self, delta_time):
        pass
    
    def on_actor_begin_overlap(self, me, other_actor):
        # change collision profile
        self.sphere.call('SetCollisionProfileName BlockAll')
        # enable physics
        self.sphere.set_simulate_physics()
        
    # once the object became a physics one, hit event will start arriving
    def on_actor_hit(self, me, other, *args):
        ue.print_string('HIT with ' + other.get_name())
```

TODO: expose more physics functions, expecially the one for applying forces

Timer
-----

A custom python class is exposed (unreal_engine.FTimerHandler) to support UE4 timers:

```py
# create a timer
timer = self.uobject.set_timer(frequency, callable[, loop, initial])
# clear a timer
timer.clear()
# pause a timer
timer.pause()
# unpause a timer
timer.unpause()
```

Fracturing
----------

Fracturing is one of the best features you get for free in unreal engine.

You can apply damage to destructible objects directly from python (more kind of damages will be added soon)

```py
class DestroyMeComponent:

    def begin_play(self):
        # get a reference to a destructible component in the actor
        self.destructible = self.uobject.get_actor_component_by_type(ue.find_class('DestructibleComponent'))
        
    def tick(self, delta_time):
        pass
        
    def explode(self):
        # damage amount
        amount = 1000
        strength = 20000
        position = self.uobject.get_owner().get_actor_location()
        up = self.uobject.get_owner().get_actor_up()
        self.destructible.destructible_apply_damage(amount, strength, position, up)
    
```

you can now call the 'explode' method via blueprints using the 'Call Python Component Method' node

Another approach (way more easier) would be adding a RadialForceComponent and fire it when you want to destroy something:

```py
# get a reference to the RadialForceComponent
self.radial_force = self.uobject.get_owner().get_actor_component_by_type(ue.find_class('RadialForceComponent'))

# fire it !
self.radial_force.call('FireImpulse')
```



Splines
-------

Splines are another amazing UE4 feature.

The following component shows how to move another actor over a spline path:

```py
class Spline:
    def begin_play(self):
        # get a reference to a spline component
        self.spline = self.uobject.get_owner().get_actor_component_by_type(ue.find_class('SplineComponent'))
        # find the length of the spline
        self.max_distance = self.spline.get_spline_length()
        self.distance = 0.0
        # get a reference to the actor to move (as a blueprint property)
        self.actor_to_move = self.uobject.get_owner().get_property('ObjectToMove')

    def tick(self, delta_time):
        if self.distance >= self.max_distance:
            return
        # find the next point on the spline
        next_point = self.spline.get_world_location_at_distance_along_spline(self.distance)
        self.actor_to_move.set_actor_location(next_point)
        self.distance += 100 * delta_time
```

Blueprints integration
----------------------

You can call blueprints functions (or custom events) via the .call() and .call_function() methods:

```py
your_funny_blueprint_object.call('AFunctionOrACustomEvent with_a_arg')
```

Whenever you need to reference external object, avoid using find_object() and similar. Instead add a public variable in your blueprint
pointing to the specific object. You can then reference this object easily getting the property value:

```py
the_other_object = self.uobject.get_property('target')
the_other_object.set_actor_location(0, 0, 0)
```

.call_function() is more advanced, as it allows for return values and python args:

```py
# an example of moving an object z with curves:
class Curver:
    def begin_play(self):
        self.curve = self.uobject.get_owner().get_property('curve')
        self.accumulator = 0.0
    def tick(self, delta_time):
        location = self.uobject.get_actor_location()
        z = self.curve.call_function('GetFloatValue', self.accumulator) * 100
        self.uobject.set_actor_location(location.x, location.y, z)
        self.accumulator += delta_time

```


Events
------

You can easily bind events (as seen before) with the bind_event function

```py
self.uobject.bind_event('OnActorBeginOverlap', a_funny_callback)
```

Support for mapping custom events directly from python is currently worked on.

If you want to map events from a blueprint to a python function, the best thing to do is using the 'python call' blueprint functions exposed by the various plugin classes:

![Alt text](screenshots/unreal_screenshot3.png?raw=true "Screenshot 3")

Audio
-----

The uobject.play_sound_at_location(sound, position[, volume_multiplier, pitch_multiplier, start_time]) api method is exposed:

```py
# get a reference to asound
sound = ue.find_object('my_sound')
# play the sound at position 0,0,0
self.uobject.play_sound_at_location(sound, FVector(0, 0, 0))
```

If you prefer to work with AudioComponent:

```py
class Sounder:
    def begin_play(self):
        # find the AudioComponent of this actor
        self.audio = self.uobject.get_component_by_type('AudioComponent')
        self.audio.call('Stop')
    def tick(self, delta_time):
        # start the sound when pressing 'A'
        if self.uobject.is_input_key_down('A'):
            self.audio.call('Play')
```

Animations
----------

You can control animation blueprints variables and events easily:

```py
# get a reference to the skeletal mesh
skeletal = self.uobject.get_component_by_type('SkeletalMeshComponent')
# get a reference to the animation class
animation = skeletal.get_anim_instance()

# set a variable
animation.set_property('Speed', 17.0)

# trigger a custom event
animation.call('AttackWithSword')
```

Packaging
---------

When you package your projects, remember to include the libpython (dll or dylib) in the binaries folder and the Scripts directory.

If you do not want to distribute python sources, you can include only the ```__pycache__``` directory with the bytecode.

Do not forget to include python third party modules (if you use any of them in your project)

Examples
--------

This is a PyActor destroying itself whenever another actor overlap it. Remember to add a mesh component to it (like a sphere) and set its collision behaviour as 'OverlapAll'. This could be tested with the third person official template.

```py
class Ball:
    def begin_play(self):
        ue.print_string('Hello')
    def tick(self, delta_time):
        pass
    def on_actor_begin_overlap(self, other_actor):
        ue.print_string('Collided with ' + other_actor.get_name())
        self.uobject.actor_destroy()
```

Now we create (at runtime !!!) a whole new PyActor:

```py
class SuperHero:
    def begin_play(self):
        # spawn a new PyActor
        new_actor = self.uobject.actor_spawn(ue.find_class('PyActor'), Fvector(0, 0, 0),FRotator(0, 0, 90))
        # add a sphere component as the root one
        static_mesh = new_actor.add_actor_root_component(ue.find_class('StaticMeshComponent'), 'SphereMesh')
        # set the mesh as the Sphere asset
        static_mesh.call('SetStaticMesh /Engine/EngineMeshes/Sphere.Sphere')
        # set the python module
        new_actor.set_property('PythonModule', 'gameclasses')
        # set the python class
        new_actor.set_property('PythonClass', 'Vertical')
        
    def tick(self, delta_time):
        pass
```

Integration with PyQT
---------------------

To correctly integrates PyQT with UnrealEngine the python plugin must correctly setup the GIL (and this is done) and exceptions must be managed ad-hoc (not doing it will result in a deadlock whenever a qt signal handler raises an exception)

This is an example of having a QT window along the editor to trigger asset reimporting (pay attention to the sys.excepthook usage):

```py
from PyQt5.QtWidgets import QApplication, QWidget, QListWidget
import unreal_engine as ue
import sys
import traceback

def ue_exception(_type, value, back):
    ue.log_error(value)
    tb_lines = traceback.format_exception(_type, value, back)
    for line in tb_lines:
        ue.log_error(line)

sys.excepthook = ue_exception

skeletal_mappings = {}

def selected_skeletal_mesh(item):
    uobject = skeletal_mappings[item.data()]
    ue.log('Ready to reimport: ' + uobject.get_name())
    uobject.asset_reimport()

app = QApplication([])

win = QWidget()
win.setWindowTitle('Unreal Engine 4 skeletal meshes reimporter')

wlist = QListWidget(win)
for asset in ue.get_assets_by_class('SkeletalMesh'):
    wlist.addItem(asset.get_name())
    skeletal_mappings[asset.get_name()] = asset
    
wlist.clicked.connect(selected_skeletal_mesh)
wlist.show()

win.show()
```

Memory management
-----------------

Dealing with 2 different GC's is really challenging.

PyActor, PyPawn and PythonComponent automatically DECREF's the mapped classes. This should be enough unless you hold references
in the python modules themselves. As this would be a bad programming practice, the current approach should be safe enough.

In addition to this, every time a uobject has to return its UObject mapping, it checks for its validity and safety:

```c
#define ue_py_check(py_u) if (!py_u->ue_object || !py_u->ue_object->IsValidLowLevel() || py_u->ue_object->IsPendingKillOrUnreachable())\
							return PyErr_Format(PyExc_Exception, "PyUObject is in invalid state")
```


Unit Testing
------------

The repository includes a TestingActor asset and a tests.py script. Just add the asset and the script to your project and the test suite will be run. The test suite is still a prototype it will be improved soon.

Threading (Experimental)
------------------------

By default the plugin is compiled without effective python threads support. This is for 2 main reasons:

* we still do not have numbers about the performance impact of constantly acquiring and releasing the GIL
* we need a better test suite

By the way, if you want to play with experimental threading support, just uncomment

```c
//#define UEPY_THREADING 1
```

on top of UnrealEnginePythonPrivatePCH.h and rebuild the plugin.

As with native threads, do not modify (included deletion) UObjects from non-main threads.

Status and Known issues
-----------------------

The project could be considered in beta state.

Exposing the full ue4 api is a huge amount of work, feel free to make pull requests for your specific needs.

.py files are not recognized by the editor. This should be fixed soon

We still do not have a plugin icon ;)

The build system is not very robust. Maybe linking the python static library into the plugin dll could be a better approach.


Contacts
--------

If you want to contact us (for help, support, sponsorship), drop a mail to info at 20tab.com or follow @unbit on twitter
