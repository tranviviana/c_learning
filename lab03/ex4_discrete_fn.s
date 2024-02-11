.globl f # this allows other files to find the function f

# f takes in two arguments:
# a0 is the value we want to evaluate f at
# a1 is the address of the "output" array (read the lab spec for more information).
# The return value should be stored in a0
f:
    # Your code here
    addi t0 a0 3 #the index is 3+ the value inputted
    slli t2 t0 2 #multiply by the size of the integers (4 bytes)
    add t2 t2 a1 #apply offset to initial address of output array
    lw a0 0(t2) #read array at initial index
    # This is how you return from a function. You'll learn more about this later.
    # This should be the last line in your program.
    jr ra
