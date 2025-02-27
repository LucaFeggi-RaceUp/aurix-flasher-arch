# tric_asm_file_start
	.file	"flash_TC2xx.c"
	.file	"flash_TC2xx.c"
.section .text,"ax",@progbits
.Ltext0:
	.align 1
	.global	start
	.type	start, @function
start:
.LFB0:
	.file 1 "flash_TC2xx.c"
	.loc 1 28 1
	.loc 1 29 3
#APP
	# 29 "flash_TC2xx.c" 1
	.global _start
	# 0 "" 2
	.loc 1 30 3
	# 30 "flash_TC2xx.c" 1
	 _start:	 nop
	# 0 "" 2
	.loc 1 31 3
	# 31 "flash_TC2xx.c" 1
	 nop
	# 0 "" 2
	.loc 1 32 3
	# 32 "flash_TC2xx.c" 1
	 movh.a   %a10,hi:(0x70004000)
	# 0 "" 2
	.loc 1 33 3
	# 33 "flash_TC2xx.c" 1
	 lea      %a10,[%a10]lo:(0x70004000)
	# 0 "" 2
	.loc 1 34 3
	# 34 "flash_TC2xx.c" 1
	 ja flashing
	# 0 "" 2
	.loc 1 35 1 is_stmt 0
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
	.loc 1 39 1 is_stmt 1
.LVL0:
	.loc 1 40 3
	.loc 1 41 3
	.loc 1 42 3
	.loc 1 43 3
	.loc 1 44 3
	.loc 1 45 3
	.loc 1 46 3
	.loc 1 47 3
	.loc 1 48 3
	.loc 1 50 3
	.loc 1 50 16 is_stmt 0
	ld.w	%d2, [%a4] 16
	.loc 1 39 1
	lea	%SP, [%SP] -296
.LCFI0:
	.loc 1 39 1
	mov.aa	%a2, %a4
	.loc 1 50 6
	jeq	%d2, 1, .L90
	.loc 1 109 3 is_stmt 1
	.loc 1 109 6 is_stmt 0
	jeq	%d2, 2, .L91
.LVL1:
.L20:
	.loc 1 254 3 is_stmt 1
#APP
	# 254 "flash_TC2xx.c" 1
		debug
	# 0 "" 2
	.loc 1 255 1 is_stmt 0
#NO_APP
	ret	#flashing
.L90:
	.loc 1 52 7 is_stmt 1
	.loc 1 52 20 is_stmt 0
	ld.w	%d2, [%a4] 8
	st.w	[%SP] 20, %d2
	.loc 1 53 7 is_stmt 1
	.loc 1 54 12 is_stmt 0
	mov	%d2, 0
	.loc 1 55 25
	movh	%d3, 36608
	.loc 1 55 10
	movh	%d4, 32768
	.loc 1 54 12
	st.w	[%SP] 36, %d2
	.loc 1 55 25
	ld.w	%d2, [%a4]0
	.loc 1 53 12
	ld.a	%a5, [%a4] 20
.LVL2:
	.loc 1 54 7 is_stmt 1
	.loc 1 55 7
	.loc 1 55 25 is_stmt 0
	and	%d2, %d3
	.loc 1 55 10
	jeq	%d2, %d4, .L92
	.loc 1 56 7 is_stmt 1
	.loc 1 56 10 is_stmt 0
	jne	%d2, %d3, .L6
	.loc 1 56 52 is_stmt 1 discriminator 1
	.loc 1 56 57 is_stmt 0 discriminator 1
	mov	%d2, 8
	st.w	[%SP] 36, %d2
.L6:
	.loc 1 57 7 is_stmt 1
	.loc 1 57 16 is_stmt 0
	ld.w	%d2, [%SP] 36
	.loc 1 57 10
	jz	%d2, .L93
.L7:
	.loc 1 59 27 is_stmt 1
	ld.w	%d2, [%a2] 12
	.loc 1 69 51 is_stmt 0
	movh.a	%a4, 44800
	.loc 1 79 50
	movh.a	%a12, 44800
	.loc 1 81 50
	movh.a	%a7, 44800
	.loc 1 85 47
	movh	%d1, 44801
	.loc 1 87 47
	movh.a	%a15, 44801
	.loc 1 89 47
	movh.a	%a14, 44801
	.loc 1 94 16
	movh.a	%a6, 63488
	.loc 1 62 10
	mov	%d6, 0
	.loc 1 69 51
	lea	%a4, [%a4] 21844
	mov	%d11, 80
	.loc 1 71 51
	mov	%d10, 93
	.loc 1 79 50
	lea	%a12, [%a12] 22000
	.loc 1 81 50
	lea	%a7, [%a7] 22004
	.loc 1 85 47
	addi	%d1, %d1, -21936
	.loc 1 87 47
	lea	%a15, [%a15] -21928
	.loc 1 89 47
	lea	%a14, [%a14] -21848
	mov	%d9, 160
	.loc 1 91 47
	mov	%d8, 122
	.loc 1 92 16
	mov	%d0, 16384
	.loc 1 94 16
	lea	%a6, [%a6] 8208
	.loc 1 97 59
	mov	%d5, 250
	.loc 1 99 47
	mov	%d7, 256
	.loc 1 59 27
	jz	%d2, .L17
.L8:
	.loc 1 61 4 is_stmt 1
	.loc 1 61 11 is_stmt 0
	ld.w	%d3, [%SP] 20
	.loc 1 62 4 is_stmt 1
	.loc 1 62 10 is_stmt 0
	st.w	[%SP] 12, %d6
	.loc 1 62 15 is_stmt 1
	ld.w	%d4, [%SP] 12
	ld.w	%d3, [%SP] 36
	jge.u	%d4, %d3, .L9
	addsc.a	%a13, %a5, %d2, 0
	mov.aa	%a3, %a5
.LVL3:
.L10:
	.loc 1 64 8 discriminator 3
	.loc 1 64 20 is_stmt 0 discriminator 3
	ld.w	%d3, [%SP] 12
	.loc 1 64 24 discriminator 3
	mov.aa	%a5, %a3
	.loc 1 64 23 discriminator 3
	sh	%d3, 2
	addi	%d3, %d3, 296
	.loc 1 64 24 discriminator 3
	ld.w	%d2, [%a5]0
	.loc 1 64 23 discriminator 3
	mov.a	%a5, %d3
	.loc 1 64 24 discriminator 3
	add.a	%a3, 4
.LVL4:
	.loc 1 64 23 discriminator 3
	add.a	%a5, %SP
	st.w	[%a5] -256, %d2
	.loc 1 65 8 is_stmt 1 discriminator 3
.LVL5:
	.loc 1 66 8 discriminator 3
	.loc 1 62 24 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 12
	.loc 1 66 20 discriminator 3
	sub.a	%a5, %a13, %a3
	.loc 1 62 24 is_stmt 1 discriminator 3
	add	%d2, 1
	st.w	[%SP] 12, %d2
	.loc 1 62 15 discriminator 3
	ld.w	%d4, [%SP] 12
	ld.w	%d3, [%SP] 36
	jlt.u	%d4, %d3, .L10
	st.a	[%a2] 12, %a5
	st.w	[%SP] 12, %d2
	.loc 1 65 12 is_stmt 0
	mov.aa	%a5, %a3
