global hashBkdr

section .text

hashBkdr:                   ; avoiding registers that we have to keep
   xor rax, rax             ; hash
   xor rcx, rcx

.loop:
   movzx rcx, byte [rdi]    ; word

   jrcxz .end

   mov r8, rax
   shl rax, 7
   add rax, r8              ; rax * 131
   add rax, r8
   add rax, r8

   lea rax, [rax + rcx]
   inc rdi
   jmp .loop

.end:
   and eax, 0x7fffffff

   ret
