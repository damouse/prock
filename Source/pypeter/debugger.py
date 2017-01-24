'''
Python live debugging shim for prock. 

Check out the source code for pdb here: https://github.com/python/cpython/blob/master/Lib/pdb.py

Of importance is the "skip" argument, which specifies which modules to ignore. Use this to avoid system calls
'''
import sys
import os
import traceback
import pd

from multiprocessing import Process, Queue
import time
import pprint


#   File "../../samplecode.py", line 2, in <module>
#     a = 1
#   File "C:\Python27\lib\bdb.py", line 49, in trace_dispatch
#     return self.dispatch_line(frame)
#   File "C:\Python27\lib\bdb.py", line 67, in dispatch_line
#     self.user_line(frame)
#   File "D:\Code\unreal\Prock\Source\pypeter\pd.py", line 158, in user_line
#     self.interaction(frame, None)
#   File "D:\Code\unreal\Prock\Source\pypeter\pd.py", line 211, in interaction
#     self.cmdloop()
#   File "C:\Python27\lib\cmd.py", line 136, in cmdloop
#     line = self.stdin.readline()
#   File "D:\Code\unreal\Prock\Source\pypeter\debugger.py", line 149, in readline
#     raise Exception
# Exception
# Uncaught exception. Entering post mortem debuggingTraceback (most recent call last):
#   File "D:\Code\unreal\Prock\Source\pypeter\debugger.py", line 191, in <module>


class ProckBugger(pd.Pdb):

    def dispatch_line(self, frame):
        if self.stop_here(frame) or self.break_here(frame):
            # Block here for input on the object
            # import time
            # time.sleep(1)
            # self.do_step(None)

            self.user_line(frame)

            if self.quitting:
                raise BdbQuit
        return self.trace_dispatch

    def trace_dispatch(self, frame, event, arg):
        print event, frame, arg
        # print locals()

        if self.quitting:
            return  # None
        if event == 'line':
            # print 'rigged dispatch'
            # return self.dispatch_line(frame)
            # Returning dispatch_line blocks on user input
            return None
        if event == 'call':
            return self.dispatch_call(frame, arg)
        if event == 'return':
            return self.dispatch_return(frame, arg)
        if event == 'exception':
            return self.dispatch_exception(frame, arg)
        if event == 'c_call':
            return self.trace_dispatch
        if event == 'c_exception':
            return self.trace_dispatch
        if event == 'c_return':
            return self.trace_dispatch
        print 'bdb.Bdb.dispatch: unknown debugging event:', repr(event)
        return self.trace_dispatch


# Subclass pdb.PDB and override cmdloop, called in pd.py:209
# Or just override cmdloop() in cmd.py
class Runner():
    ''' A pynative shim that acts as an interface to an executing script '''

    def __init__(self, path, redir):
        self.mainpyfile = path
        self.redir = redir

    def runall(self):
        ''' Create an instance of the pdb class with custom stdin/out. This allows us 
        to feed input and output for each step  '''

        if not os.path.exists(self.mainpyfile):
            print 'Error:', self.mainpyfile, 'does not exist'
            sys.exit(1)

        # Replace pdb's dir with script's dir in front of module search path.
        sys.path[0] = os.path.dirname(self.mainpyfile)

        # self.redir = StdIORedirect()
        self.debugger = ProckBugger()
        # self.debugger = pd.Pdb(stdout=self.redir, stdin=self.redir)

        try:
            self.debugger._runscript(self.mainpyfile)
            print "The program completed"
        # except Restart:
        #     print "Restarting", self.mainpyfile, "with arguments:"
        #     print "\t" + " ".join(sys.argv[1:])
        except SystemExit:
            # In most cases SystemExit does not warrant a post-mortem session.
            print "The program exited via sys.exit(). Exit status: ", sys.exc_info()[1]
        except SyntaxError:
            traceback.print_exc()
            sys.exit(1)
        except:
            import traceback
            traceback.print_exc()
            print "Uncaught exception. Entering post mortem debugging"
            print "Running 'cont' or 'step' will restart the program"
            t = sys.exc_info()[2]
            debugger.interaction(None, t)
            print "Post mortem debugger finished. The " + self.mainpyfile + " will be restarted"

# Put redirecotr on a thread
# Main thread waits 1s, sleeps, then calls worker thread


class StdIORedirect():

    def __init__(self):
        self.input_queue = Queue()
        self.output_queue = Queue()
        self.resultString = ''

    def write(self, text):

        if len(text.rstrip()):
            print text
            # self.resultString += '\n' + text

        # if '(Pdb)' in text:
        #     self.output_queue.put(self.resultString)
        #     self.resultString = ''

    def flush(self):
        # print 'FLUSH'
        pass

    def readline(self):
        ''' Makes PDB step. Could do it manually, im sure '''
        raise Exception
        return 's'

        print 'Asked for a line'
        ret = self.input_queue.get()
        print 'returning a line', ret
        return ret


def main():
    print 'Starting'

    input_redir = StdIORedirect()
    dbg = Runner('../../samplecode.py', input_redir)
    dbg.runall()
    return

    # input_thread = Process(target=dbg.runall)
    # input_thread.start()

    # input_redir.input_queue.put('s')
    # print input_redir.output_queue.get()
    # time.sleep(1)

    # input_redir.input_queue.put('s')
    # print input_redir.output_queue.get()
    # time.sleep(1)

    # input_redir.input_queue.put('s')
    # print input_redir.output_queue.get()
    # time.sleep(1)

    # input_redir.input_queue.put('q')

    # input_redir.input_queue.task_done()

    # input_redir.input_queue.put('s')
    # time.sleep(1)

    # dbg.runall()

    # pd.main('tester.py')

if __name__ == '__main__':
    main()
