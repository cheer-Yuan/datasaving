# Benchmark datasaving

| Système                        | Kernel           | Processeur              | Stockage                                | Commande                                | G++ flag optimisation                                         | Volume | Temps           | Vitesse      |
| ------------------------------ | ---------------- | ----------------------- | --------------------------------------- | --------------------------------------- | ------------------------------------------------------------- | ------ | --------------- | ------------ |
| Ubuntu 20.04.2 LTS             | 5.4.0-70-generic | i5-1035G7 CPU @ 1.20GHz | NVMe Micron CT1000P1SSD8                | ./datasaving -n 100 -i 0 -f 0 -r 0 -l 5 | -g -O3 -march=icelake-client -funroll-loops -Wall -Wextra     | 290Mb  | 11.99 secondes  | 24.1868 Mb/s |
| Ubuntu 20.04.2 LTS             | 5.4.0-70-generic | i5-1035G7 CPU @ 1.20GHz | NVMe Micron CT1000P1SSD8                | ./datasaving -n 100 -i 0 -f 0 -r 0 -l 5 | none                                                          | 248Mb  | 10.52 secondes  | 25.1063 Mb/s |
| Ubuntu 20.04.2 LTS             | 5.4.0-70-generic | i5-1035G7 CPU @ 1.20GHz | NVMe Micron CT1000P1SSD8                | ./datasaving -n 100 -i 0 -f 0 -r 0 -l 5 | Clang LLVM                                                    | 248Mb  |    |   |
| Raspbian GNU/Linux 10 (buster) | 5.10.17-v7l+     | ARMv7 rev3 (v7l)        | Micro SD Verbatim 32GB class 10 SDHC U1 | ./datasaving -n 100 -i 0 -f 0 -r 0 -l 5 | -mcpu=cortex-a72 -mtune=cortex-a72 -mfpu=neon-fp-armv8 -g -O3 | 242Mb  | 39.989 secondes |  6.0517 Mb/s |
| Raspbian GNU/Linux 10 (buster) | 5.10.17-v7l+     | ARMv7 rev3 (v7l)        | Micro SD Verbatim 32GB class 10 SDHC U1 | ./datasaving -n 100 -i 0 -f 0 -r 0 -l 5 | none                                                          | 242Mb  | 40,504 secondes |  5.9747 Mb/s |
| Raspbian GNU/Linux 10 (buster) | 5.10.17-v7l+     | ARMv7 rev3 (v7l)        | SSD SATA 500gb 860 Evo                  | ./datasaving -n 100 -i 0 -f 0 -r 0 -l 5 | none                                                          | 207Mb  | 33,900 secondes | 6,10 Mb/s
| Raspbian GNU/Linux 10 (buster) | 5.10.17-v7l+     | ARMv7 rev3 (v7l)        | SSD SATA 500gb 860 Evo                  | ./datasaving -n 100 -i 0 -f 0 -r 0 -l 5 | -mcpu=cortex-a72 -mtune=cortex-a72 -mfpu=neon-fp-armv8 -g -O3 | 207Mb  | 32,988 secondes | 6,2 Mb/s
    