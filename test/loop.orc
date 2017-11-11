.entry_point

def $i 1

push_i 0
g_store_i $i

.loop

g_load_i $i
push_i 10000000

g_i

.if

.break

.endif

g_load_i $i
push_i 1
add_i
g_store_i $i

.loop_end
