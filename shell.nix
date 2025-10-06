{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  name = "sdl-dev-env";
  
  buildInputs = with pkgs; [
    # SDL2 and related libraries
    SDL2
    SDL2_image
    SDL2_mixer
    SDL2_ttf
    # SDL2_net
    
    # Development tools
    pkg-config
    gcc
    
  ];

  # Environment variables
  shellHook = ''
    echo "SDL Development Environment"
    echo "Available libraries:"
    echo "  - SDL2: ${pkgs.SDL2}"
    echo "  - SDL2_image: ${pkgs.SDL2_image}"
    echo "  - SDL2_mixer: ${pkgs.SDL2_mixer}"
    echo "  - SDL2_ttf: ${pkgs.SDL2_ttf}"
    # echo "  - SDL2_net: ${pkgs.SDL2_net}"
    
    export PKG_CONFIG_PATH="${pkgs.SDL2}/lib/pkgconfig:${pkgs.SDL2_image}/lib/pkgconfig:${pkgs.SDL2_mixer}/lib/pkgconfig:${pkgs.SDL2_ttf}/lib/pkgconfig:${pkgs.SDL2_net}/lib/pkgconfig"
    
    # Helpful aliases
    # alias build-debug="gcc -g -O0 \$(pkg-config --cflags sdl2 SDL2_image SDL2_mixer) -o game main.c \$(pkg-config --libs sdl2 SDL2_image SDL2_mixer)"
    # alias build-release="gcc -O2 \$(pkg-config --cflags sdl2 SDL2_image SDL2_mixer) -o game main.c \$(pkg-config --libs sdl2 SDL2_image SDL2_mixer)"
  '';
}
