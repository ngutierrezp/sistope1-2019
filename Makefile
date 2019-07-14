#########################################################################################
#								Makefile General 										#
#																						#
#				Autor:		Nicolas Gutierrez											#
#				Fecha:		16/06/2019													#
#				Versión:	3.7 ( windows 10+ / Linux ) 								#
#																						#
# Este programa tiene la finalidad de crear un ejecutable a partir de la   				#
# compilacion de diferentes archivos .c													#
# 																						#
# Para utlizarlo correctamente, los archivos deben estar separados de la   				#
# siguiente manera:																		#
#																						#
# src/ <- debe incluir todos los .c del codigo											#
# obj/ <- debe incluir todos los .o resultantes de la compilci�n						#
# incl/ <- deben estar todas las librerias que utilizan los .c							#
#																						#
#########################################################################################



#################################################################################
#				Parte 0: Definicion de variables    							#
#################################################################################

CC = gcc
SRC= src
OBJ = obj
INCL= incl
MKDIR = mkdir
OP_BASH = none
SISTEMA = none
ARQUITECTURA = none
CLEAN_COMMAND = none
EXECUTABLE_NAME = lab
CLEAN_COMMAND_v2 = del
CLEAN_COMMAND_v3 = rm -f
OPTION_COMPILE = -DDEBUG -Wall
EXECUTABLE_NAME_DEBUG := $(EXECUTABLE_NAME)_debug
FILE1:= '\#include <stdio.h>\n\#include "../incl/example.h" \n\nint main(int argc, char const *argv[])\n{\n\tprintExample("This is a example of a complete program in C :D ");\n\treturn 0; \n}' 
FILE2:= '\#include <stdio.h>\n\#include "../incl/example.h"\n\nvoid printExample(char* text){\n\tprintf("%s",text);\n}'
FILE3:= '\#ifndef EXAMPLE_H\n\#define EXAMPLE_H\n/*\n * This is a function for test\n * please remove this file and .c\n */\nvoid printExample(char* text);\n\#endif'

## Solo colores
NO_COLOR=

OK_COLOR=

ERROR_COLOR=

WARN_COLOR=

SUSF_PRINT =

PUR_COLOR =


#################################################################################
#				Parte 1: Detectando Sistema Operativo							#
#################################################################################

# Detect operating system in Makefile.
# Author: He Tao
# Date: 2015-05-30

# Editado a preferencia por Nicolas Gutierrez

### WINDOWS ###
ifeq ($(OS),Windows_NT)
	SISTEMA = -D WINDOWS
	OP_BASH = -e
	EXECUTABLE_NAME := $(EXECUTABLE_NAME).exe
	EXECUTABLE_NAME_DEBUG := $(EXECUTABLE_NAME_DEBUG).exe
	CLEAN_COMMAND := del
	CLEAN_COMMAND_v2 = cmd //C del //Q //F
	CLEAN_COMMAND_v3 = rm -f
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		# x64
		ARQUITECTURA = -D AMD64
	endif
	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		# x32
		ARQUITECTURA = -D IA32
	endif
