# this program tests all the subprograms in the utils.asm file

.text
main:

#test PromptInt
la $a0, intAPrompt
jal PromptInt
move $s0, $v0

#test LeftCircularShift
move $a0, $s0
jal PrintInt

la $a0, lCircShift
jal PrintString

move $a0, $s0
jal LeftCircularShift

move $a0, $v0
jal PrintInt

jal PrintNewLine

la $a0, shouldBe
jal PrintString

rol $a0, $s0, 1

jal PrintInt

jal PrintNewLine
jal PrintNewLine

#test RightCircularShift
move $a0, $s0
jal PrintInt

la $a0, rCircShift
jal PrintString

move $a0, $s0
jal RightCircularShift

move $a0, $v0
jal PrintInt

jal PrintNewLine

la $a0, shouldBe
jal PrintString

ror $a0, $s0, 1

jal PrintInt

jal PrintNewLine
jal PrintNewLine

#test Mult4
move $a0, $s0
jal PrintInt

la $a0, mul4
jal PrintString

move $a0, $s0
jal Mult4

move $a0, $v0
jal PrintInt

jal PrintNewLine

la $a0, shouldBe
jal PrintString

mul $a0, $s0, 4

jal PrintInt

jal PrintNewLine
jal PrintNewLine

#test Mult10
move $a0, $s0
jal PrintInt

la $a0, mul10
jal PrintString

move $a0, $s0
jal Mult10

move $a0, $v0
jal PrintInt

jal PrintNewLine

la $a0, shouldBe
jal PrintString

mul $a0, $s0, 10

jal PrintInt

jal PrintNewLine
jal PrintNewLine

#test NOT
la $a0, notText
jal PrintString

move $a0, $s0
jal PrintInt

la $a0, isText
jal PrintString

move $a0, $s0
jal NOT

move $a0, $v0
jal PrintInt

jal PrintNewLine

la $a0, shouldBe
jal PrintString

not $a0, $s0

jal PrintInt

jal PrintNewLine
jal PrintNewLine

#get a second integer
la $a0, intBPrompt
jal PromptInt
move $s1, $v0

#test NAND
la $a0, nandText
jal PrintString

move $a0, $s0
jal PrintInt

la $a0, andText
jal PrintString

move $a0, $s1
jal PrintInt

la $a0, isText
jal PrintString

move $a0, $s0
move $a1, $s1
jal NAND

move $a0, $v0
jal PrintInt

jal PrintNewLine
jal PrintNewLine

#test NOR
la $a0, norText
jal PrintString

move $a0, $s0
jal PrintInt

la $a0, andText
jal PrintString

move $a0, $s1
jal PrintInt

la $a0, isText
jal PrintString

move $a0, $s0
move $a1, $s1
jal NOR

move $a0, $v0
jal PrintInt

jal PrintNewLine
jal PrintNewLine

#test Swap
move $a0, $s0
move $a1, $s1
jal Swap

move $s0, $a0
move $s1, $a1

la $a0, swapText
jal PrintString

move $a0, $s0
jal PrintInt

la $a0, swapTextB
jal PrintString

move $a0, $s1
jal PrintInt

jal PrintNewLine
jal PrintNewLine

#get a string
la $a0, stringPrompt
jal PromptString

#test ToUpper
la $a0, 0($v0)
jal ToUpper

la $s0, 0($a0)

la $a0, toUpperText
jal PrintString

la $a0, 0($s0)
jal PrintString

jal PrintNewLine
jal PrintNewLine

#test ToLower
la $a0, 0($s0)
jal ToLower

la $s1, 0($a0)

la $a0, toLowerText
jal PrintString

la $a0, 0($s1)
jal PrintString

jal PrintNewLine
jal PrintNewLine

#test Exit
jal Exit	

.data
#prompts for input
intAPrompt: .asciiz "Please enter an integer.\n"
intBPrompt: .asciiz "Please enter a second integer.\n"
stringPrompt: .asciiz "Please enter a string.\n"

#general strings used in multiple outputs
shouldBe: .asciiz "It should be "
isText: .asciiz " is "
andText: .asciiz " and "

#specific strings
lCircShift: .asciiz " left circular shifted one bit is "
rCircShift: .asciiz " right circular shifted one bit is "
mul4: .asciiz " multiplied by 4 using Mult4 is "
mul10: .asciiz " multiplied by 10 using Mult10 is "
notText: .asciiz "The not of "
nandText: .asciiz "The nand of "
norText: .asciiz "The nor of "
swapText: .asciiz "After calling SWAP, the first register is "
swapTextB: .asciiz " and the second register is "
toUpperText: .asciiz "The uppercase version of this is "
toLowerText: .asciiz "The lowercase version of this is "


.include "utils.asm"