{ pkgs ? import <nixpkgs> { } }:
pkgs.mkShell {
    nativeBuildInputs = with pkgs; [
        musl
        libgcc
    ];

    LD_LIBRARY_PATH = ''
        ${pkgs.musl.outPath}/lib
    '';

    shellHook = ''
        gcc -no-pie -static -o main main.c
    '';
}