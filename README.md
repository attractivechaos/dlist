## Generic Data Structures in C

Unlike C++, the C programming language doesn't provide a general mechanism to
implement generic data structures or algorithms. However, it is still possible
to write generic C code matching the performance of type-specific
implemntations. This repo demonstrates four ways to implement a generic
double-linked list in C. Some of these techniques can be adapted to other data
structures with no compromise on performance.

1. With `void*` pointers (`*-void.*`). This is the most common but often the
   least efficient way to implement generic data structures. It requires extra
   malloc per element, which wastes memory and data locality. I don't recommend
   it.

2. With intrusive data structures (`*-intru2.*`). This approach doesn't call
   malloc/etc inside the library code, which gives callers full control of
   memory management. It is the preferred way to implement double-linked
   list, but is not optimal for binary trees because it incurs overhead to
   comparisons between objects. Generally, intrusive data structures are not
   applicable to vectors or [closed hash tables][closed-hash].

3. Combining intrusive data structures and macros (`*-intru1.*`). This is my
   preferred way to implement binary trees (see [kavl.h][kavl]), but for
   double-linked list, it is more complex.

4. With macros (`*-macro.*`). This approach can be optimal for all common data
   structures. However, it involves unusual syntax and is inflexible in terms of
   memory management at the caller end. My [khash.h][khash] library is
   implemented this way. STL containers also follow a similar rationale.

[closed-hash]: https://en.wikipedia.org/wiki/Open_addressing
[khash]: https://github.com/attractivechaos/klib/blob/master/khash.h
[kavl]: https://github.com/attractivechaos/klib/blob/master/kavl.h
