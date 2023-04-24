 global hashBkdr_1

 section .data
 ;str: db 'hello!', 0x0
 
section .text

hashBkdr_1:
   push rdx
   push rbx
   push rcx


   xor rax, rax             ; hash
   mov rbx, 131             ; coefficient
   xor rcx, rcx
.loop:
   movzx rcx, byte [rdi]    ; word

   test rcx, rcx
   jz .end

   mul rbx

   lea rax, [rax + rcx]
   inc rdi
   jmp .loop

.end:
   and eax, 0x7fffffff

   pop rcx
   pop rbx
   pop rdx
   ret




