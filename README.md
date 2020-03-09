# cpp-project
Works for test 1,2,5. 3 and 4 are relatively in order, but when the robot reaches a blank after what has been sorted,
it places the blocks even if it's out of order. Maybe make the robot start at the beginning and check every block when it places all of them?
Or check the block before and see if it's in order, if not, recursively shift all the blocks back in order.

Some of the functions aren't using the provided functions, also the functions for giving the blocks have been slightly modified to prevent trying to get a block when the string is empty. There is probably a better solution for isDone(), but I've been focusing on getting it to work first.
