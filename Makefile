# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall -g

# Hedef dosya ve bağımlı nesne dosyaları
TARGET = Game.exe
OBJ = Player.o Room.o Item.o Creature.o Command.o Main.o

# Hedef dosyanın oluşturulması
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# .c dosyalarının .o dosyalarına derlenmesi
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

# Temizleme komutu
clean:
	rm -f $(OBJ) $(TARGET)

# Yeniden derleme (temizleme + yeniden derleme)
rebuild: clean $(TARGET)
