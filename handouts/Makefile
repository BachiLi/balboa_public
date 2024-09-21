.PHONY: FORCE

all: pdf/homework1.pdf pdf/homework2.pdf pdf/homework3.pdf pdf/homework4.pdf pdf/final.pdf

pdf/homework1.pdf: FORCE
	mkdir -p pdf
	./latexrun homework1.tex
	mv homework1.pdf pdf/homework1.pdf

pdf/homework2.pdf: FORCE
	mkdir -p pdf
	./latexrun homework2.tex
	mv homework2.pdf pdf/homework2.pdf

pdf/homework3.pdf: FORCE
	mkdir -p pdf
	./latexrun homework3.tex
	mv homework3.pdf pdf/homework3.pdf

pdf/homework4.pdf: FORCE
	mkdir -p pdf
	./latexrun homework4.tex
	mv homework4.pdf pdf/homework4.pdf

pdf/homework5.pdf: FORCE
	mkdir -p pdf
	./latexrun homework5.tex
	mv homework5.pdf pdf/homework5.pdf

pdf/final.pdf: FORCE
	mkdir -p pdf
	./latexrun final.tex
	mv final.pdf pdf/final.pdf

.PHONY: clean
clean:
	./latexrun --clean-all
