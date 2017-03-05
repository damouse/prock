'''
Python live debugging shim for prock. 

Check out the source code for pdb here: https://github.com/python/cpython/blob/master/Lib/pdb.py

Of importance is the "skip" argument, which specifies which modules to ignore. Use this to avoid system calls
'''
import sys
import os
import traceback
import bdb
import copy

from multiprocessing import Process, Queue, Pipe
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

        self.LOG = True
        self.should_break = True
        self.kill = False
        self.filename = filename
        self.forget()

        # Locals, globals, and newly created variables
        self.locals, self.globals, self.new = {}, {}, {}

        # The first greenlet sits inside the tick method, always blocked. Calling tick()
        # switches to the second greenlet, which perfroms a full step through the debugger and then switches
        # back. Although now that I think about it a little bit I'm actually not sure how it works.
        self.gr_paused = greenlet(self.step)
        self.gr_running = greenlet(self._runscript)

        # Backup module state by copying globals
        self.backup_env = {k: v for k, v in globals().iteritems()}

    # Ticking
    def forget(self):
        self.lineno = None
        self.stack = []
        self.curindex = 0
        self.curframe = None
        self.curframe_locals = {}

    def step(self):
        # Step the debugger once by switching back into the running greenlet. Save variables after the tick.
        # self.set_step()
        self.gr_running.switch()

        self.globals = self.curframe_locals
        l = {k: v for k, v in self.globals.iteritems() if not '__' in k}
        self.new = {k: v for k, v in l.iteritems() if k not in self.locals}
        self.locals = l

    def finished_step(self, frame, label):
        # Called by this class once a debugger cycle completes. Resumes control to the "tick" method
        self.collect_locals(frame)
        self.print_frame_info(frame, label)

        if self.kill:
            self.set_quit()
            self.reset()

            raise greenlet.GreenletExit
        else:
            self.gr_paused.switch()

    def print_frame_info(self, frame, label):
        filename = self.canonic(frame.f_code.co_filename)
        name = frame.f_code.co_name or "<unknown>"
        self.lineno = int(frame.f_lineno)

        if self.LOG:
            print "%s: %s#%s %s" % (label, filename, frame.f_lineno, name)

    def collect_locals(self, frame):
        self.forget()
        self.stack, self.curindex = self.get_stack(frame, None)
        self.curframe = self.stack[self.curindex][0]
        self.curframe_locals = self.curframe.f_locals

    # user_ overrides
    def user_call(self, frame, args):
        ''' The first tick sends a couple of frames we dont care about '''
        self.finished_step(frame, "Call")

    def user_line(self, frame):
        if self.should_break:
            self.should_break = False
            self.set_trace()
        # else:
        #     if 'bdb.py' in self.canonic(frame.f_code.co_filename):
        #         return

        self.finished_step(frame, "Line")

    def user_return(self, frame, return_value):
        """This method is called when a return trap is set here."""
        self.finished_step(frame, "Return")

    def user_exception(self, frame, exc_info):
        exc_type, exc_value, exc_traceback = exc_info
        """This method is called if an exception occurs,
        but only if we are to stop at or just below this level."""

        self.finished_step(frame, "Exception")

    def _runscript(self):
        # Taken from pdb as a way to start a whole file bootstrap. Kicks off the debugger
        import __main__
        __main__.__dict__.clear()
        __main__.__dict__.update({"__name__": "__main__", "__file__": self.filename})
        self._wait_for_mainpyfile = 1
        self.mainpyfile = self.canonic(self.filename)
        self._user_requested_quit = 0
        statement = 'execfile(%r)' % self.filename
        self.run(statement)

    def reset_env(self):
        ''' Put the main dict back '''
        self.set_quit()
        self.reset()
        self.kill = True
        self.gr_running.switch()

        import sys
        module = sys.modules[__name__]
        module.__dict__.clear()

        for k, v in self.backup_env.iteritems():
            setattr(module, k, v)


def main():
    # Testing function
    print 'Starting'
    dbg = Runner('../../samplecode.py')

    # Simulate delayed "ticks" based on user interaction in ue4
    for i in range(20):
        import time
        time.sleep(.4)
        dbg.step()

        import pprint
        realLocals = {k: v for k, v in dbg.locals.iteritems() if not '__' in k}

        if 'globals' in realLocals:
            continue

        print "New:", dbg.new
        pprint.pprint(realLocals)

    print 'Done'
    dbg.reset_env()

if __name__ == '__main__':
    main()