.LVL6:
.L9:
	.loc 1 68 4 is_stmt 1
	.loc 1 68 13 is_stmt 0
	ld.w	%d2, [%SP] 36
	.loc 1 68 7
	ne	%d2, %d2, 64
	jnz	%d2, .L11
	.loc 1 69 8 is_stmt 1
	.loc 1 69 51 is_stmt 0
	st.w	[%a4]0, %d11
.L11:
	.loc 1 70 4 is_stmt 1
	.loc 1 70 13 is_stmt 0
	ld.w	%d2, [%SP] 36
	.loc 1 70 7
	ne	%d2, %d2, 8
	jnz	%d2, .L12
	.loc 1 71 8 is_stmt 1
	.loc 1 71 51 is_stmt 0
	st.w	[%a4]0, %d10
.L12:
	.loc 1 72 4 is_stmt 1
	.loc 1 72 5 is_stmt 0
	st.w	[%SP] 12, %d6
	.loc 1 73 4 is_stmt 1
	.loc 1 73 12
	ld.w	%d3, [%SP] 12
	ld.w	%d2, [%SP] 36
	jge.u	%d3, %d2, .L16
.L13:
	.loc 1 75 8
	.loc 1 75 29 is_stmt 0
	ld.w	%d2, [%SP] 12
	sh	%d2, 2
	addi	%d2, %d2, 296
	mov.a	%a3, %d2
	add.a	%a3, %SP
	ld.w	%d2, [%a3] -256
	.loc 1 75 16
	st.w	[%SP] 28, %d2
	.loc 1 76 8 is_stmt 1
	.loc 1 76 9 is_stmt 0
	ld.w	%d2, [%SP] 12
	add	%d2, 1
	st.w	[%SP] 12, %d2
	.loc 1 77 8 is_stmt 1
	.loc 1 77 30 is_stmt 0
	ld.w	%d2, [%SP] 12
	sh	%d2, 2
	addi	%d2, %d2, 296
	mov.a	%a3, %d2
	add.a	%a3, %SP
	ld.w	%d2, [%a3] -256
	.loc 1 77 17
	st.w	[%SP] 32, %d2
	.loc 1 78 8 is_stmt 1
	.loc 1 78 9 is_stmt 0
	ld.w	%d2, [%SP] 12
	add	%d2, 1
	st.w	[%SP] 12, %d2
	.loc 1 79 8 is_stmt 1
	.loc 1 79 50 is_stmt 0
	ld.w	%d2, [%SP] 28
	st.w	[%a12]0, %d2
	.loc 1 80 8 is_stmt 1
#APP
	# 80 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 81 8
	.loc 1 81 50 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 32
	st.w	[%a7]0, %d2
	.loc 1 82 8 is_stmt 1
#APP
	# 82 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 73 12
#NO_APP
	ld.w	%d3, [%SP] 12
	ld.w	%d2, [%SP] 36
	jlt.u	%d3, %d2, .L13
.L16:
	.loc 1 85 4
	.loc 1 85 47 is_stmt 0
	mov.a	%a3, %d1
	ld.w	%d2, [%SP] 20
	st.w	[%a3]0, %d2
	.loc 1 86 4 is_stmt 1
#APP
	# 86 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 87 4
	.loc 1 87 47 is_stmt 0
#NO_APP
	st.w	[%a15]0, %d6
	.loc 1 88 4 is_stmt 1
#APP
	# 88 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 89 4
	.loc 1 89 47 is_stmt 0
#NO_APP
	st.w	[%a14]0, %d9
	.loc 1 90 4 is_stmt 1
#APP
	# 90 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 91 4
	.loc 1 91 47 is_stmt 0
#NO_APP
	st.w	[%a14]0, %d8
	.loc 1 92 4 is_stmt 1
	.loc 1 92 16 is_stmt 0
	st.w	[%SP]0, %d0
	.loc 1 92 32 is_stmt 1
	ld.w	%d2, [%SP]0
	jlez	%d2, .L15
.L14:
	.loc 1 94 8
	.loc 1 94 16 is_stmt 0
	ld.w	%d2, [%a6]0
	.loc 1 94 13
	st.w	[%SP] 24, %d2
	.loc 1 95 8 is_stmt 1
#APP
	# 95 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 96 8
	.loc 1 96 18 is_stmt 0
#NO_APP
	ld.w	%d2, [%SP] 24
	and	%d2, %d2, 30
	.loc 1 96 11
	jnz	%d2, .L18
	.loc 1 97 5 is_stmt 1
	.loc 1 97 12 is_stmt 0
	st.w	[%SP]0, %d2
	.loc 1 97 16 is_stmt 1
	.loc 1 97 59 is_stmt 0
	st.w	[%a4]0, %d5
.L18:
	.loc 1 98 8 is_stmt 1
	.loc 1 98 19 is_stmt 0
	ld.w	%d2, [%SP]0
	.loc 1 98 11
	jne	%d2, 1, .L19
	.loc 1 99 5 is_stmt 1
	.loc 1 99 18 is_stmt 0
	ld.w	%d2, [%SP] 20
	st.w	[%a2] 8, %d2
	.loc 1 99 34 is_stmt 1
	.loc 1 99 47 is_stmt 0
	st.w	[%a2] 16, %d7
	.loc 1 99 57 is_stmt 1
	.loc 1 99 100 is_stmt 0
	st.w	[%a4]0, %d5
	.loc 1 99 108 is_stmt 1
#APP
	# 99 "flash_TC2xx.c" 1
		debug
	# 0 "" 2
#NO_APP
.L19:
	.loc 1 92 43 discriminator 2
	ld.w	%d2, [%SP]0
	add	%d2, -1
	st.w	[%SP]0, %d2
	.loc 1 92 32 discriminator 2
	ld.w	%d2, [%SP]0
	jgtz	%d2, .L14
.L15:
	.loc 1 101 4
	.loc 1 101 23 is_stmt 0
	ld.w	%d2, [%SP] 36
	.loc 1 101 16
	ld.w	%d3, [%SP] 20
	.loc 1 101 23
	sh	%d2, 2
	.loc 1 101 16
	add	%d2, %d3
	st.w	[%SP] 20, %d2
	.loc 1 59 27 is_stmt 1
	ld.w	%d2, [%a2] 12
	jnz	%d2, .L8
.L17:
	.loc 1 103 7
	.loc 1 103 20 is_stmt 0
	mov	%d2, 0
	.loc 1 104 50
	movh.a	%a3, 44800
	lea	%a3, [%a3] 21844
	.loc 1 103 20
	st.w	[%a2] 16, %d2
	.loc 1 104 7 is_stmt 1
	.loc 1 104 50 is_stmt 0
	mov	%d2, 250
	st.w	[%a3]0, %d2
	.loc 1 105 7 is_stmt 1
#APP
	# 105 "flash_TC2xx.c" 1
		debug
	# 0 "" 2
	.loc 1 109 16 is_stmt 0
