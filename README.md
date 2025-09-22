# Tasks on MIPT course in software engineering with C++

## How to build

This guide is common for all tasks. If a certain one requires additional steps to build, consult
README.md of that task, if any.

### 0) Requirements

Installed nix package manager.

### 1) Create development environment

```bash
nix develop
```

You may need to pass additional options to nix in case you do not have corresponding features set
in nix.conf.

```bash
nix develop --extra-experimental-features nix-command --extra-experimental-features flakes
```

### 2) Build the project

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
