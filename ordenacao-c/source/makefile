HEADER:= estrutura.h manipularArquivo.h ordenacao.h
OBJECT:= estrutura.o main.o manipularArquivo.o ordenacao.o
SOURCE:= estrutura.c main.c manipularArquivo.c ordenacao.c
FLAG:= -c -Wall -g
FLAG_LIB:=
FLAG_CUSTOM:=javax.swing.JTextField[,12,425,688x36,layout=javax.swing.plaf.basic.BasicTextUI$UpdateHandler,alignmentX=0.0,alignmentY=0.0,border=javax.swing.plaf.BorderUIResource$CompoundBorderUIResource@287e5224,flags=296,maximumSize=,minimumSize=,preferredSize=,caretColor=sun.swing.PrintColorUIResource[r=51,g=51,b=51],disabledTextColor=javax.swing.plaf.ColorUIResource[r=184,g=207,b=229],editable=true,margin=javax.swing.plaf.InsetsUIResource[top=0,left=0,bottom=0,right=0],selectedTextColor=sun.swing.PrintColorUIResource[r=51,g=51,b=51],selectionColor=javax.swing.plaf.ColorUIResource[r=184,g=207,b=229],columns=0,columnWidth=0,command=,horizontalAlignment=LEADING]
CC:= gcc
OUT:= teste

all: $(OBJECT)
	$(CC) $(OBJECT) -o $(OUT) $(FLAG_LIB)

clean:
	rm -f $(OBJECT) $(OUT)

run: $(OUT)
	./$(OUT)

estrutura.o: estrutura.c
	$(CC) $(FLAG) estrutura.c

main.o: main.c
	$(CC) $(FLAG) main.c

manipularArquivo.o: manipularArquivo.c
	$(CC) $(FLAG) manipularArquivo.c

ordenacao.o: ordenacao.c
	$(CC) $(FLAG) ordenacao.c