#NO_APP
	ld.w	%d2, [%a2] 16
	.loc 1 109 3 is_stmt 1
	.loc 1 109 6 is_stmt 0
	jne	%d2, 2, .L20
.LVL7:
.L91:
	.loc 1 111 7 is_stmt 1
	.loc 1 111 12 is_stmt 0
	mov	%d2, 0
	.loc 1 112 61
	ld.w	%d4, [%a2] 8
	.loc 1 111 12
	st.w	[%SP] 8, %d2
	.loc 1 112 7 is_stmt 1
	.loc 1 112 23 is_stmt 0
	ld.w	%d2, [%a2]0
	.loc 1 112 49
	xor	%d3, %d2, %d4
	andn	%d3, %d3, ~(-256)
	.loc 1 112 10
	jz	%d3, .L94
.L21:
	.loc 1 114 7 is_stmt 1
	.loc 1 114 27 is_stmt 0
	andn	%d3, %d2, ~(-256)
	.loc 1 114 41
	addi	%d5, %d3, 16384
	.loc 1 114 65
	andn	%d2, %d4, ~(-256)
	.loc 1 114 10
	jeq	%d5, %d2, .L95
.L22:
	.loc 1 116 7 is_stmt 1
	.loc 1 116 41 is_stmt 0
	mov.u	%d5, 32768
	add	%d5, %d3
	.loc 1 116 10
	jeq	%d2, %d5, .L96
.L23:
	.loc 1 118 7 is_stmt 1
	.loc 1 118 41 is_stmt 0
	mov.u	%d5, 49152
	add	%d5, %d3
	.loc 1 118 10
	jeq	%d2, %d5, .L97
.L24:
	.loc 1 120 7 is_stmt 1
	.loc 1 120 41 is_stmt 0
	addih	%d5, %d3, 1
	.loc 1 120 10
	jeq	%d2, %d5, .L98
.L25:
	.loc 1 122 7 is_stmt 1
	.loc 1 122 41 is_stmt 0
	movh	%d5, 1
	addi	%d5, %d5, 16384
	add	%d5, %d3
	.loc 1 122 10
	jeq	%d2, %d5, .L99
.L26:
	.loc 1 124 7 is_stmt 1
	.loc 1 124 41 is_stmt 0
	movh	%d5, 2
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 124 10
	jeq	%d2, %d5, .L100
.L27:
	.loc 1 126 7 is_stmt 1
	.loc 1 126 41 is_stmt 0
	movh	%d5, 2
	addi	%d5, %d5, -16384
	add	%d5, %d3
	.loc 1 126 10
	jeq	%d2, %d5, .L101
.L28:
	.loc 1 128 7 is_stmt 1
	.loc 1 128 41 is_stmt 0
	addih	%d5, %d3, 2
	.loc 1 128 10
	jeq	%d2, %d5, .L102
.L29:
	.loc 1 130 7 is_stmt 1
	.loc 1 130 41 is_stmt 0
	movh	%d5, 3
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 130 10
	jeq	%d2, %d5, .L103
.L30:
	.loc 1 132 7 is_stmt 1
	.loc 1 132 41 is_stmt 0
	addih	%d5, %d3, 3
	.loc 1 132 10
	jeq	%d2, %d5, .L104
.L31:
	.loc 1 134 7 is_stmt 1
	.loc 1 134 41 is_stmt 0
	movh	%d5, 4
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 134 10
	jeq	%d2, %d5, .L105
.L32:
	.loc 1 136 7 is_stmt 1
	.loc 1 136 41 is_stmt 0
	addih	%d5, %d3, 4
	.loc 1 136 10
	jeq	%d2, %d5, .L106
.L33:
	.loc 1 138 7 is_stmt 1
	.loc 1 138 41 is_stmt 0
	movh	%d5, 5
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 138 10
	jeq	%d2, %d5, .L107
.L34:
	.loc 1 140 7 is_stmt 1
	.loc 1 140 41 is_stmt 0
	addih	%d5, %d3, 5
	.loc 1 140 10
	jeq	%d2, %d5, .L108
.L35:
	.loc 1 142 7 is_stmt 1
	.loc 1 142 41 is_stmt 0
	movh	%d5, 6
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 142 10
	jeq	%d2, %d5, .L109
.L36:
	.loc 1 144 7 is_stmt 1
	.loc 1 144 41 is_stmt 0
	addih	%d5, %d3, 6
	.loc 1 144 10
	jeq	%d2, %d5, .L110
.L37:
	.loc 1 146 7 is_stmt 1
	.loc 1 146 41 is_stmt 0
	addih	%d5, %d3, 7
	.loc 1 146 10
	jeq	%d2, %d5, .L111
.L38:
	.loc 1 148 7 is_stmt 1
	.loc 1 148 41 is_stmt 0
	addih	%d5, %d3, 8
	.loc 1 148 10
	jeq	%d2, %d5, .L112
.L39:
	.loc 1 150 7 is_stmt 1
	.loc 1 150 41 is_stmt 0
	addih	%d5, %d3, 9
	.loc 1 150 10
	jeq	%d2, %d5, .L113
.L40:
	.loc 1 152 7 is_stmt 1
	.loc 1 152 41 is_stmt 0
	addih	%d5, %d3, 10
	.loc 1 152 10
	jeq	%d2, %d5, .L114
.L41:
	.loc 1 154 7 is_stmt 1
	.loc 1 154 41 is_stmt 0
	addih	%d5, %d3, 12
	.loc 1 154 10
	jeq	%d2, %d5, .L115
.L42:
	.loc 1 156 7 is_stmt 1
	.loc 1 156 41 is_stmt 0
	addih	%d5, %d3, 14
	.loc 1 156 10
	jeq	%d2, %d5, .L116
.L43:
	.loc 1 158 7 is_stmt 1
	.loc 1 158 41 is_stmt 0
	addih	%d5, %d3, 16
	.loc 1 158 10
	jeq	%d2, %d5, .L117
.L44:
	.loc 1 160 7 is_stmt 1
	.loc 1 160 41 is_stmt 0
	addih	%d5, %d3, 20
	.loc 1 160 10
	jeq	%d2, %d5, .L118
.L45:
	.loc 1 162 7 is_stmt 1
	.loc 1 162 41 is_stmt 0
	addih	%d5, %d3, 24
	.loc 1 162 10
	jeq	%d2, %d5, .L119
.L46:
	.loc 1 164 7 is_stmt 1
	.loc 1 164 41 is_stmt 0
	addih	%d5, %d3, 28
	.loc 1 164 10
	jeq	%d2, %d5, .L120
.L47:
	.loc 1 166 7 is_stmt 1
	.loc 1 166 41 is_stmt 0
	addih	%d5, %d3, 32
	.loc 1 166 10
	jeq	%d2, %d5, .L121
.L48:
	.loc 1 168 7 is_stmt 1
	.loc 1 168 41 is_stmt 0
	movh	%d5, 32
	addi	%d5, %d5, 16384
	add	%d5, %d3
	.loc 1 168 10
	jeq	%d2, %d5, .L122
