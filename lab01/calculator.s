	.syntax unified
	.arch armv7-a
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"calculator.c"
	.text
	.align	2
	.global	add
	.thumb
	.thumb_func
	.type	add, %function
add:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	str	r1, [r7, #0]
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #0]
	adds	r3, r2, r3
	mov	r0, r3
	add	r7, r7, #12
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	add, .-add
	.align	2
	.global	subtract
	.thumb
	.thumb_func
	.type	subtract, %function
subtract:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	str	r1, [r7, #0]
	ldr	r2, [r7, #4]
	ldr	r3, [r7, #0]
	subs	r3, r2, r3
	mov	r0, r3
	add	r7, r7, #12
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	subtract, .-subtract
	.align	2
	.global	multiply
	.thumb
	.thumb_func
	.type	multiply, %function
multiply:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	str	r1, [r7, #0]
	ldr	r3, [r7, #4]
	ldr	r2, [r7, #0]
	mul	r3, r2, r3
	mov	r0, r3
	add	r7, r7, #12
	mov	sp, r7
	pop	{r7}
	bx	lr
	.size	multiply, .-multiply
	.global	__aeabi_idiv
	.align	2
	.global	divide
	.thumb
	.thumb_func
	.type	divide, %function
divide:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	str	r1, [r7, #0]
	ldr	r0, [r7, #4]
	ldr	r1, [r7, #0]
	bl	__aeabi_idiv
	mov	r3, r0
	mov	r0, r3
	add	r7, r7, #8
	mov	sp, r7
	pop	{r7, pc}
	.size	divide, .-divide
	.section	.rodata
	.align	2
.LC0:
	.ascii	"\012Enter the first integer: \000"
	.align	2
.LC1:
	.ascii	"%d\000"
	.align	2
.LC2:
	.ascii	"\012Enter the second integer: \000"
	.align	2
.LC3:
	.ascii	"\012Enter the operator (+, -, *, /): \000"
	.align	2
.LC4:
	.ascii	"%c\000"
	.align	2
.LC5:
	.ascii	"Something went wrong.\000"
	.align	2
.LC6:
	.ascii	"The result is %d.\000"
	.text
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #16
	add	r7, sp, #0
.L12:
	movw	r3, #:lower16:.LC0
	movt	r3, #:upper16:.LC0
	mov	r0, r3
	bl	printf
	movw	r3, #:lower16:.LC1
	movt	r3, #:upper16:.LC1
	mov	r2, r7
	mov	r0, r3
	mov	r1, r2
	bl	__isoc99_scanf
	movw	r3, #:lower16:.LC2
	movt	r3, #:upper16:.LC2
	mov	r0, r3
	bl	printf
	movw	r3, #:lower16:.LC1
	movt	r3, #:upper16:.LC1
	add	r2, r7, #4
	mov	r0, r3
	mov	r1, r2
	bl	__isoc99_scanf
	movw	r3, #:lower16:.LC3
	movt	r3, #:upper16:.LC3
	mov	r0, r3
	bl	printf
	movw	r3, #:lower16:.LC4
	movt	r3, #:upper16:.LC4
	add	r2, r7, #15
	mov	r0, r3
	mov	r1, r2
	bl	__isoc99_scanf
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #43
	bne	.L6
	ldr	r2, [r7, #0]
	ldr	r3, [r7, #4]
	mov	r0, r2
	mov	r1, r3
	bl	add
	str	r0, [r7, #8]
	b	.L7
.L6:
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #45
	bne	.L8
	ldr	r2, [r7, #0]
	ldr	r3, [r7, #4]
	mov	r0, r2
	mov	r1, r3
	bl	subtract
	b	.L7
.L8:
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #42
	bne	.L9
	ldr	r2, [r7, #0]
	ldr	r3, [r7, #4]
	mov	r0, r2
	mov	r1, r3
	bl	multiply
	b	.L7
.L9:
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #47
	bne	.L10
	ldr	r2, [r7, #0]
	ldr	r3, [r7, #4]
	mov	r0, r2
	mov	r1, r3
	bl	divide
	b	.L7
.L10:
	ldrb	r3, [r7, #15]	@ zero_extendqisi2
	cmp	r3, #113
	bne	.L11
	mov	r3, #0
	mov	r0, r3
	add	r7, r7, #16
	mov	sp, r7
	pop	{r7, pc}
.L11:
	movw	r0, #:lower16:.LC5
	movt	r0, #:upper16:.LC5
	bl	puts
.L7:
	movw	r3, #:lower16:.LC6
	movt	r3, #:upper16:.LC6
	mov	r0, r3
	ldr	r1, [r7, #8]
	bl	printf
	b	.L12
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",%progbits
