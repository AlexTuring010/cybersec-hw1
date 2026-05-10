# cybersec-hw1

Homework #1 for *Introduction to Computer Security* at the University of Athens (Department of Informatics & Telecommunications).

A battery of binary-exploitation challenges hosted on the class HackCenter — stack overflows, format strings, ROP, shellcode, and a JVM reverse-engineering puzzle. **Final score: 1230 points.**

## What's in this repo

- **[`challenges/`](challenges/)** — one Markdown write-up per challenge. All in English. The interesting ones are summarized below.
- **[`programs/`](programs/)** — the target binaries / source files for each challenge, preserved so the write-ups are reproducible.

## Highlights

### Favourite — `argv0`

A canary-protected binary where the trick was to *use* the canary mechanism in our favour. Carefully crafted payload + correct offsets + assembly reading to figure out where the input gets stored — and the canary check ends up printing the flag for us.

### Hardest

- **`choose_your_path`** — I didn't have enough experience with the specific exploit class yet. Read about it, came back, solved it.
- **`fatty2`** — finding shellcode that actually worked took most of the time. When it finally did, it dropped a shell with no privileges.
- **`syzygy`** — first attempt was inserting NOPs by hand in GDB (terrible idea, very slow). Switched to **radare2** and solved it in a fraction of the time.

The full list of challenges with detailed solutions is in [`challenges/`](challenges/).

## License

[MIT](LICENSE) — applies to my own work in this repo (writeups, scripts, exploits). Class-distributed source/binaries (e.g. the contents of [`programs/`](programs/)) retain their original course copyright.

## Sequence

Part of a five-piece cybersecurity coursework cluster:

1. [cybersec-bn0](https://github.com/AlexTuring010/cybersec-bn0) — class warm-up
2. [cybersec-hw0](https://github.com/AlexTuring010/cybersec-hw0) — first homework
3. **cybersec-hw1** *(you are here)* — HackCenter binary exploitation (1230 points)
4. [cybersec-hw2](https://github.com/AlexTuring010/cybersec-hw2) — HackCenter web & crypto (3rd place)
5. [cybersec-hw3-chimera-agents](https://github.com/AlexTuring010/cybersec-hw3-chimera-agents) — team CTF capstone
