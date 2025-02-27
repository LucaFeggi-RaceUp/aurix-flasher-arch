# tric_asm_file_start
	.file	"flash_TC4xx.c"
	.file	"flash_TC4xx.c"
.section .text,"ax",@progbits
.Ltext0:
	.align 1
	.global	start
	.type	start, @function
start:
.LFB0:
	.file 1 "flash_TC4xx.c"
	.loc 1 37 1
	.loc 1 38 3
#APP
	# 38 "flash_TC4xx.c" 1
	.global _start
	# 0 "" 2
	.loc 1 39 3
	# 39 "flash_TC4xx.c" 1
	 _start:	 nop
	# 0 "" 2
	.loc 1 40 3
	# 40 "flash_TC4xx.c" 1
	 nop
	# 0 "" 2
	.loc 1 41 3
	# 41 "flash_TC4xx.c" 1
	 movh.a   %a10,hi:(0x70004000)
	# 0 "" 2
	.loc 1 42 3
	# 42 "flash_TC4xx.c" 1
	 lea      %a10,[%a10]lo:(0x70004000)
	# 0 "" 2
	.loc 1 43 3
	# 43 "flash_TC4xx.c" 1
	 ja flashing
	# 0 "" 2
	.loc 1 44 1 is_stmt 0
#NO_APP
	ret	#start
.LFE0:
	.size start, .-start
	.global	start_end
start_end:
	.align 1
	.global	flashing
	.type	flashing, @function
flashing:
.LFB1:
	.loc 1 48 1 is_stmt 1
.LVL0:
	.loc 1 49 3
	.loc 1 50 3
	.loc 1 51 3
	.loc 1 52 3
	.loc 1 53 3
	.loc 1 54 3
	.loc 1 55 3
	.loc 1 58 3
	.loc 1 58 47 is_stmt 0
	mov	%d2, 255
	movh.a	%a3, 63492
	lea	%a3, [%a3] 20
	st.w	[%a3]0, %d2
	.loc 1 59 3 is_stmt 1
	.loc 1 59 8 is_stmt 0
	ld.w	%d2, [%a4] 16
	.loc 1 48 1
	lea	%SP, [%SP] -560
.LCFI0:
	.loc 1 48 1
	mov.aa	%a2, %a4
	.loc 1 59 8
	lea	%a3, [%a4] 16
	.loc 1 59 6
	jeq	%d2, 1, .L91
.LVL1:
.L4:
	.loc 1 129 3 is_stmt 1
	.loc 1 129 8 is_stmt 0
	ld.w	%d2, [%a2] 16
	lea	%a3, [%a2] 16
	.loc 1 129 6
	jeq	%d2, 2, .L92
	.loc 1 164 3 is_stmt 1
	.loc 1 164 8 is_stmt 0
	ld.w	%d2, [%a2] 16
	lea	%a3, [%a2] 16
	.loc 1 164 6
	jeq	%d2, 3, .L93
.L31:
	.loc 1 289 3 is_stmt 1
	.loc 1 289 8 is_stmt 0
	ld.w	%d2, [%a2] 16
	lea	%a3, [%a2] 16
	.loc 1 289 6
	jeq	%d2, 4, .L94
	.loc 1 361 3 is_stmt 1
	.loc 1 361 49 is_stmt 0
	mov	%d2, 256
	st.w	[%a2] 16, %d2
	.loc 1 362 3 is_stmt 1
#APP
	# 362 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
	.loc 1 363 3
	.loc 1 364 1 is_stmt 0
#NO_APP
	mov	%d2, 0
	ret	#flashing
.L94:
	.loc 1 291 7 is_stmt 1
	.loc 1 291 19 is_stmt 0
	mov	%d2, 256
.LBB2:
	.loc 1 313 51
	movh.a	%a4, 63492
	movh	%d7, 49152
.LBE2:
	.loc 1 291 19
	st.w	[%a3]0, %d2
	.loc 1 292 7 is_stmt 1
	.loc 1 292 12 is_stmt 0
	ld.a	%a3, [%a2] 20
.LVL2:
	.loc 1 293 7 is_stmt 1
	.loc 1 293 21
.LBB3:
	.loc 1 329 15 is_stmt 0
	movh	%d2, 61167
	.loc 1 324 38
	movh	%d9, 43691
.LBE3:
	.loc 1 293 18
	ld.w	%d3, [%a3]0
.LBB4:
	.loc 1 345 14
	movh.a	%a5, 63492
	.loc 1 346 18
	movh	%d5, 65528
	.loc 1 300 12
	mov	%d10, 0
	.loc 1 313 51
	lea	%a4, [%a4] 272
	add	%d7, 3
	.loc 1 305 98
	movh	%d6, 21760
	.loc 1 329 15
	addi	%d2, %d2, -4370
	.loc 1 324 38
	addi	%d9, %d9, -21846
	.loc 1 345 14
	lea	%a5, [%a5] 268
	.loc 1 346 18
	addi	%d5, %d5, -9
	.loc 1 349 51
	movh	%d8, 49152
	.loc 1 337 98
	mov	%d1, -1025
.LBE4:
	.loc 1 293 21
	jne	%d3, -1, .L49
.L61:
	.loc 1 357 7 is_stmt 1
	.loc 1 357 52 is_stmt 0
	mov	%d2, 0
	st.w	[%a2] 16, %d2
	.loc 1 358 7 is_stmt 1
#APP
	# 358 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
	.loc 1 361 3
	.loc 1 361 49 is_stmt 0
#NO_APP
	mov	%d2, 256
	st.w	[%a2] 16, %d2
	.loc 1 362 3 is_stmt 1
#APP
	# 362 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
	.loc 1 363 3
	.loc 1 364 1 is_stmt 0
#NO_APP
	mov	%d2, 0
	ret	#flashing
.LVL3:
.L96:
.LBB5:
	.loc 1 305 8 is_stmt 1
	.loc 1 305 86 is_stmt 0
	ld.a	%a7, [%a7]0
	.loc 1 305 54
	ld.w	%d3, [%a7]0
	.loc 1 305 41
	ld.a	%a7, [%a3] 20
	.loc 1 305 98
	or	%d3, %d6
	.loc 1 305 52
	st.w	[%a7]0, %d3
	.loc 1 306 8 is_stmt 1
#APP
	# 306 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 307 8
	.loc 1 307 86 is_stmt 0
#NO_APP
	ld.a	%a7, [%a3] 20
	.loc 1 307 54
	ld.w	%d3, [%a7]0
	.loc 1 307 41
	ld.a	%a7, [%a3] 20
	.loc 1 307 98
	insert	%d3, %d3, 15, 10, 1
	.loc 1 307 52
	st.w	[%a7]0, %d3
	.loc 1 308 8 is_stmt 1
#APP
	# 308 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 316 4
	.loc 1 316 12 is_stmt 0
#NO_APP
	ld.w	%d3, [%a3] 24
	.loc 1 316 17
	ld.w	%d4, [%a6]0
	.loc 1 316 7
	jeq	%d3, %d4, .L95
.LVL4:
.L89:
	.loc 1 329 15
	st.w	[%a3] 12, %d2
.L56:
	.loc 1 331 4 is_stmt 1
	.loc 1 331 12 is_stmt 0
	ld.w	%d3, [%a3] 20
	lea	%a6, [%a3] 20
	.loc 1 331 7
	jz	%d3, .L57
	.loc 1 333 8 is_stmt 1
	.loc 1 333 46 is_stmt 0
	ld.a	%a6, [%a6]0
	.loc 1 333 14
	ld.w	%d3, [%a6] 8196
	.loc 1 333 12
	st.w	[%SP] 40, %d3
	.loc 1 334 8 is_stmt 1
	.loc 1 334 18 is_stmt 0
	ld.w	%d3, [%SP] 40
	and	%d3, %d5
	.loc 1 334 11
	jz	%d3, .L58
	.loc 1 334 34 is_stmt 1 discriminator 1
	.loc 1 334 41 is_stmt 0 discriminator 1
	st.w	[%a3] 12, %d2
.L58:
	.loc 1 335 8 is_stmt 1
	.loc 1 335 86 is_stmt 0
	ld.a	%a6, [%a3] 20
	.loc 1 335 54
	ld.w	%d3, [%a6]0
	.loc 1 335 41
	ld.a	%a6, [%a3] 20
	.loc 1 335 98
	or	%d3, %d6
	.loc 1 335 52
	st.w	[%a6]0, %d3
	.loc 1 336 8 is_stmt 1
#APP
	# 336 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 337 8
	.loc 1 337 86 is_stmt 0
#NO_APP
	ld.a	%a6, [%a3] 20
	.loc 1 337 54
	ld.w	%d3, [%a6]0
	.loc 1 337 41
	ld.a	%a6, [%a3] 20
	.loc 1 337 98
	or	%d3, %d1
	.loc 1 337 52
	st.w	[%a6]0, %d3
	.loc 1 338 8 is_stmt 1
#APP
	# 338 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 339 8
	.loc 1 339 46 is_stmt 0
#NO_APP
	ld.a	%a6, [%a3] 20
	.loc 1 339 14
	ld.w	%d3, [%a6] 8196
