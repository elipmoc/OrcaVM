.func test

	.stack_size 4

	def $s 1
	def $arr 3
	
	load_a $i
	push_i 0
	astore_a $arr

	push_i 5
	push_i 0
	astore_i $arr

	load_i $i

.func_end

.entry_point

def $arr 5
def $i 1

g_load_a $i
push_i 0
g_astore_a $arr

push_i 3
push_i 0
g_astore_i $arr

g_load_i $i

invoke test
