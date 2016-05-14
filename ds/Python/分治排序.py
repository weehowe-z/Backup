def merge(lst1,lst2,lst3):
    i1,i2,i3=0,0,0
    n1,n2=len(lst1),len(lst2)
    while i1<n1 and i2<n2:
        if lst1[i1]<lst2[i2]:
            lst3[i3]=lst1[i1]
            i1+=1
        else:
            lst3[i3]=lst2[i2]
            i2+=1
        i3+=1
    while i1<n1:
        lst3[i3]=lst1[i1]
        i3+=1
        i1+=1
    while i2<n2:
        lst3[i3]=lst2[i2]
        i3+=1
        i2+=1
    return lst3

def mergeSort(nums):
    n=len(nums)
    if n>1:
        m=n/2
        nums1,nums2=nums[:m],nums[m:]
        mergeSort(nums1)
        mergeSort(nums2)
        merge(nums1,nums2,nums)
    return nums