.L90:
	.loc 1 351 12
	st.w	[%SP] 44, %d3
	.loc 1 352 8 is_stmt 1
	.loc 1 352 15 is_stmt 0
	ld.w	%d3, [%SP] 40
	st.w	[%a3] 24, %d3
	.loc 1 353 8 is_stmt 1
	.loc 1 353 15 is_stmt 0
	ld.w	%d3, [%SP] 44
	st.w	[%a3] 28, %d3
	.loc 1 355 4 is_stmt 1
.LVL5:
.LBE5:
	.loc 1 293 21
	.loc 1 293 18 is_stmt 0
	ld.w	%d3, [%a3] 32
	lea	%a3, [%a3] 32
.LVL6:
	.loc 1 293 21
	jeq	%d3, -1, .L61
.LVL7:
.L49:
.LBB6:
	.loc 1 295 4 is_stmt 1
	.loc 1 296 4
	.loc 1 297 4
	.loc 1 298 4
	.loc 1 299 4
	.loc 1 300 4
	.loc 1 300 12 is_stmt 0
	st.w	[%SP] 36, %d10
	.loc 1 301 4 is_stmt 1
	.loc 1 301 36 is_stmt 0
	ld.a	%a6, [%a3]0
.LVL8:
	.loc 1 302 4 is_stmt 1
	.loc 1 302 14 is_stmt 0
	ld.w	%d0, [%a3] 4
.LVL9:
	.loc 1 303 4 is_stmt 1
	.loc 1 303 12 is_stmt 0
	ld.w	%d3, [%a3] 20
	lea	%a7, [%a3] 20
	.loc 1 303 7
	jnz	%d3, .L96
	.loc 1 313 8 is_stmt 1
	.loc 1 313 51 is_stmt 0
	st.w	[%a4]0, %d7
	.loc 1 314 8 is_stmt 1
#APP
	# 314 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 316 4
	.loc 1 316 12 is_stmt 0
#NO_APP
	ld.w	%d3, [%a3] 24
	.loc 1 316 17
	ld.w	%d4, [%a6]0
	.loc 1 316 7
	jne	%d3, %d4, .L89
.L95:
	.loc 1 318 17 is_stmt 1
	jz	%d0, .L53
	.loc 1 299 17 is_stmt 0
	mov	%d3, 0
	j	.L54
.LVL10:
.L97:
	.loc 1 320 15
	ld.w	%d4, [%a7] 4
.LVL11:
.L54:
	.loc 1 320 13
	ld.w	%d11, [%SP] 36
	addsc.a	%a7, %a6, %d3, 0
.LVL12:
	.loc 1 320 5 is_stmt 1
	.loc 1 320 13 is_stmt 0
	add	%d4, %d11
	.loc 1 322 7
	add	%d3, 4
.LVL13:
	.loc 1 320 13
	st.w	[%SP] 36, %d4
	.loc 1 321 5 is_stmt 1
.LVL14:
	.loc 1 322 5
	.loc 1 318 17
	jlt.u	%d3, %d0, .L97
.LVL15:
.L53:
	.loc 1 324 8
	.loc 1 324 26 is_stmt 0
	ld.w	%d4, [%a3] 8
	.loc 1 324 20
	ld.w	%d3, [%SP] 36
	.loc 1 324 11
	jne	%d4, %d3, .L89
	.loc 1 324 31 is_stmt 1 discriminator 1
	.loc 1 324 38 is_stmt 0 discriminator 1
	st.w	[%a3] 12, %d9
	j	.L56
.L57:
	.loc 1 345 8 is_stmt 1
	.loc 1 345 14 is_stmt 0
	ld.w	%d3, [%a5]0
	.loc 1 345 12
	st.w	[%SP] 40, %d3
	.loc 1 346 8 is_stmt 1
	.loc 1 346 18 is_stmt 0
	ld.w	%d3, [%SP] 40
	and	%d3, %d5
	.loc 1 346 11
	jz	%d3, .L60
	.loc 1 346 34 is_stmt 1 discriminator 1
	.loc 1 346 41 is_stmt 0 discriminator 1
	st.w	[%a3] 12, %d2
.L60:
	.loc 1 347 8 is_stmt 1
	.loc 1 347 51 is_stmt 0
	st.w	[%a4]0, %d7
	.loc 1 348 8 is_stmt 1
#APP
	# 348 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 349 8
	.loc 1 349 51 is_stmt 0
#NO_APP
	st.w	[%a4]0, %d8
	.loc 1 350 8 is_stmt 1
#APP
	# 350 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 351 8
	.loc 1 351 14 is_stmt 0
#NO_APP
	ld.w	%d3, [%a5]0
	j	.L90
.LVL16:
.L92:
.LBE6:
	.loc 1 131 7 is_stmt 1
	.loc 1 131 53 is_stmt 0
	mov	%d6, 256
	.loc 1 132 50
	ld.w	%d2, [%a2] 8
	.loc 1 131 53
	st.w	[%a3]0, %d6
	.loc 1 132 7 is_stmt 1
	.loc 1 132 50 is_stmt 0
	movh.a	%a3, 63497
	lea	%a3, [%a3] -21936
	st.w	[%a3]0, %d2
	.loc 1 133 7 is_stmt 1
#APP
	# 133 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 134 7
	.loc 1 134 50 is_stmt 0
#NO_APP
	movh.a	%a3, 63497
	ld.w	%d2, [%a2] 12
	lea	%a3, [%a3] -21928
	st.w	[%a3]0, %d2
	.loc 1 135 7 is_stmt 1
#APP
	# 135 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 136 7
	.loc 1 136 50 is_stmt 0
#NO_APP
	mov	%d2, 128
	movh.a	%a3, 63497
	lea	%a3, [%a3] -21848
	st.w	[%a3]0, %d2
	.loc 1 137 7 is_stmt 1
#APP
	# 137 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 138 7
	.loc 1 138 50 is_stmt 0
#NO_APP
	mov	%d2, 80
	st.w	[%a3]0, %d2
	.loc 1 139 7 is_stmt 1
#APP
	# 139 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 147 12 is_stmt 0
#NO_APP
	movh.a	%a3, 63492
	.loc 1 151 14
	movh.a	%a4, 63492
	.loc 1 142 11
	mov	%d4, 0
	.loc 1 142 18
	mov	%d3, 16384
	.loc 1 147 12
	add.a	%a3, 4
	.loc 1 151 14
	lea	%a4, [%a4] 16
	.loc 1 151 57
	mov	%d5, 4351
.L26:
	.loc 1 140 7 is_stmt 1
	.loc 1 142 4
	.loc 1 142 11 is_stmt 0
	st.w	[%SP] 4, %d4
	.loc 1 142 18 is_stmt 1
	ld.w	%d2, [%SP] 4
	jge.u	%d2, %d3, .L27
.L24:
	.loc 1 144 8 discriminator 3
	.loc 1 144 10 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 4
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 145 8 is_stmt 1 discriminator 3
	.loc 1 145 10 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 4
	add	%d2, -1
	st.w	[%SP] 4, %d2
	.loc 1 142 29 is_stmt 1 discriminator 3
	ld.w	%d2, [%SP] 4
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 142 18 discriminator 3
	ld.w	%d2, [%SP] 4
	jlt.u	%d2, %d3, .L24
.L27:
	.loc 1 147 4
	.loc 1 147 12 is_stmt 0
	ld.w	%d2, [%a3]0
	.loc 1 147 9
	st.w	[%SP] 20, %d2
	.loc 1 148 4 is_stmt 1
#APP
	# 148 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 149 4
	.loc 1 149 14 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 20
	insert	%d2, %d2, 0, 19, 13
	.loc 1 149 7
	jnz	%d2, .L26
	.loc 1 151 8 is_stmt 1
	.loc 1 151 14 is_stmt 0
	ld.w	%d2, [%a4]0
	.loc 1 151 57
	and	%d2, %d5
	.loc 1 151 11
	jz	%d2, .L28
	.loc 1 152 3 is_stmt 1
	.loc 1 152 49 is_stmt 0
	st.w	[%a2] 16, %d6
	.loc 1 155 8 is_stmt 1
#APP
	# 155 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L26
.L28:
	.loc 1 154 3
	.loc 1 154 49 is_stmt 0
	st.w	[%a2] 16, %d2
	.loc 1 155 8 is_stmt 1
#APP
	# 155 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L26
.LVL17:
.L91:
	.loc 1 61 7
	.loc 1 61 53 is_stmt 0
	mov	%d2, 256
	.loc 1 65 24
	movh	%d3, 34816
	.loc 1 65 10
	movh	%d4, 32768
	.loc 1 61 53
	st.w	[%a3]0, %d2
	.loc 1 62 7 is_stmt 1
	.loc 1 62 20 is_stmt 0
	ld.w	%d2, [%a4] 8
	st.w	[%SP] 16, %d2
	.loc 1 63 7 is_stmt 1
	.loc 1 64 13 is_stmt 0
	mov	%d2, 0
	.loc 1 63 12
	ld.a	%a6, [%a4] 20
.LVL18:
	.loc 1 64 7 is_stmt 1
	.loc 1 64 13 is_stmt 0
	st.w	[%SP] 32, %d2
	.loc 1 65 7 is_stmt 1
	.loc 1 65 24 is_stmt 0
	ld.w	%d2, [%a4]0
	and	%d2, %d3
	.loc 1 65 10
	jeq	%d2, %d4, .L98
	.loc 1 66 7 is_stmt 1
	.loc 1 66 10 is_stmt 0
	jne	%d2, %d3, .L6
	.loc 1 66 51 is_stmt 1 discriminator 1
	.loc 1 66 56 is_stmt 0 discriminator 1
	mov	%d2, 8
	st.w	[%SP] 32, %d2
