'''
Python live debugging shim for prock. 

Check out the source code for pdb here: https://github.com/python/cpython/blob/master/Lib/pdb.py

Of importance is the "skip" argument, which specifies which modules to ignore. Use this to avoid system calls
'''
import sys
import os
import traceback
import pdb


class Runner():
    ''' A pynative shim that acts as an interface to an executing script '''

    def __init__(self, path):
        self.mainpyfile = path

    def runall(self):
        ''' Create an instance of the pdb class with custom stdin/out. This allows us 
        to feed input and output for each step  '''

        if not os.path.exists(self.mainpyfile):
            print 'Error:', self.mainpyfile, 'does not exist'
            sys.exit(1)

        # Replace pdb's dir with script's dir in front of module search path.
        sys.path[0] = os.path.dirname(self.mainpyfile)

        redir = StdIORedirect()
        debugger = pdb.Pdb(stdout=redir, stdin=redir)

        try:
            debugger._runscript(self.mainpyfile)
            print "The program completed"
        except Restart:
            print "Restarting", self.mainpyfile, "with arguments:"
            print "\t" + " ".join(sys.argv[1:])
        except SystemExit:
            # In most cases SystemExit does not warrant a post-mortem session.
            print "The program exited via sys.exit(). Exit status: ", sys.exc_info()[1]
        except SyntaxError:
            traceback.print_exc()
            sys.exit(1)
        except:
            traceback.print_exc()
            print "Uncaught exception. Entering post mortem debugging"
            print "Running 'cont' or 'step' will restart the program"
            t = sys.exc_info()[2]
            debugger.interaction(None, t)
            print "Post mortem debugger finished. The " + self.mainpyfile + " will be restarted"


class StdIORedirect():

    def write(self, text):
        if len(text.rstrip()):
            print text

    def flush(self):
        # print 'FLUSH'
        pass

    def readline(self):
        ''' Makes PDB step. Could do it manually, im sure '''
        # print 'Asked for a line'
        return 's'


if __name__ == '__main__':
    print 'Starting'
    dbg = Runner('../../samplecode.py')
    dbg.runall()
    # pd.main('tester.py')
