{
    description = "Tasks on MIPT course in software engineering with C++";

    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";
    };

    outputs = {
        nixpkgs,
        ...
    }: let
        system = "x86_64-linux";
    in {
        devShells."${system}".default = let
            pkgs = import nixpkgs {
                inherit system;
            };
        in (pkgs.mkShell.override { stdenv = pkgs.gcc15Stdenv; }) {
            nativeBuildInputs = with pkgs; [
                cmake
            ];
        };
    };
}