.L6:
	.loc 1 67 7 is_stmt 1
	.loc 1 67 17 is_stmt 0
	ld.w	%d2, [%SP] 32
	.loc 1 67 10
	jz	%d2, .L99
.L7:
	.loc 1 72 26 is_stmt 1
	ld.w	%d2, [%a2] 12
	.loc 1 81 51 is_stmt 0
	movh.a	%a5, 63496
.LVL19:
	.loc 1 91 50
	movh.a	%a4, 63496
	.loc 1 97 47
	movh.a	%a15, 63497
	.loc 1 99 47
	movh.a	%a14, 63497
	.loc 1 101 47
	movh.a	%a12, 63497
	.loc 1 108 16
	movh.a	%a7, 63492
	.loc 1 74 10
	mov	%d6, 0
	.loc 1 81 51
	lea	%a5, [%a5] 21844
	mov	%d10, 80
	.loc 1 83 51
	mov	%d9, 93
	.loc 1 91 50
	lea	%a4, [%a4] 22004
	.loc 1 97 47
	lea	%a15, [%a15] -21936
	.loc 1 99 47
	lea	%a14, [%a14] -21928
	.loc 1 101 47
	lea	%a12, [%a12] -21848
	mov	%d8, 160
	.loc 1 103 47
	mov	%d1, 166
	.loc 1 106 16
	mov	%d0, 16384
	.loc 1 108 16
	add.a	%a7, 4
	.loc 1 111 59
	mov	%d5, 250
	.loc 1 114 80
	mov	%d7, 256
	.loc 1 72 26
	jz	%d2, .L19
.L8:
	.loc 1 74 4 is_stmt 1
	.loc 1 74 10 is_stmt 0
	st.w	[%SP] 4, %d6
	.loc 1 74 15 is_stmt 1
	ld.w	%d4, [%SP] 4
	ld.w	%d3, [%SP] 32
	jge.u	%d4, %d3, .L11
	addsc.a	%a13, %a6, %d2, 0
	mov.aa	%a3, %a6
.LVL20:
.L12:
	.loc 1 76 8 discriminator 3
	.loc 1 76 20 is_stmt 0 discriminator 3
	ld.w	%d3, [%SP] 4
	.loc 1 76 24 discriminator 3
	mov.aa	%a6, %a3
	.loc 1 76 23 discriminator 3
	sh	%d3, 2
	addi	%d3, %d3, 560
	.loc 1 76 24 discriminator 3
	ld.w	%d2, [%a6]0
	.loc 1 76 23 discriminator 3
	mov.a	%a6, %d3
	.loc 1 76 24 discriminator 3
	add.a	%a3, 4
.LVL21:
	.loc 1 76 23 discriminator 3
	add.a	%a6, %SP
	st.w	[%a6] -512, %d2
	.loc 1 77 8 is_stmt 1 discriminator 3
.LVL22:
	.loc 1 78 8 discriminator 3
	.loc 1 74 24 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 4
	.loc 1 78 20 discriminator 3
	sub.a	%a6, %a13, %a3
	.loc 1 74 24 is_stmt 1 discriminator 3
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 74 15 discriminator 3
	ld.w	%d4, [%SP] 4
	ld.w	%d3, [%SP] 32
	jlt.u	%d4, %d3, .L12
	st.a	[%a2] 12, %a6
	st.w	[%SP] 4, %d2
	.loc 1 77 12 is_stmt 0
	mov.aa	%a6, %a3
.LVL23:
.L11:
	.loc 1 80 4 is_stmt 1
	.loc 1 80 13 is_stmt 0
	ld.w	%d2, [%SP] 32
	.loc 1 80 7
	ne	%d2, %d2, 128
	jnz	%d2, .L13
	.loc 1 81 8 is_stmt 1
	.loc 1 81 51 is_stmt 0
	st.w	[%a5]0, %d10
.L13:
	.loc 1 82 4 is_stmt 1
	.loc 1 82 13 is_stmt 0
	ld.w	%d2, [%SP] 32
	.loc 1 82 7
	ne	%d2, %d2, 8
	jnz	%d2, .L14
	.loc 1 83 8 is_stmt 1
	.loc 1 83 51 is_stmt 0
	st.w	[%a5]0, %d9
.L14:
	.loc 1 84 4 is_stmt 1
	.loc 1 84 5 is_stmt 0
	st.w	[%SP] 4, %d6
	.loc 1 85 4 is_stmt 1
	.loc 1 85 12
	ld.w	%d3, [%SP] 4
	ld.w	%d2, [%SP] 32
	jge.u	%d3, %d2, .L18
.L15:
	.loc 1 87 8
	.loc 1 87 29 is_stmt 0
	ld.w	%d2, [%SP] 4
	sh	%d2, 2
	addi	%d2, %d2, 560
	mov.a	%a3, %d2
	add.a	%a3, %SP
	ld.w	%d2, [%a3] -512
	.loc 1 87 16
	st.w	[%SP] 24, %d2
	.loc 1 88 8 is_stmt 1
	.loc 1 88 9 is_stmt 0
	ld.w	%d2, [%SP] 4
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 89 8 is_stmt 1
	.loc 1 89 30 is_stmt 0
	ld.w	%d2, [%SP] 4
	sh	%d2, 2
	addi	%d2, %d2, 560
	mov.a	%a3, %d2
	add.a	%a3, %SP
	ld.w	%d2, [%a3] -512
	.loc 1 89 17
	st.w	[%SP] 28, %d2
	.loc 1 90 8 is_stmt 1
	.loc 1 90 9 is_stmt 0
	ld.w	%d2, [%SP] 4
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 91 8 is_stmt 1
	.loc 1 91 50 is_stmt 0
	ld.w	%d2, [%SP] 24
	st.w	[%a4]0, %d2
	.loc 1 92 8 is_stmt 1
#APP
	# 92 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 93 8
	.loc 1 93 50 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 28
	st.w	[%a4]0, %d2
	.loc 1 94 8 is_stmt 1
#APP
	# 94 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 85 12
#NO_APP
	ld.w	%d3, [%SP] 4
	ld.w	%d2, [%SP] 32
	jlt.u	%d3, %d2, .L15
.L18:
	.loc 1 97 4
	.loc 1 97 47 is_stmt 0
	ld.w	%d2, [%SP] 16
	st.w	[%a15]0, %d2
	.loc 1 98 4 is_stmt 1
#APP
	# 98 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 99 4
	.loc 1 99 47 is_stmt 0
#NO_APP
	st.w	[%a14]0, %d6
	.loc 1 100 4 is_stmt 1
#APP
	# 100 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 101 4
	.loc 1 101 47 is_stmt 0
#NO_APP
	st.w	[%a12]0, %d8
	.loc 1 102 4 is_stmt 1
#APP
	# 102 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 103 4
	.loc 1 103 47 is_stmt 0
#NO_APP
	st.w	[%a12]0, %d1
	.loc 1 104 4 is_stmt 1
#APP
	# 104 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 106 4
	.loc 1 106 16 is_stmt 0
#NO_APP
	st.w	[%SP]0, %d0
	.loc 1 106 32 is_stmt 1
	ld.w	%d2, [%SP]0
	jlez	%d2, .L17
.L16:
	.loc 1 108 8
	.loc 1 108 16 is_stmt 0
	ld.w	%d2, [%a7]0
	.loc 1 108 13
	st.w	[%SP] 20, %d2
	.loc 1 109 8 is_stmt 1
#APP
	# 109 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 110 8
	.loc 1 110 18 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 20
	insert	%d2, %d2, 0, 19, 13
	.loc 1 110 11
	jnz	%d2, .L20
	.loc 1 111 5 is_stmt 1
	.loc 1 111 12 is_stmt 0
	st.w	[%SP]0, %d2
	.loc 1 111 16 is_stmt 1
	.loc 1 111 59 is_stmt 0
	st.w	[%a5]0, %d5
.L20:
	.loc 1 112 8 is_stmt 1
	.loc 1 112 19 is_stmt 0
	ld.w	%d2, [%SP]0
	.loc 1 112 11
	jne	%d2, 1, .L21
	.loc 1 114 5 is_stmt 1
	.loc 1 114 18 is_stmt 0
	ld.w	%d2, [%SP] 16
	st.w	[%a2] 8, %d2
	.loc 1 114 34 is_stmt 1
	.loc 1 114 80 is_stmt 0
	st.w	[%a2] 16, %d7
	.loc 1 114 90 is_stmt 1
	.loc 1 114 133 is_stmt 0
	st.w	[%a5]0, %d5
	.loc 1 114 141 is_stmt 1
#APP
	# 114 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
.L21:
	.loc 1 106 43 discriminator 2
	ld.w	%d2, [%SP]0
	add	%d2, -1
	st.w	[%SP]0, %d2
	.loc 1 106 32 discriminator 2
	ld.w	%d2, [%SP]0
	jgtz	%d2, .L16