.L49:
	.loc 1 170 7 is_stmt 1
	.loc 1 170 41 is_stmt 0
	movh	%d5, 33
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 170 10
	jeq	%d2, %d5, .L123
.L50:
	.loc 1 172 7 is_stmt 1
	.loc 1 172 41 is_stmt 0
	movh	%d5, 33
	addi	%d5, %d5, -16384
	add	%d5, %d3
	.loc 1 172 10
	jeq	%d2, %d5, .L124
.L51:
	.loc 1 174 7 is_stmt 1
	.loc 1 174 41 is_stmt 0
	addih	%d5, %d3, 33
	.loc 1 174 10
	jeq	%d2, %d5, .L125
.L52:
	.loc 1 176 7 is_stmt 1
	.loc 1 176 41 is_stmt 0
	movh	%d5, 33
	addi	%d5, %d5, 16384
	add	%d5, %d3
	.loc 1 176 10
	jeq	%d2, %d5, .L126
.L53:
	.loc 1 178 7 is_stmt 1
	.loc 1 178 41 is_stmt 0
	movh	%d5, 34
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 178 10
	jeq	%d2, %d5, .L127
.L54:
	.loc 1 180 7 is_stmt 1
	.loc 1 180 41 is_stmt 0
	movh	%d5, 34
	addi	%d5, %d5, -16384
	add	%d5, %d3
	.loc 1 180 10
	jeq	%d2, %d5, .L128
.L55:
	.loc 1 182 7 is_stmt 1
	.loc 1 182 41 is_stmt 0
	addih	%d5, %d3, 34
	.loc 1 182 10
	jeq	%d2, %d5, .L129
.L56:
	.loc 1 184 7 is_stmt 1
	.loc 1 184 41 is_stmt 0
	movh	%d5, 35
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 184 10
	jeq	%d2, %d5, .L130
.L57:
	.loc 1 186 7 is_stmt 1
	.loc 1 186 41 is_stmt 0
	addih	%d5, %d3, 35
	.loc 1 186 10
	jeq	%d2, %d5, .L131
.L58:
	.loc 1 188 7 is_stmt 1
	.loc 1 188 41 is_stmt 0
	movh	%d5, 36
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 188 10
	jeq	%d2, %d5, .L132
.L59:
	.loc 1 190 7 is_stmt 1
	.loc 1 190 41 is_stmt 0
	addih	%d5, %d3, 36
	.loc 1 190 10
	jeq	%d2, %d5, .L133
.L60:
	.loc 1 192 7 is_stmt 1
	.loc 1 192 41 is_stmt 0
	movh	%d5, 37
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 192 10
	jeq	%d2, %d5, .L134
.L61:
	.loc 1 194 7 is_stmt 1
	.loc 1 194 41 is_stmt 0
	addih	%d5, %d3, 37
	.loc 1 194 10
	jeq	%d2, %d5, .L135
.L62:
	.loc 1 196 7 is_stmt 1
	.loc 1 196 41 is_stmt 0
	movh	%d5, 38
	addi	%d5, %d5, -32768
	add	%d5, %d3
	.loc 1 196 10
	jeq	%d2, %d5, .L136
.L63:
	.loc 1 198 7 is_stmt 1
	.loc 1 198 41 is_stmt 0
	addih	%d5, %d3, 38
	.loc 1 198 10
	jeq	%d2, %d5, .L137
.L64:
	.loc 1 200 7 is_stmt 1
	.loc 1 200 41 is_stmt 0
	addih	%d5, %d3, 39
	.loc 1 200 10
	jeq	%d2, %d5, .L138
.L65:
	.loc 1 202 7 is_stmt 1
	.loc 1 202 41 is_stmt 0
	addih	%d5, %d3, 40
	.loc 1 202 10
	jeq	%d2, %d5, .L139
.L66:
	.loc 1 204 7 is_stmt 1
	.loc 1 204 41 is_stmt 0
	addih	%d5, %d3, 41
	.loc 1 204 10
	jeq	%d2, %d5, .L140
.L67:
	.loc 1 206 7 is_stmt 1
	.loc 1 206 41 is_stmt 0
	addih	%d5, %d3, 42
	.loc 1 206 10
	jeq	%d2, %d5, .L141
.L68:
	.loc 1 208 7 is_stmt 1
	.loc 1 208 41 is_stmt 0
	addih	%d5, %d3, 44
	.loc 1 208 10
	jeq	%d2, %d5, .L142
.L69:
	.loc 1 210 7 is_stmt 1
	.loc 1 210 41 is_stmt 0
	addih	%d5, %d3, 46
	.loc 1 210 10
	jeq	%d2, %d5, .L143
.L70:
	.loc 1 212 7 is_stmt 1
	.loc 1 212 41 is_stmt 0
	addih	%d5, %d3, 48
	.loc 1 212 10
	jeq	%d2, %d5, .L144
.L71:
	.loc 1 214 7 is_stmt 1
	.loc 1 214 41 is_stmt 0
	addih	%d5, %d3, 52
	.loc 1 214 10
	jeq	%d2, %d5, .L145
.L72:
	.loc 1 216 7 is_stmt 1
	.loc 1 216 41 is_stmt 0
	addih	%d5, %d3, 56
	.loc 1 216 10
	jeq	%d2, %d5, .L146
.L73:
	.loc 1 218 7 is_stmt 1
	.loc 1 218 41 is_stmt 0
	addih	%d3, %d3, 60
	.loc 1 218 10
	jeq	%d2, %d3, .L147
.L74:
	.loc 1 220 7 is_stmt 1
	.loc 1 220 12 is_stmt 0
	mov	%d2, 1
	st.w	[%SP] 8, %d2
	.loc 1 221 7 is_stmt 1
	.loc 1 221 16 is_stmt 0
	ld.w	%d2, [%SP] 8
	.loc 1 221 10
	jz	%d2, .L148
.L75:
	.loc 1 227 7 is_stmt 1
	.loc 1 227 50 is_stmt 0
	movh.a	%a3, 44801
	lea	%a3, [%a3] -21936
	st.w	[%a3]0, %d4
	.loc 1 228 7 is_stmt 1
#APP
	# 228 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 229 7
	.loc 1 229 50 is_stmt 0
#NO_APP
	mov	%d2, 1
	movh.a	%a3, 44801
	lea	%a3, [%a3] -21928
	st.w	[%a3]0, %d2
	.loc 1 230 7 is_stmt 1
#APP
	# 230 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 231 7
	.loc 1 231 50 is_stmt 0
#NO_APP
	mov	%d2, 128
	movh.a	%a3, 44801
	lea	%a3, [%a3] -21848
	st.w	[%a3]0, %d2
	.loc 1 232 7 is_stmt 1
#APP
	# 232 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 233 7
	.loc 1 233 50 is_stmt 0
#NO_APP
	mov	%d2, 80
	st.w	[%a3]0, %d2
	.loc 1 234 7 is_stmt 1
#APP
	# 234 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 239 12 is_stmt 0
#NO_APP
	movh.a	%a3, 63488
	.loc 1 237 10
	mov	%d4, 0
	.loc 1 237 15
	movh	%d3, 4
	.loc 1 239 12
	lea	%a3, [%a3] 8208
