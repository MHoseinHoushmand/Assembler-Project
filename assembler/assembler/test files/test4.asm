main   addi     1,0,5   #add
       addi     2,0,20   #add
       addi     3,0,30   #add
       jalr     5,1    #jump to addfunc
       sw       2,0,sum 
addfun add      2,2,3    #add
       slti     2,2,10      
       jalr     1,5  
addfun add      2,2,3    #add
       slti     2,2,10      
       jalr     1,5              
done   halt
sum    .space   1