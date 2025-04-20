,>                 Read first digit into cel 0, second into cel 1
++++++[<-------->-]  Subtract 48 from both (convert ASCII to number)
<[                  Start outer loop (first number times)
  >[->+>+<<]         Copy second number to temp and result
  >>[-<<+>>]         Move temp to result
  <<                 Back to second number
  <-                 Decrease first number
]

>>>                 Go to result cell

>++++++[<++++++++>-]  Set up divisor 10 in cell before result
<<                   Go to result

[->+>+<<]            Copy result to two cells
>>[-<<+>>]           Move one copy to original result again
<<

++++++++++          Add 10 to result
>[-<+++++>]<         Divide by 10 (store quotient in cell 1)

>>++++++++++        Move to quotient (tens), add 48 for ASCII
++++++++++          (total +20)
++++++++++          (total +30 = 48)
.

<[-]                Clear original result (cell 2)
<[-]                Clear original quotient (cell 1)

>>[-]               Clear leftover in temp

<+                  Move to remainder
++++++++++          Add 10 again
>[-<+++++>]<         Divide by 10 (gets remainder this time)

>>++++++++++        Add 48 to make it printable ASCII
++++++++++          (same as acima)
++++++++++          
.