.L78:
	.loc 1 235 7 is_stmt 1
	.loc 1 237 4
	.loc 1 237 10 is_stmt 0
	st.w	[%SP] 12, %d4
	.loc 1 237 15 is_stmt 1
	ld.w	%d2, [%SP] 12
	jge.u	%d2, %d3, .L79
.L76:
	.loc 1 238 8 discriminator 3
	.loc 1 238 9 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 12
	add	%d2, 1
	st.w	[%SP] 12, %d2
	.loc 1 238 14 is_stmt 1 discriminator 3
	.loc 1 238 15 is_stmt 0 discriminator 3
	ld.w	%d2, [%SP] 12
	add	%d2, -1
	st.w	[%SP] 12, %d2
	.loc 1 237 26 is_stmt 1 discriminator 3
	ld.w	%d2, [%SP] 12
	add	%d2, 1
	st.w	[%SP] 12, %d2
	.loc 1 237 15 discriminator 3
	ld.w	%d2, [%SP] 12
	jlt.u	%d2, %d3, .L76
.L79:
	.loc 1 239 4
	.loc 1 239 12 is_stmt 0
	ld.w	%d2, [%a3]0
	.loc 1 239 9
	st.w	[%SP] 24, %d2
	.loc 1 240 4 is_stmt 1
#APP
	# 240 "flash_TC2xx.c" 1
		dsync
	# 0 "" 2
	.loc 1 241 4
	.loc 1 241 10 is_stmt 0
#NO_APP
	ld.w	%d2, [%a3]0
	.loc 1 241 53
	and	%d2, %d2, 30
	.loc 1 241 7
	jnz	%d2, .L78
	.loc 1 243 8 is_stmt 1
	.loc 1 243 21 is_stmt 0
	st.w	[%a2] 16, %d2
	.loc 1 244 8 is_stmt 1
#APP
	# 244 "flash_TC2xx.c" 1
		nop
	# 0 "" 2
	.loc 1 245 8
	# 245 "flash_TC2xx.c" 1
		nop
	# 0 "" 2
	.loc 1 246 8
	# 246 "flash_TC2xx.c" 1
		nop
	# 0 "" 2
	.loc 1 247 8
	# 247 "flash_TC2xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L78
.L148:
	.loc 1 223 4
	.loc 1 223 17 is_stmt 0
	mov	%d2, 256
	st.w	[%a2] 16, %d2
	.loc 1 224 4 is_stmt 1
#APP
	# 224 "flash_TC2xx.c" 1
		debug
	# 0 "" 2
	.loc 1 227 61 is_stmt 0
#NO_APP
	ld.w	%d4, [%a2] 8
	j	.L75
.L94:
	.loc 1 112 89 discriminator 1
	ld.w	%d3, [%SP] 8
	.loc 1 112 80 discriminator 1
	jnz	%d3, .L21
	.loc 1 113 4 is_stmt 1
	.loc 1 113 7 is_stmt 0
	mov	%d5, 16384
	st.w	[%SP] 4, %d5
	.loc 1 113 15 is_stmt 1
	.loc 1 113 20 is_stmt 0
	mov	%d5, 1
	st.w	[%SP] 8, %d5
	.loc 1 113 23 is_stmt 1
	.loc 1 113 31 is_stmt 0
	st.w	[%SP] 16, %d3
	j	.L21
.LVL8:
.L93:
	.loc 1 58 4 is_stmt 1
	.loc 1 58 17 is_stmt 0
	mov	%d2, 256
	st.w	[%a2] 16, %d2
	.loc 1 58 25 is_stmt 1
#APP
	# 58 "flash_TC2xx.c" 1
		debug
	# 0 "" 2
#NO_APP
	j	.L7
.LVL9:
.L147:
	.loc 1 218 91 is_stmt 0 discriminator 1
	ld.w	%d2, [%SP] 8
	.loc 1 218 82 discriminator 1
	jnz	%d2, .L74
	.loc 1 219 4 is_stmt 1
	.loc 1 219 7 is_stmt 0
	movh	%d3, 4
	st.w	[%SP] 4, %d3
	.loc 1 219 16 is_stmt 1
	.loc 1 219 21 is_stmt 0
	mov	%d3, 1
	st.w	[%SP] 8, %d3
	.loc 1 219 24 is_stmt 1
	.loc 1 219 32 is_stmt 0
	st.w	[%SP] 16, %d2
	j	.L74
.LVL10:
.L92:
	.loc 1 55 52 is_stmt 1 discriminator 1
	.loc 1 55 57 is_stmt 0 discriminator 1
	mov	%d2, 64
	st.w	[%SP] 36, %d2
	.loc 1 56 7 is_stmt 1 discriminator 1
	.loc 1 57 7 discriminator 1
	.loc 1 57 16 is_stmt 0 discriminator 1
	ld.w	%d2, [%SP] 36
	.loc 1 57 10 discriminator 1
	jnz	%d2, .L7
	j	.L93
.LVL11:
.L98:
	.loc 1 120 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 120 81 discriminator 1
	jnz	%d5, .L25
	.loc 1 121 4 is_stmt 1
	.loc 1 121 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 121 15 is_stmt 1
	.loc 1 121 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 121 23 is_stmt 1
	.loc 1 121 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L25
.L97:
	.loc 1 118 89 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 118 80 discriminator 1
	jnz	%d5, .L24
	.loc 1 119 4 is_stmt 1
	.loc 1 119 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 119 15 is_stmt 1
	.loc 1 119 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 119 23 is_stmt 1
	.loc 1 119 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L24
.L96:
	.loc 1 116 89 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 116 80 discriminator 1
	jnz	%d5, .L23
	.loc 1 117 4 is_stmt 1
	.loc 1 117 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 117 15 is_stmt 1
	.loc 1 117 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 117 23 is_stmt 1
	.loc 1 117 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L23
.L95:
	.loc 1 114 89 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 114 80 discriminator 1
	jnz	%d5, .L22
	.loc 1 115 4 is_stmt 1
	.loc 1 115 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 115 15 is_stmt 1
	.loc 1 115 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 115 23 is_stmt 1
	.loc 1 115 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L22
.L138:
	.loc 1 200 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 200 82 discriminator 1
	jnz	%d5, .L65
	.loc 1 201 4 is_stmt 1
	.loc 1 201 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 201 16 is_stmt 1
	.loc 1 201 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 201 24 is_stmt 1
	.loc 1 201 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L65
.L137:
	.loc 1 198 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 198 82 discriminator 1
	jnz	%d5, .L64
	.loc 1 199 4 is_stmt 1
	.loc 1 199 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 199 16 is_stmt 1
	.loc 1 199 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 199 24 is_stmt 1
	.loc 1 199 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L64
.L136:
	.loc 1 196 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 196 82 discriminator 1
	jnz	%d5, .L63
	.loc 1 197 4 is_stmt 1
	.loc 1 197 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 197 15 is_stmt 1
	.loc 1 197 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 197 23 is_stmt 1
	.loc 1 197 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L63
