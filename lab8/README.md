# Hashing

This lab investigates hash structures. The goal is to have fast insertion,
retrieval, and deletion of any given item. Assuming that the original memory
allocation of some object is properly optimized --a separate issue-- the main
bottleneck in working with allocated items is the time it takes to insert,
retrieve, and delete them as needed by the program. The worst cases are
unsorted containers like a singly linked list. One must iterate over the list
until finding the desired item.  Slightly better are sorted containers, though
binary searching is still not as fast as hashing. 

The trick comes by linking the objects and their addresses mathematically. If
one can develop such a function, then the bottle-neck becomes the speed of 
computing the function. This is better referred to as hashing. It is done by
taking a property of the object, usually referred to as the `key`, and then
`hashing` it with a suitable function to generate a memory location, sometimes
called an `index`.

`key` -> `hash` -> `index`

Insertion, retrieval/search, and deletion all become (essentially) the same
mathematical process. Consequently, average insertion, retrieval, and deletion
complexities all reduce to O(1).  This is a nice perk, and entire technologies
wrap themselves around the concept. Redis, a popular key-value store, is one 
such example.

# Implementation

Here, I use what I think is referred to as a coalescing hash map. Essentially, 
the buckets contain nodes with the object itself and a pointer to the next 
node. This way, if one encounters a collision upon hashing an object, one 
simply iterates through the singly linked list until the pointer to the next 
node is NULL, and we then insert the object.

# Compilation and Memory Checking

    $ g++ -g main.cpp ../student.* -o lab4
    $ ./lab4
    $ valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes ./lab4
