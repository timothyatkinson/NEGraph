INCDIRS=P-GP2/include Math Datasets Network
LIBDIR=P-GP2/lib
ATOMIC_MUTATIONS =
GP2_OBJECTS = $(ATOMIC_MUTATIONS)
OBJECTS := Math/*.c Datasets/dataset.c Datasets/narma.c *.c Network/*.c
CC=gcc

CFLAGS = 	$(foreach var,$(INCDIRS),-I $(var)) $(foreach var,$(GP2_OBJECTS),-I $(var)) -L $(LIBDIR) -O2 -lgp2 -lgsl -lgslcblas -lm -g

default:	$(OBJECTS)
		$(foreach var,$(GP2_OBJECTS),rm -f -r $(var); mkdir -p $(var);	echo '$(var) compile'; P-GP2/bin/gp2 -l P-GP2 -m $(notdir $(var)) -o $(var) $(var).gp2; )
		$(CC) $(OBJECTS) $(foreach var,$(GP2_OBJECTS), $(var)/*.c) $(CFLAGS) -o $(output)

clean:
		rm -f -r $(output)
		rm -f -r pgp2
