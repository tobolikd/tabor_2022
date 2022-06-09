# Plizicka

[Popis hry v google docs](https://docs.google.com/document/d/1kOLHCZoacSRWv5MQ4x295WQCXiYDrSBl9Jj2OTDksoE/edit?usp=sharing)

## log_generator
 - log_generator.sh - vygeneruje pdf soubory s logy ke hře
 - potřebné předpoklady
   - LaTex s potřebnými knihovnami (např. TeXLive)
   - dvips a ps2pdf (součástí TeXLive)
   - překladač g++ nebo jiný (nutno změnit v ./log_generator/Makefile )
 - výsledné soubory jsou v ./log_generator/output
 - Uspořádání do složek
```
cd ./log_generator/output
mkdir pdf
mkdir tex
mv *.tex ./tex/
mv *.pdf ./pdf/
```
