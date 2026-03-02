{
    description = "Tasks on MIPT course in software engineering with C++";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-25.11";
    };

    outputs = {
        nixpkgs,
        ...
    }: let
        system = "x86_64-linux";
        pkgs = import nixpkgs {
            inherit system;
        };
    in {
        devShells."${system}" = {
          default = (pkgs.mkShell.override { stdenv = pkgs.gcc15Stdenv; }) {
              buildInputs = with pkgs; [
                  gtest
                  gbenchmark
              ];
              nativeBuildInputs = with pkgs; [
                  cmake
              ];
          };
          for_modules = let
              llvm_packages = pkgs.llvmPackages_21;
              libcxx = llvm_packages.libcxx;
              llvm_stdenv = llvm_packages.libcxxStdenv;
          in (pkgs.mkShell.override { stdenv = llvm_stdenv; }) {
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
