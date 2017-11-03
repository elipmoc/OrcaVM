.func test2

	.stack_size 1

	def $n 1
	def $i 1

	push_i 4

	store_i $n

	load_i $n

	return

.func_end

.func test1

	.stack_size 1

	def $n 1

	push_i 3

	store_i $n

	load_i $n

	invoke test2

	add_i

	return

.func_end

.entry_point

invoke test1

itos
push_s "\n"
add_s

output