else
#### PARA EL RESTO DE OS ####

	OP_BASH =

	EXECUTABLE_NAME := $(EXECUTABLE_NAME).out

	EXECUTABLE_NAME_DEBUG := $(EXECUTABLE_NAME_DEBUG).out

	CLEAN_COMMAND := rm -f

	NO_COLOR :=\033[0;0m

	OK_COLOR :=\033[0;32m

	ERROR_COLOR :=\033[0;31m

	WARN_COLOR :=\033[0;36m

	SUSF_PRINT :=\033[0;34m

	PUR_COLOR := \033[0;35m

	UNAME_S := $(shell uname -s)
	### LINUX ###
	ifeq ($(UNAME_S),Linux)
		SISTEMA := -D LINUX
	endif
	### MAC OS ###
	ifeq ($(UNAME_S),Darwin)
		SISTEMA := -D OSX
	endif
		UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARQUITECTURA := -D AMD64
	endif
		ifneq ($(filter %86,$(UNAME_P)),)
	ARQUITECTURA := -D IA32
		endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		SISTEMA := -D ARM
	endif
endif



#################################################################################
#				Parte 2: Sentencias de compilacion  							#
#################################################################################


########################
# Sentencia de Recetas #
########################

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: clean main
	@echo "$(PUR_COLOR)Ejecutable generado!$(NO_COLOR) Nombre: $(OK_COLOR)$(EXECUTABLE_NAME)$(NO_COLOR) "


main: $(OBJECTS)
	@echo "Generando ejecutable ..."
	($(CC) $^ -lm $(DEBUG_MODE) $(SISTEMA)  -o $(EXECUTABLE_NAME) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )
	@echo "\n"

init:
	@echo "Inicializando programa: "
	@echo "Generando carpetas contenedoras ..."
	($(MKDIR) $(SRC) $(OBJ) $(INCL) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )

	@echo "Generando $(WARN_COLOR)Archivo example.c$(NO_COLOR) en carpetas ..."
	((cd $(SRC) && echo $(OP_BASH) $(FILE2) >> example.c) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )

	@echo "Generando $(WARN_COLOR)Archivo example.h$(NO_COLOR) en carpetas ..."
	((cd $(INCL) && echo $(OP_BASH) $(FILE3) >> example.h) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )

	@echo "Generando $(WARN_COLOR)Archivo main.c$(NO_COLOR) en carpetas ..."
	((cd $(SRC) && echo $(OP_BASH) $(FILE1) >> main.c) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; ) 


debug: set-debug
set-debug: DEBUG_MODE := -DDEBUG
set-debug: all-debug

all-debug: clean main-debug
	@echo "$(ERROR_COLOR)[DEBUG MODE] $(PUR_COLOR)Ejecutable generado!$(NO_COLOR) Nombre: $(OK_COLOR)$(EXECUTABLE_NAME_DEBUG)$(NO_COLOR) "


main-debug: $(OBJECTS)
	@echo "Generando ejecutable ..."
	($(CC) $^ -lm $(SISTEMA) -o $(EXECUTABLE_NAME_DEBUG) $(DEBUG_MODE) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )
	@echo "\n"

$(OBJ)/%.o: $(SRC)/%.c
	@echo "Generando archivos object de $@ ...."
	($(CC) $(DEBUG_MODE) $(SISTEMA)  -lm -I$(SRC) -c $< -o $@ && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )

clean:

	@echo "Eliminado $(WARN_COLOR).out$(NO_COLOR) antiguo..."
	@echo >> rm.out

	(($(CLEAN_COMMAND) *.out || $(CLEAN_COMMAND_v2) *.out || $(CLEAN_COMMAND_v3) *.out ) \
		&& echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )


	@echo "Eliminado $(WARN_COLOR).exe$(NO_COLOR) antiguo..."
	@echo >> rm.exe


	(($(CLEAN_COMMAND) *.exe || $(CLEAN_COMMAND_v2) *.exe || $(CLEAN_COMMAND_v3) *.exe ) \
		&& echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )


	@echo "Eliminado $(WARN_COLOR).o$(NO_COLOR) antiguo..."
	(cd $(OBJ) && echo >> rm.o )


	(cd $(OBJ) && ($(CLEAN_COMMAND) *.o || $(CLEAN_COMMAND_v2) *.o || $(CLEAN_COMMAND_v3) *.o ) \
		&& echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; ) \


	@echo "Limpieza de archivos residuales $(OK_COLOR)completa!!$(NO_COLOR)"
	@echo "$(PUR_COLOR)-------------------------------------------------------$(NO_COLOR)"

.SILENT: clean all make main $(OBJ)/%.o $(SOURCES) $(OBJECTS) init $(SRC)/%.c main-debug