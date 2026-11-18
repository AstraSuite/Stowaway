{
  description = "Stowaway - Wayland clipboard & character picker overlay";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
  };

  outputs = {
    self,
    nixpkgs,
    ...
  }: let
    forAllSystems = fn:
      nixpkgs.lib.genAttrs nixpkgs.lib.platforms.linux (
        system: fn nixpkgs.legacyPackages.${system}
      );
  in {
    packages = forAllSystems (pkgs: rec {
      stowaway = pkgs.callPackage ./nix {};
      default = stowaway;
    });

    devShells = forAllSystems (pkgs: {
      default = pkgs.mkShell {
        packages = with pkgs; [
          cmake
          ninja
          pkg-config
          qt6.qtbase
          qt6.qtdeclarative
          qt6.qtsvg
          quickshell
          wtype
          wl-clipboard
          cliphist
        ];
      };
    });

    apps = forAllSystems (pkgs: {
      default = {
        type = "app";
        program = "${self.packages.${pkgs.stdenv.hostPlatform.system}.default}/bin/stowaway";
        meta.description = "Launch Stowaway Wayland clipboard & character picker overlay";
      };
      stowaway = {
        type = "app";
        program = "${self.packages.${pkgs.stdenv.hostPlatform.system}.default}/bin/stowaway";
        meta.description = "Launch Stowaway Wayland clipboard & character picker overlay";
      };
    });

    homeManagerModules.default = { config, lib, pkgs, ... }:
      with lib;
      let
        pkg = self.packages.${pkgs.stdenv.hostPlatform.system}.default;
        cfg = config.programs.stowaway;
      in {
        options.programs.stowaway = {
          enable = mkEnableOption "Stowaway Wayland clipboard & emoji overlay";
          package = mkOption {
            type = types.package;
            default = pkg;
            description = "The stowaway package to use.";
          };
          daemon = {
            enable = mkOption {
              type = types.bool;
              default = true;
              description = "Whether to run Stowaway as a background daemon for instant overlay (<10ms).";
            };
          };
        };

        config = mkIf cfg.enable {
          home.packages = [ cfg.package ];

          systemd.user.services.stowaway = mkIf cfg.daemon.enable {
            Unit = {
              Description = "Stowaway Wayland Clipboard Daemon";
              PartOf = [ "graphical-session.target" ];
              After = [ "graphical-session.target" ];
            };
            Service = {
              ExecStart = "${cfg.package}/bin/stowaway --daemon --foreground";
              Restart = "on-failure";
              RestartSec = "1s";
            };
            Install = {
              WantedBy = [ "graphical-session.target" ];
            };
          };
        };
      };
  };
}
