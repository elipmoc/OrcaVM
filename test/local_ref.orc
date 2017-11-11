.func test

	def $i 1
	def $n 1

	.stack_size 2

	push_i 3
	store_i $i

	load_a $i
	store_a $n

	load_i $n
	itos
	push_s "\n"
	add_s
	output

	push_i 2
	store_i $n

	load_i $i

.func_end

.entry_point

invoke test