.L17:
	.loc 1 117 4
	.loc 1 117 23 is_stmt 0
	ld.w	%d2, [%SP] 32
	.loc 1 117 16
	ld.w	%d3, [%SP] 16
	.loc 1 117 23
	sh	%d2, 2
	.loc 1 117 16
	add	%d2, %d3
	st.w	[%SP] 16, %d2
	.loc 1 72 26 is_stmt 1
	ld.w	%d2, [%a2] 12
	jnz	%d2, .L8
.L19:
	.loc 1 119 7
	.loc 1 119 13 is_stmt 0
	movh.a	%a3, 63492
	ld.w	%d3, [%a3] 16
	.loc 1 119 56
	mov	%d2, 4351
	and	%d2, %d3
	.loc 1 119 13
	lea	%a3, [%a3] 16
	.loc 1 119 10
	jnz	%d2, .L9
	.loc 1 122 2 is_stmt 1
	.loc 1 122 48 is_stmt 0
	st.w	[%a2] 16, %d2
.L22:
	.loc 1 123 7 is_stmt 1
	.loc 1 123 50 is_stmt 0
	mov	%d2, 250
	movh.a	%a3, 63496
	lea	%a3, [%a3] 21844
	st.w	[%a3]0, %d2
	.loc 1 124 7 is_stmt 1
#APP
	# 124 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L4
.L9:
	.loc 1 120 2
	.loc 1 120 48 is_stmt 0
	mov	%d2, 256
	st.w	[%a2] 16, %d2
	j	.L22
.LVL24:
.L99:
	.loc 1 69 4 is_stmt 1
	.loc 1 69 50 is_stmt 0
	mov	%d2, 256
	st.w	[%a2] 16, %d2
	.loc 1 70 4 is_stmt 1
#APP
	# 70 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L7
.L98:
	.loc 1 65 51 discriminator 1
	.loc 1 65 56 is_stmt 0 discriminator 1
	mov	%d2, 128
	st.w	[%SP] 32, %d2
	.loc 1 66 7 is_stmt 1 discriminator 1
	.loc 1 67 7 discriminator 1
	.loc 1 67 17 is_stmt 0 discriminator 1
	ld.w	%d2, [%SP] 32
	.loc 1 67 10 discriminator 1
	jnz	%d2, .L7
	j	.L99
.LVL25:
.L93:
	.loc 1 199 7 is_stmt 1
	.loc 1 199 53 is_stmt 0
	mov	%d2, 256
	st.w	[%a3]0, %d2
	.loc 1 200 7 is_stmt 1
	.loc 1 200 50 is_stmt 0
	movh.a	%a3, 63497
	ld.w	%d2, [%a2] 8
	lea	%a3, [%a3] -21936
	st.w	[%a3]0, %d2
	.loc 1 201 7 is_stmt 1
#APP
	# 201 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 202 7
	.loc 1 202 50 is_stmt 0
#NO_APP
	mov	%d2, 1
	movh.a	%a3, 63497
	lea	%a3, [%a3] -21928
	st.w	[%a3]0, %d2
	.loc 1 203 7 is_stmt 1
#APP
	# 203 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 204 7
	.loc 1 204 50 is_stmt 0
#NO_APP
	mov	%d2, 128
	movh.a	%a3, 63497
	lea	%a3, [%a3] -21848
	st.w	[%a3]0, %d2
	.loc 1 205 7 is_stmt 1
#APP
	# 205 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 206 7
	.loc 1 206 50 is_stmt 0
#NO_APP
	mov	%d2, 80
	st.w	[%a3]0, %d2
	.loc 1 207 7 is_stmt 1
#APP
	# 207 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 215 12 is_stmt 0
#NO_APP
	movh.a	%a3, 63492
	.loc 1 219 14
	movh.a	%a4, 63492
	.loc 1 210 11
	mov	%d4, 0
	.loc 1 210 18
	movh	%d3, 4
	.loc 1 215 12
	add.a	%a3, 4
	.loc 1 219 14
	lea	%a4, [%a4] 16
	.loc 1 219 57
	mov	%d6, 4351
	.loc 1 221 51
	mov	%d5, 257
.L34:
	.loc 1 208 7 is_stmt 1
	.loc 1 210 4
	.loc 1 210 11 is_stmt 0
	st.w	[%SP] 4, %d4
	.loc 1 210 18 is_stmt 1
	ld.w	%d2, [%SP] 4
	jge.u	%d2, %d3, .L35
.L32:
	.loc 1 212 8 discriminator 3
	.loc 1 212 10 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 4
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 213 8 is_stmt 1 discriminator 3
	.loc 1 213 10 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 4
	add	%d2, -1
	st.w	[%SP] 4, %d2
	.loc 1 210 30 is_stmt 1 discriminator 3
	ld.w	%d2, [%SP] 4
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 210 18 discriminator 3
	ld.w	%d2, [%SP] 4
	jlt.u	%d2, %d3, .L32
.L35:
	.loc 1 215 4
	.loc 1 215 12 is_stmt 0
	ld.w	%d2, [%a3]0
	.loc 1 215 9
	st.w	[%SP] 20, %d2
	.loc 1 216 4 is_stmt 1
#APP
	# 216 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 217 4
	.loc 1 217 14 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 20
	insert	%d2, %d2, 0, 19, 13
	.loc 1 217 7
	jnz	%d2, .L34
	.loc 1 219 8 is_stmt 1
	.loc 1 219 14 is_stmt 0
	ld.w	%d2, [%a4]0
	.loc 1 219 57
	and	%d2, %d6
	.loc 1 219 11
	jz	%d2, .L36
	.loc 1 221 5 is_stmt 1
	.loc 1 221 51 is_stmt 0
	st.w	[%a2] 16, %d5
	.loc 1 222 5 is_stmt 1
#APP
	# 222 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L34
.L36:
	.loc 1 226 5
	.loc 1 232 19 is_stmt 0
	mov	%d3, 512
	.loc 1 226 51
	st.w	[%a2] 16, %d2
	.loc 1 227 5 is_stmt 1
.LDL1:
	.loc 1 232 15
	.loc 1 239 47 is_stmt 0
	movh.a	%a4, 63496
	.loc 1 232 19
	st.w	[%SP] 12, %d3
	.loc 1 233 7 is_stmt 1
	.loc 1 233 13 is_stmt 0
	mov	%d3, 8
	.loc 1 243 51
	movh.a	%a3, 63496
	.loc 1 251 47
	movh.a	%a13, 63497
	.loc 1 233 13
	st.w	[%SP] 32, %d3
	.loc 1 234 7 is_stmt 1
	.loc 1 253 47 is_stmt 0
	movh.a	%a12, 63497
	.loc 1 255 47
	movh.a	%a7, 63497
	.loc 1 234 12
	ld.w	%d5, [%a2] 20
.LVL26:
	.loc 1 235 7 is_stmt 1
	.loc 1 235 9 is_stmt 0
	st.w	[%SP] 8, %d2
	.loc 1 236 7 is_stmt 1
	.loc 1 238 6 is_stmt 0
	mov	%d10, 0
	.loc 1 239 47
	lea	%a4, [%a4] 21844
	mov	%d9, 93
	.loc 1 243 51
	lea	%a3, [%a3] 22004
	.loc 1 251 47
	lea	%a13, [%a13] -21936
	.loc 1 253 47
	lea	%a12, [%a12] -21928
	.loc 1 255 47
	lea	%a7, [%a7] -21848
	mov	%d8, 160
	.loc 1 266 48
	mov	%d4, 250
	.loc 1 271 51
	mov	%d6, 258
	.loc 1 238 6
	mov	%d1, 0
.L38:
	.loc 1 261 16
	movh.a	%a6, 63492
	.loc 1 277 10
	movh.a	%a14, 63492
	.loc 1 257 47
	mov	%d11, 166
	.loc 1 259 17
	mov	%d0, 16384
	.loc 1 261 16
	add.a	%a6, 4
	.loc 1 277 10
	lea	%a14, [%a14] 16
	.loc 1 277 53
	mov	%d7, 4351
.L44:
	.loc 1 236 16 is_stmt 1
	ld.w	%d3, [%SP] 8
	ld.w	%d2, [%SP] 12
	jge.u	%d3, %d2, .L100
	.loc 1 238 4
	.loc 1 238 6 is_stmt 0
	st.w	[%SP] 4, %d1
	.loc 1 239 4 is_stmt 1
	.loc 1 239 47 is_stmt 0
	st.w	[%a4]0, %d9
	.loc 1 240 4 is_stmt 1
	.loc 1 240 13
	ld.w	%d3, [%SP] 4
	ld.w	%d2, [%SP] 32
	jge.u	%d3, %d2, .L42
.L39:
	.loc 1 242 8
	.loc 1 242 26 is_stmt 0
	ld.w	%d3, [%SP] 8
	ld.w	%d2, [%SP] 4
	.loc 1 242 23
	mov.a	%a5, %d5
	.loc 1 242 26
	add	%d2, %d3
	.loc 1 242 23
	sh	%d2, 2
	addsc.a	%a5, %a5, %d2, 0
	ld.w	%d2, [%a5]0
	.loc 1 242 17
	st.w	[%SP] 24, %d2
	.loc 1 243 8 is_stmt 1
	.loc 1 243 51 is_stmt 0
	ld.w	%d2, [%SP] 24
	st.w	[%a3]0, %d2
	.loc 1 244 8 is_stmt 1
