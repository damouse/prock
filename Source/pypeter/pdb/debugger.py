'''
Python live debugging shim for prock. 

Check out the source code for pdb here: https://github.com/python/cpython/blob/master/Lib/pdb.py
'''
import sys
import os
import traceback

import pd
# import tester


class StdIORedirect():

    def write(self, text):
        if len(text.rstrip()):
            print text

    def flush(self):
        # print 'FLUSH'
        pass

    def readline(self):
        # print 'Asked for a line'
        return 's'


def start_pdb(mainpyfile):
    ''' Create an instance of the pdb class with custom stdin/out. This allows us 
    to feed input and output for each step  ''' 

    if not os.path.exists(mainpyfile):
        print 'Error:', mainpyfile, 'does not exist'
        sys.exit(1)

    # Replace pdb's dir with script's dir in front of module search path.
    sys.path[0] = os.path.dirname(mainpyfile)

    redir = StdIORedirect()
    pdb = pd.Pdb(stdout=redir, stdin=redir)

    # while True:
    try:
        pdb._runscript(mainpyfile)
        print "The program completed"
    except Restart:
        print "Restarting", mainpyfile, "with arguments:"
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
        pdb.interaction(None, t)
        print "Post mortem debugger finished. The " + mainpyfile + " will be restarted"


if __name__ == '__main__':
    print 'Starting'
    start_pdb('tester.py')
    # pd.main('tester.py')