.L135:
	.loc 1 194 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 194 82 discriminator 1
	jnz	%d5, .L62
	.loc 1 195 4 is_stmt 1
	.loc 1 195 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 195 15 is_stmt 1
	.loc 1 195 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 195 23 is_stmt 1
	.loc 1 195 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L62
.L134:
	.loc 1 192 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 192 82 discriminator 1
	jnz	%d5, .L61
	.loc 1 193 4 is_stmt 1
	.loc 1 193 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 193 15 is_stmt 1
	.loc 1 193 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 193 23 is_stmt 1
	.loc 1 193 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L61
.L133:
	.loc 1 190 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 190 82 discriminator 1
	jnz	%d5, .L60
	.loc 1 191 4 is_stmt 1
	.loc 1 191 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 191 15 is_stmt 1
	.loc 1 191 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 191 23 is_stmt 1
	.loc 1 191 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L60
.L132:
	.loc 1 188 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 188 82 discriminator 1
	jnz	%d5, .L59
	.loc 1 189 4 is_stmt 1
	.loc 1 189 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 189 15 is_stmt 1
	.loc 1 189 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 189 23 is_stmt 1
	.loc 1 189 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L59
.L131:
	.loc 1 186 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 186 82 discriminator 1
	jnz	%d5, .L58
	.loc 1 187 4 is_stmt 1
	.loc 1 187 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 187 15 is_stmt 1
	.loc 1 187 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 187 23 is_stmt 1
	.loc 1 187 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L58
.L130:
	.loc 1 184 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 184 82 discriminator 1
	jnz	%d5, .L57
	.loc 1 185 4 is_stmt 1
	.loc 1 185 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 185 15 is_stmt 1
	.loc 1 185 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 185 23 is_stmt 1
	.loc 1 185 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L57
.L129:
	.loc 1 182 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 182 82 discriminator 1
	jnz	%d5, .L56
	.loc 1 183 4 is_stmt 1
	.loc 1 183 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 183 15 is_stmt 1
	.loc 1 183 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 183 23 is_stmt 1
	.loc 1 183 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L56
.L128:
	.loc 1 180 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 180 82 discriminator 1
	jnz	%d5, .L55
	.loc 1 181 4 is_stmt 1
	.loc 1 181 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 181 15 is_stmt 1
	.loc 1 181 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 181 23 is_stmt 1
	.loc 1 181 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L55
.L127:
	.loc 1 178 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 178 82 discriminator 1
	jnz	%d5, .L54
	.loc 1 179 4 is_stmt 1
	.loc 1 179 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 179 15 is_stmt 1
	.loc 1 179 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 179 23 is_stmt 1
	.loc 1 179 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L54
.L126:
	.loc 1 176 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 176 82 discriminator 1
	jnz	%d5, .L53
	.loc 1 177 4 is_stmt 1
	.loc 1 177 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 177 15 is_stmt 1
	.loc 1 177 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 177 23 is_stmt 1
	.loc 1 177 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L53
.L125:
	.loc 1 174 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 174 82 discriminator 1
	jnz	%d5, .L52
	.loc 1 175 4 is_stmt 1
	.loc 1 175 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 175 15 is_stmt 1
	.loc 1 175 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 175 23 is_stmt 1
	.loc 1 175 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L52
.L124:
	.loc 1 172 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 172 82 discriminator 1
	jnz	%d5, .L51
	.loc 1 173 4 is_stmt 1
	.loc 1 173 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 173 15 is_stmt 1
	.loc 1 173 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 173 23 is_stmt 1
	.loc 1 173 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L51
.L123:
	.loc 1 170 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 170 82 discriminator 1
	jnz	%d5, .L50
	.loc 1 171 4 is_stmt 1
	.loc 1 171 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 171 15 is_stmt 1
	.loc 1 171 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 171 23 is_stmt 1
	.loc 1 171 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L50
.L146:
	.loc 1 216 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 216 82 discriminator 1
	jnz	%d5, .L73
	.loc 1 217 4 is_stmt 1
	.loc 1 217 7 is_stmt 0
	movh	%d6, 4
	st.w	[%SP] 4, %d6
	.loc 1 217 16 is_stmt 1
	.loc 1 217 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 217 24 is_stmt 1
	.loc 1 217 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L73
.L145:
	.loc 1 214 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 214 82 discriminator 1
	jnz	%d5, .L72
	.loc 1 215 4 is_stmt 1
	.loc 1 215 7 is_stmt 0
	movh	%d6, 4
	st.w	[%SP] 4, %d6
	.loc 1 215 16 is_stmt 1
	.loc 1 215 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 215 24 is_stmt 1
	.loc 1 215 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L72
.L144:
	.loc 1 212 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 212 82 discriminator 1
	jnz	%d5, .L71
	.loc 1 213 4 is_stmt 1
	.loc 1 213 7 is_stmt 0
	movh	%d6, 4
	st.w	[%SP] 4, %d6
	.loc 1 213 16 is_stmt 1
	.loc 1 213 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 213 24 is_stmt 1
	.loc 1 213 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L71
.L143:
	.loc 1 210 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 210 82 discriminator 1
	jnz	%d5, .L70
	.loc 1 211 4 is_stmt 1
	.loc 1 211 7 is_stmt 0
	movh	%d6, 2
	st.w	[%SP] 4, %d6
	.loc 1 211 16 is_stmt 1
	.loc 1 211 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 211 24 is_stmt 1
	.loc 1 211 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L70
.L142:
	.loc 1 208 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 208 82 discriminator 1
	jnz	%d5, .L69
	.loc 1 209 4 is_stmt 1
	.loc 1 209 7 is_stmt 0
	movh	%d6, 2
	st.w	[%SP] 4, %d6
	.loc 1 209 16 is_stmt 1
	.loc 1 209 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 209 24 is_stmt 1
	.loc 1 209 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L69
.L141:
	.loc 1 206 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 206 82 discriminator 1
	jnz	%d5, .L68
	.loc 1 207 4 is_stmt 1
	.loc 1 207 7 is_stmt 0
	movh	%d6, 2
	st.w	[%SP] 4, %d6
	.loc 1 207 16 is_stmt 1
	.loc 1 207 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 207 24 is_stmt 1
	.loc 1 207 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L68
.L140:
	.loc 1 204 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 204 82 discriminator 1
	jnz	%d5, .L67
	.loc 1 205 4 is_stmt 1
	.loc 1 205 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 205 16 is_stmt 1
	.loc 1 205 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 205 24 is_stmt 1
	.loc 1 205 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L67
.L139:
	.loc 1 202 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 202 82 discriminator 1
	jnz	%d5, .L66
	.loc 1 203 4 is_stmt 1
	.loc 1 203 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 203 16 is_stmt 1
	.loc 1 203 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 203 24 is_stmt 1
	.loc 1 203 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L66
.L106:
	.loc 1 136 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 136 81 discriminator 1
	jnz	%d5, .L33
	.loc 1 137 4 is_stmt 1
	.loc 1 137 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 137 15 is_stmt 1
	.loc 1 137 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 137 23 is_stmt 1
	.loc 1 137 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L33
