#log_generator Makefile for latex

SHELL = /bin/bash -O extglob -c

RMFLAGS = -f -v

LATEX = latex
DVIPS = dvips
PS2PDF = ps2pdf

OUTPUT = 1>log_generator.log 2>log_generator_ERR.log

all:
	@printf "\033[0;32m\n\nExecuting LaTeX\033[0m \n"
	@$(LATEX) *.tex $(OUTPUT)

	@printf "\033[0;32m\n\nReruning LaTeX\033[0m \n"
	@$(LATEX) *.tex $(OUTPUT)

	@printf "\033[0;32m\n\nExecuting dvips\033[0m \n"
	@$(DVIPS) *.dvi $(OUTPUT)

	@printf "\033[0;32m\n\nExecuting ps2pdf\033[0m \n"
	@$(PS2PDF) *.ps $(OUTPUT)

clean:
	@$(RM) $(RMFLAGS) !(*.tex|*.pdf|Makefile|sources|.gitignore|*.log)

purge: clean
	@$(RM) $(RMFLAGS) *.pdf
