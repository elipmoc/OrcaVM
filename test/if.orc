push_i 1
push_i 2
e_i

.if

push_s "true\n"
output

.else

push_s "false\n"
output

.endif

push_s "end\n"
output
