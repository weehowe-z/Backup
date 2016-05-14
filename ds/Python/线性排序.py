def movetower(n,source,temp,dest):
    if n==1:
        print "Move a disk from", source, "to", dest
    else:
        movetower (n-1,source,dest,temp)
        movetower (1,source,temp,dest)
        movetower (n-1,temp,source,dest)
