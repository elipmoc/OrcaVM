push_i 1
g_store_i 1

label:@loop

g_load_i 1
push_i 100000
le_i
jump_false @end

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

jump_false @p1

push_s "FizzBuzz\n"
output
jump @pluscnt

label:@p1

g_load_i 1
push_i 3
mod_i
push_i 0
e_i
jump_false @p2

push_s "Fizz\n"
output

jump @pluscnt

label:@p2

g_load_i 1
push_i 5
mod_i
push_i 0
e_i

jump_false @num

push_s "Buzz\n"
output

jump @pluscnt

label:@num

push_s "else\n"
output

label:@pluscnt

g_load_i 1
push_i 1
add_i
g_store_i 1

jump @loop

label:@end

g_load_i 1
