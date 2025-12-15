# C++ modules and import std

## How to build

### 1) Create development environment

```bash
nix develop .#for_modules
```

You may need to pass additional options to nix in case you do not have corresponding features set
in nix.conf.

```bash
nix develop .#for_modules --extra-experimental-features nix-command --extra-experimental-features flakes
```

### 2) Build the project

```bash
cmake -Wno-dev -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
