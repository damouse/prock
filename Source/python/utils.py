
def log(s):
    ''' Use ue.log vs print based on where we are '''

    try:
        import unreal_engine as ue
        ue.log(s)
    except Exception as e:
        print s
