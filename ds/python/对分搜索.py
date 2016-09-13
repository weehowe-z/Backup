
def half_search_judge(x,list):    #must be orderd from small to big
    n_min=0
    n_max=len(list)-1
    while n_min<=n_max:
        mid=(n_max+n_min)/2
        if list[mid]==x:
            return 1
        elif list[mid]<x:
            n_min=mid+1
        else:
            n_max=mid-1
    return 0


def research_bin(x, list, n_min, n_max):
    if n_min>n_max:
        return 0
    mid=(n_max+n_min)/2
    if x==list[mid]:
        return 1
    elif x<list[mid]:
        return research_bin(x,list,n_min,mid-1)
    else:
        return research_bin(x,list,mid+1,n_max)
def recursion_half_research(x,list):
    return research_bin(x,list,0,len(list)-1)
