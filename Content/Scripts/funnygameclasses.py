import unreal_engine as ue
import sys

class Hero:

    # this is called on game start
    def begin_play(self):
        ue.log('Trying to import the baron. Current path: ')

        import redbaron
        
        ue.log('Succees!')
        ue.log(redbaron)

    # this is called at every 'tick'    
    def tick(self, delta_time):
        # get current location
        location = self.uobject.get_actor_location()
        # increase Z honouring delta_time
        location.z += 100 * delta_time
        # set new location
        self.uobject.set_actor_location(location)