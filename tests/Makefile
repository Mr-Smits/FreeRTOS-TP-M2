# Nom de l'exécutable
TARGET = test

# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.. # Inclure le répertoire parent pour les headers

# Fichiers sources et headers
SRCS = test.c test_generator.c test_pretraitement.c ../generator.c ../pretraitement.c
HEADERS = test.h test_generator.h test_pretraitement.h ../generator.h ../pretraitement.h

# Règle principale
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Nettoyage
clean:
	rm -f $(TARGET)