#APP
	# 244 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 245 8
	.loc 1 245 10 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 4
	.loc 1 246 24
	mov.a	%a5, %d5
	.loc 1 245 10
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 246 8 is_stmt 1
	.loc 1 246 27 is_stmt 0
	ld.w	%d3, [%SP] 8
	ld.w	%d2, [%SP] 4
	add	%d2, %d3
	.loc 1 246 24
	sh	%d2, 2
	addsc.a	%a5, %a5, %d2, 0
	ld.w	%d2, [%a5]0
	.loc 1 246 18
	st.w	[%SP] 28, %d2
	.loc 1 247 8 is_stmt 1
	.loc 1 247 51 is_stmt 0
	ld.w	%d2, [%SP] 28
	st.w	[%a3]0, %d2
	.loc 1 248 8 is_stmt 1
#APP
	# 248 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 249 8
	.loc 1 249 10 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 4
	add	%d2, 1
	st.w	[%SP] 4, %d2
	.loc 1 240 13 is_stmt 1
	ld.w	%d3, [%SP] 4
	ld.w	%d2, [%SP] 32
	jlt.u	%d3, %d2, .L39
.L42:
	.loc 1 251 4
	.loc 1 251 65 is_stmt 0
	ld.w	%d2, [%SP] 8
	.loc 1 251 61
	ld.w	%d3, [%a2] 8
	.loc 1 251 65
	sh	%d2, 2
	.loc 1 251 61
	add	%d2, %d3
	.loc 1 251 47
	st.w	[%a13]0, %d2
	.loc 1 252 4 is_stmt 1
#APP
	# 252 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 253 4
	.loc 1 253 47 is_stmt 0
#NO_APP
	st.w	[%a12]0, %d10
	.loc 1 254 4 is_stmt 1
#APP
	# 254 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 255 4
	.loc 1 255 47 is_stmt 0
#NO_APP
	st.w	[%a7]0, %d8
	.loc 1 257 4 is_stmt 1
	.loc 1 257 47 is_stmt 0
	st.w	[%a7]0, %d11
	.loc 1 258 4 is_stmt 1
#APP
	# 258 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 259 4
	.loc 1 259 17 is_stmt 0
#NO_APP
	st.w	[%SP]0, %d0
	.loc 1 259 35 is_stmt 1
	ld.w	%d2, [%SP]0
	jlez	%d2, .L41
.L40:
	.loc 1 261 8
	.loc 1 261 16 is_stmt 0
	ld.w	%d2, [%a6]0
	.loc 1 261 13
	st.w	[%SP] 20, %d2
	.loc 1 262 8 is_stmt 1
#APP
	# 262 "flash_TC4xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 263 8
	.loc 1 263 18 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 20
	insert	%d2, %d2, 0, 19, 13
	.loc 1 263 11
	jnz	%d2, .L45
	.loc 1 265 5 is_stmt 1
	.loc 1 265 13 is_stmt 0
	st.w	[%SP]0, %d2
	.loc 1 266 5 is_stmt 1
	.loc 1 266 48 is_stmt 0
	st.w	[%a4]0, %d4
.L45:
	.loc 1 268 8 is_stmt 1
	.loc 1 268 20 is_stmt 0
	ld.w	%d2, [%SP]0
	.loc 1 268 11
	jne	%d2, 1, .L46
	.loc 1 270 5 is_stmt 1
	.loc 1 270 17 is_stmt 0
	ld.w	%d2, [%SP] 16
	st.w	[%a2] 8, %d2
	.loc 1 271 5 is_stmt 1
	.loc 1 271 51 is_stmt 0
	st.w	[%a2] 16, %d6
	.loc 1 272 5 is_stmt 1
	.loc 1 272 48 is_stmt 0
	st.w	[%a4]0, %d4
	.loc 1 273 5 is_stmt 1
#APP
	# 273 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
.L46:
	.loc 1 259 47 discriminator 2
	ld.w	%d2, [%SP]0
	add	%d2, -1
	st.w	[%SP]0, %d2
	.loc 1 259 35 discriminator 2
	ld.w	%d2, [%SP]0
	jgtz	%d2, .L40
.L41:
	.loc 1 276 4
	ld.w	%d2, [%SP] 32
	.loc 1 276 6 is_stmt 0
	ld.w	%d3, [%SP] 8
	add	%d2, %d3
	st.w	[%SP] 8, %d2
	.loc 1 277 4 is_stmt 1
	.loc 1 277 10 is_stmt 0
	ld.w	%d2, [%a14]0
	.loc 1 277 53
	and	%d2, %d7
	.loc 1 277 7
	jz	%d2, .L44
	.loc 1 279 8 is_stmt 1
	.loc 1 279 54 is_stmt 0
	mov	%d2, 259
	st.w	[%a2] 16, %d2
	.loc 1 280 8 is_stmt 1
#APP
	# 280 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L38
.L100:
	.loc 1 283 7
	.loc 1 283 53 is_stmt 0
	mov	%d2, 0
	st.w	[%a2] 16, %d2
	.loc 1 284 7 is_stmt 1
#APP
	# 284 "flash_TC4xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L31
.LFE1:
	.size flashing, .-flashing
	.global	flashing_end
flashing_end:
	.section	.debug_frame,"",@progbits
.Lframe0:
	.uaword	.LECIE0-.LSCIE0
.LSCIE0:
	.uaword	0xffffffff
	.byte	0x3
	.string	""
	.uleb128 0x1
	.sleb128 1
	.uleb128 0x1b
	.byte	0xc
	.uleb128 0x1a
	.uleb128 0
	.align 2
.LECIE0:
.LSFDE0:
	.uaword	.LEFDE0-.LASFDE0
.LASFDE0:
	.uaword	.Lframe0
	.uaword	.LFB0
	.uaword	.LFE0-.LFB0
	.align 2
.LEFDE0:
.LSFDE2:
	.uaword	.LEFDE2-.LASFDE2
.LASFDE2:
	.uaword	.Lframe0
	.uaword	.LFB1
	.uaword	.LFE1-.LFB1
	.byte	0x4
	.uaword	.LCFI0-.LFB1
	.byte	0xe
	.uleb128 0x230
	.align 2
.LEFDE2:
.section .text,"ax",@progbits
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x31b
	.uahalf	0x5
	.byte	0x1
	.byte	0x4
	.uaword	.Ldebug_abbrev0
	.uleb128 0x8
	.string	"GNU C17 11.3.1 20221230 -mtc162 -g3 -O2 -fno-peephole2 -fno-common -fno-short-enums -fsingle-precision-constant"
	.byte	0x1d
	.string	"flash_TC4xx.c"
	.string	"/home/dummy/share/HOST/AURIX_MINGW_INSTALL/DAS_v8_0_5_Linux.tar/aurix_flasher_linux/gdb_flash_drivers"
	.uaword	.Ltext0
	.uaword	.Letext0-.Ltext0
	.uaword	.Ldebug_line0
	.uaword	.Ldebug_macro0
	.uleb128 0x9
	.string	"flashing"
	.byte	0x1
	.byte	0x2f
	.byte	0x1
	.uaword	0x29e
	.uaword	.LFB1
	.uaword	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.uaword	0x29e
	.uleb128 0x7
	.string	"parameter"
	.byte	0x1a
	.uaword	0x2aa
	.uaword	.LLST0
	.uleb128 0x7
	.string	"notused"
	.byte	0x2c
	.uaword	0x2c4
	.uaword	.LLST1
	.uleb128 0x1
	.string	"timeout"
	.byte	0x31
	.byte	0x10
	.uaword	0x2a5
	.uleb128 0x3
	.byte	0x91
	.sleb128 -560
	.uleb128 0x1
	.string	"i"
	.byte	0x32
	.byte	0x19
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -556
	.uleb128 0x1
	.string	"j"
	.byte	0x32
	.byte	0x1c
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -552
	.uleb128 0x1
	.string	"len"
	.byte	0x32
	.byte	0x1f
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -548
	.uleb128 0x1
	.string	"addr_aligned"
	.byte	0x33
	.byte	0x19
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -544
	.uleb128 0xa
	.string	"data"
	.byte	0x1
	.byte	0x34
	.byte	0x1a
	.uaword	0x2eb
	.uaword	.LLST2
	.uleb128 0x1
	.string	"read"
	.byte	0x34
	.byte	0x20
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -540
	.uleb128 0x1
	.string	"low32bit"
	.byte	0x35
	.byte	0x19
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -536
	.uleb128 0x1
	.string	"high32bit"
	.byte	0x35
	.byte	0x23
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -532
	.uleb128 0x1
	.string	"burst"
	.byte	0x36
	.byte	0x19
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -528
	.uleb128 0x1
	.string	"burst_buffer"
	.byte	0x37
	.byte	0x19
	.uaword	0x300
	.uleb128 0x3
	.byte	0x91
	.sleb128 -512
	.uleb128 0xb
	.string	"program_copy"
	.byte	0x1
	.byte	0xe8
	.byte	0x1
	.uaword	.LDL1
	.uleb128 0xc
	.uaword	.LLRL3
	.uleb128 0x4
	.string	"addr_begin"
	.uahalf	0x127
	.byte	0x12
	.uaword	0x305
	.uaword	.LLST4
	.uleb128 0x4
	.string	"len_verify"
	.uahalf	0x128
	.byte	0x11
	.uaword	0x2d6
	.uaword	.LLST5
	.uleb128 0x5
	.string	"checksum"
	.uahalf	0x129
	.byte	0x1a
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -524
	.uleb128 0x5
	.string	"tmp1"
	.uahalf	0x12a
	.byte	0x1a
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -520
	.uleb128 0x5
	.string	"tmp2"
	.uahalf	0x12a
	.byte	0x1f
	.uaword	0x2e6
	.uleb128 0x3
	.byte	0x91
	.sleb128 -516
	.uleb128 0x4
	.string	"ii"
	.uahalf	0x12b
	.byte	0x11
	.uaword	0x2d6
	.uaword	.LLST6
	.byte	0
	.byte	0
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x6
	.uaword	0x29e
	.uleb128 0x2
	.uaword	0x2af
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.string	"long unsigned int"
	.uleb128 0x2
	.uaword	0x2c9
	.uleb128 0x2
	.uaword	0x2ce
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.string	"char"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.string	"unsigned int"
	.uleb128 0x6
	.uaword	0x2d6
	.uleb128 0x2
	.uaword	0x2e6
	.uleb128 0xd
	.uaword	0x2e6
	.uaword	0x300
	.uleb128 0xe
	.uaword	0x2af
	.byte	0x7f
	.byte	0
	.uleb128 0x6
	.uaword	0x2f0
	.uleb128 0x2
	.uaword	0x2d6
	.uleb128 0xf
	.string	"start"
	.byte	0x1
	.byte	0x24
	.byte	0x1
	.uaword	.LFB0
	.uaword	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0x21
	.sleb128 47
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.uleb128 0x79
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loclists,"",@progbits
	.uaword	.Ldebug_loc3-.Ldebug_loc2