.L105:
	.loc 1 134 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 134 81 discriminator 1
	jnz	%d5, .L32
	.loc 1 135 4 is_stmt 1
	.loc 1 135 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 135 15 is_stmt 1
	.loc 1 135 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 135 23 is_stmt 1
	.loc 1 135 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L32
.L104:
	.loc 1 132 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 132 81 discriminator 1
	jnz	%d5, .L31
	.loc 1 133 4 is_stmt 1
	.loc 1 133 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 133 15 is_stmt 1
	.loc 1 133 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 133 23 is_stmt 1
	.loc 1 133 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L31
.L103:
	.loc 1 130 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 130 81 discriminator 1
	jnz	%d5, .L30
	.loc 1 131 4 is_stmt 1
	.loc 1 131 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 131 15 is_stmt 1
	.loc 1 131 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 131 23 is_stmt 1
	.loc 1 131 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L30
.L102:
	.loc 1 128 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 128 81 discriminator 1
	jnz	%d5, .L29
	.loc 1 129 4 is_stmt 1
	.loc 1 129 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 129 15 is_stmt 1
	.loc 1 129 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 129 23 is_stmt 1
	.loc 1 129 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L29
.L101:
	.loc 1 126 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 126 81 discriminator 1
	jnz	%d5, .L28
	.loc 1 127 4 is_stmt 1
	.loc 1 127 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 127 15 is_stmt 1
	.loc 1 127 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 127 23 is_stmt 1
	.loc 1 127 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L28
.L100:
	.loc 1 124 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 124 81 discriminator 1
	jnz	%d5, .L27
	.loc 1 125 4 is_stmt 1
	.loc 1 125 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 125 15 is_stmt 1
	.loc 1 125 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 125 23 is_stmt 1
	.loc 1 125 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L27
.L99:
	.loc 1 122 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 122 81 discriminator 1
	jnz	%d5, .L26
	.loc 1 123 4 is_stmt 1
	.loc 1 123 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 123 15 is_stmt 1
	.loc 1 123 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 123 23 is_stmt 1
	.loc 1 123 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L26
.L122:
	.loc 1 168 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 168 82 discriminator 1
	jnz	%d5, .L49
	.loc 1 169 4 is_stmt 1
	.loc 1 169 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 169 15 is_stmt 1
	.loc 1 169 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 169 23 is_stmt 1
	.loc 1 169 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L49
.L121:
	.loc 1 166 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 166 82 discriminator 1
	jnz	%d5, .L48
	.loc 1 167 4 is_stmt 1
	.loc 1 167 7 is_stmt 0
	mov	%d6, 16384
	st.w	[%SP] 4, %d6
	.loc 1 167 15 is_stmt 1
	.loc 1 167 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 167 23 is_stmt 1
	.loc 1 167 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L48
.L120:
	.loc 1 164 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 164 82 discriminator 1
	jnz	%d5, .L47
	.loc 1 165 4 is_stmt 1
	.loc 1 165 7 is_stmt 0
	movh	%d6, 4
	st.w	[%SP] 4, %d6
	.loc 1 165 16 is_stmt 1
	.loc 1 165 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 165 24 is_stmt 1
	.loc 1 165 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L47
.L119:
	.loc 1 162 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 162 82 discriminator 1
	jnz	%d5, .L46
	.loc 1 163 4 is_stmt 1
	.loc 1 163 7 is_stmt 0
	movh	%d6, 4
	st.w	[%SP] 4, %d6
	.loc 1 163 16 is_stmt 1
	.loc 1 163 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 163 24 is_stmt 1
	.loc 1 163 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L46
.L118:
	.loc 1 160 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 160 82 discriminator 1
	jnz	%d5, .L45
	.loc 1 161 4 is_stmt 1
	.loc 1 161 7 is_stmt 0
	movh	%d6, 4
	st.w	[%SP] 4, %d6
	.loc 1 161 16 is_stmt 1
	.loc 1 161 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 161 24 is_stmt 1
	.loc 1 161 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L45
.L117:
	.loc 1 158 91 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 158 82 discriminator 1
	jnz	%d5, .L44
	.loc 1 159 4 is_stmt 1
	.loc 1 159 7 is_stmt 0
	movh	%d6, 4
	st.w	[%SP] 4, %d6
	.loc 1 159 16 is_stmt 1
	.loc 1 159 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 159 24 is_stmt 1
	.loc 1 159 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L44
.L116:
	.loc 1 156 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 156 81 discriminator 1
	jnz	%d5, .L43
	.loc 1 157 4 is_stmt 1
	.loc 1 157 7 is_stmt 0
	movh	%d6, 2
	st.w	[%SP] 4, %d6
	.loc 1 157 16 is_stmt 1
	.loc 1 157 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 157 24 is_stmt 1
	.loc 1 157 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L43
.L115:
	.loc 1 154 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 154 81 discriminator 1
	jnz	%d5, .L42
	.loc 1 155 4 is_stmt 1
	.loc 1 155 7 is_stmt 0
	movh	%d6, 2
	st.w	[%SP] 4, %d6
	.loc 1 155 16 is_stmt 1
	.loc 1 155 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 155 24 is_stmt 1
	.loc 1 155 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L42
.L114:
	.loc 1 152 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 152 81 discriminator 1
	jnz	%d5, .L41
	.loc 1 153 4 is_stmt 1
	.loc 1 153 7 is_stmt 0
	movh	%d6, 2
	st.w	[%SP] 4, %d6
	.loc 1 153 16 is_stmt 1
	.loc 1 153 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 153 24 is_stmt 1
	.loc 1 153 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L41
.L113:
	.loc 1 150 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 150 81 discriminator 1
	jnz	%d5, .L40
	.loc 1 151 4 is_stmt 1
	.loc 1 151 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 151 16 is_stmt 1
	.loc 1 151 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 151 24 is_stmt 1
	.loc 1 151 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L40
.L112:
	.loc 1 148 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 148 81 discriminator 1
	jnz	%d5, .L39
	.loc 1 149 4 is_stmt 1
	.loc 1 149 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 149 16 is_stmt 1
	.loc 1 149 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 149 24 is_stmt 1
	.loc 1 149 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L39
.L111:
	.loc 1 146 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 146 81 discriminator 1
	jnz	%d5, .L38
	.loc 1 147 4 is_stmt 1
	.loc 1 147 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 147 16 is_stmt 1
	.loc 1 147 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 147 24 is_stmt 1
	.loc 1 147 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L38
.L110:
	.loc 1 144 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 144 81 discriminator 1
	jnz	%d5, .L37
	.loc 1 145 4 is_stmt 1
	.loc 1 145 7 is_stmt 0
	movh	%d6, 1
	st.w	[%SP] 4, %d6
	.loc 1 145 16 is_stmt 1
	.loc 1 145 21 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 145 24 is_stmt 1
	.loc 1 145 32 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L37
.L109:
	.loc 1 142 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 142 81 discriminator 1
	jnz	%d5, .L36
	.loc 1 143 4 is_stmt 1
	.loc 1 143 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 143 15 is_stmt 1
	.loc 1 143 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 143 23 is_stmt 1
	.loc 1 143 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L36
