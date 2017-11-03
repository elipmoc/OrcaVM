.func fib

	.stack_size 1

	def $n 1

	store_i $n	
	
	load_i $n
	push_i 2
	l_i

	.if
		load_i $n
		return
	.else
		load_i $n
		push_i 1
		sub_i
		invoke fib

		load_i $n
		push_i 2
		sub_i
		
		invoke fib

		add_i

		return
	.endif

.func_end

.entry_point

push_i 30

invoke fib

itos
push_s "\n"
add_s

output
