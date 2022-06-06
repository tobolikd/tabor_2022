#log_generator Makefile for latex

SHELL = /bin/bash -O extglob -c

RMFLAGS = -f -v

LATEX = latex
DVIPS = dvips
PS2PDF = ps2pdf

OUTPUT = 1>>log_generator.log 2>>log_generator_ERR.log

all:
	@printf "\033[0;32mExecuting LaTeX\033[0m \n"
	@$(LATEX) *.tex $(OUTPUT) && printf "\033[0;32mDONE\033[0m \n"

	@printf "\033[0;32m\nReruning LaTeX\033[0m \n"
	@$(LATEX) *.tex $(OUTPUT) && printf "\033[0;32mDONE\033[0m \n"

	@printf "\033[0;32m\nExecuting dvips\033[0m \n"
	@$(DVIPS) *.dvi $(OUTPUT) && printf "\033[0;32mDONE\033[0m \n"

	@printf "\033[0;32m\nExecuting ps2pdf\033[0m \n"
	@$(PS2PDF) *.ps $(OUTPUT) && printf "\033[0;32mDONE\033[0m \n"

clean:
	@$(RM) $(RMFLAGS) !(*.tex|*.pdf|Makefile|sources|.gitignore|*.log)

purge: clean
	@$(RM) $(RMFLAGS) *.pdf *.log
