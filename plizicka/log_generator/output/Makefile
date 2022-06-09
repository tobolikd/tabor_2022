#log_generator Makefile for latex

SHELL = /bin/bash -O extglob -c

RMFLAGS = -f -v

LATEX = latex
DVIPS = dvips
PS2PDF = ps2pdf

OUTPUT = 1>>log_generator.log 2>>log_generator_ERR.log

# COLORS
NO_COLOR=\033[0m
GREEN=\033[0;32m

all:
	@printf "${GREEN}Executing LaTeX${NO_COLOR} \n"
	@for texfile in *.tex; do \
		echo $$texfile; \
		$(LATEX) $$texfile $(OUTPUT) && printf "${GREEN}DONE${NO_COLOR} \n"; \
	done

	@printf "${GREEN}\nReruning LaTeX${NO_COLOR} \n"
	@for texfile in *.tex; do \
		echo $$texfile; \
		$(LATEX) $$texfile $(OUTPUT) && printf "${GREEN}DONE${NO_COLOR} \n"; \
	done

	@printf "${GREEN}\nExecuting dvips${NO_COLOR} \n"
	@for dvifile in *.dvi; do \
		echo $$dvifile; \
		$(DVIPS) $$dvifile $(OUTPUT) && printf "${GREEN}DONE${NO_COLOR} \n"; \
	done

	@printf "${GREEN}\nExecuting ps2pdf${NO_COLOR} \n"
	@for psfile in *.ps; do \
		echo $$psfile; \
		$(PS2PDF) $$psfile $(OUTPUT) && printf "${GREEN}DONE${NO_COLOR} \n"; \
	done

clean: autoremove
	@$(RM) $(RMFLAGS) *.log

autoremove:
	@$(RM) $(RMFLAGS) !(*.tex|*.pdf|Makefile|sources|.gitignore)

purge: clean
	@$(RM) $(RMFLAGS) *.pdf
