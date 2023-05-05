# CRYPI : Project 5: E-voting based on Homomorphic Encryption

## Dependencies

- cmake (Version 3.24 or higher)
- python3
- C++20
- [SEAL](https://github.com/microsoft/SEAL)

## Commands

To build:

```bash
$ cmake .
$ make
```

To run:

```bash
$ ./src/e_voting --docroot . --http-address 0.0.0.0 --http-port 9090
```

To clean:

```bash
$ python3 clean.py
```
