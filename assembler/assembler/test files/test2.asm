main   addi     1,0,15   #add
       addi     2,0,-11   #add
       sub      2,2,1
       nand     3,2,1      
       or       4,3,2
       lui      4,20
       sw       4,0,result       
       lw       5,0,result   
       halt
result .space   1