log

phase_1:

 8048a7e:    89 04 24         mov   %eax,(%esp) 
 8048a81:    e8 ad 00 00 00      call  8048b33 <phase_1> 
 8048a86:    e8 6f 08 00 00      call  80492fa <phase_defused>



08048b33 <phase_1>: 
 8048b33:    83 ec 14         sub   $0x14,%esp 
 8048b36:    68 c4 a0 04 08      push  $0x804a0c4 
 8048b3b:    ff 74 24 1c       pushl  0x1c(%esp) 
 8048b3f:    e8 66 05 00 00      call  80490aa <strings_not_equal> 
 8048b44:    83 c4 10         add   $0x10,%esp 
 8048b47:    85 c0          test  %eax,%eax 
 8048b49:    74 05          je   8048b50 <phase_1+0x1d> 
 8048b4b:    e8 51 06 00 00      call  80491a1 <explode_bomb> 
 8048b50:    83 c4 0c         add   $0xc,%esp 
 8048b53:    c3            ret



 8048a79:    e8 83 07 00 00      call  8049201 <read_line> 
 8048a7e:    89 04 24         mov   %eax,(%esp)





08048b54 <phase_2>: 
 8048b54:    56            push  %esi 
 8048b55:    53            push  %ebx 
 8048b56:    83 ec 2c         sub   $0x2c,%esp 
 8048b59:    65 a1 14 00 00 00    mov   %gs:0x14,%eax 
 8048b5f:    89 44 24 24       mov   %eax,0x24(%esp) 
 8048b63:    31 c0          xor   %eax,%eax 
 8048b65:    8d 44 24 0c       lea   0xc(%esp),%eax 
 8048b69:    50            push  %eax 
 8048b6a:    ff 74 24 3c       pushl  0x3c(%esp) 
 8048b6e:    e8 53 06 00 00      call  80491c6 <read_six_numbers> 
 8048b73:    83 c4 10         add   $0x10,%esp 
 8048b76:    83 7c 24 04 00      cmpl  $0x0,0x4(%esp)





 8048a8b:    c7 04 24 74 a0 04 08   movl  $0x804a074,(%esp)

该地址的内容为：

0x804a074:    0x73616850    0x20312065    0x75666564    0x2e646573 
0x804a084:    0x776f4820    0x6f626120    0x74207475    0x6e206568 
0x804a094:    0x20747865    0x3f656e6f    0x00000000    0x79206f53 
0x804a0a4:    0x6720756f    0x7420746f    0x20746168    0x2e656e6f 
0x804a0b4:    0x72542020    0x68742079    0x6f207369    0x002e656e