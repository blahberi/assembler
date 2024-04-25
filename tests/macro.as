mcr outer_macro
mov #10, r1
inner_macro
add r1, r2
endmcr

.define yummy = 5
mcr inner_macro
mov #yummy, r1
sub #20, r2
endmcr

outer_macro
prn r1
hlt