def line_search(x,list):
    found="No"
    for i in range(len(list)):
        if list[i]==x:
            print "have found",x,"at",i+1
            found="Yes"
    if found=="No":
        print "There is no",x,"in the list"

def line_search_judge(x,list):            # 1 for exist,0 for not
    for i in range(len(list)):
        if list[i]==x:
            return 1
    return 0

