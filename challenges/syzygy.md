So far, in all challenges of this type that I’ve done, my approach has been simple: run `objdump -d`, inspect the disassembly, figure out what input the program expects to output the flag, and go from there. But this time was different.

The disassembly I got was... weird. The instructions didn't make sense. Was this really what the program was running? Turns out, **no**. The binary had been tampered with — randomly inserted `xor eax, eax` followed immediately by `je` instructions. Since xoring a register with itself always results in zero, it sets the zero flag (ZF), and the je (jump if equal) instruction that follows will always be taken. These jumps, often just 1–3 bytes forward, would throw off the entire instruction alignment. The result? A completely broken disassembly if you tried to look at it linearly.

At first, I thought about fixing it manually — patching all those places by inserting `nop`s after the jumps to realign everything. But there were a _lot_ of these. Doing that by hand would’ve taken hours, so I looked for tooling help.

That’s when I found **re2**, a reverse engineering tool that really stepped up. I’m still learning everything it can do, but a few things stood out right away: it could analyze functions in much more depth than I was used to, show control flow graphs with arrows, and even — somehow — include helpful comments next to instructions, like ASCII equivalents for hex values. Even better, it automatically compensated for the misalignments by parsing byte-by-byte where needed. This made the analysis process way smoother.

Once the disassembly started making sense, I focused on figuring out the expected input. The `auth` function looked like the right place, and sure enough, it contained a long chain of `cmp` instructions — one character at a time being compared to input values. Using:

```bash
[0x00001060]> pdf @ 0x000011d5 | grep cmp
│       ╎   0x000011e9      3c64           cmp al, 0x64                ; 'd'
│     │     0x00001211      3c39           cmp al, 0x39                ; '9'
│     │││   0x00001224  ~   3b6a39         cmp ebp, dword [edx + 0x39]
│     ││    0x00001238      3c34           cmp al, 0x34                ; elf_phdr
│   ││││    0x0000124e      3bff           cmp edi, edi
│   ││││    0x0000125e      3c39           cmp al, 0x39                ; '9'
│  ││││││   0x00001270  ~   396a39         cmp dword [edx + 0x39], ebp
│  │││││    0x00001284      3c61           cmp al, 0x61                ; 'a'
│  │││││    0x000012ab      3c62           cmp al, 0x62                ; 'b'
│ ││ │││    0x000012d1      3c64           cmp al, 0x64                ; 'd'
│ ││││││    0x000012f8      3c63           cmp al, 0x63                ; 'c'
│ ││││││    0x00001320      3c35           cmp al, 0x35                ; '5'
│ ││││││    0x00001348      3c63           cmp al, 0x63                ; 'c'
│ ││││││    0x0000136f      3c64           cmp al, 0x64                ; 'd'
│ ││││││    0x00001395      3c65           cmp al, 0x65                ; 'e'
│ ││││││    0x000013bb      3c63           cmp al, 0x63                ; 'c'
│ ││││││    0x000013e3      3c32           cmp al, 0x32                ; '2'
│ ││││││    0x0000140b      3c38           cmp al, 0x38                ; '8'
│ ││││││    0x00001433      3c36           cmp al, 0x36                ; '6'
│ ││││││    0x00001459      3c62           cmp al, 0x62                ; 'b'
│ ││││││    0x0000147f      3c30           cmp al, 0x30                ; '0'
│ ││││││    0x000014a7      3c36           cmp al, 0x36                ; '6'
│ ││││││    0x000014ce      3c66           cmp al, 0x66                ; 'f'
│ ││││││    0x000014f6      3c36           cmp al, 0x36                ; '6'
│ ││││││    0x0000151d      3c61           cmp al, 0x61                ; 'a'
│ ││││││    0x00001544      3c36           cmp al, 0x36                ; '6'
│ ││││││    0x0000156a      3c38           cmp al, 0x38                ; '8'
│ ││││││    0x00001592      3c64           cmp al, 0x64                ; 'd'
│ ││││││    0x000015b9      3c38           cmp al, 0x38                ; '8'
│ ││││││    0x000015e1      3c31           cmp al, 0x31                ; '1'
│ ││││││    0x00001609      3c32           cmp al, 0x32                ; '2'
│ ││││││    0x0000162f      3c38           cmp al, 0x38                ; '8'
│ ││││││    0x00001656      3c36           cmp al, 0x36                ; '6'
│ ││││││    0x0000167b      3c63           cmp al, 0x63                ; 'c'
│ ││││││    0x000016a0      3c32           cmp al, 0x32                ; '2'
```

I got a full list of all the characters being compared against. Conveniently, re2 even showed the ASCII equivalents in the comments — I’m guessing it auto-detected them based on the byte values, which saved me a ton of time.

After pulling them all out, I got this string:

```
d949abdc5cdec286bb06f6a68d81286c2
```

And… it worked! That was the correct flag.
