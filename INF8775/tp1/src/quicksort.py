import random

def quicksort(the_list, start, end, random_pivot=False):
    if start < end:
        pivot_index = partition(the_list, start, end, random_pivot)
        quicksort(the_list, start, pivot_index - 1, random_pivot)
        quicksort(the_list, pivot_index + 1, end, random_pivot)


def quicksort_threshold(theList, start, end, random_pivot=False):
    do_quicksort(end, random_pivot, start, theList)


def quicksort_random(the_list, start, end, random_pivot=True):
    do_quicksort(end, random_pivot, start, the_list)


def do_quicksort(end, random_pivot, start, the_list):
    if end - start < 15:
        the_list[start:end + 1] = sorted(the_list[start:end + 1])
    else:
        pivot_index = partition(the_list, start, end, random_pivot)
        quicksort(the_list, start, pivot_index - 1, random_pivot)
        quicksort(the_list, pivot_index + 1, end, random_pivot)


def partition(the_list, start, end, random_pivot):
    if random_pivot:
        pivot_index = random.randint(start, end)
        the_list[start], the_list[pivot_index] = the_list[pivot_index], the_list[start]
    pivot = the_list[start]
    i = start + 1
    j = end

    while True:
        while i <= j and the_list[i] <= pivot:
            i += 1
        while i <= j and the_list[j] >= pivot:
            j -= 1
        if i <= j:
            the_list[i], the_list[j] = the_list[j], the_list[i]
        else:
            break

    the_list[start], the_list[j] = the_list[j], the_list[start]

    return j
