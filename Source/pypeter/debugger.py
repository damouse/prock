'''
Python live debugging shim for prock. 

Check out the source code for pdb here: https://github.com/python/cpython/blob/master/Lib/pdb.py

Of importance is the "skip" argument, which specifies which modules to ignore. Use this to avoid system calls
'''
import sys
import os
import traceback
import pd
import bdb

from multiprocessing import Process, Queue
import time
import pprint

from greenlet import greenlet


class Runner(bdb.Bdb):
    '''
    Python native debugger wrapper. 

    Useful in setting this up: https://www.safaribooksonline.com/library/view/python-standard-library/0596000960/ch11s03.html

    Because none of the builtin debugger faculties are built to tick at someone else's pace, this class uses greenlets to 
    block debugger continuation. 
    '''

    def __init__(self, filename):
        bdb.Bdb.__init__(self)
        self.should_break = True
        self.filename = filename

        # The first greenlet sits inside the tick method, always blocked. Calling tick()
        # switches to the second greenlet, which perfroms a full step through the debugger and then switches
        # back. Although now that I think about it a little bit I'm actually not sure how it works.
        self.gr_paused = greenlet(self.tick)
        self.gr_running = greenlet(self._runscript)

    def tick(self):
        # Step the debugger once by switching back into the running greenlet.
        self.gr_running.switch()

    def finished_tick(self):
        # Called by this class once a debugger cycle completes. Resumes control to the "tick" method
        self.gr_paused.switch()

    def user_call(self, frame, args):
        print 'Call'
        name = frame.f_code.co_name or "<unknown>"
        print "call", name, args

        self.set_step()
        self.finished_tick()

    def user_line(self, frame):
        print 'Line'

        if self.should_break:
            self.should_break = False
            self.set_trace()
        else:
            # arrived at breakpoint
            name = frame.f_code.co_name or "<unknown>"
            filename = self.canonic(frame.f_code.co_filename)
            print "break at", filename, frame.f_lineno, "in", name

        self.finished_tick()

    def _runscript(self):
        # Taken from pdb wholesale as a means to bootstrap a debugging session
        # The script has to run in __main__ namespace (or imports from
        # __main__ will break).
        #
        # So we clear up the __main__ and set several special variables
        # (this gets rid of pdb's globals and cleans old variables on restarts).
        import __main__
        __main__.__dict__.clear()
        __main__.__dict__.update({"__name__": "__main__",
                                  "__file__": self.filename,
                                  # "__builtins__": __builtins__,
                                  })

        # When bdb sets tracing, a number of call and line events happens
        # BEFORE debugger even reaches user's code (and the exact sequence of
        # events depends on python version). So we take special measures to
        # avoid stopping before we reach the main script (see user_line and
        # user_call for details).
        self._wait_for_mainpyfile = 1
        self.mainpyfile = self.canonic(self.filename)
        self._user_requested_quit = 0
        statement = 'execfile(%r)' % self.filename
        self.run(statement)


def main():
    print 'Starting'

    dbg = Runner('../../samplecode.py')

    for i in range(20):
        import time
        time.sleep(.1)
        dbg.tick()


if __name__ == '__main__':
    main()
