
##########################################################################
# Version : 3.2
# Fecha : 06-05-2019
# Javier Pérez - Nicolás Gutiérrez
##########################################################################

#------------------------------------------------------------------------#
#						Makefile Sistope Lab 1							 #
#------------------------------------------------------------------------#


# Nota: Se asume que el codigo será compilado bajo el sistema operativo
# Linux, por lo que no se encuentra necesario hacer una instancia para 
# la deteccion del sistema operativo. Se asume que se utiliza Linux.

#-------------------------------------------------------------------------
###########################
# Sentencia de Constantes #
###########################

# --- opciones de ejecución ---
CLEAN_COMMAND := rm
COMPILE_COMMAND := gcc
EXE_NAME := lab1.out
DEBUG_MODE :=
EXE_NAME_DEBUG := lab1_debug.out
EXE_NAME_CHILD := vis.out

# --- Carpetas ---
INCLUDE_DIR := include# contiene los headers (.h)
SRC := src/# contiene los .c con codigo tradicional
OBJ := obj/# contiene los object (.o) resultantes de compilacion -c

# --- colores ---

NO_COLOR= \033[0m
OK_COLOR= \033[32;01m
ERROR_COLOR= \033[31;01m
WARN_COLOR= \033[33;01m
SUSF_PRINT = \033[1;34m
PUR_COLOR = \033[0;35m



#-------------------------------------------------------------------------
########################
# Sentencia de Recetas #
########################

SOURCES := $(wildcard $(SRC)*.c)
OBJECTS := $(patsubst $(SRC)%.c, $(OBJ)%.o, $(SOURCES))

all: clean main hijo
	
	@echo "$(PUR_COLOR)Ejecutable generado!$(NO_COLOR) Nombre: $(OK_COLOR)$(EXE_NAME)$(NO_COLOR) "


main: $(OBJECTS)
	@echo "Generando ejecutable ..."
	($(CC) $^ -g -lm $(DEBUG_MODE) -o $(EXE_NAME) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )
	@echo "\n"
	

debug: set-debug

set-debug: DEBUG_MODE := -DDEBUG
set-debug: all-debug

all-debug: clean main-debug
	@echo "$(ERROR_COLOR)[DEBUG MODE] $(PUR_COLOR)Ejecutable generado!$(NO_COLOR) Nombre: $(OK_COLOR)$(EXE_NAME_DEBUG)$(NO_COLOR) "


main-debug: $(OBJECTS)
	@echo "Generando ejecutable ..."
	($(CC) $^ -lm $(DEBUG_MODE) -o $(EXE_NAME_DEBUG) && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )
	@echo "\n"

$(OBJ)%.o: $(SRC)%.c
	@echo "Generando archivos object de $@ ...."
	($(CC) $(DEBUG_MODE) -g -lm -I$(SRC) -c $< -o $@ && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )

hijo: main-child
	@echo "$(PUR_COLOR)Ejecutable Hijo generado!$(NO_COLOR) Nombre: $(OK_COLOR)$(EXE_NAME_CHILD)$(NO_COLOR) "
main-child: 
	@echo "Generando ejecutable Hijo ..."
	(make -C hijo/ all && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; )
	@echo "\n"
	
clean: 
	
	@echo "Eliminado $(WARN_COLOR).out$(NO_COLOR) antiguo..."
	@echo >> rm.out


	($(CLEAN_COMMAND) *.out && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; ) 


	@echo "Eliminado $(WARN_COLOR).o$(NO_COLOR) desactualizados..."
	@echo >> $(OBJ)rm.o

	($(CLEAN_COMMAND) $(OBJ)*.o && echo "$(OK_COLOR)[OK]$(NO_COLOR)") \
		||  (echo "$(ERROR_COLOR)[ERROR]$(NO_COLOR)" && exit 1; ) 

	@echo "Limpieza de archivos residuales $(OK_COLOR)completa!!$(NO_COLOR)"
	@echo "$(PUR_COLOR)-------------------------------------------------------$(NO_COLOR)"

.SILENT: clean all make main $(OBJ)%.o $(SOURCES) $(OBJECTS) main-child $(SRC)%.c main-debug
