.loop

input
push_s "test"
e_s

	.if
		.break
	.else
		push_s "else\n"
		output	
	.endif
	
input
push_s "test2"
e_s

	.if
		.break
	.else
		push_s "else2\n"
		output
	.endif

.loopend
