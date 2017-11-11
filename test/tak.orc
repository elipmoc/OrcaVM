.func tak

	.stack_size 3

	def $x 1
	def $y 1
	def $z 1

	store_i $z
	store_i $y
	store_i $x

	load_i $x
	load_i $y

	le_i

	.if
		load_i $y
		return
	.else
		load_i $x
		push_i 1
		sub_i
		load_i $y
		load_i $z
		invoke tak

		load_i $y
		push_i 1
		sub_i
		load_i $z
		load_i $x
		invoke tak

		load_i $z
		push_i 1
		sub_i
		load_i $x
		load_i $y
		invoke tak

		invoke tak
		
	.endif

.func_end

.entry_point

push_i 6
push_i 3
push_i 0

invoke tak



