.Ldebug_loc2:
	.uahalf	0x5
	.byte	0x4
	.byte	0
	.uaword	0
.Ldebug_loc0:
.LLST0:
	.byte	0x4
	.uleb128 .LVL0-.Ltext0
	.uleb128 .LVL1-.Ltext0
	.uleb128 0x1
	.byte	0x64
	.byte	0x4
	.uleb128 .LVL1-.Ltext0
	.uleb128 .LFE1-.Ltext0
	.uleb128 0x1
	.byte	0x62
	.byte	0
.LLST1:
	.byte	0x4
	.uleb128 .LVL0-.Ltext0
	.uleb128 .LVL1-.Ltext0
	.uleb128 0x1
	.byte	0x65
	.byte	0x4
	.uleb128 .LVL1-.Ltext0
	.uleb128 .LVL17-.Ltext0
	.uleb128 0x4
	.byte	0xa3
	.uleb128 0x1
	.byte	0x65
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL17-.Ltext0
	.uleb128 .LVL19-.Ltext0
	.uleb128 0x1
	.byte	0x65
	.byte	0x4
	.uleb128 .LVL19-.Ltext0
	.uleb128 .LVL24-.Ltext0
	.uleb128 0x4
	.byte	0xa3
	.uleb128 0x1
	.byte	0x65
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL24-.Ltext0
	.uleb128 .LVL25-.Ltext0
	.uleb128 0x1
	.byte	0x65
	.byte	0x4
	.uleb128 .LVL25-.Ltext0
	.uleb128 .LFE1-.Ltext0
	.uleb128 0x4
	.byte	0xa3
	.uleb128 0x1
	.byte	0x65
	.byte	0x9f
	.byte	0
.LLST2:
	.byte	0x4
	.uleb128 .LVL2-.Ltext0
	.uleb128 .LVL5-.Ltext0
	.uleb128 0x1
	.byte	0x63
	.byte	0x4
	.uleb128 .LVL5-.Ltext0
	.uleb128 .LVL6-.Ltext0
	.uleb128 0x3
	.byte	0x83
	.sleb128 32
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL6-.Ltext0
	.uleb128 .LVL16-.Ltext0
	.uleb128 0x1
	.byte	0x63
	.byte	0x4
	.uleb128 .LVL18-.Ltext0
	.uleb128 .LVL20-.Ltext0
	.uleb128 0x1
	.byte	0x66
	.byte	0x4
	.uleb128 .LVL20-.Ltext0
	.uleb128 .LVL21-.Ltext0
	.uleb128 0x1
	.byte	0x63
	.byte	0x4
	.uleb128 .LVL21-.Ltext0
	.uleb128 .LVL22-.Ltext0
	.uleb128 0x3
	.byte	0x83
	.sleb128 -4
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL22-.Ltext0
	.uleb128 .LVL23-.Ltext0
	.uleb128 0x1
	.byte	0x63
	.byte	0x4
	.uleb128 .LVL23-.Ltext0
	.uleb128 .LVL25-.Ltext0
	.uleb128 0x1
	.byte	0x66
	.byte	0x4
	.uleb128 .LVL26-.Ltext0
	.uleb128 .LFE1-.Ltext0
	.uleb128 0x1
	.byte	0x55
	.byte	0
.LLST4:
	.byte	0x4
	.uleb128 .LVL3-.Ltext0
	.uleb128 .LVL4-.Ltext0
	.uleb128 0x1
	.byte	0x66
	.byte	0x4
	.uleb128 .LVL8-.Ltext0
	.uleb128 .LVL10-.Ltext0
	.uleb128 0x1
	.byte	0x66
	.byte	0x4
	.uleb128 .LVL12-.Ltext0
	.uleb128 .LVL14-.Ltext0
	.uleb128 0x1
	.byte	0x67
	.byte	0
.LLST5:
	.byte	0x4
	.uleb128 .LVL3-.Ltext0
	.uleb128 .LVL7-.Ltext0
	.uleb128 0x1
	.byte	0x50
	.byte	0x4
	.uleb128 .LVL9-.Ltext0
	.uleb128 .LVL16-.Ltext0
	.uleb128 0x1
	.byte	0x50
	.byte	0
.LLST6:
	.byte	0x4
	.uleb128 .LVL3-.Ltext0
	.uleb128 .LVL4-.Ltext0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL7-.Ltext0
	.uleb128 .LVL10-.Ltext0
	.uleb128 0x2
	.byte	0x30
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL10-.Ltext0
	.uleb128 .LVL11-.Ltext0
	.uleb128 0x1
	.byte	0x53
	.byte	0x4
	.uleb128 .LVL12-.Ltext0
	.uleb128 .LVL13-.Ltext0
	.uleb128 0x1
	.byte	0x53
	.byte	0x4
	.uleb128 .LVL13-.Ltext0
	.uleb128 .LVL14-.Ltext0
	.uleb128 0x3
	.byte	0x73
	.sleb128 -4
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL14-.Ltext0
	.uleb128 .LVL15-.Ltext0
	.uleb128 0x1
	.byte	0x53
	.byte	0
.Ldebug_loc3:
	.section	.debug_aranges,"",@progbits
	.uaword	0x1c
	.uahalf	0x2
	.uaword	.Ldebug_info0
	.byte	0x4
	.byte	0
	.uahalf	0
	.uahalf	0
	.uaword	.Ltext0
	.uaword	.Letext0-.Ltext0
	.uaword	0
	.uaword	0
	.section	.debug_rnglists,"",@progbits
.Ldebug_ranges0:
	.uaword	.Ldebug_ranges3-.Ldebug_ranges2
.Ldebug_ranges2:
	.uahalf	0x5
	.byte	0x4
	.byte	0
	.uaword	0
.LLRL3:
	.byte	0x4
	.uleb128 .LBB2-.Ltext0
	.uleb128 .LBE2-.Ltext0
	.byte	0x4
	.uleb128 .LBB3-.Ltext0
	.uleb128 .LBE3-.Ltext0
	.byte	0x4
	.uleb128 .LBB4-.Ltext0
	.uleb128 .LBE4-.Ltext0
	.byte	0x4
	.uleb128 .LBB5-.Ltext0
	.uleb128 .LBE5-.Ltext0
	.byte	0x4
	.uleb128 .LBB6-.Ltext0
	.uleb128 .LBE6-.Ltext0
	.byte	0
.Ldebug_ranges3:
	.section	.debug_macro,"",@progbits
