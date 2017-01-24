
class myDebugger(bdb.Bdb):
    runn = 0

    def user_call(self, frame, args):
        print 'Call'
        name = frame.f_code.co_name or "<unknown>"
        print "call", name, args
        self.set_step()  # continue

    def user_line(self, frame):
        print 'Line'
        if self.runn:
            self.runn = 0
            self.set_trace()  # start tracing
        else:
            # arrived at breakpoint
            name = frame.f_code.co_name or "<unknown>"
            filename = self.canonic(frame.f_code.co_filename)
            print "break at", filename, frame.f_lineno, "in", name
        print "continue..."
        self.set_step()  # continue to next breakpoint

    def user_return(self, frame, value):
        print 'Return'
        name = frame.f_code.co_name or "<unknown>"
        print "return from", name, value
        print "continue..."
        self.set_step()  # continue

    def user_exception(self, frame, exception):
        print 'Return'
        name = frame.f_code.co_name or "<unknown>"
        print "exception in", name, exception
        print "continue..."
        self.set_step()  # continue

    def _runscript(self, filename):
        # Taken from pdb wholesale as a means to bootstrap a debugging session
        # The script has to run in __main__ namespace (or imports from
        # __main__ will break).
        #
        # So we clear up the __main__ and set several special variables
        # (this gets rid of pdb's globals and cleans old variables on restarts).
        import __main__
        __main__.__dict__.clear()
        __main__.__dict__.update({"__name__": "__main__",
                                  "__file__": filename,
                                  # "__builtins__": __builtins__,
                                  })

        # When bdb sets tracing, a number of call and line events happens
        # BEFORE debugger even reaches user's code (and the exact sequence of
        # events depends on python version). So we take special measures to
        # avoid stopping before we reach the main script (see user_line and
        # user_call for details).
        self._wait_for_mainpyfile = 1
        self.mainpyfile = self.canonic(filename)
        self._user_requested_quit = 0
        statement = 'execfile(%r)' % filename
        print statement
        self.run(statement)

db = myDebugger()
db.runn = 1
# db.set_break('../../samplecode.py', 1)
db._runscript('../../samplecode.py')
