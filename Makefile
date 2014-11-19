CC = g++
#CFLAGS = -O2 -Wall -g -D ALLGEN
CFLAGS = -Wall -g 
INCLUDES = -I $(shell root-config --incdir)
LIBS = $(shell root-config --libs) -lMinuit -lMathCore -lrt

#OBJ = BaseIO.o  Cluster.o  Data_Cluster.o Data_Muon.o  Data_Track.o  Muon.o  Track.o main.o
OBJ =

all: reader writer

reader: $(OBJ) reader.o
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) -o reader $(OBJ) reader.o

writer: $(OBJ) writer.o
	$(CC) $(CFLAGS) $(LIBS) $(INCLUDES) -o writer $(OBJ) writer.o

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm $(OBJ)
