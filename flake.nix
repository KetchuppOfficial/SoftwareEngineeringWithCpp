{
  description = "Tasks on MIPT course in software engineering with C++";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs =
    {
      nixpkgs,
      ...
    }:
    let
      system = "x86_64-linux";
      pkgs = import nixpkgs {
        inherit system;
      };
      native_build_inputs = [
        pkgs.cmake
        pkgs.ninja
        pkgs.nixfmt
      ];
    in
    {
      devShells."${system}" = {
        default = (pkgs.mkShell.override { stdenv = pkgs.gcc15Stdenv; }) {
          buildInputs = with pkgs; [
            gtest
            gbenchmark
            boost
            cli11
          ];
          nativeBuildInputs = native_build_inputs;
        };
        llvm =
          let
            llvm_packages = pkgs.llvmPackages_21;
            llvm_stdenv = llvm_packages.stdenv;
          in
          (pkgs.mkShell.override { stdenv = llvm_stdenv; }) {
            buildInputs = [
              (pkgs.gtest.override { stdenv = llvm_stdenv; })
              (pkgs.gbenchmark.override { stdenv = llvm_stdenv; })
              (pkgs.boost.override { stdenv = llvm_stdenv; })
              (pkgs.cli11.override { stdenv = llvm_stdenv; })
            ];
            nativeBuildInputs = native_build_inputs ++ [
              llvm_packages.clang-tools
            ];
            shellHook =
              let
                vscodeDir = ".vscode";
                vscodeConfig = {
                  "clangd.path" = "${pkgs.clang-tools}/bin/clangd";
                };
              in
              ''
                mkdir -p ${vscodeDir}
                jq --indent 4 -n '${builtins.toJSON vscodeConfig}' > ${vscodeDir}/settings.json
              '';
          };
        for_modules =
          let
            llvm_packages = pkgs.llvmPackages_21;
            libcxx = llvm_packages.libcxx;
            llvm_stdenv = llvm_packages.libcxxStdenv;
          in
          (pkgs.mkShell.override { stdenv = llvm_stdenv; }) {
            buildInputs = with pkgs; [
              (gtest.override { stdenv = llvm_stdenv; })
            ];
            nativeBuildInputs = with pkgs; [
              cmake
              ninja
              llvm_packages.clang-tools
            ];
            hardeningDisable = [
              "all" # error: using declaration referring to 'printf' with internal linkage cannot be exported
            ];
            env.NIX_CFLAGS_COMPILE = toString [
              "-stdlib=libc++" # clang++ -print-library-module-manifest-path
              "-Wno-unused-command-line-argument" # silence the annoying warning
              "-B${pkgs.lib.getLib libcxx}/lib" # to find the `libc++.modules.json`, clang driver searches for libc++.a https://github.com/llvm/llvm-project/blob/b555c991e4208cd4829b2dfd0bcb8b2afd0c1292/clang/lib/Driver/Driver.cpp#L6618-L6650
              "-isystem ${pkgs.lib.getDev libcxx}/include/c++/v1" # for `__config` and other headers
            ];
          };
      };
    };
}
