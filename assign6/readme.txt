The most difficult part of implementing multithreading into this program 
was creating a structure to give inputs (such as the number of threads, 
the index of the current thread, and a pointer to a shared scene variable) 
and store outputs (scaled_color array for every pixel), and then giving this 
structure to each thread.
The other, more conceptual difficulty was deciding how to split the work 
between an unknown number of threads. I decided to give each consecutive 
pixel to a different thread, based on ((px * height + py ) % nthreads).

My solution allows vast improvements through parallelization, turning a 56 
second process into a 7 second one. As expected, the user time stays the 
same regardless of parallelization, since the same amount of work is just 
split between more simultaneous threads.
