main   addi     1,0,1
       addi     2,0,2   
       addi     3,0,3
       addi     4,0,4
       addi     5,0,0
for    slti     6,5,10
       beq      6,1,endf      
       addi     2,2,5
       addi     3,3,5
       addi     4,4,5
       addi     5,5,1
       j        for                 
end    sw       2,0,arr
       sw       3,1,arr
       sw       4,2,arr
       halt
array  .space   3