.func fib

.stack_size 1

store_i 0

load_i 0
push_i 2
l_i

.if
	load_i 0
	return

.else

	load_i 0
	push_i 1
	sub_i

	invoke fib

	load_i 0
	push_i 2
	sub_i

	invoke fib

	add_i

	return

.endif

return

.func_end

.entry_point

push_i 30

invoke fib

itos
push_s "\n"
add_s

output