.Ldebug_macro0:
	.uahalf	0x5
	.byte	0x2
	.uaword	.Ldebug_line0
	.byte	0x3
	.uleb128 0
	.uleb128 0x1
	.byte	0x1
	.uleb128 0
	.string	"__STDC__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__STDC_VERSION__ 201710L"
	.byte	0x1
	.uleb128 0
	.string	"__STDC_UTF_16__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__STDC_UTF_32__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__STDC_HOSTED__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__GNUC__ 11"
	.byte	0x1
	.uleb128 0
	.string	"__GNUC_MINOR__ 3"
	.byte	0x1
	.uleb128 0
	.string	"__GNUC_PATCHLEVEL__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__VERSION__ \"11.3.1 20221230\""
	.byte	0x1
	.uleb128 0
	.string	"__ATOMIC_RELAXED 0"
	.byte	0x1
	.uleb128 0
	.string	"__ATOMIC_SEQ_CST 5"
	.byte	0x1
	.uleb128 0
	.string	"__ATOMIC_ACQUIRE 2"
	.byte	0x1
	.uleb128 0
	.string	"__ATOMIC_RELEASE 3"
	.byte	0x1
	.uleb128 0
	.string	"__ATOMIC_ACQ_REL 4"
	.byte	0x1
	.uleb128 0
	.string	"__ATOMIC_CONSUME 1"
	.byte	0x1
	.uleb128 0
	.string	"__OPTIMIZE__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FINITE_MATH_ONLY__ 0"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_INT__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_LONG__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_LONG_LONG__ 8"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_SHORT__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_FLOAT__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_DOUBLE__ 8"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_LONG_DOUBLE__ 8"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_SIZE_T__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__CHAR_BIT__ 8"
	.byte	0x1
	.uleb128 0
	.string	"__BIGGEST_ALIGNMENT__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__ORDER_LITTLE_ENDIAN__ 1234"
	.byte	0x1
	.uleb128 0
	.string	"__ORDER_BIG_ENDIAN__ 4321"
	.byte	0x1
	.uleb128 0
	.string	"__ORDER_PDP_ENDIAN__ 3412"
	.byte	0x1
	.uleb128 0
	.string	"__BYTE_ORDER__ __ORDER_LITTLE_ENDIAN__"
	.byte	0x1
	.uleb128 0
	.string	"__FLOAT_WORD_ORDER__ __ORDER_LITTLE_ENDIAN__"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_POINTER__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__GNUC_EXECUTION_CHARSET_NAME \"UTF-8\""
	.byte	0x1
	.uleb128 0
	.string	"__GNUC_WIDE_EXECUTION_CHARSET_NAME \"UTF-32LE\""
	.byte	0x1
	.uleb128 0
	.string	"__SIZE_TYPE__ long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__PTRDIFF_TYPE__ long int"
	.byte	0x1
	.uleb128 0
	.string	"__WCHAR_TYPE__ int"
	.byte	0x1
	.uleb128 0
	.string	"__WINT_TYPE__ unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__INTMAX_TYPE__ long long int"
	.byte	0x1
	.uleb128 0
	.string	"__UINTMAX_TYPE__ long long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__CHAR16_TYPE__ short unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__CHAR32_TYPE__ long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__SIG_ATOMIC_TYPE__ int"
	.byte	0x1
	.uleb128 0
	.string	"__INT8_TYPE__ signed char"
	.byte	0x1
	.uleb128 0
	.string	"__INT16_TYPE__ short int"
	.byte	0x1
	.uleb128 0
	.string	"__INT32_TYPE__ long int"
	.byte	0x1
	.uleb128 0
	.string	"__INT64_TYPE__ long long int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT8_TYPE__ unsigned char"
	.byte	0x1
	.uleb128 0
	.string	"__UINT16_TYPE__ short unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT32_TYPE__ long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT64_TYPE__ long long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST8_TYPE__ signed char"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST16_TYPE__ short int"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST32_TYPE__ long int"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST64_TYPE__ long long int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST8_TYPE__ unsigned char"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST16_TYPE__ short unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST32_TYPE__ long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST64_TYPE__ long long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST8_TYPE__ int"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST16_TYPE__ int"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST32_TYPE__ int"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST64_TYPE__ long long int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST8_TYPE__ unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST16_TYPE__ unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST32_TYPE__ unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST64_TYPE__ long long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__INTPTR_TYPE__ long int"
	.byte	0x1
	.uleb128 0
	.string	"__UINTPTR_TYPE__ long unsigned int"
	.byte	0x1
	.uleb128 0
	.string	"__GXX_ABI_VERSION 1016"
	.byte	0x1
	.uleb128 0
	.string	"__USING_SJLJ_EXCEPTIONS__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__SCHAR_MAX__ 0x7f"
	.byte	0x1
	.uleb128 0
	.string	"__SHRT_MAX__ 0x7fff"
	.byte	0x1
	.uleb128 0
	.string	"__INT_MAX__ 0x7fffffff"
	.byte	0x1
	.uleb128 0
	.string	"__LONG_MAX__ 0x7fffffffL"
	.byte	0x1
	.uleb128 0
	.string	"__LONG_LONG_MAX__ 0x7fffffffffffffffLL"
	.byte	0x1
	.uleb128 0
	.string	"__WCHAR_MAX__ 0x7fffffff"
	.byte	0x1
	.uleb128 0
	.string	"__WCHAR_MIN__ (-__WCHAR_MAX__ - 1)"
	.byte	0x1
	.uleb128 0
	.string	"__WINT_MAX__ 0xffffffffU"
	.byte	0x1
	.uleb128 0
	.string	"__WINT_MIN__ 0U"
	.byte	0x1
	.uleb128 0
	.string	"__PTRDIFF_MAX__ 0x7fffffffL"
	.byte	0x1
	.uleb128 0
	.string	"__SIZE_MAX__ 0xffffffffUL"
	.byte	0x1
	.uleb128 0
	.string	"__SCHAR_WIDTH__ 8"
	.byte	0x1
	.uleb128 0
	.string	"__SHRT_WIDTH__ 16"
	.byte	0x1
	.uleb128 0
	.string	"__INT_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__LONG_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__LONG_LONG_WIDTH__ 64"
	.byte	0x1
	.uleb128 0
	.string	"__WCHAR_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__WINT_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__PTRDIFF_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__SIZE_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__INTMAX_MAX__ 0x7fffffffffffffffLL"
	.byte	0x1
	.uleb128 0
	.string	"__INTMAX_C(c) c ## LL"
	.byte	0x1
	.uleb128 0
	.string	"__UINTMAX_MAX__ 0xffffffffffffffffULL"
	.byte	0x1
	.uleb128 0
	.string	"__UINTMAX_C(c) c ## ULL"
	.byte	0x1
	.uleb128 0
	.string	"__INTMAX_WIDTH__ 64"
	.byte	0x1
	.uleb128 0
	.string	"__SIG_ATOMIC_MAX__ 0x7fffffff"
	.byte	0x1
	.uleb128 0
	.string	"__SIG_ATOMIC_MIN__ (-__SIG_ATOMIC_MAX__ - 1)"
	.byte	0x1
	.uleb128 0
	.string	"__SIG_ATOMIC_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__INT8_MAX__ 0x7f"
	.byte	0x1
	.uleb128 0
	.string	"__INT16_MAX__ 0x7fff"
	.byte	0x1
	.uleb128 0
	.string	"__INT32_MAX__ 0x7fffffffL"
	.byte	0x1
	.uleb128 0
	.string	"__INT64_MAX__ 0x7fffffffffffffffLL"
	.byte	0x1
	.uleb128 0
	.string	"__UINT8_MAX__ 0xff"
	.byte	0x1
	.uleb128 0
	.string	"__UINT16_MAX__ 0xffff"
	.byte	0x1
	.uleb128 0
	.string	"__UINT32_MAX__ 0xffffffffUL"
	.byte	0x1
	.uleb128 0
	.string	"__UINT64_MAX__ 0xffffffffffffffffULL"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST8_MAX__ 0x7f"
	.byte	0x1
	.uleb128 0
	.string	"__INT8_C(c) c"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST8_WIDTH__ 8"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST16_MAX__ 0x7fff"
	.byte	0x1
	.uleb128 0
	.string	"__INT16_C(c) c"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST16_WIDTH__ 16"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST32_MAX__ 0x7fffffffL"
	.byte	0x1
	.uleb128 0
	.string	"__INT32_C(c) c ## L"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST32_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST64_MAX__ 0x7fffffffffffffffLL"
	.byte	0x1
	.uleb128 0
	.string	"__INT64_C(c) c ## LL"
	.byte	0x1
	.uleb128 0
	.string	"__INT_LEAST64_WIDTH__ 64"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST8_MAX__ 0xff"
	.byte	0x1
	.uleb128 0
	.string	"__UINT8_C(c) c"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST16_MAX__ 0xffff"
	.byte	0x1
	.uleb128 0
	.string	"__UINT16_C(c) c"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST32_MAX__ 0xffffffffUL"
	.byte	0x1
	.uleb128 0
	.string	"__UINT32_C(c) c ## UL"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_LEAST64_MAX__ 0xffffffffffffffffULL"
	.byte	0x1
	.uleb128 0
	.string	"__UINT64_C(c) c ## ULL"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST8_MAX__ 0x7fffffff"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST8_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST16_MAX__ 0x7fffffff"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST16_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST32_MAX__ 0x7fffffff"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST32_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST64_MAX__ 0x7fffffffffffffffLL"
	.byte	0x1
	.uleb128 0
	.string	"__INT_FAST64_WIDTH__ 64"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST8_MAX__ 0xffffffffU"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST16_MAX__ 0xffffffffU"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST32_MAX__ 0xffffffffU"
	.byte	0x1
	.uleb128 0
	.string	"__UINT_FAST64_MAX__ 0xffffffffffffffffULL"
	.byte	0x1
	.uleb128 0
	.string	"__INTPTR_MAX__ 0x7fffffffL"
	.byte	0x1
	.uleb128 0
	.string	"__INTPTR_WIDTH__ 32"
	.byte	0x1
	.uleb128 0
	.string	"__UINTPTR_MAX__ 0xffffffffUL"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_IEC_559 0"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_IEC_559_COMPLEX 0"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_EVAL_METHOD__ 0"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_EVAL_METHOD_TS_18661_3__ 0"
	.byte	0x1
	.uleb128 0
	.string	"__DEC_EVAL_METHOD__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_RADIX__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_MANT_DIG__ 24"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_DIG__ 6"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_MIN_EXP__ (-125)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_MIN_10_EXP__ (-37)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_MAX_EXP__ 128"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_MAX_10_EXP__ 38"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_DECIMAL_DIG__ 9"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_MAX__ 3.4028234663852886e+38F"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_NORM_MAX__ 3.4028234663852886e+38F"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_MIN__ 1.1754943508222875e-38F"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_EPSILON__ 1.1920928955078125e-7F"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_DENORM_MIN__ 1.4012984643248171e-45F"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_HAS_DENORM__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_HAS_INFINITY__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_HAS_QUIET_NAN__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FP_FAST_FMAF 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT_IS_IEC_60559__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_MANT_DIG__ 53"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_DIG__ 15"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_MIN_EXP__ (-1021)"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_MIN_10_EXP__ (-307)"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_MAX_EXP__ 1024"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_MAX_10_EXP__ 308"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_DECIMAL_DIG__ 17"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_MAX__ ((double)1.7976931348623157e+308L)"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_NORM_MAX__ ((double)1.7976931348623157e+308L)"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_MIN__ ((double)2.2250738585072014e-308L)"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_EPSILON__ ((double)2.2204460492503131e-16L)"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_DENORM_MIN__ ((double)4.9406564584124654e-324L)"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_HAS_DENORM__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_HAS_INFINITY__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_HAS_QUIET_NAN__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__DBL_IS_IEC_60559__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_MANT_DIG__ 53"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_DIG__ 15"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_MIN_EXP__ (-1021)"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_MIN_10_EXP__ (-307)"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_MAX_EXP__ 1024"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_MAX_10_EXP__ 308"
	.byte	0x1
	.uleb128 0
	.string	"__DECIMAL_DIG__ 17"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_DECIMAL_DIG__ 17"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_MAX__ 1.7976931348623157e+308L"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_NORM_MAX__ 1.7976931348623157e+308L"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_MIN__ 2.2250738585072014e-308L"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_EPSILON__ 2.2204460492503131e-16L"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_DENORM_MIN__ 4.9406564584124654e-324L"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_HAS_DENORM__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_HAS_INFINITY__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_HAS_QUIET_NAN__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__LDBL_IS_IEC_60559__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_MANT_DIG__ 24"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_DIG__ 6"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_MIN_EXP__ (-125)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_MIN_10_EXP__ (-37)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_MAX_EXP__ 128"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_MAX_10_EXP__ 38"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_DECIMAL_DIG__ 9"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_MAX__ 3.4028234663852886e+38F32"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_NORM_MAX__ 3.4028234663852886e+38F32"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_MIN__ 1.1754943508222875e-38F32"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_EPSILON__ 1.1920928955078125e-7F32"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_DENORM_MIN__ 1.4012984643248171e-45F32"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_HAS_DENORM__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_HAS_INFINITY__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_HAS_QUIET_NAN__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FP_FAST_FMAF32 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32_IS_IEC_60559__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_MANT_DIG__ 53"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_DIG__ 15"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_MIN_EXP__ (-1021)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_MIN_10_EXP__ (-307)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_MAX_EXP__ 1024"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_MAX_10_EXP__ 308"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_DECIMAL_DIG__ 17"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_MAX__ 1.7976931348623157e+308F64"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_NORM_MAX__ 1.7976931348623157e+308F64"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_MIN__ 2.2250738585072014e-308F64"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_EPSILON__ 2.2204460492503131e-16F64"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_DENORM_MIN__ 4.9406564584124654e-324F64"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_HAS_DENORM__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_HAS_INFINITY__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_HAS_QUIET_NAN__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT64_IS_IEC_60559__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_MANT_DIG__ 53"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_DIG__ 15"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_MIN_EXP__ (-1021)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_MIN_10_EXP__ (-307)"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_MAX_EXP__ 1024"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_MAX_10_EXP__ 308"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_DECIMAL_DIG__ 17"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_MAX__ 1.7976931348623157e+308F32x"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_NORM_MAX__ 1.7976931348623157e+308F32x"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_MIN__ 2.2250738585072014e-308F32x"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_EPSILON__ 2.2204460492503131e-16F32x"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_DENORM_MIN__ 4.9406564584124654e-324F32x"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_HAS_DENORM__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_HAS_INFINITY__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_HAS_QUIET_NAN__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__FLT32X_IS_IEC_60559__ 2"
	.byte	0x1
	.uleb128 0
	.string	"__REGISTER_PREFIX__ %"
	.byte	0x1
	.uleb128 0
	.string	"__USER_LABEL_PREFIX__ "
	.byte	0x1
	.uleb128 0
	.string	"__GNUC_STDC_INLINE__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_BOOL_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_CHAR_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_CHAR16_T_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_CHAR32_T_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_WCHAR_T_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_SHORT_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_INT_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_LONG_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_LLONG_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_TEST_AND_SET_TRUEVAL 1"
	.byte	0x1
	.uleb128 0
	.string	"__GCC_ATOMIC_POINTER_LOCK_FREE 1"
	.byte	0x1
	.uleb128 0
	.string	"__HAVE_SPECULATION_SAFE_VALUE 1"
	.byte	0x1
	.uleb128 0
	.string	"__PRAGMA_REDEFINE_EXTNAME 1"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_WCHAR_T__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_WINT_T__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__SIZEOF_PTRDIFF_T__ 4"
	.byte	0x1
	.uleb128 0
	.string	"__tricore 1"
	.byte	0x1
	.uleb128 0
	.string	"__tricore__ 1"
	.byte	0x1
	.uleb128 0
	.string	"tricore 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TC162__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_CORE__ 0x162"
	.byte	0x1
	.uleb128 0
	.string	"__TC33XX__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_NAME__ 0x3300"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_DIV__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_FTOIZ__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_MOV64__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_POPCNT__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_LHA__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_CRCN__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_SHUFFLE__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_FTOHP__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_HPTOF__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_HAVE_FLOAT16__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_NOP 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_LROTATE 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_RROTATE 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_INSERT 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_IMASK 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_SWAPW 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_SWAPMSKW 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_CMPSWAPW 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_SATB 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_SATH 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_SATBU 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_SATHU 1"
	.byte	0x1
	.uleb128 0
	.string	"__BUILTIN_TRICORE_LDMST 1"
	.byte	0x1
	.uleb128 0
	.string	"__ELF__ 1"
	.byte	0x1
	.uleb128 0x6
	.string	"flashaddress parameter[0]"
	.byte	0x1
	.uleb128 0x7
	.string	"databuswidth parameter[1]"
	.byte	0x1
	.uleb128 0x8
	.string	"address parameter[2]"
	.byte	0x1
	.uleb128 0x9
	.string	"number parameter[3]"
	.byte	0x1
	.uleb128 0xa
	.string	"status parameter[4]"
	.byte	0x1
	.uleb128 0xb
	.string	"databegin parameter[5]"
	.byte	0x1
	.uleb128 0xc
	.string	"dummy1 parameter[6]"
	.byte	0x1
	.uleb128 0xd
	.string	"dummy2 parameter[7]"
	.byte	0x1
	.uleb128 0xe
	.string	"HCI_STATUS 0xF8040004u"
	.byte	0x1
	.uleb128 0xf
	.string	"HCI_CLRERR 0xF8040014u"
	.byte	0x1
	.uleb128 0x10
	.string	"HCI_ERR 0xF8040010u"
	.byte	0x1
	.uleb128 0x11
	.string	"DMU_GP_HOST_DFECCS 0xF804010Cu"
	.byte	0x1
	.uleb128 0x12
	.string	"DMU_GP_HOST_DFECCC 0xF8040110u"
	.byte	0x1
	.uleb128 0x15
	.string	"MEM(address) (*((volatile unsigned int *)(address)))"
	.byte	0x1
	.uleb128 0x18
	.string	"MEM16(address) (*((volatile unsigned short *)(address)))"
	.byte	0x1
	.uleb128 0x1b
	.string	"MEM8(address) (*((volatile unsigned char *)(address)))"
	.byte	0x1
	.uleb128 0x1e
	.string	"PFRWBxy_UR_FLASHCON2_OFFS 0x0u"
	.byte	0x1
	.uleb128 0x1f
	.string	"PFRWBxy_UR_FLASHCON3_OFFS 0x4u"
	.byte	0x1
	.uleb128 0x20
	.string	"PFRWBxy_UR_ECCR_OFFS 0x2000u"
	.byte	0x1
	.uleb128 0x21
	.string	"PFRWBxy_UR_ECCS_OFFS 0x2004u"
	.byte	0x4
	.byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"",@progbits
	.ident	"GCC: (GNU) 11.3.1 20221230"
.section .callinfo
  .word start #name
  .word start_end #sz
  .word 0x00000000 #reg
  .word 0x00000000 #arg
  .word 0x00000000 #ret
  .word 0x00000080 #stat
  .word flashing #name
  .word flashing_end #sz
  .word 0xf4fc0fff #reg
  .word 0x00300000 #arg
  .word 0x00000004 #ret
  .word 0x00008080 #stat
