push_i 1
push_i 2

e_i

.if

push_s "t\n"
output

.else

push_i 2
push_i 3

e_i

	.if
		push_s "t2\n"
		output	

	.else

		push_s "t3\n"
		output
	
	.endif

.endif
