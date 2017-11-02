push_i 1
g_store_i 1

.loop

push_i 500
g_load_i 1
le_i

.if
	.break
.endif

g_load_i 1
itos
push_s "\n"
add_s
output

g_load_i 1
push_i 1
add_i
g_store_i 1

.loopend