.L108:
	.loc 1 140 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 140 81 discriminator 1
	jnz	%d5, .L35
	.loc 1 141 4 is_stmt 1
	.loc 1 141 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 141 15 is_stmt 1
	.loc 1 141 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 141 23 is_stmt 1
	.loc 1 141 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L35
.L107:
	.loc 1 138 90 discriminator 1
	ld.w	%d5, [%SP] 8
	.loc 1 138 81 discriminator 1
	jnz	%d5, .L34
	.loc 1 139 4 is_stmt 1
	.loc 1 139 7 is_stmt 0
	mov.u	%d6, 32768
	st.w	[%SP] 4, %d6
	.loc 1 139 15 is_stmt 1
	.loc 1 139 20 is_stmt 0
	mov	%d6, 1
	st.w	[%SP] 8, %d6
	.loc 1 139 23 is_stmt 1
	.loc 1 139 31 is_stmt 0
	st.w	[%SP] 16, %d5
	j	.L34
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
	.uleb128 0x128
	.align 2
.LEFDE2:
.section .text,"ax",@progbits
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.uaword	0x2ae
	.uahalf	0x5
	.byte	0x1
	.byte	0x4
	.uaword	.Ldebug_abbrev0
	.uleb128 0x6
	.string	"GNU C17 11.3.1 20221230 -mtc161 -g3 -O2 -fno-peephole2 -fno-common -fno-short-enums -fsingle-precision-constant"
	.byte	0x1d
	.string	"flash_TC2xx.c"
	.string	"/home/dummy/share/HOST/AURIX_MINGW_INSTALL/DAS_v8_0_5_Linux.tar/aurix_flasher_linux/gdb_flash_drivers"
	.uaword	.Ltext0
	.uaword	.Letext0-.Ltext0
	.uaword	.Ldebug_line0
	.uaword	.Ldebug_macro0
	.uleb128 0x7
	.string	"flashing"
	.byte	0x1
	.byte	0x26
	.byte	0x1
	.uaword	.LFB1
	.uaword	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.uaword	0x24b
	.uleb128 0x8
	.string	"parameter"
	.byte	0x1
	.byte	0x26
	.byte	0x1a
	.uaword	0x24b
	.uaword	.LLST0
	.uleb128 0x1
	.string	"timeout"
	.byte	0x28
	.byte	0x10
	.uaword	0x26a
	.uleb128 0x3
	.byte	0x91
	.sleb128 -296
	.uleb128 0x1
	.string	"len"
	.byte	0x29
	.byte	0x19
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -292
	.uleb128 0x1
	.string	"valid"
	.byte	0x29
	.byte	0x1e
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -288
	.uleb128 0x1
	.string	"i"
	.byte	0x29
	.byte	0x25
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -284
	.uleb128 0x2
	.string	"j"
	.byte	0x29
	.byte	0x28
	.uaword	0x27e
	.uleb128 0x1
	.string	"physical"
	.byte	0x29
	.byte	0x2b
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -280
	.uleb128 0x2
	.string	"addr"
	.byte	0x2a
	.byte	0x1a
	.uaword	0x283
	.uleb128 0x2
	.string	"addr_unaligned"
	.byte	0x2b
	.byte	0x19
	.uaword	0x27e
	.uleb128 0x1
	.string	"addr_aligned"
	.byte	0x2b
	.byte	0x29
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -276
	.uleb128 0x9
	.string	"data"
	.byte	0x1
	.byte	0x2c
	.byte	0x1a
	.uaword	0x283
	.uaword	.LLST1
	.uleb128 0x1
	.string	"read"
	.byte	0x2c
	.byte	0x20
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -272
	.uleb128 0x1
	.string	"low32bit"
	.byte	0x2d
	.byte	0x19
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -268
	.uleb128 0x1
	.string	"high32bit"
	.byte	0x2d
	.byte	0x23
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -264
	.uleb128 0x1
	.string	"burst"
	.byte	0x2e
	.byte	0x19
	.uaword	0x27e
	.uleb128 0x3
	.byte	0x91
	.sleb128 -260
	.uleb128 0x1
	.string	"burst_buffer"
	.byte	0x2f
	.byte	0x19
	.uaword	0x298
	.uleb128 0x3
	.byte	0x91
	.sleb128 -256
	.uleb128 0x2
	.string	"dummy"
	.byte	0x30
	.byte	0x19
	.uaword	0x27e
	.byte	0
	.uleb128 0x5
	.uaword	0x250
	.uleb128 0x3
	.byte	0x7
	.string	"long unsigned int"
	.uleb128 0x3
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.uaword	0x264
	.uleb128 0x3
	.byte	0x7
	.string	"unsigned int"
	.uleb128 0x4
	.uaword	0x26f
	.uleb128 0x5
	.uaword	0x27e
	.uleb128 0xa
	.uaword	0x27e
	.uaword	0x298
	.uleb128 0xb
	.uaword	0x250
	.byte	0x3f
	.byte	0
	.uleb128 0x4
	.uaword	0x288
	.uleb128 0xc
	.string	"start"
	.byte	0x1
	.byte	0x1b
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
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x5
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
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 .LVL2-.Ltext0
	.uleb128 .LVL3-.Ltext0
	.uleb128 0x1
	.byte	0x65
	.byte	0x4
	.uleb128 .LVL3-.Ltext0
	.uleb128 .LVL4-.Ltext0
	.uleb128 0x1
	.byte	0x63
	.byte	0x4
	.uleb128 .LVL4-.Ltext0
	.uleb128 .LVL5-.Ltext0
	.uleb128 0x3
	.byte	0x83
	.sleb128 -4
	.byte	0x9f
	.byte	0x4
	.uleb128 .LVL5-.Ltext0
	.uleb128 .LVL6-.Ltext0
	.uleb128 0x1
	.byte	0x63
	.byte	0x4
	.uleb128 .LVL6-.Ltext0
	.uleb128 .LVL7-.Ltext0
	.uleb128 0x1
	.byte	0x65
	.byte	0x4
	.uleb128 .LVL8-.Ltext0
	.uleb128 .LVL9-.Ltext0
	.uleb128 0x1
	.byte	0x65
	.byte	0x4
	.uleb128 .LVL10-.Ltext0
	.uleb128 .LVL11-.Ltext0
	.uleb128 0x1
	.byte	0x65
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
	.string	"__TC161__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_CORE__ 0x161"
	.byte	0x1
	.uleb128 0
	.string	"__TC22XX__ 1"
	.byte	0x1
	.uleb128 0
	.string	"__TRICORE_NAME__ 0x2200"
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
	.string	"FLASH0_FSR 0xf8002010u"
	.byte	0x1
	.uleb128 0x11
	.string	"MEM(address) (*((volatile unsigned int *)(address)))"
	.byte	0x1
	.uleb128 0x14
	.string	"MEM16(address) (*((volatile unsigned short *)(address)))"
	.byte	0x1
	.uleb128 0x17
	.string	"MEM8(address) (*((volatile unsigned char *)(address)))"
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
  .word 0x00100000 #arg
  .word 0x00000000 #ret
  .word 0x00008080 #stat
