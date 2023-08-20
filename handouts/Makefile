.PHONY: FORCE

all: pdf/homework1.pdf

pdf/homework1.pdf: FORCE
	mkdir -p pdf
	./latexrun homework1.tex
	mv homework1.pdf pdf/homework1.pdf

.PHONY: clean
clean:
	./latexrun --clean-all
