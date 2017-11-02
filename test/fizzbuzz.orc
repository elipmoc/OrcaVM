push_i 1
g_store_i 1

.loop

g_load_i 1
push_i 1000000
ge_i

.if
	.break
.endif

g_load_i 1
push_i 3
mod_i
push_i 0
e_i

g_load_i 1
push_i 5
mod_i
push_i 0
e_i

and

.if
	push_s "FizzBuzz\n"
	output

.else

	g_load_i 1
	push_i 3
	mod_i
	push_i 0
	e_i

	.if
		push_s "Fizz\n"
		output
	.else

		g_load_i 1
		push_i 5
		mod_i
		push_i 0
		e_i

		.if
			push_s "Buzz\n"
			output
		.else
			g_load_i 1
			itos
			push_s "\n"
			add_s
			output
		.endif
	.endif
.endif

g_load_i 1
push_i 1
add_i
g_store_i 1


.loopend
