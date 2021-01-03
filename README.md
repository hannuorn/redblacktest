## Red-black tree in C++

Simple C++ implementation of a red-black tree and
a performance comparison with `std::map`.

Built in Visual Studio 2019, the results look like this:


```
RB_Tree vs. std::map
Adding and removing 4000000 nodes

RB_Tree... elapsed time: 0.989817 seconds.

std::map...elapsed time: 1.21503 seconds.
```

Obviously, `std::map` is much more feature-rich and complex than
my simple and straightforward red-black exercise, so it is not
a fair comparison - I do not believe for a second that my implementation
is better in any sense, although it was marginally quicker in this test.

However, the test demonstrates how a good algorithm can yield great
results even when you are not trying to 'optimize' your code.
No effort was applied to make this code fast. It is a straightforward
implementation of the red-black algorithm as described by
*Cormen, Thomas H., et al (2009), Introduction to Algorithms, Third Edition*.
