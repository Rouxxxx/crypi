# CRYPI : Project 5: E-voting based on Homomorphic Encryption

## Dependencies

- cmake (Version 3.24 or higher) to build the project
- python3
- C++20
- [SEAL](https://github.com/microsoft/SEAL) for cryptography operations
- [Wt](https://www.webtoolkit.eu/wt) for the web server

## Commands

Build the project:

```bash
cmake .
make
```

Clean the project:

```bash
python3 clean.py
```

Run the app:

```bash
./src/e_voting
```

### Run options

- Testsuite

```bash
./src/e_voting --check
```

- Server run

```bash
./src/e_voting --docroot . --http-address <ip> --http-port <server>
```

- Disable social security number checking

```bash
./src/e_voting [...] --skip-social-verif
```
