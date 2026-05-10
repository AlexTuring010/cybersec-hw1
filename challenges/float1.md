From the source, I saw that to get the flag, I had to give it a number where `number != number` — which only happens with `NaN`.

NaN in 64-bit IEEE format is `0x7ff8000000000000`, and since the system is little-endian, I sent the bytes like this:

```bash
echo -ne '\x00\x00\x00\x00\x00\x00\xf8\x7f' | nc shell.hackintro25.di.uoa.gr 17625
```

Flag dropped.
